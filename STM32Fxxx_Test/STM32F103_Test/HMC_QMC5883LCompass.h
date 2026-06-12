// HMC_QMC5883LCompass.h
void setupQMC5883LCompass();

void setSmoothing();
void startQMC5883LCompassCalibrate();

void loopQMC5883LCompassXYZ();
void loopQMC5883LCompassDirection();
void loopQMC5883LCompassAzimuth();
void loopQMC5883LCompassBearing();
void dumpQMC5883LCompass(String& message);
