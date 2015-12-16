/*
 * Reference:
 * LightBlue Latch -- Sandbox keycode
 * 
 * Input: TouchPad/BLE Verification
 * Drive: Servo
 * 
 * Difficult to connect through BLE
 * 
 * PWMA: 1 Attached Servo PWM Pin
 * AIN1: 0
 * AIN2: 2
 * STBY: 3
 * 
 * Switch Pin Connection: (Active Low)
 * SW1: 5
 * 
 * High = Locked
 * Low = Unlocked
 */
#include <Servo.h>
Servo boltDrive;
/*----------------------------------------------------*/
#define UNLOCK_TIMEOUT_MS 300
#define LOCK_TIMEOUT_MS   275
#define KEYCODE_SIZE      sizeof(KEY_CODE)

/* Pin Definition ------------------------------------*/
/* TODO: check ATMEGA328p pinout */
int PWMA = 1; // Speed Control
//int AIN1 = 0; // Direction
//int AIN2 = 2; // Direction
//int STBY = 3; // standby

/* Electric Strike ------------------------------------*/
int SW1 = 5;

/* Unlock keycode ------------------------------------*/
const char* KEY_CODE = "12345678";

void setup() {
  // put your setup code here, to run once:
  boltDrive.attach(PWMA);
  Serial.begin(57600);      // Baud Rate
  Serial.setTimeout(25);

  // Motor Controller Setup
  pinMode(PWMA, OUTPUT);
//  pinMode(STBY, OUTPUT);
//  pinMode(AIN1, OUTPUT);
//  pinMode(AIN2, OUTPUT);

  pinMode(SW1, INPUT);

  Bean.enableWakeOnConnect( true ); // SDK issue? after first handshake no state change?
}

void loop() {
  // Heartbeat
//  Bean.setLed(0, 255, 0); 
  
  // put your main code here, to run repeatedly:
  char buffer[10];
  size_t readLength = 10;
  static char last_value = 0;
  static char index = 0;
  static char lock_state = 0;

  readLength = Serial.readBytes(buffer, readLength);
  Serial.print("Receive: ");
  Serial.println(buffer);
  Bean.sleep(0xFFFFFFFF);
}
