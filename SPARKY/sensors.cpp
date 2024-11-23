#include "sensors.h"
#include <Arduino.h>

// Pin definitions
const int echoPin = 10;
const int trigPin = 11;

// Initialize the ultrasonic sensor
void initializeSensor() {
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT); // Set trigPin as output
    Serial.begin(9600);      // Start serial communication
}

// Measure distance in inches
long measureDistanceInInches() {
    long duration;

    // Send a 10-microsecond pulse to the trigger pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the duration of the echo pulse
    duration = pulseIn(echoPin, HIGH);

    // Convert duration to inches
    return duration / 74 / 2;
}

// Measure distance in centimeters
long measureDistanceInCM() {
    long duration;

    // Send a 10-microsecond pulse to the trigger pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the duration of the echo pulse
    duration = pulseIn(echoPin, HIGH);

    // Convert duration to centimeters
    return duration / 29 / 2;
}
