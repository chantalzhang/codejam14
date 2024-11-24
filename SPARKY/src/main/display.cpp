#include "display.h"
#include <Arduino.h>

// Example display variable
extern int displayValue = 0;
const int LED_PIN = 12;

void initializeDisplay() {
    Serial.println("Initializing display...");
    pinMode(LED_PIN, OUTPUT);
}

void updateDisplay() {
    displayValue = analogRead(A0); // Example based on sensor
    Serial.print("Display Value: ");
    Serial.println(displayValue);
}

void led_on() {
    digitalWrite(LED_PIN, HIGH);
}

void led_off() {
    digitalWrite(LED_PIN, LOW);
}
