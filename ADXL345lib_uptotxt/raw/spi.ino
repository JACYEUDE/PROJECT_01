#include <SPI.h>


//ADXL345

#define SCLpin  D5//GPIO 14 Serial clock pin
#define SDOpin  D6//GPIO 12 MISO pin
#define SDApin  D7//GPIO 13 MOSI pin
#define SSpin   D0// CS pin
//#define SSpin   D8//GPIO 15 CHip Select
//Nodemcu pin 3.3 -----> pin VCC ADXL345
//Nodemcu pin GND -----> pin GND ADXL345

char BW_RATE = 0x2C;   // Data Rate and power mode control
char POWER_CTL=0x2D;   // Power Control Register
char DATA_FORMAT=0x31; // Data Format Register
char DATAX0=0x32;
char DATAX1=0x33;
char DATAY0=0x34;
char DATAY1=0x35;
char DATAZ0=0x36;
char DATAZ1=0x37;

int16_t X_Data, Y_Data, Z_Data;

char str[10];
long lastMsg=0;
byte TO_READ = 6;




void setup()
{
  Serial.begin(115200);
  SPI.begin(); 
  SPI.beginTransaction(SPISettings(5000000,MSBFIRST,SPI_MODE3));
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
 
  writeRegister(POWER_CTL, 0x00);// Configured in Stand By Mode
  writeRegister(POWER_CTL, 0x08); // Configured in Measurement Mode
  writeRegister(BW_RATE, 0x0C);
}

void loop()
{
  readRegister(DATAX0, TO_READ, str);
  X_Data= ((int16_t)str[1] << 8) | (int16_t)str[0];
  Y_Data= ((int16_t)str[3] << 8) | (int16_t)str[2];
  Z_Data= ((int16_t)str[5] << 8) | (int16_t)str[4];

  Serial.println(X_Data);
  Serial.println(Y_Data);
  Serial.println(Z_Data);
  Serial.println();
}


void writeRegister(char registerAddress, char value)
{
    digitalWrite(SS, LOW);
    SPI.transfer(registerAddress);
    SPI.transfer(value);
    digitalWrite(SS, HIGH);
    SPI.endTransaction();
}

void readRegister(char registerAddress, int16_t numBytes,char * str)
{
    char address = (0x80 | registerAddress);
    if (numBytes > 1)address = address | 0x40;
    digitalWrite(SS, LOW);
    SPI.transfer(address);
   
       for (int16_t i = 0; i < numBytes; i++)
       {
            str = SPI.transfer(0x00);
       }
       
    digitalWrite(SS, HIGH);
    SPI.endTransaction();
}