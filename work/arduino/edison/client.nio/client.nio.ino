#include <SPI.h>
#include <Ethernet.h>
#define serial_port 9600

byte mac[] = {0x90 , 0xA2 , 0xDA , 0xF6 , 0x03 , 0x50};
IPAddress ip(192 , 168 , 1 , 141);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(serial_port);
  //Ethernet.begin(mac , ip);
  
  if( Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;);
  }
  

  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("My IP address : " );
  for(byte i = 0 ; i < 4 ; i ++)
  {
    Serial.print(Ethernet.localIP()[i]);
    Serial.print(".");
  }
  Serial.println();
  delay(1000);
}
