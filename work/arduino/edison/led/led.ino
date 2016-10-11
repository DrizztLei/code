int ledPin = 10;
void setup()
{
  pinMode(ledPin, OUTPUT);
  printf("init done");
}
void loop()
{
  
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
  
}

