// MPU6500_WESensor.h

#pragma once

#include <Arduino.h>
#include <MPU6500_WE.h>

void setupMPU6500_WESensor();
void loopMPU6500_WESensor();
bool readMPU6500_WESensor(xyzFloat& gValue, xyzFloat& gyr, float& temp, float& resultantG);
void jsonDumpMPU6500_WESensor(String& jsonDump);