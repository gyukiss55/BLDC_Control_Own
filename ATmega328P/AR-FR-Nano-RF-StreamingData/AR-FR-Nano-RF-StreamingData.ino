#include "AR-FR-Nano-RF-StreamingData.h"
void setup() {
	Serial.begin(115200);
	delay(1000);
	setupRF_TransmitReceive();
}

void loop() {
	loopRF_TransmitReceive();
}
