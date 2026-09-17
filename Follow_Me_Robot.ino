#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

// Sensor pins
#define TRIG_PIN A1
#define ECHO_PIN A0
#define IR_RIGHT A2
#define IR_LEFT A3
#define MAX_DISTANCE 200

unsigned int distance = 0;
unsigned int Right_Value = 0;
unsigned int Left_Value = 0;

// Ultrasonic sensor
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Servo for sensors
Servo sensorServo;
int servoPos = 90; // start at center
int servoDir = 1;  // for sweeping direction control

// Motor setup (HW-130)
AF_DCMotor Motor1(1, MOTOR12_1KHZ);
AF_DCMotor Motor2(2, MOTOR12_1KHZ);
AF_DCMotor Motor3(3, MOTOR34_1KHZ);
AF_DCMotor Motor4(4, MOTOR34_1KHZ);

void setup() {
  Serial.begin(9600);

  // Attach servo to pin 10 (serv1)
  sensorServo.attach(10);
  sensorServo.write(servoPos);

  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);
}

// Function to move forward
void moveForward(int spd = 200) {
  Motor1.setSpeed(spd); Motor1.run(FORWARD);
  Motor2.setSpeed(spd); Motor2.run(FORWARD);
  Motor3.setSpeed(spd); Motor3.run(BACKWARD);
  Motor4.setSpeed(spd); Motor4.run(BACKWARD);
}

// Function to move backward
void moveBackward(int spd = 200) {
  Motor1.setSpeed(spd); Motor1.run(BACKWARD);
  Motor2.setSpeed(spd); Motor2.run(BACKWARD);
  Motor3.setSpeed(spd); Motor3.run(FORWARD);
  Motor4.setSpeed(spd); Motor4.run(FORWARD);
}

// Function to stop
void stopAll() {
  Motor1.run(RELEASE);
  Motor2.run(RELEASE);
  Motor3.run(RELEASE);
  Motor4.run(RELEASE);
}

// Function to turn left
void turnLeft(int spd = 200) {
  Motor1.setSpeed(spd); Motor1.run(BACKWARD);
  Motor2.setSpeed(spd); Motor2.run(BACKWARD);
  Motor3.setSpeed(spd); Motor3.run(BACKWARD);
  Motor4.setSpeed(spd); Motor4.run(BACKWARD);
}

// Function to turn right
void turnRight(int spd = 200) {
  Motor1.setSpeed(spd); Motor1.run(FORWARD);
  Motor2.setSpeed(spd); Motor2.run(FORWARD);
  Motor3.setSpeed(spd); Motor3.run(FORWARD);
  Motor4.setSpeed(spd); Motor4.run(FORWARD);
}

// Function to sweep servo slowly between 60°–120°
void sweepServo() {
  servoPos += servoDir;
  if (servoPos >= 120 || servoPos <= 60) {
    servoDir = -servoDir;
  }
  sensorServo.write(servoPos);
}

void loop() {
  // Read sensors
  distance = sonar.ping_cm();
  if (distance == 0) distance = MAX_DISTANCE; // no echo → far away
  Right_Value = digitalRead(IR_RIGHT);
  Left_Value = digitalRead(IR_LEFT);

  Serial.print("Distance: "); Serial.println(distance);
  Serial.print("Right IR: "); Serial.println(Right_Value);
  Serial.print("Left IR: "); Serial.println(Left_Value);

   // ---------------------------
  // Decision Logic
  // ---------------------------

  // Too close → Move Backward + Servo Scan
  if (distance <= 10) {
    moveBackward(200);
    //sweepServo();  // scan while reversing
  }
  // Human detected in range → Move Forward + Servo Scan
  else if ((distance > 10) && (distance < 30) && Right_Value == 1 && Left_Value == 1) {
    moveForward(200);
    //sweepServo();  // scan while moving forward
  }
  // Turn RIGHT (Right IR blocked)  ✅ FIXED
  else if (Right_Value == 0 && Left_Value == 1) {
    turnRight(200);
    sensorServo.write(60);  // look right
    delay(150);
  }
  // Turn LEFT (Left IR blocked) ✅ FIXED
  else if (Right_Value == 1 && Left_Value == 0) {
    turnLeft(200);
    sensorServo.write(120); // look left
    delay(150);
  }
  // No human detected → Stop + Center servo
  else if (distance > 20) {
    stopAll();
    sensorServo.write(90);
  }


  delay(50);
}

