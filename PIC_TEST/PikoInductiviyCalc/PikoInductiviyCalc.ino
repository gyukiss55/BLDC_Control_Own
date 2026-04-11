#include <math.h>

//GPIO15 (PWM out) ────┬──── Lx ────┬── GND
//                     │            │
//                     │            C
//                     │            │
//GPIO26 (ADC0) ───────┴────────────┘

// Pins
const int pwmPin = 15;
const int adcPin = 26;

// Known capacitor (Farads!)
const float C = 100e-9; // 100 nF

// Sweep settings
const int fStart = 1000;     // 1 kHz
const int fEnd   = 200000;   // 200 kHz
const int steps  = 200;

float bestFreq = 0;
int bestAmplitude = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pwmPin, OUTPUT);
  analogReadResolution(12);

  delay(2000);
  Serial.println("Inductance meter start...");
}

int measureAmplitude() {
  int maxVal = 0;
  int minVal = 4095;

  // sample waveform
  for (int i = 0; i < 200; i++) {
    int v = analogRead(adcPin);
    if (v > maxVal) maxVal = v;
    if (v < minVal) minVal = v;
  }

  return maxVal - minVal; // peak-to-peak
}

void loop() {
  bestAmplitude = 0;
  bestFreq = 0;

  Serial.println("Sweeping...");

  for (int i = 0; i < steps; i++) {
    float f = fStart + (fEnd - fStart) * (float)i / steps;

    analogWriteFreq((int)f);
    analogWrite(pwmPin, 128); // 50% duty

    delay(10); // settle

    int amp = measureAmplitude();

    if (amp > bestAmplitude) {
      bestAmplitude = amp;
      bestFreq = f;
    }
  }

  Serial.print("Resonant frequency: ");
  Serial.print(bestFreq);
  Serial.println(" Hz");

  // Calculate inductance
  float L = 1.0f / (pow(2.0f * PI * bestFreq, 2) * C);

  Serial.print("Inductance: ");
  Serial.print(L * 1000.0f, 3); // mH
  Serial.println(" mH");

  Serial.println("----------------------");

  delay(3000);
}
