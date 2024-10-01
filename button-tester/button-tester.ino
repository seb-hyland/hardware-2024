void setup() {
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("LEFT: ");
  Serial.print(digitalRead(7));
  Serial.print("\tRIGHT: ");
  Serial.println(digitalRead(11));
}
