// Write data to I2C slave device
#include <Wire.h>
byte device = 0x24,data;
long startMotor;
void setup()
{
  Wire.begin(); // Start I2C bus
  Serial.begin(115200); // Setup serial for debug
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}
void loop()
{
  int temp=analogRead(A0);
  int temp2=digitalRead(A1);
  Serial.print(temp);
  Serial.print(":");
  Serial.println(temp2);
  if(temp<970&&temp2==1)
  {
    opend();
    closed();
  }


}
void closed(){
  byte address,data,device;
  address = 0x24;
  device = address; 
  startMotor = millis();
  while ((millis()-startMotor)<=2500){
    data = 0x10;
    for (int i = 1 ; i <= 4; i++)
    {
      Wire.beginTransmission(device);
      Wire.write(data);
      Wire.endTransmission();
      delay(5);
      data = data << 1;
    }
  }
}

void opend(){
  byte address,data,device;
  address = 0x24;
  device = address; 
  startMotor = millis();
  while ((millis()-startMotor)<=2500){
    data = 0x80;
    for (int i = 1 ; i <= 4; i++)
    {
      Wire.beginTransmission(device);
      Wire.write(data);
      Wire.endTransmission();
      delay(5);
      data = data >> 1;
    }
  }
}
