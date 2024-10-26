#include <Servo.h>

int output1Value = 0;
int sen1Value = 0;
int sen2Value = 0;
int const gas_sensor = A0;
int const LDR = A1;
int limit = 50;
const int trigPin = 6;
const int echoPin = 5;         
const int threshold = 10;  // threshold to turn LED on
int SENSOR_PIN= 9;
#define RELAY_PIN  13
#define RELAY_PIN_SEC  3
long duration;
int distance;

int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

Servo myServo;

void setup()
{
   Serial.begin(9600);    //initialize serial communication
  pinMode(LDR, INPUT);   //LDR
  pinMode(gas_sensor,INPUT);        //gas sensor **** clear
  pinMode(RELAY_PIN, OUTPUT); 
  pinMode(RELAY_PIN_SEC, OUTPUT); //connected to relay done
  myServo.attach(7, 500, 2500); //servo motor
  pinMode(8,OUTPUT);      //signal to piezo buzzer
  pinMode(9, INPUT);    //signal to PIR 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  myServo.attach(7); // Defines on which pin is the servo motor attached
 
}

void loop()
{
Serial.print(" || ");
int sensor_ldr = analogRead(LDR);   // read sensor value
  if(sensor_ldr < 150){  // if sensor reading is less than threshold
    Serial.print("Light ON : LDR Value - ");
    Serial.print(sensor_ldr); 
    digitalWrite(RELAY_PIN_SEC, LOW); 
  }  
  else{ 
    Serial.print(" Light OFF : LDR Value - ");
    Serial.print(sensor_ldr); 
    digitalWrite(RELAY_PIN_SEC, HIGH);
  }
 Serial.print(" || ");
//--------------------------------------------------------------  
        //------ light & fan control --------// 
//--------------------------------------------------------------

  //If object movement is detected then the sensor value will be 1 else the value will be 0
  int sensorValue = digitalRead(SENSOR_PIN);
  if (sensorValue == HIGH)
  {
    Serial.print("Motion Detected! : " ); 
    Serial.print(sensorValue); 
    digitalWrite(RELAY_PIN, LOW);  //Relay is low level triggered relay so we need to write LOW to switch on the light
  }
  else
  {
    digitalWrite(RELAY_PIN, HIGH);  
    Serial.print("NO Motion Detected : " );
    Serial.print(sensorValue); 
  }
  Serial.print(" || ");
//---------------------------------------------------------------
       // ------- Gas Sensor --------//
//---------------------------------------------------------------

int val = analogRead(gas_sensor);      //read sensor value
  Serial.print("No Smoke at all : ");
  Serial.print(val);           //Printing in serial monitor
  if (val > 300)
    {
      tone(8, 650);
      Serial.print("Alert! Smoke Detected : ");
      Serial.print(val);
    }
  delay(300);
  noTone(8);

 //-------------------------------------------------------------- 
      //-------  Ultrasonic & servo motor  ---------//
 //------------------------------------------------------------- 
  Serial.print(" || ");
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  if (distance < 10) 
    {
      myServo.write(180);
      Serial.print("Ultrasonic : ");
      Serial.print(distance);
    }
    else 
    {
      myServo.write(0);
      Serial.print("Ultrasonic ");
      Serial.print(distance);
  }
  Serial.println(" || ");
}