#include <smorphi.h>

Smorphi my_robot;

void setup() {
  Serial.begin(115200);
  my_robot.BeginSmorphi();
}

void loop() {
    int sensor1_status = my_robot.module1_sensor_status(0);
    int sensor2_status = my_robot.module2_sensor_status(4);
    int sensor3_status = my_robot.module3_sensor_status(0);
//    Serial.println("***********");
//    Serial.println(sensor1_status);
//    Serial.println(sensor3_status);
//    Serial.println("***********");
    if (sensor2_status == 1){
      if (sensor1_status == 0 && sensor3_status == 0){
        my_robot.MoveForward(10);
      }
      else if (sensor1_status == 1 && sensor3_status == 0){
        my_robot.CenterPivotLeft(10);
      }
      else if (sensor1_status == 0 && sensor3_status == 1){
        my_robot.CenterPivotRight(10);
      }
      
      my_robot.sm_reset_M1();
      my_robot.sm_reset_M2();
      my_robot.sm_reset_M3();
      my_robot.sm_reset_M4();
    }

    else {
      my_robot.stopSmorphi();
    }
}
