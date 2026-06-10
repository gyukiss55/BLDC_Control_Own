// RF_Radio.cpp
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RF_Radio.h"


#define CE_PIN 10
#define CSN_PIN 9
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);
