// ESCControl.h

void setupESCControl();
void loopESCControl();

void SetNextPeriodPulse(int period, int pulse);
void ClearAllESCPin();
void SetEscPinAB();
void SetEscPinAC();
void SetEscPinBC();
void SetEscPinBA();
void SetEscPinCA();
void SetEscPinCB();

int GetNextPeriod();
int GetNextPulse();
