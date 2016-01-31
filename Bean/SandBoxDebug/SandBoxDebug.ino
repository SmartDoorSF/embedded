/**
 * I2C Comm
 * 
 * Master: Bean
 * Slave: Photon
 */
#include <Wire.h>

int address = 8;
int dataCount = 0;

/* Global States--------------------------------------*/
static bool connected = false;
void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
//  Wire.requestFrom(8, 6);       // Request 6 bytes from slave device #8
  connected = Bean.getConnectionState();
//  Wire.beginTransmission(address);
//  Wire.write(dataCount);
//  Wire.endTransmission();
//  delay(500);

  if (connected) {
    Bean.setLed(0, 255, 0);
  } else {
    Bean.setLed(0, 0, 0);  
  }

  Bean.sleep(100);
}
