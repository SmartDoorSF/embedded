// SoftAp with button enable interrupt
#include "application.h"

SYSTEM_THREAD(ENABLE);
// SYSTEM_MODE(MANUEL);
SYSTEM_MODE(attachButton());

void attachButton()
{
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH);       // indicate that from now on you can use the button
  attachInterrput(D6, toSetupMode, FALLING);
  Particle.connect();
}

void toSetupMode()
{
  if(digitalWrite(D7)) {
    digitalWrite(D7, LOW);
    WiFi.listen();
  }
}

uint32_t msTimeout;

void setup()
{
  msTimeout = millis();
}

void loop()
{
  // WiFi.hasCredentials();
  if (millis() - msTimeout > 15000) // 15sec after setup()
    digtialWrite(D7, LOW);          // prevent button press from entering Listening mode
}
