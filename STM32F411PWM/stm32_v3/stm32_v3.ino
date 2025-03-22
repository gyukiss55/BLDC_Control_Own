// Define pin numbers for PB6, PB7, PB8, and PB9
const int pinPWM1 = PA0;  // Corresponds to PB6
const int pinPWM2 = PA1;  // Corresponds to PB7
const int pinPWM3 = PB7;  // Corresponds to PB8
const int pinPWM4 = PB9;  // Corresponds to PB9

const int pinPWM5 = PB0;  // Corresponds to PB0
const int pinPWM6 = PB1;  // Corresponds to PB1

const int pinLed = PC13;  // Corresponds to PC13

const int pwm_pin1 = PB6;
const int pwm_pin2 = PB8;

const int pwmFrequency = 2000;   // 1 kHz
const int resolution = 256;      // 8-bit resolution
int dutyCycle = 10;              // Starting duty cycle percentage
bool increasing = true;          // Flag to track if duty is increasing or decreasing

void setup() {

    // Set pins as OUTPUT
    pinMode(pinPWM1, OUTPUT);
    pinMode(pinPWM2, OUTPUT);
    pinMode(pinPWM3, OUTPUT);
    pinMode(pinPWM4, OUTPUT);
    pinMode(pinPWM5, OUTPUT);
    pinMode(pinPWM6, OUTPUT);

    pinMode(pwm_pin1, OUTPUT);
    pinMode(pwm_pin2, OUTPUT);

    // Configure the PWM frequency
    analogWriteFrequency(pwmFrequency);

    // Set PWM resolution
    analogWriteResolution(8);  // 256 steps for 8-bit resolution

    pinMode(pinLed, OUTPUT);
}

void loop() {
    // Turn on all pins
    const uint32_t  delayMicros = 100;

    int pwmValue = map(dutyCycle, 0, 100, 0, resolution - 1);
    pwmValue = map(10, 0, 100, 0, resolution - 1);
    analogWrite(pwm_pin1, pwmValue);
    analogWrite(pwm_pin2, 255 - pwmValue);

    if (increasing) {
        dutyCycle++;
        if (dutyCycle >= 90) increasing = false; // Start decreasing when it reaches 90%
    }
    else {
        dutyCycle--;
        if (dutyCycle <= 10) increasing = true;  // Start increasing when it reaches 10%
    }

    digitalWrite(pinPWM1, HIGH);
    digitalWrite(pinPWM2, HIGH);
    digitalWrite(pinPWM3, HIGH);
    digitalWrite(pinPWM4, HIGH);
    digitalWrite(pinPWM5, HIGH);
    digitalWrite(pinPWM6, HIGH);
   
    delayMicroseconds(delayMicros);

    digitalWrite(pinLed, LOW);

    // Turn off all pins
    digitalWrite(pinPWM1, LOW);
    delayMicroseconds(delayMicros);

    digitalWrite(pinLed, HIGH);

    digitalWrite(pinPWM2, LOW);
    delayMicroseconds(delayMicros);

    digitalWrite(pinPWM3, LOW);
    delayMicroseconds(delayMicros);

    digitalWrite(pinPWM4, LOW);
    delayMicroseconds(delayMicros);

    digitalWrite(pinPWM5, LOW);
    delayMicroseconds(delayMicros);

    digitalWrite(pinPWM6, LOW);
    delayMicroseconds(delayMicros * 5);
}