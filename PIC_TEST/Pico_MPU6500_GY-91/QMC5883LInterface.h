// QMC5883LInterface.h

#include <Arduino.h>

void PicoQMC5883L_Init();
void PicoQMC5883L_DumpDirection();
void PicoQMC5883L_Calibration();
void PicoQMC5883L_Smoothing(int step = 10, bool advanced = false);
void jsonDumpQMC5883L(String& jsonDump);
