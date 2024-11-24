#include <WiFiS3.h> // Include the WiFiS3 library for Arduino UNO R4 WiFi

// Replace with your Wi-Fi credentials
const char* ssid = "Ray's iPhone"; // Replace with your Wi-Fi SSID
const char* password = "rayphone"; // Replace with your Wi-Fi password

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial); // Wait for serial connection to be established

  // Initialize Wi-Fi module
  Serial.println("Initializing WiFi...");
  WiFi.disconnect(); // Ensure Wi-Fi module is disconnected
  delay(100);

  // Connect to Wi-Fi network
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Start the connection process

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Connected!
  Serial.println("\nConnected to Wi-Fi.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the assigned IP address
}

void loop() {
  // Optional: Keep checking the Wi-Fi connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected. Reconnecting...");
    WiFi.begin(ssid, password); // Attempt to reconnect
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nReconnected to Wi-Fi.");
  }

  // Your main code here
  delay(5000);
}
