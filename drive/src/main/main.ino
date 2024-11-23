int motor1pin1 = 2; // Motor 1 direction control
int motor1pin2 = 3; 
int motor2pin1 = 4; // Motor 2 direction control
int motor2pin2 = 5;
int motor3pin1 = 6; // Motor 3 direction control
int motor3pin2 = 7; 
int motor4pin1 = 8; // Motor 4 direction control
int motor4pin2 = 9; 

unsigned long obstacleStartTime = 0;
const int OBSTACLE_THRESHOLD_MS = 100;  // Time in milliseconds to confirm obstacle before stopping motors 
bool isObstacleDetected = false;

void setup() {
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void forward() {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);

      digitalWrite(motor3pin1, HIGH);
      digitalWrite(motor3pin2, LOW);

      digitalWrite(motor4pin1, LOW);
      digitalWrite(motor4pin2, HIGH);
}

void backward() {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor3pin1, LOW);
      digitalWrite(motor3pin2, HIGH);

      digitalWrite(motor4pin1, HIGH);
      digitalWrite(motor4pin2, LOW);
}

void turn_right() {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);

      digitalWrite(motor3pin1, LOW);
      digitalWrite(motor3pin2, HIGH);

      digitalWrite(motor4pin1, LOW);
      digitalWrite(motor4pin2, HIGH);
}
void turn_left() {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor3pin1, HIGH);
      digitalWrite(motor3pin2, LOW);

      digitalWrite(motor4pin1, HIGH);
      digitalWrite(motor4pin2, LOW);
}

void stop() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor3pin1, LOW);
  digitalWrite(motor3pin2, LOW);
  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, LOW);
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
    
    // Check distance
    long inches = measureDistance();
    
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
