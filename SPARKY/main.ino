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

    if (Serial.available() > 0) {
        char command = Serial.read();
        
        // Debug output
        Serial.print("Command received: ");
        Serial.print(command);
        
        switch (command) {
            case 'F':
                forward();
                break;
            case 'B':
                backward();
                break;
            case 'S':
                stop();
                break;
            case 'L':
                turn_left();
                break;
            case 'R':
                turn_right();
                break;
        }
    }

    delay(1000); // Delay before the next measurement
    forward();
    backward();
    updateDisplay();
    delay(500); // Add delay for readability
}

