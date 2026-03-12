const int LED_PIN = 22;     // Built-in LED for Lolin32 Lite
const int GPIO_PIN = 27;

bool ledState = false;
bool lastLedState = false;
bool lastGpioState = false;

unsigned long lastTime = 1;
const unsigned long interval1 = 200;
const unsigned long interval2 = 2800;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(GPIO_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(GPIO_PIN, HIGH);

  lastLedState = digitalRead(LED_PIN);
  lastGpioState = digitalRead(GPIO_PIN);
}

void ChangeState () {
   ledState = !ledState;

    digitalWrite(LED_PIN, ledState);
    digitalWrite(GPIO_PIN, ledState ? LOW : HIGH);
}

void loop() {
  unsigned long now = millis();

  if (!ledState && ((now - lastTime) >= interval1)) {
    lastTime = lastTime + interval1;
    ChangeState ();
 
  }
  if (ledState && ((now - lastTime) >= interval2)) {
    lastTime = lastTime + interval2;
    ChangeState ();
 
  }

  bool currentLed = digitalRead(LED_PIN);
  bool currentGpio = digitalRead(GPIO_PIN);

  if (currentLed != lastLedState || currentGpio != lastGpioState) {
    Serial.print("LED: ");
    Serial.print(currentLed ? "HIGH" : "LOW");
    Serial.print("  GPIO12: ");
    Serial.println(currentGpio ? "HIGH" : "LOW");

    lastLedState = currentLed;
    lastGpioState = currentGpio;
  }
}