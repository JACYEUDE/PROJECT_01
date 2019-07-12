#include <Wire.h>
#include "ADXL345lib.h"


Accelerometer acc;
bool fail;

void setup()
{
    Serial.begin(9600);
    
    // set the I2C address of the accelerometer
    //
    // With the OSEPP Accelerometer use:
    //      OSEPP_ACC_SW_ON    - Switch is in the ON position
    //      OSEPP_ACC_SW_OFF   - Switch is in the OFF position
    //
    // begin will return 0 on success
    acc.begin(OSEPP_ACC_SW_ON);
    acc.setSensitivity(ADXL345_RANGE_PM4G);
}

void loop()
{
    
    double x, y, z;

    acc.readGs(&x, &y, &z);
    
    // print them out
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.println(z);

    delay(200);
}
