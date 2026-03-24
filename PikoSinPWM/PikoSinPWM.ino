// GPIO setup
//const int signalPin = 11;          // GPIO11
const int ledPin = LED_BUILTIN;    // Built-in LED

const int pwmPin = 11;

const float pwmFreq = 100000.0f;   // 100 kHz PWM carrier
const float sineFreq = 1.0f;       // 1 Hz modulation

const int pwmMax = 255;            // 8-bit resolution


// LED timing (in milliseconds)
const uint32_t led_on_time = 100;  // 100 ms ON
const uint32_t led_period = 1000;  // 1 Hz = 1000 ms

uint32_t lastLedTime = 0;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(pwmPin, OUTPUT);

  analogWriteFreq(pwmFreq);        // set PWM frequency
}

void setup1() {
  pinMode(ledPin, OUTPUT);

}


void loop() {
  // Time in seconds
  float t = micros() / 1000000.0f;

  // Sine modulation (0..1)
  float s = (sinf(2.0f * PI * sineFreq * t) + 1.0f) * 0.5f;

  // Scale to PWM range
  int duty = (int)(s * pwmMax);

  analogWrite(pwmPin, duty);
}

void loop1() {
  // --- LED blink (non-blocking) ---
  uint32_t currentMillis = millis();

  if (!ledState && (currentMillis - lastLedTime >= (led_period - led_on_time))) {
    digitalWrite(ledPin, HIGH);
    ledState = true;
    lastLedTime = currentMillis;
  }

  if (ledState && (currentMillis - lastLedTime >= led_on_time)) {
    digitalWrite(ledPin, LOW);
    ledState = false;
    lastLedTime = currentMillis;
    Serial.println(micros());
  }
  
}