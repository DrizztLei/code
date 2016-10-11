int const infrared = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(infrared);
  Serial.print("Value for : ");
  Serial.println(value);
  delay(1000);
}
