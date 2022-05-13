/*
MAX30100 update current 4.4 mA and 10 sampling
*/

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     2000
PulseOximeter pox;
float a,b;
int i = 10;
float c = 0;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("STAY STILL Measuring...");
}

void setup()
{
    Serial.begin(115200);

    Serial.print("Initializing pulse oximeter..");

    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    // The default current for the IR LED is 50mA and it could be changed
    //   by uncommenting the following line. Check MAX30100_Registers.h for all the
    //   available options.
    pox.setIRLedCurrent(MAX30100_LED_CURR_4_4MA);

    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
     pox.update();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      a = pox.getHeartRate();
      b = pox.getSpO2();
          if( a == 0 || b == 0)
            {
              return;
            }

              if (i>0)
              {
                c = ((c+a)/2);
                i = i-1;
                Serial.println(i);
              }
             if (i==0)
              {
                i=10;
                Serial.print("Heart rate: ");
                Serial.print(c);
                Serial.print(" bpm & SpO2: ");
                Serial.print(b);
                Serial.println("%");
                c=0;             
              } 
        tsLastReport = millis();
    }
    
}
