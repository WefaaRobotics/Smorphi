
#include <smorphi.h>
//#include <AStar32U4.h>
#define sensorPin 16

Smorphi my_robot;

unsigned long lastEvent = 0;

void setup(){
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
  my_robot.BeginSmorphi();
}

void loop (){
  int sensorData = digitalRead(sensorPin);
  Serial.println(sensorData);
  // If pin goes LOW, sound is detected
  if (sensorData == LOW){
    // If 25ms have passed since last LOW state, it means that the sound is detected and not due to any spurious sounds
    if (millis() - lastEvent > 25){
      Serial.println("Sound detected!");
      my_robot.MoveForward(10);// robot moves forward with speed 10
      delay(3000);
      my_robot.stopSmorphi();
      Serial.println("stop sm");
    }
    lastEvent = millis();

  }
}
/* CHALLENGE
it is possible to code Smorphi such that it moves forward when no sound is detected
 and move away when it detects noise (might be someone walking into the robot)*/
