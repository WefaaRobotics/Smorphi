#include <smorphi.h>

Smorphi my_robot;
String last_movement = "last";

void setup() {
  Serial.begin(115200);
  my_robot.BeginSmorphi();
}

void loop() {
    int sensor1_status = my_robot.module1_sensor2_status();
    int sensor2_status = my_robot.module2_sensor2_status();
    int sensor3_status = my_robot.module3_sensor2_status();
    int sensor4_status = my_robot.module4_sensor2_status();
    
//    Serial.println("***********");
//    Serial.println(sensor1_status);
//    Serial.println(sensor2_status);
//    Serial.println(sensor3_status);
//    Serial.println(sensor4_status);
//    Serial.println("***********");
    
    if (sensor1_status == 1){
       = "forward";
      if (last_movement!="backward"){
        //my_robot.MoveForward(10);
        last_movement = "forward";
      }
      else{
        last_movement = "backward";
      }
    }

    if (sensor1_status == 0 && sensor4_status == 1){

      if ((last_movement!="right") && (last_movement!="backward")){
        //my_robot.MoveLeft(10);
        last_movement = "left";
      } 
      else{
        last_movement = "backward";
      }
    }

    if (sensor2_status == 1 && sensor4_status == 0 && sensor1_status == 0){

      if (last_movement!="left"){
        //my_robot.MoveRight(10);
        last_movement = "right";
      } 
    }

    Serial.println(last_movement);

    my_robot.sm_reset_M1();
    my_robot.sm_reset_M2();
    my_robot.sm_reset_M3();
    my_robot.sm_reset_M4();
}
