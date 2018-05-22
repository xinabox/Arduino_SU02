/*************************************************************
  This is an example for the SU02
  Digital Input

  You can buy one on our store!
  -----> https://xinabox.cc/products/SU02/

  This example determines the input state.

  The sensor communicates over the I2C Bus.

*************************************************************/

#include <xCore.h>
#include <xSU02.h>

xSU02 SU02;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Set the I2C Pins for CW01
#ifdef ESP8266
  Wire.pins(2, 14);
  Wire.setClockStretchLimit(15000);
#endif

  // Start the  SU02 Sensor
  SU02.begin();
}

void loop() {

  SU02.poll();

  if (SU02.getState()) {
    Serial.println("button pressed");
  } else {
    Serial.println("nothing new");
  }

  delay(1000);
}
