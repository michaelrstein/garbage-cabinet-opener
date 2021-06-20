/* Cabinet_opener
 by Michael Stein
 Much of this code came from Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int sensor1 = 12;   // setup sensor 1 to pin 12
int sensor2 = 11;
boolean servoIsRunning = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  //setup servo to pin 9
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  Serial.println("Set servo to 0.");
    
  pinMode(12, INPUT);  //set pin 12 as input
  pinMode(11, INPUT);  //set pin 11 as input
}

void openDoor() {
  servoIsRunning = true;  
  myservo.write(180);
  //Serial.println("set to 180");
  delay(1000);
  myservo.write(0);
  //Serial.println("set to 0");
  delay(1000);
  servoIsRunning = false;
}

void loop() {
  int detectSensor1 = digitalRead(sensor1);
  int countDown = 0;
  int detectSensor2 = HIGH;
  
  if (detectSensor1 == LOW ) {
    if (servoIsRunning == true) {
      Serial.println("sensor 1 triggered but servo is running");
    } else {
      Serial.println("sensor 1 detected");
      //openDoor();
      countDown = 100;
  
      while(countDown > 0) {
        //check to see if other sensor is hit
        detectSensor2 = digitalRead(sensor2);
        if (detectSensor2 == LOW) {
          //Serial.println("sensor 2 detected");
          openDoor();
          countDown = 0;
        } else {
          countDown-- ;
        }
        //Serial.println(countDown);
        delay(10); 
      }      
    }
  } 
  delay(50);    
}  
