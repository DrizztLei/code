
#include <SPI.h>
#include <Ethernet.h>
 
byte mac[] = { 0x90 , 0xA2 , 0xDA , 0xF6 , 0x03 , 0x50 };
IPAddress ip(121,250,223,15);
 

EthernetServer server(100);
 
void setup() {
  Serial.begin(9600);
  //Ethernet.begin(mac, ip);
  Serial.print("Geting the ip ");
  Ethernet.begin(mac);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
 
void loop() {
  Serial.print("Run in loop , ip for : ");
  Serial.println(Ethernet.localIP());
  delay(1000);
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");       
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disonnected");
  }
}
