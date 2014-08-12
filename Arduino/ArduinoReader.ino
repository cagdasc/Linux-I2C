#include <Wire.h>
#define DEV_ADD 0x21
byte data[3];
void setup()
{
  Wire.begin(DEV_ADD);
  Serial.begin(115200);
  Wire.onReceive(receiveData);
  
}

void loop()
{
  Serial.println("Receive data buffer");
  Serial.print(data[0]);
  Serial.print("----");
  Serial.print(data[1]);
  Serial.print("----");
  Serial.println(data[2]);
  
  delay(300);
  
}

void receiveData(int byteCount){
  int index = 0;
  while(Wire.available() && index < 3)
  {
    data[index] = Wire.read();
    index++;
  }
}
