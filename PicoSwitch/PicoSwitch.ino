const int LED_PIN = 25;     // Built-in LED for Rpi Pico
const int SWITCH_1_L_PIN = 11;
const int SWITCH_1_R_PIN = 10;

bool ledState = false;
bool lastLedState = false;
bool lastSwitchState1 = false;
bool lastSwitchDir1 = false;

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

void ChangeState (bool switch, bool rightNotLeft = false) {
   ledState = !ledState;
    
    digitalWrite(LED_PIN, ledState);
    if(switch) {
      if(switch) {
      }
      digitalWrite(SWITCH_1_L_PIN, ledState);
    } else {
      digitalWrite(SWITCH_1_L_PIN, LOW);
      digitalWrite(SWITCH_1_R_PIN, LOW);
    }
    
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