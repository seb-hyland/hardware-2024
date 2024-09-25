void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 200);

}