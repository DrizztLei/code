
#include <Wire.h> //IIC库

#include <math.h> 

int BH1750address = 0x23;//芯片地址为16位23

byte buff[2];

void setup()

{

  
  Serial.begin(9600);
  Wire.begin();

}




void loop()

{

 int i;

 uint16_t val=0;

 BH1750_Init(BH1750address);

 delay(1000);
 int result = BH1750_Read(BH1750address);
 Serial.print("Result : ");
 Serial.print(result);
 Serial.print("\n");
 if(2==result)

  {

   val=((buff[0]<<8)|buff[1])/1.2;

   Serial.print(val,DEC);     

   Serial.println("[lx]"); 

  }       
        delay(150);

}




int BH1750_Read(int address) //

{

  int i=0;

  Wire.beginTransmission(address);

  Wire.requestFrom(address, 2);

  while(Wire.available()) //

  {

    buff[i] = Wire.read();  // read one byte

    i++;

  }

  Wire.endTransmission();  

  return i;

}




void BH1750_Init(int address) 

{

  Wire.beginTransmission(address);

  Wire.write(0x10);//1lx reolution 120ms

  Wire.endTransmission();

}
