/**
 * I2C Comm
 * 
 * Master: Bean
 * Slave: Photon
 */

#include <Wire.h>

int address = 8;
int dataCount = 0;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Bean.setLed(0, 0, 255);
  delay(200);
  Bean.setLed(0, 0, 255);
//  Wire.requestFrom(8, 6);       // Request 6 bytes from slave device #8
  Wire.beginTransmission(address);
  Wire.write(dataCount);
  Wire.endTransmission();
  dataCount+=1;
  if (dataCount > 5) {
    dataCount = 0;  
  }
  delay(500);
}
