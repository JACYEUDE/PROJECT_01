#include <SPI.h>

//ADXL345
#define BW_RATE 0x2C //Data rate and power mode control
#define POWER_CTL 0x2D //Power Control Register
#define DATA_FORMAT 0x31 //Data format control
#define DATAX0 0x32 //X-Axis Data 0


//Nodemcu pin D5 GPIO 14 -----> pin SCL ADXL345
//Nodemcu pin D6 GPIO 12 -----> pin SDO ADXL345
//Nodemcu pin D7 GPIO 13 -----> pin SDA ADXL345
//Nodemcu pin D0 GPIO 16 -----> pin CS/SS ADXL345
//Nodemcu pin 3.3 -----> pin VCC ADXL345
//Nodemcu pin GND -----> pin GND ADXL345

#define SS 16 

char values[10];
int16_t x, y, z;
float xg, yg, zg;

void setup() {
SPI.begin();
SPI.setDataMode(SPI_MODE3);
SPI.setBitOrder(MSBFIRST);
SPI.setFrequency(5000000);
//SPI.setClockDivider(SPI_CLOCK_DIV16);


Serial.begin(9600);

// SS Hight
pinMode(SS, OUTPUT);
digitalWrite(SS, HIGH);

// ADXL345
writeRegister(DATA_FORMAT, 0x03); // ±16g 10bit
writeRegister(POWER_CTL, 0x08); //
writeRegister(BW_RATE, 0x0F); //
}

void loop() {
// DATAX0
readRegister(DATAX0, 6, values);

// 2Byte
x = ((int16_t)values[1] << 8) | (int16_t)values[0];
y = ((int16_t)values[3] << 8) | (int16_t)values[2];
z = ((int16_t)values[5] << 8) | (int16_t)values[4];

// 0.03125 = (16*2)/(2^10)
xg = x * 0.03125;
yg = y * 0.03125;
zg = (z * 0.03125) - 1;



//

Serial.print(x);
Serial.print(",");
Serial.print("\t");
Serial.print(y);
Serial.print(",");
Serial.print("\t");
Serial.println(z);
}

void writeRegister(char registerAddress, char value) {
// SPI
digitalWrite(SS, LOW);
//
SPI.transfer(registerAddress);
//
SPI.transfer(value);
// SPI
digitalWrite(SS, HIGH);
}

void readRegister(char registerAddress, int16_t numBytes, char * values) {
//
char address = 0x80 | registerAddress;
//
if (numBytes > 1)address = address | 0x40;
// SPI
digitalWrite(SS, LOW);
//
SPI.transfer(address);
//
for (int16_t i = 0; i < numBytes; i++) {
values[i] = SPI.transfer(0x00);
}
// SPI CS HIGH
digitalWrite(SS, HIGH);
}
