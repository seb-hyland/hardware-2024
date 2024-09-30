const int dirPin = 3;
const int stepPin = 2;
const int stepsPerRevolution = 1600;
int initSpeed = 300;
int curDir = HIGH;
int mixingSpeed = 500;
int numRotations = 0;
float mixingDistance = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);

  delay(2000);
  Serial.println("                                    @");                         
  Serial.println("                                   @@   @");                     
  Serial.println("                                  @@   @");                      
  Serial.println("                                 @@  @@  @@");                   
  Serial.println("                                @@ @@@ @@@");                    
  Serial.println("                               @ @@@ @@@");                      
  Serial.println("                            @@@@ @@@@@  @@@");                   
  Serial.println("                 @@@@@@     @@@    @@@@@");                      
  Serial.println("                @@@    @@   @@@ @@@@@   @@");                    
  Serial.println("                   @    @@  @@ @@@@@@@@");                       
  Serial.println("                   @@     @@  @@@@@@@@@@");                      
  Serial.println("                   @@ @@@@ @@ @@@");                             
  Serial.println("                    @@@   @@ @@   @@");                          
  Serial.println("                    @@ @@@ @@");                                 
  Serial.println("                  @@@@@@@ @");                                   
  Serial.println("                  @@@@@@@@@@");                                  
  Serial.println("                  @@      @@");                                  
  Serial.println("                   @@    @@");                                   
  Serial.println("                     @@@");                                      
  Serial.println("                    @@  @@");                                   
  Serial.println("                   @@    @@");
  Serial.println("\nWelcome to the UBC-iGEM 2024 Microfluidic Pump System.");
  Serial.println("At any point during operation, input \"s\" to stop the pump system.\n");
  Serial.println("----------------------------------------------------------------------\n");
  Serial.println("Ready to align motor and clear syringes. Press 0 when motor path is clear.");
  while (Serial.read() != '0') {}
  Serial.println("Press 0 to stop when the pump contacts the end of its chamber.");
  digitalWrite(dirPin, HIGH);
  while (Serial.read() != '0')
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(initSpeed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(initSpeed);
    }
  Serial.println("Ensure motor path and output syringe are clear. Press 0 to begin initial system aeration.");
  while (Serial.read() != '0') {}
  Serial.println("Starting initial air suction.");
  digitalWrite(dirPin, LOW);
  for (int x = 0; x < stepsPerRevolution * 2; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(initSpeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(initSpeed);
  }
  Serial.println("Ready to receive fluid one. Press 1 to start.");
  while (Serial.read() != '1') {}
  Serial.println("Press 1 to stop when all of fluid 1 has been suctioned.");
  while (Serial.read() != '1') {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(initSpeed / 1.5);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(initSpeed / 1.5);
  }
  //    Serial.println("Ready to receive fluid two. Press 2 to start.");
  //    while (Serial.read() != '2') {}
  //    Serial.println("Press 2 to stop when all of fluid 2 has been suctioned.");
  //    while (Serial.read() != '2') {
  //      digitalWrite(stepPin, HIGH);
  //      delayMicroseconds(initSpeed / 2.5);
  //      digitalWrite(stepPin, LOW);
  //      delayMicroseconds(initSpeed / 2.5);
  //    }
  Serial.println("Ready to clear output pipe. Press 0 to start.");
  while (Serial.read() != '0') {}
  Serial.println("Press 0 to stop when output line has been cleared.");
  while (Serial.read() != '0') {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(initSpeed * 3);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(initSpeed * 3);
    mixingDistance += 0.25;
  }
  Serial.println("Ready to calibrate mixing. Press 0 to start.");
  while (Serial.read() != '0') {}
  Serial.println("Press 0 to stop when full mixing depth has been reached.");
  while (Serial.read() != '0') {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(initSpeed * 5);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(initSpeed * 5);
    mixingDistance++;
  }
  numRotations = int(mixingDistance);
  Serial.println(mixingDistance);
  Serial.println("Calibration complete. Now running standard mixing cycle. Press \"o\" when ready to output fluid.");
}


void loop() {
  digitalWrite(dirPin, curDir);
  for (int x = 0; x < numRotations; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(mixingSpeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(mixingSpeed);
    if (Serial.read() == 'o') {
      Serial.println("Outputting liquid now. Press \"s\" when all liquid has been output.");
      while (Serial.read() != 's') {
	digitalWrite(dirPin, HIGH);
	digitalWrite(stepPin, HIGH);
	delayMicroseconds(initSpeed);
	digitalWrite(stepPin, LOW);
	delayMicroseconds(initSpeed);
	mixingDistance++;
      }
      Serial.println("Thank you for using the UBC-iGEM microfluidic platform. The microfluidic protocol has concluded.");
      while (true) {} // Stops the program.
    }
  }
  curDir = !curDir;
}



