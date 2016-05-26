// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// PCA9685
// This code is designed to work with the PCA9685_I2CPWM8W16I12V I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/FET-Drivers?sku=PCA9685_I2CPWM8W16I12V#tabs-0-product_tabset-2

#include<Wire.h>

// PCA9685 I2C address is 0x40(64)
#define Addr 0x40

int mode = 0;
void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, Baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select MODE2 register
  Wire.write(0x01);
  // All pin's outputs are configured with a totem pole structure.
  Wire.write(0x04);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select MODE1 register
  Wire.write(0x00);
  // Response to LED all-call I2C address
  Wire.write(0x01);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(5);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);

  // Read 1 byte of data
  if (Wire.available() == 1)
  {
    mode = Wire.read();
  }

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select MODE1 register
  Wire.write(0x00);
  // Response to LED all-call I2C address
  Wire.write(0x10);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PRE_SCALE register
  Wire.write(0xFE);
  // Set prescale frequency to 60 Hz
  Wire.write(0x65);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select MODE1 register
  Wire.write(0x00);
  // Response to LED all-call I2C address
  Wire.write((byte)mode);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(5);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select MODE1 register
  Wire.write(0x00);
  // Response to LED all-call I2C address
  Wire.write((mode | 0x80));
  // Stop I2C Transmission
  Wire.endTransmission();
}

void loop()
{
  // Increase Brightness of ALL LED
  for (int i = 0; i < 4096; i += 3)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select ALL_LED_ON_L register
    Wire.write(0xFA);
    // ALL_LED_ON lower byte
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select ALL_LED_ON_H register
    Wire.write(0xFB);
    // ALL_LED_ON higher byte
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select ALL_LED_OFF_L register
    Wire.write(0xFC);
    // ALL_LED_OFF lower byte
    Wire.write((byte)(i & 0xFF));
    
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select ALL_LED_OFF_H register
    Wire.write(0xFD);
    // ALL_LED_OFF higher byte
    Wire.write((i >> 8));
    // Stop I2C Transmission
    Wire.endTransmission();
  }
  delay(2500);

  // Decrease Brightness of ALL LED
  for(int i = 4095; i >= 0; i -= 3)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select ALL_LED_ON_L register
    Wire.write(0xFA);
    // ALL_LED_ON lower byte
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select ALL_LED_ON_H register
    Wire.write(0xFB);
    // ALL_LED_ON higher byte
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select ALL_LED_OFF_L register
    Wire.write(0xFC);
    // ALL_LED_OFF lower byte
    Wire.write((byte)(i & 0xFF));
    
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select ALL_LED_OFF_H register
    Wire.write(0xFD);
    // ALL_LED_OFF higher byte
    Wire.write((i >> 8));
    // Stop I2C Transmission
    Wire.endTransmission();
  }
  delay(2500);  
}

