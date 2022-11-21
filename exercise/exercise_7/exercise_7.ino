#include <smorphi.h>

Smorphi my_robot;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  my_robot.BeginSmorphi();
}

void loop() {
  // put your main code here, to run repeatedly:
  //int sensor_status = my_robot.module1/2/3/4_sensor_status(0/2/4/6/8/10);  change the paramter according to which module and port you use
  int sensor_status = my_robot.module1_sensor_status(0);  // using sensor on module 1 port 1
  Serial.println(sensor_status);
  //If sensor returns LOW, something is in front
  if (sensor_status == HIGH){
    Serial.println("Nothing is in front!");
    // robot moves forward with speed 10
    my_robot.MoveForward(10);
    }
   if (sensor_status == LOW){
    Serial.println("Something is in front!");    
    my_robot.stopSmorphi();
   }
}
