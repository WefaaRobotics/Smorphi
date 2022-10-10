// Inclusion of necessary libraries
#include<smorphi.h>
//#include<Pixy2.h>
//#include <Pixy2I2C.h>
#include<Pixy2ICSP_ESP32.h>



// Smorphi is instantiated as my_robot
Smorphi my_robot;
// Pixy2 is instantiated as pixy
//Pixy2 pixy; 
//Pixy2I2C pixy;
Pixy2ICSP_ESP32 pixy;

// Setting up variables and required flags
int front_sensor_status ;
int right_sensor_status ;
int rear_sensor_status ;
int left_sensor_status ;
String last_action = "";
String I_shape_done = "false";
String O_shape_done = "false";
String red_color_done = "false";
String yellow_color_done = "false";
// Pixy2  color_detected status written as variable
int color_signature;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  my_robot.BeginSmorphi();
  pixy.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  sensor_initialisation();
  //Pixy functionality is included
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
      color_signature = pixy.ccc.blocks[i].m_signature;
    }
  }
  if (front_sensor_status==0 && red_color_done != "True" && color_signature == 1){ // 1 is red color
    if (I_shape_done != "True" && my_robot.sm_getShape() != 'i'){
      my_robot.sm_reset_M1();
      my_robot.sm_reset_M2();
      my_robot.sm_reset_M3();
      my_robot.sm_reset_M4();
      my_robot.I();
      front_sensor_status = my_robot.module1_sensor_status(0);
      right_sensor_status = my_robot.module1_sensor_status(4);
      rear_sensor_status = my_robot.module3_sensor_status(0);
      left_sensor_status = my_robot.module1_sensor_status(10);
      I_shape_done = "True";
      red_color_done = "True";
      
    }
  }
  if (front_sensor_status==0 && yellow_color_done != "True" && color_signature == 2){ // 2 is yellow color
    if (O_shape_done != "True" && my_robot.sm_getShape() != 'o'){
      my_robot.sm_reset_M1();
      my_robot.sm_reset_M2();
      my_robot.sm_reset_M3();
      my_robot.sm_reset_M4();
      my_robot.O();
      front_sensor_status = my_robot.module1_sensor_status(0);
      right_sensor_status = my_robot.module1_sensor_status(4);
      rear_sensor_status = my_robot.module3_sensor_status(6);
      left_sensor_status = my_robot.module4_sensor_status(0);
      O_shape_done = "True";
      yellow_color_done = "True";
      
    }
  }
  
// These conditions never execute as robot always falls under else condition    
//  my_robot.stopSmorphi();
//  my_robot.sm_reset_M1();
//  my_robot.sm_reset_M2();
//  my_robot.sm_reset_M3();
//  my_robot.sm_reset_M4();
 
}
