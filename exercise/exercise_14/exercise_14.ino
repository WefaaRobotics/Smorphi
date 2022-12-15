#include <smorphi.h>

Smorphi my_robot;

void setup() {
  Serial.begin(115200);
  my_robot.BeginSmorphi();
}

void loop() {
    // sensor 1-3 will be in line following mode, sensor 4 will be obstacle avoiding mode
    int sensor1_status = my_robot.module1_sensor_status(0);
    int sensor2_status = my_robot.module2_sensor_status(4);
    int sensor3_status = my_robot.module3_sensor_status(0);
    int sensor4_status = my_robot.module1_sensor_status(4);
//    Serial.println("***********");
//    Serial.println(sensor1_status);
//    Serial.println(sensor3_status);
//    Serial.println("***********");
// note that output for line following mode and obstacle avoiding mode is opposite
// if robot is in line and no obstacle in front
    if (sensor2_status == 1 && sensor4_status == 1){
      // if robot is not moving out of line
      if (sensor1_status == 0 && sensor3_status == 0){
        my_robot.MoveForward(10);
      }
      // if robot is leaning to the right
      else if (sensor1_status == 1 && sensor3_status == 0){
        my_robot.CenterPivotLeft(10);
      }
      // if robot is leaning to the left
      else if (sensor1_status == 0 && sensor3_status == 1){
        my_robot.CenterPivotRight(10);
      }
      
      my_robot.sm_reset_M1();
      my_robot.sm_reset_M2();
      my_robot.sm_reset_M3();
      my_robot.sm_reset_M4();
    }
    // if robot is not in line or there is obstacle in front
    else {
      my_robot.stopSmorphi();
    }
}
