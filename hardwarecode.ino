#include <Servo.h>

int output1Value = 0;
int sen1Value = 0;
int sen2Value = 0;

// Define sensor and actuator pins
const int gas_sensor = A1;  // Gas sensor connected to Analog Pin A1
const int LDR = A0;         // LDR connected to Analog Pin A0
const int triggerPin = 6;   // Ultrasonic Trigger connected to Digital Pin 6
const int echoPin = 6;      // Ultrasonic Echo connected to Digital Pin 6
const int motionSensorPin = 9; // PIR sensor connected to Digital Pin 9
const int relayPin = 13;    // Relay connected to Digital Pin 13
const int piezoBuzzerPin = 8; // Piezo Buzzer connected to Digital Pin 8
const int redLEDPin = 4;    // Red LED connected to Digital Pin 4
const int greenLEDPin = 3;  // Green LED connected to Digital Pin 3
const int limit = 400;      // Gas sensor threshold limit

Servo servo_7; // Servo object

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // Set pin modes
  pinMode(LDR, INPUT); // Set LDR as input
  pinMode(gas_sensor, INPUT); // Set gas sensor as input
  pinMode(relayPin, OUTPUT); // Set relay pin as output
  pinMode(piezoBuzzerPin, OUTPUT); // Set piezo buzzer pin as output
  pinMode(motionSensorPin, INPUT); // Set PIR sensor as input
  pinMode(redLEDPin, OUTPUT); // Set red LED as output
  pinMode(greenLEDPin, OUTPUT); // Set green LED as output

  servo_7.attach(7, 500, 2500); // Attach servo motor to Digital Pin 7
}

void loop() {
  // Code for light intensity control, motion detection, gas detection, and servo motor operation
  // (Your previous loop code goes here)
}

// Function to read ultrasonic distance
long readUltrasonicDistance() {
  pinMode(triggerPin, OUTPUT); // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  pinMode(echoPin, INPUT); // Set echo pin as input
  return pulseIn(echoPin, HIGH); // Return the time it takes for the echo
}
