# 🤖 Human-Following Robot

A simple Arduino-based robot that automatically detects and follows a person using sensors. The robot uses an ultrasonic sensor to measure distance and IR sensors to determine the direction of the person.

## 📌 Project Description

The **Human-Following Robot** is designed to follow a person automatically without requiring manual control. An Arduino Uno processes data from the sensors and controls four DC motors to move the robot according to the person's position.

## 🛠️ Components Used

* Arduino Uno
* HW-130 Motor Driver Shield
* 4 × DC Gear Motors
* Ultrasonic Sensor
* 2 × IR Sensors
* Servo Motor
* Robot Chassis
* Battery/Power Supply
* Connecting Wires

## ⚙️ Working

1. The ultrasonic sensor detects the distance of the person.
2. The servo motor helps scan the surroundings.
3. The IR sensors detect whether the person is on the left or right side.
4. Arduino processes the sensor readings.
5. The motor driver controls the four motors.
6. The robot moves forward, left, right, or stops according to the person's position.

## 🔌 Pin Configuration

| Component          | Arduino Pin |
| ------------------ | ----------- |
| Ultrasonic Echo    | A0          |
| Ultrasonic Trigger | A1          |
| Right IR Sensor    | A2          |
| Left IR Sensor     | A3          |
| Servo Motor        | Pin 10      |

## 📚 Libraries Used

* `AFMotor`
* `Servo`
* `NewPing`

## 🎯 Features

* Automatic human detection
* Automatic movement and following
* Distance measurement using ultrasonic sensor
* Left/right direction detection
* Servo-based scanning
* Four-wheel drive movement

## 🚀 Future Improvements

* Add obstacle avoidance
* Improve human detection accuracy
* Add Bluetooth/Wi-Fi control
* Add a camera for better person tracking
* Add rechargeable battery monitoring

## 👨‍💻 Project

**Project Name:** Human-Following Robot
**Platform:** Arduino Uno
**Type:** IoT / Robotics Project

## 📄 License

This project is created for educational and learning purposes.
