const int LED_PIN = 25;     // Built-in LED for Rpi Pico
const int SWITCH_1_L_PIN = 11;
const int SWITCH_1_R_PIN = 10;

bool ledState = false;
bool lastLedState = false;


unsigned long lastTime = 1;
const unsigned long interval2 = 200;
const unsigned long interval1 = 400;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_1_L_PIN, OUTPUT);
  pinMode(SWITCH_1_R_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(SWITCH_1_L_PIN, LOW);
  digitalWrite(SWITCH_1_R_PIN, LOW);

  // lastLedState = digitalRead(LED_PIN);
  // lastSwitchDir1 = digitalRead(SWITCH_1_R_PIN);
}

void ChangeState (bool switchSt, bool rightNotLeft = false) {
   ledState = !ledState;
    
    digitalWrite(LED_PIN, ledState);
    digitalWrite(SWITCH_1_L_PIN, LOW);
    digitalWrite(SWITCH_1_R_PIN, LOW);
    if(switchSt) {
      if(rightNotLeft)
        digitalWrite(SWITCH_1_R_PIN, ledState);
      else
        digitalWrite(SWITCH_1_L_PIN, ledState);
    }
}

void loop() {
  unsigned long now = millis();
  static bool leftSwitch = false;

  if (!ledState && ((now - lastTime) >= interval1)) {
    leftSwitch = !leftSwitch;
    lastTime = lastTime + interval1;
    ChangeState (true, leftSwitch);
 
  }
  if (ledState && ((now - lastTime) >= interval2)) {
    lastTime = lastTime + interval2;
    ChangeState (false, leftSwitch);
 
  }

  bool currentLed = digitalRead(LED_PIN);
  bool currentLeft = digitalRead(SWITCH_1_L_PIN);
  bool currentRight = digitalRead(SWITCH_1_R_PIN);

  if (currentLed != lastLedState) {
    Serial.print("LED: ");
    Serial.print(currentLed ? "HIGH" : "LOW");
    Serial.print("  left1: ");
    Serial.println(currentLeft ? "HIGH" : "LOW");
    Serial.print("  left1: ");
    Serial.println(currentRight ? "HIGH" : "LOW");

    lastLedState = currentLed;

  }
}