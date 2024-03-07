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
// V1.0 - initial release, March 1, 2024
// V1.1 - deactivate on destruct
//
// Notes:
// 1) In my test it was 2-5 cm detection range depending on the material and material color
// 2) It seems to "bounce" - triggers multiple times when an object is moving into or out of range
//
// --------------

class IRProx
{
  public:
    //--- Constructor ---
    IRProx(int gpiopin);
    ~IRProx() { deactivate(); }
    
    //--- millis() time when we last triggered, 0 means none
    unsigned long lastTriggerTime() { return trigTime; }
    
    // true if we triggered with the last xms
    int triggeredWithin(unsigned long xms);
    
    // how many times it triggered since last time we checked by calling currentTriggers
    unsigned long currentTriggers();
    
    int activate();
    
    int deactivate();

    int trigCount() { return triggerCount; }
    
  private:
    void ARDUINO_ISR_ATTR isr() { triggerCount++; trigTime = millis(); }
    int gpioPin; // -1 means inactive
    unsigned long triggerCount;
    unsigned long trigTime;
    unsigned long lastReadTriggerCount; // trigger count last time we checked
};
