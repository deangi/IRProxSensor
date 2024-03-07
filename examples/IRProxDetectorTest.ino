//--------------------------------------------------------------
// HiLetgo IR Proximity Sensor - HW-201 test
//
// Dean Gienger, March 1, 2023
//
// This is an infrared obstacle/proximity sensor from HiLetgo
// It responds to an obstacle 2 to 30 cm away depending on the
// object.   It has about a 35 degree detection angle.
//
// There are three pins:
// VCC - 3 to 5VDC so 3.3V works
// GND - ground
// OUT - output signal, I think open circuit - can pull a 5V relay to ground
//
// Connections:
// VCC - ESP32 3.3V or 5V
// GND - ESP32 ground
// OUT - ESP32 gpio pin with weak pull-up enabled
//
//
#include <Arduino.h>
#include "IRProx.h"

#define PROXPIN 14

IRProx prox(PROXPIN);

void setup() 
{
  Serial.begin(115200);
  Serial.println("\nIR Proximity sensor test\n");
  prox.activate();

}

void loop() 
{
  delay(500);
  Serial.print("trigTime "); Serial.print(prox.lastTriggerTime());
  Serial.print(", trigCount "); Serial.println(prox.trigCount());
}
