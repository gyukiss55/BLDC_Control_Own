const int LED_PIN = 25;     // Built-in LED for Rpi Pico
const int SWITCH_1_L_PIN = 11;
const int SWITCH_1_R_PIN = 10;
const int speed = 128;
bool ledState = false;
bool lastLedState = false;


unsigned long lastTime = 1;
const unsigned long interval2 = 500;
const unsigned long interval1 = 1500;

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
   
    
    digitalWrite(LED_PIN, switchSt);
    analogWrite(SWITCH_1_L_PIN, 0);
    analogWrite(SWITCH_1_R_PIN, 0);
    Serial.print (switchSt);
    if(switchSt) {
      Serial.print ("/");
      Serial.print (rightNotLeft);
      if(rightNotLeft)
        analogWrite(SWITCH_1_R_PIN, speed);
        
      else
        analogWrite(SWITCH_1_L_PIN, speed);
    }
    Serial.println ();
}

void loop() {
  unsigned long now = millis();
  static bool leftSwitch = false;

  if (ledState && ((now - lastTime) >= interval1)) {
    leftSwitch = !leftSwitch;
    ledState = !ledState;
    lastTime = lastTime + interval1;
    ChangeState (true, leftSwitch);
 
  }
  if (!ledState && ((now - lastTime) >= interval2)) {
    lastTime = lastTime + interval2;
    ledState = !ledState;
    ChangeState (false, leftSwitch);
 
  }

  bool currentLed = ledState;
  bool currentLeft = leftSwitch;
  bool currentRight = !leftSwitch;

  if (ledState != lastLedState) {
    Serial.print("LED: ");
    Serial.print(currentLed ? "HIGH" : "LOW");
    Serial.print("  left1: ");
    Serial.print(currentLeft ? "HIGH" : "LOW");
    Serial.print("  right1: ");
    Serial.println(currentRight ? "HIGH" : "LOW");

    lastLedState = ledState;

  }
}