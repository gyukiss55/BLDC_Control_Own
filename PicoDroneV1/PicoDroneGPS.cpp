// PicoDroneGPS.c

#include <Arduino.h>
#include "PicoDroneGPS.h"
#include "DroneData.h"

struct GPRMC_Data {
    char time[11];      // hhmmss.sss
    bool valid;         // A = valid, V = invalid
    double latitude;
    double longitude;
    double speed_knots;
    char date[7];       // ddmmyy
};

struct GPGGA_Data {
    char time[11];
    double latitude;
    double longitude;
    int fix_quality;
    int satellites;
    float hdop;
    float altitude;
};

GPRMC_Data rmc;
GPGGA_Data gga;

unsigned long lastUpdate = 0;

double nmeaToDecimal(const char* coord, const char* dir) {
    if (coord == NULL || coord[0] == '\0') return 0;

    double val = atof(coord);
    int degrees = (int)(val / 100);
    double minutes = val - (degrees * 100);
    double decimal = degrees + (minutes / 60.0);

    if (dir[0] == 'S' || dir[0] == 'W') {
        decimal = -decimal;
    }
    return decimal;
}

bool parseGPRMC(const String& line, GPRMC_Data* data) {
    char sentence[100];
    char* token;
    int field = 0;
    sentence[0] = '\0';
    if (line.length() >= sizeof(sentence))
        return false;
    strcpy(sentence, line.c_str());

    token = strtok(sentence, ",");

    while (token != NULL) {
        switch (field) {
        case 1: strncpy(data->time, token, sizeof(data->time)); break;
        case 2: data->valid = (token[0] == 'A'); break;
        case 3: {
            char lat[15]; strcpy(lat, token);
            token = strtok(NULL, ","); field++;
            data->latitude = nmeaToDecimal(lat, token);
            break;
        }
        case 5: {
            char lon[15]; strcpy(lon, token);
            token = strtok(NULL, ","); field++;
            data->longitude = nmeaToDecimal(lon, token);
            break;
        }
        case 7: data->speed_knots = atof(token); break;
        case 8: strncpy(data->date, token, sizeof(data->date)); break;
        }
        token = strtok(NULL, ",");
        field++;
    }
    return true;
}

bool parseGPGGA(const String& line, GPGGA_Data* data) {
	char sentence[100];
    char* token;
    int field = 0;
	sentence[0] = '\0';
    if(line.length() >= sizeof(sentence))
        return false;
    strcpy(sentence, line.c_str());
    token = strtok(sentence, ",");

    while (token != NULL) {
        switch (field) {
        case 1: strncpy(data->time, token, sizeof(data->time)); break;

        case 2: {
            char lat[15]; strcpy(lat, token);
            token = strtok(NULL, ","); field++;
            data->latitude = nmeaToDecimal(lat, token);
            break;
        }

        case 4: {
            char lon[15]; strcpy(lon, token);
            token = strtok(NULL, ","); field++;
            data->longitude = nmeaToDecimal(lon, token);
            break;
        }

        case 6: data->fix_quality = atoi(token); break;
        case 7: data->satellites = atoi(token); break;
        case 8: data->hdop = atof(token); break;
        case 9: data->altitude = atof(token); break;
        }

        token = strtok(NULL, ",");
        field++;
    }
    return true;
}

void PicoDroneGPS_init()
{
    Serial1.setTX(0);
    Serial1.setRX(1);
    Serial1.begin(9600);
}

void PicoDroneGPS_update()
{
    if (millis() - lastUpdate < 2000) return;
	String logLast = "";
    while (Serial1.available())
    {
        String line = Serial1.readStringUntil('\n');
	    Serial.println("GPS data: " + line);
		logLast += line;
        if (line.startsWith("$GPGGA"))
        {
			gps.timestamp = millis();
            gps.fix = true;
        }
        if (line.startsWith("$GPRMC")) {
            parseGPRMC(line, &rmc);

            Serial.println("RMC:");
            Serial.println(rmc.latitude, 6);
            gps.lat = rmc.latitude;
            Serial.println(rmc.longitude, 6);
            gps.lon = rmc.longitude;
			gps.time = String(rmc.time);
			gps.date = String(rmc.date);
        }

        if (line.startsWith("$GPGGA")) {
            parseGPGGA(line, &gga);

            Serial.println("GGA:");
            Serial.println(gga.altitude);
			gps.alt = gga.altitude;
            Serial.println(gga.satellites);
			gps.sats = gga.satellites;
        }
        if (gps.fix && (line.startsWith("$GPGGA") || line.startsWith("$GPRMC"))) {
		    gps.logDataI = gps.logDataI % 10;
            gps.logDataN[gps.logDataI++] = line;
	    }
        Serial.println("GPS log data: " + line);
    }
}

float getGPSLatitude()
{
    return gps.lat;
}
float getGPSLongitude()
{
    return gps.lon;
}
int getGPSSatellites()
{
    return gps.sats;
}
