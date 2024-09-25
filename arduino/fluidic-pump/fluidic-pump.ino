const int dirPin = 3;
const int stepPin = 2;
const int stepsPerRevolution = 1600;
int curStep = 0;
int curDir = HIGH;

void setup()
{
  // Declare pins as Outputs
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
}
void loop()
{
  // Set motor direction clockwise
  digitalWrite(dirPin, curDir);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);


  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(300);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(300);
    }
  curStep += 1;
  Serial.println(curStep);
  if(curStep == 33) {
    if(curDir == HIGH) {
      curDir = LOW;
    }
    else {
      curDir = HIGH;
    }
    curStep = 1;
  }
  //	delay(1000); // Wait a second
}
