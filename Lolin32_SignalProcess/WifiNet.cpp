// WifiNet.cpp
#include "WifiNet.h"

#include <WiFi.h>

#include <time.h>

// ---------- WiFi ----------
const char* ssid = "ASUS_98_2G";
const char* password = "LiDoDa#959285$";
//const char* ssid     = "HUAWEI P30";
//const char* password = "6381bf07b666";

// ---------- Time ----------
void setupTime() {
    configTime(3600, 0, "pool.ntp.org");
}


void setupWifi() {


    WiFi.begin(ssid, password);
    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected!");
    Serial.println(WiFi.localIP());

    setupTime();
}

bool getDateTime(String& dateStrIn, String& timeStrIn) {

	dateStrIn = "";
	timeStrIn = "";
    // ---- Time ----
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {

        char dateStr[20];
        char timeStr[20];

        sprintf(dateStr, "%04d.%02d.%02d",
            timeinfo.tm_year + 1900,
            timeinfo.tm_mon + 1,
            timeinfo.tm_mday);

        sprintf(timeStr, "%02d:%02d:%02d",
            timeinfo.tm_hour,
            timeinfo.tm_min,
            timeinfo.tm_sec);
		dateStrIn = String(dateStr);
		timeStrIn = String(timeStr);
		return true;
    }
	return false;
}

bool getTimeInfo(struct tm* timeinfo) {
    return getLocalTime(timeinfo);
}
