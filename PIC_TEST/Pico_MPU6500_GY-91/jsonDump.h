// jsonDump.h
#include <Arduino.h>

void jsonDump(const char* sensorName, float value, String& jsonStr);
void jsonDump(const char* sensorName, int value, String& jsonStr);
void jsonDump(const char* sensorName, const char* value, String& jsonStr);
void jsonDump(const char* sensorName, float value1, float value2, float value3, String& jsonStr);
void jsonDump(const char* sensorName, int value1, int value2, int value3, String& jsonStr);
