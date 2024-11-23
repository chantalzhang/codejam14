#include "motors.h"
#include <Arduino.h>

// Pin definitions
const int motor1pin1 = 2;
const int motor1pin2 = 3;
const int motor2pin1 = 4;
const int motor2pin2 = 5;
const int motor3pin1 = 6;
const int motor3pin2 = 7;
const int motor4pin1 = 8;
const int motor4pin2 = 9;

// Initialize the motor pins as outputs
void initializeMotors() {
    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(motor2pin1, OUTPUT);
    pinMode(motor2pin2, OUTPUT);
    pinMode(motor3pin1, OUTPUT);
    pinMode(motor3pin2, OUTPUT);
    pinMode(motor4pin1, OUTPUT);
    pinMode(motor4pin2, OUTPUT);
}

// Move all motors forward
void moveMotorsForward() {
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

    digitalWrite(motor3pin1, HIGH);
    digitalWrite(motor3pin2, LOW);

    digitalWrite(motor4pin1, HIGH);
    digitalWrite(motor4pin2, LOW);

    delay(1000); // Adjust as needed
}

// Move all motors backward
void moveMotorsBackward() {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);

    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, HIGH);

    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, HIGH);

    delay(1000); // Adjust as needed
}
