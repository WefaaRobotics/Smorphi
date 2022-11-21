#include <smorphi.h>
#define sensorPin 16  //insert pin number

Smorphi my_robot;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin,INPUT);
  Serial.begin(115200);
  my_robot.BeginSmorphi();
  //pinMode(12,OUTPUT);//LED
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorData = digitalRead(sensorPin);
  Serial.println(sensorData);
  //If sensor returns LOW, something detected
  if (sensorData == HIGH){
    Serial.println("Nothing is in front!");
    // robot moves forward with speed 10
    my_robot.MoveForward(10);
    }
  if (sensorData == LOW) {
    Serial.println("Something is in front!");
    my_robot.stopSmorphi();
   }
}
