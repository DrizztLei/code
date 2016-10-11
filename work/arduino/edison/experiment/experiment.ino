#include <stdio.h>
#include <SPI.h>
#include <Ethernet.h>
#define LED 13
#define port 9600
#define SOCKET 8888

void show(int light);
void done(int light);

byte mac[] = {
  0x90,
  0xA2,
  0xDA,
  0xFE,
  0x03,
  0x50
};

IPAddress ip(192,168,1,6);

bool flag = false;
bool connected = false;
String content = "";

void show(int light)
{
  pinMode(light , OUTPUT);
  digitalWrite(light , HIGH); 
  delay(1000);
}

void done(int light)
{
  digitalWrite(light , LOW); 
  delay(1000);
  pinMode(light , INPUT);
}

EthernetServer server(SOCKET);

void setup()
{
  Serial.begin(port);
  Ethernet.begin(mac , ip);
  //Ethernet.begin(mac);
  server.begin();
}

void loop()
{
  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  EthernetClient client = server.available();
  show(2);
  done(2);
  
  while(client.connected())
  {
    if(client.available()){
      char c = client.read();
      //Serial.write(c);
      if(c == '\0')
      {
        content += c;     
      }
      Serial.print("Get the info for : ");
      Serial.println(content);
      content = "";
    }
    client.println("Info get From here .");
  }















  /*
  if(client)
  {
    if(!connected)
    {
      client.flush();
      Serial.println("Get the new client");
      client.println("Hello , client");
      connected = true;
    }

    if(client.available() > 0)
    {
      char info = client.read();
      content += info;
      if(info == '\n')
      {
        server.println(content);
        Serial.println(content);
        content = "";
      }
    }
  }
  */
  /*
  digitalWrite(LED , HIGH);
  delay(300);
  digitalWrite(LED , LOW);
  printf("Get the info from %d \n" , digitalRead(LED));
  //exit(0);
  digitalWrite(LED , LOW);
  delay(300);
  Serial.println("INFO FROM");
  printf("Get the info from %d \n" , digitalRead(LED));
  flag = !flag;
  if(flag)
  {
    pinMode(LED , INPUT);
    digitalWrite(LED , LOW);
  }
  else
  {
    pinMode(LED , OUTPUT);
    digitalWrite(LED , HIGH);
  }
  */
}

