#include <Wire.h>
#define OV7670_ADDRESS 0x42

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Starting OV7670 I2C test...");

  Wire.begin();

  Serial.println("Checking I2C connection...");
  if (testCameraConnection()) {
    Serial.println("OV7670 Camera found!");
  } else {
    Serial.println("OV7670 Camera not found. Check connections!");
  }
}

void loop() {
}

// Function to test camera I2C connection
bool testCameraConnection() {
  Serial.println("Sending I2C start condition...");
  Wire.beginTransmission(OV7670_ADDRESS >> 1); // Address in write mode
  byte error = Wire.endTransmission();
  Serial.print("I2C response code: ");
  Serial.println(error);

  return (error == 0); // Return true if no error
}
