//Import the library to  use Servo motor
#include <ESP32Servo.h>

//Register the pin numbers for reference
//HC-SR04
const byte trig_pin=12;
const byte echo_pin=26;
//Servo motor
const byte servo_pin = 19; 
//LED 
const byte led_pin=21;

//Create an object for using Servo motor
Servo servo;

void setup() {

  //Select the mode of IO for each pin
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led_pin,OUTPUT);

  //Connect the servo motor object to the pin
  servo.attach(servo_pin);

  //Initiate the serial communication
  Serial.begin(115200);
}

void loop() {

  //Calculating distance between the hand and sensor
  long int distance=get_distance();

  //Deciding the turn on and off state of the dispenser
  if(distance<=15){
    Serial.println("Sanitizer ON");
    servo.write(180);//Change the shaft angle for dispensing
    digitalWrite(led_pin,HIGH); //Turn ON the LED
  }
  else{
    Serial.println("Sanitizer OFF");
    servo.write(0);//Change the shaft angle for turning off the dispenser
    digitalWrite(led_pin,LOW);//Turn OFF the LED
  }

  delay(10); //Speed up the simulation
}

//User-defined function to calculate the distance between the hand and sensor
int get_distance(){
  
  //Clear the noise in case
  digitalWrite(trig_pin , LOW);
  delayMicroseconds(2);

  //Sending trigger burst
  digitalWrite(trig_pin , HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin , LOW);

  //Waiting for response : checking HIGH duration of echo pin
  long int duration = pulseIn(echo_pin , HIGH);
  
  //Convert the time to distance
  long int distance = (duration * 0.034) / 2;

  return distance;
}