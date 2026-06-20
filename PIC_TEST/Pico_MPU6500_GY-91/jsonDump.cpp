//jsonDump.cpp

#include <Arduino.h>


void jsonDump(const char* sensorName, float value, String& jsonDump) {
	jsonDump += "{";
	jsonDump += String(sensorName) + ":" + String(value, 2);
	jsonDump += "}";
}

void jsonDump(const char* sensorName, int value, String& jsonDump) {
	jsonDump += "{";
	jsonDump += String(sensorName) + ":" + String(value);
	jsonDump += "}";
}

void jsonDump(const char* sensorName, const char* value, String& jsonDump) {
	jsonDump += "{";
	jsonDump += String(sensorName) + ":" + String(value);
	jsonDump += "}";
}

void jsonDump(const char* sensorName, float value1, float value2, float value3, String& jsonStr)
{
	jsonStr += "{";
	jsonStr += String(sensorName);
	jsonStr += ":[" + String(value1, 2) + ", ";
	jsonStr += String(value2, 2) + ", ";
	jsonStr += String(value3, 2);
	jsonStr += "]}";
}

void jsonDump(const char* sensorName, int value1, int value2, int value3, String& jsonStr)
{
	jsonStr += "{";
	jsonStr += String(sensorName);
	jsonStr += ":[" + String(value1) + ", ";
	jsonStr += String(value2) + ", ";
	jsonStr += String(value3);
	jsonStr += "]}";
}
