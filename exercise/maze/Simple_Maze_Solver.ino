#include<smorphi.h>


Smorphi my_robot;

int front_sensor_status ;
int right_sensor_status ;
int rear_sensor_status ;
int left_sensor_status ;
String last_action = "";



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  my_robot.BeginSmorphi();
}

void loop() {
  // put your main code here, to run repeatedly:
  int front_sensor_status = my_robot.module1_sensor_status(0);
  int right_sensor_status = my_robot.module1_sensor_status(4);
  int rear_sensor_status = my_robot.module3_sensor_status(6);
  int left_sensor_status = my_robot.module4_sensor_status(0);


  
  if (front_sensor_status==1 && rear_sensor_status==1 && left_sensor_status==0 && right_sensor_status==0){
    Serial.println("Move Straight");
    my_robot.MoveForward(8);
  }

  else if(front_sensor_status==0 && right_sensor_status==0){
    pivot_left();
    last_action = "pivot_left";
  }
  else if(last_action=="pivot_left" || last_action=="pivot_left" && right_sensor_status==0 ){
    pivot_left();
    delay(1500);  
    last_action="nill_pivot_left";
  }
  else if(front_sensor_status==0 && left_sensor_status==0){
    pivot_right();
    last_action = "pivot_right";
  }
  else if(last_action=="pivot_right" || last_action=="pivot_right" && left_sensor_status==0 ){
    pivot_right();
    delay(1500);  
    last_action="nill_pivot_right";
  }
  else if(last_action=="nill_pivot_right" && left_sensor_status==0 || left_sensor_status==0){
    pivot_right();
    delay(10);
    last_action="";
  }
  else if(last_action=="nill_pivot_left" && right_sensor_status==0 || right_sensor_status==0){
    pivot_left();
    delay(10);
    last_action="";
  }
  
      
  else{
    Serial.println("Move Forward");
    my_robot.MoveForward(10);
  }

  my_robot.stopSmorphi();
  my_robot.sm_reset_M1();
  my_robot.sm_reset_M2();
  my_robot.sm_reset_M3();
  my_robot.sm_reset_M4();

}
 void pivot_left(){

      Serial.println("Pivot Left");
    
      my_robot.CenterPivotLeft(80);
      Serial.println(front_sensor_status);

 }
 void pivot_right(){

      Serial.println("Pivot Right");
    
      my_robot.CenterPivotRight(80);

    
  }
