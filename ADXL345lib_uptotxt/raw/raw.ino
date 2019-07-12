#include <Wire.h>
#include "ADXL345lib.h"
#include <math.h>

#define S 15

Accelerometer acc;

int16_t getraw(void)
{
    Serial.println("Gathering raw values...");    

    for (uint8_t i = 0; i < S; ++i)
    {
        int16_t x, y, z;

        if (acc.readRaw(&x, &y, &z) != 0)
        {
            Serial.println("Failed to read sensor. End.");
            return -1;
        }
        delay(50);
        
        Serial.println("Raw values:");
        Serial.print("X: ");
        Serial.print(x);
        Serial.print(" Y: ");
        Serial.print(y);
        Serial.print(" Z: ");
        Serial.println(z);

    return 0;       
    }
}

void setup()
{
    Serial.begin(57600);
    
    
    if (acc.begin(OSEPP_ACC_SW_ON) != 0)
    {
        Serial.println("Error connecting to accelerometer");
        return;
    }

   
acc.setSensitivity(ADXL345_RANGE_PM2G);
    
acc.setOffsets(0, 0, 0);

}

void loop()
{
    getraw();
    delay(100);

}
