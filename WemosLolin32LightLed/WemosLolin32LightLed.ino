const int pwmPin = 32;
const int pwmPin2 = 12;
// max 10 bit 50 kHz - 20 usec
//const int pwmFreq = 50000;
//const int pwmResolution = 10;

// max 8 bit 200 kHz - 5 usec
const int pwmFreq = 200000;
const int pwmResolution = 8;

void setup()
{
  ledcAttach(pwmPin, pwmFreq, pwmResolution);
  ledcAttach(pwmPin2, pwmFreq, pwmResolution);
}

void loop()
{
  ledcWrite(pwmPin, 3);   // 25%
  ledcWrite(pwmPin2, 3);   // 25%
  delay(1000);

  ledcWrite(pwmPin, 64);   // 25%
  ledcWrite(pwmPin2, 64);   // 25%
  delay(1000);

  ledcWrite(pwmPin, 128);  // 50%
  ledcWrite(pwmPin2, 128);   // 25%
  delay(1000);

  ledcWrite(pwmPin, 253);  // 100%
  ledcWrite(pwmPin2, 253);   // 25%
  delay(1000);
}