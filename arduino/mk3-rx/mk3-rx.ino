#include <DHT11.h>

DHT11 dht11(13);

const int MOTOR_PIN_1 = 12;
const int MOTOR_PIN_2 = 13;
const int SPEED_PIN = 11;

const int LED_0_PIN = 3;
const int LED_1_PIN = 4;
const int LED_2_PIN = 2;
const int LED_ON_PIN = 5;
const int LED_OFF_PIN = 6;

const int STATE_BUTTON_PIN = 8;
const int OO_BUTTON_PIN = 7;


bool mixingLiquid = true; // whether pushing air or liquid during mixing
unsigned long curTime = 0;
unsigned long lastMix = 0;
unsigned long lastStateSwitch = 0;
unsigned long lastOOSwitch = 0;
bool OO_state = false;
int progIndex = 0;
unsigned long lastFlash = 0;
bool flashState = true;

int STATE_buttonReading = LOW;
int STATE_buttonPrevReading = LOW;
int OO_buttonReading = LOW;
int OO_buttonPrevReading = LOW;



void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(SPEED_PIN, OUTPUT);

  pinMode(LED_0_PIN, OUTPUT);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_OFF_PIN, OUTPUT);
  pinMode(LED_ON_PIN, OUTPUT);

  pinMode(STATE_BUTTON_PIN, INPUT);
  pinMode(OO_BUTTON_PIN, INPUT);

  digitalWrite(LED_0_PIN, HIGH);
  digitalWrite(LED_1_PIN, LOW);
  digitalWrite(LED_2_PIN, LOW);
  digitalWrite(LED_OFF_PIN, HIGH);
  digitalWrite(LED_ON_PIN, LOW);
} 

void dhtRead() {
  int temp = 0;
  int humidity = 0;

  int result = dht11.readTemperatureHumidity(temp, humidity);
  if (result == 0) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print("°C\tHumidity: ");
    Serial.print(humidity);
    Serial.println("%");
  } else {
    // Print error message based on the error code.
    Serial.println(DHT11::getErrorString(result));
  }
}

void fluidIn(int flow) {
  analogWrite(SPEED_PIN, flow);
  digitalWrite(MOTOR_PIN_1, HIGH);
  digitalWrite(MOTOR_PIN_2, LOW);
}

void fluidOut(int flow) {
  analogWrite(SPEED_PIN, flow);
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, HIGH);
}

void mixer(int flow, int time) {
  if (mixingLiquid == true && curTime > (lastMix + time)) {
    fluidIn(flow);
    lastMix = curTime;
    mixingLiquid = false;
  } 
  else if (mixingLiquid == false && curTime > (lastMix + (time * 1.7))) {
    fluidOut(flow);
    lastMix = curTime;
    mixingLiquid = true;
  } 
}

void off() {
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, LOW);
}

void stateLEDOn() {
  switch (progIndex) {
  case 0:
    digitalWrite(LED_0_PIN, HIGH);
    digitalWrite(LED_1_PIN, LOW);
    digitalWrite(LED_2_PIN, LOW);
    Serial.println("LIGHT ONE ON");
    break;
  case 1:
    digitalWrite(LED_0_PIN, LOW);
    digitalWrite(LED_1_PIN, HIGH);
    digitalWrite(LED_2_PIN, LOW);
    Serial.println("LIGHT TWO ON");
    break;
  case 2:
    digitalWrite(LED_0_PIN, LOW);
    digitalWrite(LED_1_PIN, LOW);
    digitalWrite(LED_2_PIN, HIGH);
    Serial.println("LIGHT THREE ON");
    break;
  }
}

void stateLEDControl() {
//  if (OO_state) {
//    stateLEDOn(stateLEDIndex);
//  }
//  else {
//    if (curTime > lastFlash + 300) {
//      flashState = !flashState;
//      lastFlash = curTime; 
//    }
//    if (flashState) {
//      stateLEDOn(stateLEDIndex); 
//    }
//    else {
//      digitalWrite(LED_0_PIN, LOW);
//      digitalWrite(LED_1_PIN, LOW);
//      digitalWrite(LED_2_PIN, LOW);
//    }
//  }

  stateLEDOn();
}

void readStateButton() {
  STATE_buttonReading = digitalRead(STATE_BUTTON_PIN);
  if (STATE_buttonReading == HIGH &&
      STATE_buttonPrevReading == LOW &&
      curTime > lastStateSwitch + 50 &&
      OO_state == false)  {
    STATE_buttonPrevReading = HIGH;
    lastStateSwitch = curTime;
  }
  if (STATE_buttonReading == LOW &&
      STATE_buttonPrevReading == HIGH &&
      curTime > lastStateSwitch + 50 &&
      OO_state == false) {
    STATE_buttonPrevReading = LOW;
    lastStateSwitch = curTime;
    // progIndex bounds from 0 to 2
    // This moves progIndex to its next value
    // 0 -> 1,  1 -> 2,  2 -> 0
    progIndex = (progIndex + 1) % 3;
    stateLEDControl();
  }
}

void runProg(int flow, int time) {
  if (OO_state == true) {
    switch (progIndex) {
    case 0:
      mixer(flow, time);
      Serial.println("Running mixer");
      break;
    case 1:
      fluidIn(flow);
      Serial.println("Running fluidIN");
      break;
    case 2:
      fluidOut(flow);
      Serial.println("Running fluidOUT");
      break;
    }
  }
  else {
    off();
  }
}

void readOOButton() {
  OO_buttonReading = digitalRead(OO_BUTTON_PIN);
  if (OO_buttonReading == HIGH && OO_buttonPrevReading == LOW && curTime > lastOOSwitch + 50)  {
    OO_buttonPrevReading = HIGH;
    lastOOSwitch = curTime;
  }
  if (OO_buttonReading == LOW && OO_buttonPrevReading == HIGH && curTime > lastOOSwitch + 50) {
    OO_buttonPrevReading = LOW;
    lastOOSwitch = curTime;
    if (OO_state == false) {
      OO_state = true;
      mixingLiquid = false;
      digitalWrite(LED_OFF_PIN, LOW);
      digitalWrite(LED_ON_PIN, HIGH);
    }
    else {
      OO_state = false;
      digitalWrite(LED_OFF_PIN, HIGH);
      digitalWrite(LED_ON_PIN, LOW);
    }
  }
}


void loop() {
  curTime = millis();
  readOOButton();
  //  dhtRead();
  readStateButton();
  runProg(220, 2500);
//mixer(220, 2500);
//    Serial.print(curTime);
//    Serial.print("\t");
//    Serial.println(lastMix);
}
