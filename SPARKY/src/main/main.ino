#include "sensors.h"
#include "motors.h"
#include "display.h"

// Add these variables at the top
unsigned long obstacleStartTime = 0;
const int OBSTACLE_THRESHOLD_MS = 100;  // Time in milliseconds to confirm obstacle
bool isObstacleDetected = false;

void setup() {
    Serial.begin(9600);
    initializeSensors();
    initializeMotors();
    initializeDisplay();
}

void loop() {
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
    
    long inches = measureDistanceInInches();
    long cm = measureDistanceInCM();

    // Print the results to the Serial Monitor
    Serial.print(inches);
    Serial.print(" in, ");
    Serial.print(cm);
    Serial.println(" cm");
    
    // Check for sustained obstacle detection
    if (inches < 10) {
        if (!isObstacleDetected) {
            // First time detecting obstacle
            obstacleStartTime = millis();
            isObstacleDetected = true;
        } else if ((millis() - obstacleStartTime) >= OBSTACLE_THRESHOLD_MS) {
            // Obstacle has been detected consistently for the threshold time
            stop();
        }
    } else {
        // No obstacle detected, reset the flag
        isObstacleDetected = false;
    }
}

