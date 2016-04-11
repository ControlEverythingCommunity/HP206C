// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HP206C
// This code is designed to work with the HP206C_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=HP206C_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// HP206C I2C address is 0x76(118)
#define Addr 0x76

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[6];

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Send OSR and channel setting command
  Wire.write(0x44 | 0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x10);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 bytes of data
  // cTemp msb, cTemp csb, cTemp lsb, pressure msb, pressure csb, pressure lsb
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  // Convert the data to 20-bits
  float cTemp = (((data[0] & 0x0F) * 65536) + (data[1] * 256) + data[2]) / 100.00;
  float fTemp = (cTemp * 1.8) + 32;
  float pressure = (((data[3] & 0x0F) * 65536) + (data[4] * 256) + data[5]) / 100.00;

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Send OSR and channel setting command
  Wire.write(0x44 | 0x01);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x31);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 3 bytes of data
  Wire.requestFrom(Addr, 3);

  // Read 3 bytes of data
  // altitude msb, altitude csb, altitude lsb
  if (Wire.available() == 3)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
  }

  // Convert the data to 20-bits
  float altitude = (((data[0] & 0x0F) * 65536) + (data[1] * 256) + data[2]) / 100.00;

  // Output data to serial monitor
  Serial.print("Altitude : ");
  Serial.print(altitude);
  Serial.println(" m");
  Serial.print("Pressure : ");
  Serial.print(pressure);
  Serial.println(" Pa");
  Serial.print("Temperature in Celsius : ");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit : ");
  Serial.print(fTemp);
  Serial.println(" F");
  delay(1000);
}
