#include <smorphi.h>

Smorphi my_robot;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  my_robot.BeginSmorphi();

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor_status = my_robot.module1_sensor_status(0);  // change according to whichever module and port you are using 
  Serial.println(sensor_status);
  //If sensor returns HIGH, what has happened?
  if (sensor_status == HIGH) {
    
    // your code here

  }
  //If sensor returns LOW, what has happened?
  if (sensor_status == LOW) {
    
    //your code here

  }
}
