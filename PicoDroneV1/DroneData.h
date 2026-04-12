#include <Arduino.h>

typedef struct {
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    float temperature1;
    float temperature2;
    float pressure;
    float altitude;
    bool ok;
} GAM_Data;

typedef struct {
	uint32_t timestamp;
    float lat;
    float lon;
    float alt;
    int sats;
    bool fix;
    String time;
    String date;
    String logDataN[10];
    int logDataI;
} GPS_Data;

extern GPS_Data gps;

extern GAM_Data gam;
