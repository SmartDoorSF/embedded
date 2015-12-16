/*
 * Reference:
 * LightBlue Latch -- Sandbox keycode
 * 
 * Input: TouchPad/BLE Verification
 * Drive: Servo
 * 
 * PWMA: 1 Attached Servo PWM Pin
 * AIN1: 0
 * AIN2: 2
 * STBY: 3
 * 
 * Switch Pin Connection: (Active Low)
 * SW1: 5
 * 
 * Swithc High = Locked
 * Switch Low = Unlocked
 */
#include <Servo.h>
Servo boltDrive;
/*----------------------------------------------------*/
#define UNLOCK_TIMEOUT_MS 300
#define LOCK_TIMEOUT_MS   275

/* Pin Definition ------------------------------------*/
/* TODO: check ATMEGA328p pinout */
int PWMA = 1; // Speed Control
int AIN1 = 0; // Direction
int AIN2 = 2; // Direction
int STBY = 3; // standby

/* Electric Strike */
int SW1 = 5;

/* Unlock keycode (hardcoded) */
const char* KEY_CODE = "123456789";

void setup() {
  // put your setup code here, to run once:
  boltDrive.attach(PWMA);
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
