#include <smorphi.h>

Smorphi my_robot;

unsigned long lastEvent = 0;

void setup(){
  Serial.begin(115200);
  my_robot.BeginSmorphi();
}

void loop (){
  // int sensor_status = my_robot.module1/2/3/4_sensor_status(0/2/4/6/8/10);  change the paramter according to which module and port you use
  int sensor_status = my_robot.module1_sensor_status(0);  // using sensor on module 1 port 1
  Serial.println(sensor_status);
  // If pin goes LOW, sound is detected
  if (sensor_status == 0){
    Serial.println("Sound detected");
    // If 25ms have passed since last LOW state, it means that the sound is detected and not due to any spurious sounds
    if (millis() - lastEvent > 25){
      Serial.println("Sound detected!");
      my_robot.MoveForward(10); // robot moves forward with speed 10 for 3 seconds
      delay(3000);
      Serial.println("Stop Smorphi!");
      my_robot.stopSmorphi();

    }
    lastEvent = millis();
  }
}

/* CHALLENGE
it is possible to code Smorphi such that it moves forward when no sound is detected
 and move away when it detects noise (might be someone walking into the robot)*/
