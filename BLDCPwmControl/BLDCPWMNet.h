// BLDCPWMNet.h
#ifndef BLDC_PWM_NET_H
#define BLDC_PWM_NET_H
#include <Arduino.h>

class BLDCPWMControl;

class BLDCPWMNet {
public:
    BLDCPWMNet(BLDCPWMControl* ctrl);
    void begin();
    void handleClient();

private:
    BLDCPWMNet();

    BLDCPWMControl* control;

    void setupWebServer();
    void handleRoot();
    void handleSet();
};

#endif
