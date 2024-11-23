#ifndef SENSORS_H
#define SENSORS_H

// Pin declarations
extern const int echoPin;
extern const int trigPin;

// Function declarations
void initializeSensors();
long measureDistanceInInches();
long measureDistanceInCM();

#endif
