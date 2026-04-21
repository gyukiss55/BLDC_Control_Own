// QMC5883LInterface.h

void PicoQMC5883L_Init();
void PicoQMC5883L_DumpDirection();
void PicoQMC5883L_Calibration();
void PicoQMC5883L_Smoothing(int step = 10, bool advanced = false);

