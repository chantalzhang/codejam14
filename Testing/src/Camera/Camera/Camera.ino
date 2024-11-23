#include <Wire.h>
#include <OV7670.h>  // Include OV7670 library (You might need to install it)

#define OV7670_ADDR 0x42  // OV7670 I2C address

OV7670 camera;

void setup() {
  // Start Serial communication
  Serial.begin(9600);
  while (!Serial);

  // Initialize camera
  camera.begin(OV7670_ADDR);
  
  // Test camera with a simple check (you can also add more camera settings here)
  if (camera.begin()) {
    Serial.println("OV7670 Camera initialized successfully!");
  } else {
    Serial.println("Failed to initialize OV7670 camera.");
  }
  
  // Adjust camera settings (example)
  camera.setResolution(OV7670_RES_VGA);  // Set resolution to VGA
  camera.setColorFormat(OV7670_FORMAT_RGB565);  // Set color format
  
  delay(1000);  // Wait a bit to ensure camera settings are applied
}

void loop() {
  // Read image data from camera
  uint8_t pixelData = camera.readPixel();  // Read a pixel
  
  // Print the pixel data to the Serial Monitor
  Serial.print("Pixel Data: ");
  Serial.println(pixelData, HEX);

  // Implement any image capture or manipulation logic here
  
  delay(100);  // Small delay to avoid overwhelming the serial monitor
}
