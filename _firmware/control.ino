#include <Servo.h>
#include <Wire.h>

int M1dirpin = 7;  
int M1steppin = 6; 
int M1en=8;  
int M2dirpin = 4;  
int M2steppin = 5;
int M2en=12;  

float wheel_dia=115;   
float wheel_base=127.5;  
int steps_rev=1600;      
float speed = 0.05;        

int customDelay,customDelayMapped; 

Servo Servo0;
Servo Servo1;
Servo ServoBar;

int pos = 0;   

String flag = "0";


void setup()
{

 Wire.begin(8);               
 Wire.onReceive(receiveEvent); 
 Serial.begin(9600);          

  pinMode(3, OUTPUT);
 
  pinMode(M1dirpin,OUTPUT);
  pinMode(M1steppin,OUTPUT);
  pinMode(M1en,OUTPUT);
  pinMode(M2dirpin,OUTPUT);
  pinMode(M2steppin,OUTPUT);
  pinMode(M2en,OUTPUT);
 
  Servo0.attach(9);
  Servo1.attach(10);
  ServoBar.attach(11);

  Servo0.write(90);
  Servo1.write(0);
  ServoBar.write(0);

  digitalWrite(M1en,LOW);
  digitalWrite(M2en,LOW);

}


void loop() {
  if(flag == "a") {
    pushHit();
    flag = "0";
  } else if(flag == "x") {
    pushXplus();
    flag = "0";
  } else if(flag == "X") {
    pushXminus();
    flag = "0";
  } else if(flag == "y") {
    pushYplus();
    flag = "0";
  } else if(flag == "Y") {
    pushYminus();
    flag = "0";
  }
}

void pushHit() {
  pushXplus();

  delay(1000);
  Servo0.write(0);
  Servo1.write(90);
  delay(1000);
  pushXminus();

  delay(3000);

  Servo0.write(90);
  Servo1.write(0);

}


void pushXplus() {
  int distance = 150;
  int steps = step(distance);
  float usDelay = (1/speed) * 70;

  digitalWrite(M1dirpin, LOW);
 
  for(int i=0; i < steps; i++){
    digitalWrite(M1steppin, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(M1steppin, LOW);
    delayMicroseconds(usDelay);
  }
}


void pushXminus() {
  int distance = 150;
  int steps = step(distance);
  float usDelay = (1/speed) * 70;

  digitalWrite(M1dirpin, HIGH);
 
  for(int i=0; i < steps; i++){
    digitalWrite(M1steppin, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(M1steppin, LOW);
    delayMicroseconds(usDelay);
  }
}


void pushYplus() {
  int distance = 30;
  int steps = step(distance);
  float usDelay = (1/speed) * 70;

  digitalWrite(M2dirpin, LOW);
 
  for(int i=0; i < steps; i++){
    digitalWrite(M2steppin, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(M2steppin, LOW);
    delayMicroseconds(usDelay);
  }
}


void pushYminus() {
  int distance = 30;
  int steps = step(distance);
  float usDelay = (1/speed) * 70;

  digitalWrite(M2dirpin, HIGH);
 
  for(int i=0; i < steps; i++){
    digitalWrite(M2steppin, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(M2steppin, LOW);
    delayMicroseconds(usDelay);
  }
}


void receiveEvent(int howMany) {
  String data="";
  while (0 <Wire.available()) {
    char c = Wire.read();     
    data += c;
  }

  if(data == "a") {
    flag = "a";
  } else if(data == "x") {
    flag = "x";
  } else if(data == "X") {
    flag = "X";
  } else if(data == "y") {
    flag = "y";
  } else if(data == "Y") {
    flag = "Y";
  }
}


int step(float distance){
  float steps = distance * steps_rev / (wheel_dia * 3.1412); 
  return int(steps);  
}


void moveForward(float distance){
  move(distance, HIGH, LOW);
}


void moveBackward(float distance){
  move(distance, LOW, HIGH);
}


void move(float distance, int dir1, int dir2){
  int steps = step(distance);
  float usDelay = (1/speed) * 70;

  digitalWrite(M1dirpin, dir1);
  digitalWrite(M2dirpin, dir2);
 
  for(int i=0; i < steps; i++){
    digitalWrite(M1steppin, HIGH);
    digitalWrite(M2steppin, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(M1steppin, LOW);
    digitalWrite(M2steppin, LOW);
    delayMicroseconds(usDelay);
  }

}