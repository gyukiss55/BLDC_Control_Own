// WifiNet.h
#ifndef WIFI_NET_H
#define WIFI_NET_H

#include <Arduino.h>
#include <time.h>

void setupWifi();
bool getDateTime(String& dateStrIn, String& timeStrIn);
bool getTimeInfo(struct tm* timeinfo);

#endif
