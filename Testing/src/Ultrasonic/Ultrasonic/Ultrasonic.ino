int echoPin = 10;
int trigPin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT); // Fix: trigPin should be OUTPUT
}

void loop() {
  long duration, inches, cm;

  // Send a 10-microsecond pulse to trigger the ultrasonic sensor

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Convert the time to distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCM(duration);

  // Display results in Serial Monitor
  Serial.println(inches);
  Serial.println(" in, ");
  Serial.println(cm);
  Serial.println(" cm");

  delay(1000); // Small delay before the next measurement
}

// Convert microseconds to inches
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2; // Divide by 74 and then halve
}

// Convert microseconds to centimeters
long microsecondsToCM(long microseconds) {
  return microseconds / 29 / 2; // Divide by 29 and then halve
}
