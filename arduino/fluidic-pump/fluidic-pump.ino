const int dirPin = 3;
const int stepPin = 2;
const int stepsPerRevolution = 1600;
int curStep = 0;
int curDir = HIGH;
int curSpeed = 1000;
int numRotations = 0;

void setup()
{
  // Declare pins as Outputs
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  

}
void loop()
{
  // Set motor direction clockwise
  digitalWrite(dirPin, curDir);

  if (curDir == HIGH) {
    curSpeed = 1000;
  }
  else {
    curSpeed = 5000;
  }
  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(curSpeed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(curSpeed);
    }
  curStep += 1;
  Serial.println(curStep);
  if(curStep == 7) {
    curDir = !curDir;
    curStep = 0;
  }
  //	delay(1000); // Wait a second
}
