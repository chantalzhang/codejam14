#ifndef MOTORS_H
#define MOTORS_H

// Pin definitions
extern const int motor1pin1;
extern const int motor1pin2;
extern const int motor2pin1;
extern const int motor2pin2;
extern const int motor3pin1;
extern const int motor3pin2;
extern const int motor4pin1;
extern const int motor4pin2;

// Function declarations
void initializeMotors();
void forward();
void backward();
void turn_right();
void turn_left();
void stop();

#endif
