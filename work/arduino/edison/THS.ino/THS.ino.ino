#include <dht11.h>
#define DHT11PIN  2

dht11 DHT11;
float dht11t()
{
  int chk = DHT11.read(DHT11PIN);
  return DHT11.temperature;
}

float dht11h()
{
  int chk = DHT11.read(DHT11PIN);
  return DHT11.humidity;
}


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Tep:");
  Serial.print(" ");
  Serial.print(  dht11t());
  Serial.print(" ");
  Serial.print("Hum:");
  Serial.print(" ");
  Serial.print( dht11h());
  Serial.print(" ");
  Serial.println();
}

