/**
 * Photon WebIDE version
 * I2C Comm
 * Master: Bean
 * Slave: Photon
 */
// Slave address
char addr = 8;
int x = 0;     // Receive buffer
char skip = 0;
void setup() {
    if (!Wire.isEnabled()){ 
        Wire.begin(addr);
        Wire.onReceive(receiveEvent);
    }
    pinMode(D7, OUTPUT);
    
    // Debug Port: Serial requires speed
    Serial.begin(57600);
    delay(20);
    Serial.println("Connecting... with Mac Host");
}

void receiveEvent(int bytes) {
    x = Wire.read();
}

void loop() {
    Serial.println(x);
    delay(20);
    if (x == 0) {
        digitalWrite(D7, HIGH);
        delay(200);
        digitalWrite(D7, LOW);
        delay(200);
    }
    if (x == 3) {
        digitalWrite(D7, HIGH);
        delay(200);
        digitalWrite(D7, LOW);
        delay(200);
    }
}
