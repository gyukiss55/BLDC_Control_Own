#include <math.h>

//GPIO15 (PWM out) ────┬──── Lx ────┬── GND
//                     │            │
//                     │            C
//                     │            │
//GPIO26 (ADC0) ───────┴────────────┘

//find resonance frequency f0
//automatically detect f1 and f2 (-3 dB points)
//bandwidth f2-f1
//compute L, Q, ESR
//Q=f0/(f2-f1)
//ESR - R=omegaL/R
//print a full report

// Pins
const int pwmPin = 15;
const int adcPin = 26;

// Known capacitor (adjust this!)
const float C = 100e-9; // 100 nF

// Sweep settings
const int fStart = 1000;
const int fEnd   = 200000;
const int steps  = 300;

// Storage
float freq[steps];
int amp[steps];

void setup() {
  Serial.begin(115200);
  pinMode(pwmPin, OUTPUT);
  analogReadResolution(12);

  delay(2000);
  Serial.println("Advanced LCR measurement...");
}

int measureAmplitude() {
  int maxVal = 0;
  int minVal = 4095;

  for (int i = 0; i < 200; i++) {
    int v = analogRead(adcPin);
    if (v > maxVal) maxVal = v;
    if (v < minVal) minVal = v;
  }

  return maxVal - minVal;
}

void loop() {

  Serial.println("\nSweeping...");

  // --- Sweep ---
  for (int i = 0; i < steps; i++) {
    float f = fStart + (fEnd - fStart) * (float)i / steps;

    freq[i] = f;

    analogWriteFreq((int)f);
    analogWrite(pwmPin, 128);

    delay(8);

    amp[i] = measureAmplitude();
  }

  // --- Find peak ---
  int peakIndex = 0;
  int peakAmp = 0;

  for (int i = 0; i < steps; i++) {
    if (amp[i] > peakAmp) {
      peakAmp = amp[i];
      peakIndex = i;
    }
  }

  float f0 = freq[peakIndex];

  // --- Find -3 dB level ---
  float threshold = peakAmp * 0.707;

  float f1 = f0, f2 = f0;

  // Left side (f1)
  for (int i = peakIndex; i > 0; i--) {
    if (amp[i] < threshold) {
      f1 = freq[i];
      break;
    }
  }

  // Right side (f2)
  for (int i = peakIndex; i < steps - 1; i++) {
    if (amp[i] < threshold) {
      f2 = freq[i];
      break;
    }
  }

  float bandwidth = f2 - f1;

  // --- Compute values ---
  float L = 1.0f / (pow(2.0f * PI * f0, 2) * C);
  float Q = f0 / bandwidth;
  float ESR = (2.0f * PI * f0 * L) / Q;

  // --- Print results ---
  Serial.println("\n===== RESULT =====");

  Serial.print("f0 (resonance): ");
  Serial.print(f0, 2);
  Serial.println(" Hz");

  Serial.print("f1: ");
  Serial.print(f1, 2);
  Serial.println(" Hz");

  Serial.print("f2: ");
  Serial.print(f2, 2);
  Serial.println(" Hz");

  Serial.print("Bandwidth: ");
  Serial.print(bandwidth, 2);
  Serial.println(" Hz");

  Serial.print("Inductance: ");
  Serial.print(L * 1000.0f, 4);
  Serial.println(" mH");

  Serial.print("Q factor: ");
  Serial.println(Q, 2);

  Serial.print("ESR: ");
  Serial.print(ESR, 3);
  Serial.println(" Ohm");

  Serial.println("==================");

  delay(5000);
}