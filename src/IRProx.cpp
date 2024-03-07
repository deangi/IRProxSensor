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
// V1.0 - initial release
// V1.1 - deactivate on destruct

#include <Arduino.h>
#include "IRProx.h"
#include <FunctionalInterrupt.h>

//------------------------------------------------
// Constructor
IRProx::IRProx(int gpiopin)
{
    gpioPin = gpiopin;
    triggerCount = 0;
    lastReadTriggerCount = 0;
    trigTime = 0;
    pinMode(gpioPin,INPUT_PULLUP);
}

//------------------------------------------------
// activate a PIR sensor on a particular pin
int IRProx::activate()
{
  triggerCount = 0;
  lastReadTriggerCount = 0;
  trigTime = 0;
  pinMode(gpioPin,INPUT_PULLUP);
  // trigger on a falling edge
  attachInterrupt(digitalPinToInterrupt(gpioPin), std::bind(&IRProx::isr,this), FALLING);
  return true; // success
}

//------------------------------------------------
// detach a PIR sensor - make it inactive
int IRProx::deactivate()
{
  detachInterrupt(gpioPin);
  gpioPin = -1; // not assigned, not active
  return true; // success
}

//------------------------------------------------
// true if there was a trigger in last xms
int IRProx::triggeredWithin(unsigned long xms)
{
  unsigned long x = millis() - trigTime;
  return x <= xms;
}

//------------------------------------------------
// see how many triggers since last time
// this routine was called
unsigned long IRProx::currentTriggers() 
{ 
  unsigned long n = triggerCount - lastReadTriggerCount; 
  lastReadTriggerCount = triggerCount; 
  return n;
}
