// Motor pin definitions
int motor1Pin1 = 2;  // Motor 1 direction control
int motor1Pin2 = 3;  
int motor2Pin1 = 4;  // Motor 2 direction control
int motor2Pin2 = 5;  
int motor3Pin1 = 6;  // Motor 3 direction control
int motor3Pin2 = 7;  
int motor4Pin1 = 8;  // Motor 4 direction control
int motor4Pin2 = 9;  

// Time to spin in each direction (milliseconds)
const int spinTime = 2000;

void setup() {
  // Set motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);
}

void loop() {
  // Spin all wheels forward
  spinForward();
  delay(spinTime);

  // Stop motors briefly
  stopMotors();
  delay(500);

  // Spin all wheels backward
  spinBackward();
  delay(spinTime);

  // Stop motors briefly
  stopMotors();
  delay(500);
}

void spinForward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);

  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);

  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
}

void spinBackward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);

  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);

  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);

  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);

  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
}
