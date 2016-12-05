//#include <stdlib.h>
//#include <unistd.h>
//#include <stdio.h>
//#include <string.h>
//#include <Bridge.h>

const int led = 13;
const int fsr = 3;
const int info_length = 10;
void setup()
{
  pinMode(led,OUTPUT);
  pinMode(fsr,INPUT);
  //analogWrite( fsr , 784);
  Serial.begin(9600);
    digitalWrite(13 , HIGH);
  //Bridge.begin();

}

void loop()
{ 
  int value = analogRead(fsr);
  Serial.print("Value for : ");
  Serial.println(value);
  //char info[info_length];
  //string info = itoa(value); 
  //itoa(value , info , info_length);
  //Bridge.put("key" , info);
  
  //Serial.print("Put done " );
  //Serial.println(info);
  /*
  Serial.println("COMPLIETEION");
  analogWrite(fsr , 623);
  int value = analogRead(fsr);
  Serial.print("Get the value for : ");
  Serial.println(value);
  delay(1000);
  */
  //Serial.println("INFO ");
}
