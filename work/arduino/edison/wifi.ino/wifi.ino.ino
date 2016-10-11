#include <WiFi.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Network scaning .");
  int numSSID = WiFi.scanNetworks();
  Serial.print("Get the number for : ");
  Serial.println(numSSID);
}

void loop()
{
  int numSSID = WiFi.scanNetworks();
  Serial.print("Get the number for : ");
  Serial.println(numSSID);
}

