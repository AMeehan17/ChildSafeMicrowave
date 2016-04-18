/*
  Child-proof Microwave Arduino Solution

 Incorporates a system of pushpin buttons with different 
 colors (red, blue, yellow) that allow people older than 7 to use a
 microwave safely and intuitively. 
 
 White LED - Simulates when the microwave is being run. 
 Red Button - Simulates the microwave's red start/unlock button
 Blue Button - Simulates the microwave's blue start/unlock button
 Yellow Button - Simulates the microwave's yellow start/unlock button
 Servo - Simulates both the microwave's lock/unlock AND opening feature
 

 created April 16, 2016
 by Andrew Meehan
 
 This example code is in the public domain.
*/

#include <Servo.h>

Servo doorLatch; // create servo object to control a servo that serves as the door's
// open/close mechanism as well as locking the door

// constants won't change. They're used here to
// set pin numbers:
const int redButtonPin = 13; // the number of the red pushbutton pin
const int blueButtonPin = 12; // the number of the blue pushbutton pin
const int yellowButtonPin = 4; // the number of the yellow pushbutton pin

const int RledWhitePin = 9; // the number of the red pin for the microwave LED
const int GledWhitePin = 11; // the number of the green pin for the microwave LED
const int BledWhitePin = 10; // the number of the blue pin for the microwave LED

const int servoPin = 3; // the number of the servo pin

// variables will change:
int buttonStateRed = HIGH;         // variable for reading the pushbutton status
int buttonStateBlue = HIGH;
int buttonStateYellow = HIGH;
int microwaveCounter = 0;
int whiteR = 0; // variable for red LED cooking simulation
int whiteG = 0; // variable for green LED cooking simulation
int whiteB = 0; // variable for blue LED cooking simulation
int servoClosed = 0; // variable for servo's locked angle
int servoOpen = 100; // variable for servo's open angle

int redStart = 1;
int blueStart = 2;
int yellowStart = 3;
int startColor = 0;

int waiter = 0; // counter to wait for food to cool
int unlockedChoice = 0; // color button pressed for unlocking the microwave

int changeSeed = 0; // seed number for random number generator


void setup() {
  // attaches servo
  doorLatch.attach(3);
  doorLatch.write(0);
  Serial.begin(9600); //reads serial information
  
  // initialize the microwave LED pins as an outputs:
  pinMode(RledWhitePin, OUTPUT);
  pinMode(GledWhitePin, OUTPUT);
  pinMode(BledWhitePin, OUTPUT);
  // initialize the colored pushbutton pins as an inputs:
  pinMode(redButtonPin, INPUT);
  pinMode(blueButtonPin, INPUT);
  pinMode(yellowButtonPin, INPUT);
  Serial.println("Setup Complete");
}  

void loop() {
  doorLatch.write(0);
  // read the state of the red pushbutton value:
  buttonStateRed = digitalRead(redButtonPin);
  // check if red pushbutton is pressed.
  // if red is, the redButtonState is HIGH:
  if (buttonStateRed == LOW) {
    Serial.println("Red Start");
    startColor = redStart;
    // simulates cooking for 10 seconds:
    microwaveSimple();
    waitForUser();
  }
  
  // read the state of the blue pushbutton value:
   buttonStateBlue = digitalRead(blueButtonPin);
  // check if the blue pushbutton is pressed.
  // if blue is, the blueButtonState is HIGH:
  if (buttonStateBlue == LOW) {
    Serial.println("Blue Start");
   // simulates cooking for 10 seconds:
   microwaveSimple();
   waitForUser();
  }
  
  // read the state of the yellow pushbutton vlaue:
   buttonStateYellow = digitalRead(yellowButtonPin);
  // check if the yellow pushbutton is pressed.
  // if yellow is, the yellowButtonState is HIGH:
  if (buttonStateYellow == LOW){
    Serial.println("Yellow Start");
    // simulates cooking for 10 seconds:
    microwaveSimple();
    waitForUser();
    
}
Serial.println("looping");
}


void microwave() {
  Serial.println("microwaving");
  // this makes the color change while simulating a 10 second microwave
 while (microwaveCounter < 10000){
   changeSeed = random(0, 10000);
   randomSeed(changeSeed);
   whiteR = random(0, 255);
   whiteG = random(0, 255);
   whiteB = random(0, 255);
   
   analogWrite(RledWhitePin, whiteR);
   analogWrite(GledWhitePin, whiteG);
   analogWrite(BledWhitePin, whiteB);
   
   delay(1);
   microwaveCounter++;
 }
   microwaveCounter = 0;
   analogWrite(RledWhitePin, 0);
   analogWrite(GledWhitePin, 0);
   analogWrite(BledWhitePin, 0);
   Serial.println("microwaveCounter full");
}
 
 void microwaveSimple() {
   Serial.println("Simple Microwaving");
   digitalWrite(RledWhitePin, HIGH);
   delay(10000);
   digitalWrite(RledWhitePin, LOW);
 }
 
 void openMicrowave() {
   Serial.println("opening microwave");
 doorLatch.write(170);
 }
 
 void waitForUser() {
  while (waiter < 50){
    buttonStateRed = digitalRead(redButtonPin);
      if (buttonStateRed == LOW){
           Serial.println("red pressed to unlock");
           Serial.println(startColor);
           unlockedChoice = redStart;
         if (unlockedChoice == startColor){
           openMicrowave();
           reset();
          }
         }
         delay(1000);
    buttonStateBlue = digitalRead(blueButtonPin);
      if (buttonStateBlue == LOW){
          Serial.println("blue pressed to unlock");
          Serial.println(startColor);
          unlockedChoice = blueStart;
        if (unlockedChoice == startColor){
          openMicrowave;
          reset();
         }
        }
        delay(1000);
    buttonStateYellow = digitalRead(yellowButtonPin);
      if (buttonStateYellow == LOW){
          Serial.println("yellow pressed to unlock");
          Serial.println(startColor);
          unlockedChoice = yellowStart;
        if (unlockedChoice == startColor){
          openMicrowave;
          reset();
         }
        }
        delay(1000);
  waiter++;
  }
  Serial.println("waiter full, opening...");
  openMicrowave();
  return;
 }
    
 void reset(){
  Serial.println("Resetting");
  delay(5000);
  loop();
 }
