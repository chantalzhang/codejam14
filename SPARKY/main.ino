#include "sensors.h"
#include "motors.h"
#include "display.h"

void setup() {
    Serial.begin(9600);
    initializeSensors();
    initializeMotors();
    initializeDisplay();
}

void loop() {
    long inches = measureDistanceInInches();
    long cm = measureDistanceInCM();

    // Print the results to the Serial Monitor
    Serial.print(inches);
    Serial.print(" in, ");
    Serial.print(cm);
    Serial.println(" cm");

    delay(1000); // Delay before the next measurement
    moveMotorsForward();
    moveMotorsBackward();
    updateDisplay();
    delay(500); // Add delay for readability
}

