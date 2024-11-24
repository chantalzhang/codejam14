#include "sensors.h"
#include "motors.h"
#include "display.h"

// State tracking variables
unsigned long forwardStartTime = 0;    // When we started driving forward
unsigned long forwardDriveTime = 0;    // Total time spent driving forward
bool isReturning = false;             // Are we currently returning?
bool isDrivingForward = false;        // Are we currently driving forward?

// Timing constants
const unsigned long MIN_DRIVE_TIME = 2000;     // Minimum 2 seconds of movement
const unsigned long COMMAND_TIMEOUT = 1000;    // Wait 1 full second before stopping on lost signal
const float RETURN_FACTOR = 0.5;              // Return 90% of the forward distance
unsigned long lastCommandTime = 0;           // Track when we last got a command

void setup() {
    Serial.begin(9600);
    initializeSensors();
    initializeMotors();
    initializeDisplay();
}

void loop() {
    unsigned long currentTime = millis();
    
    if (Serial.available() > 0) {
        char command = Serial.read();
        lastCommandTime = currentTime;
        
        // Debug output
        Serial.print("Command received: ");
        Serial.println(command);
        
        switch (command) {
            case 'P':
                if (!isDrivingForward && !isReturning) {
                    // Start driving forward if we're not already moving
                    led_on();
                    forward();
                    isDrivingForward = true;
                    forwardStartTime = currentTime;
                }
                // If already driving forward, update the last command time
                if (isDrivingForward) {
                    lastCommandTime = currentTime;
                }
                break;
                
            case 'N':
                if (isDrivingForward && 
                    (currentTime - forwardStartTime >= MIN_DRIVE_TIME)) {
                    // Stop and remember how far we went
                    stop();
                    isDrivingForward = false;
                    forwardDriveTime = currentTime - forwardStartTime;
                    // Start return journey
                    backward();
                    isReturning = true;
                    forwardStartTime = currentTime; // Reuse for return timing
                }
                led_off();
                break;
        }
    } else if (isDrivingForward && 
              (currentTime - lastCommandTime > COMMAND_TIMEOUT) && 
              (currentTime - forwardStartTime >= MIN_DRIVE_TIME)) {
        // If we haven't received a command recently and have moved minimum distance, stop
        stop();
        isDrivingForward = false;
        forwardDriveTime = currentTime - forwardStartTime;
        // Start return journey
        backward();
        isReturning = true;
        forwardStartTime = currentTime;
        led_off();
    }
    
    // Check ultrasonic sensor
    long inches = measureDistanceInInches();
    
    // Check for obstacles and handle return journey timing
    if (inches > 6) {
        if (isDrivingForward) {
            // Hit obstacle while going forward
            stop();
            isDrivingForward = false;
            forwardDriveTime = currentTime - forwardStartTime;
            Serial.print("Drove forward for (ms): ");
            Serial.println(forwardDriveTime);
        }
    }
    
    // Check if we've driven backward for the adjusted return time
    if (isReturning && (currentTime - forwardStartTime >= (forwardDriveTime * RETURN_FACTOR))) {
        stop();
        isReturning = false;
        Serial.println("Return journey complete");
    }
}

