#include <smorphi_single_250.h>
#include<Encoder_250.h>

Smorphi_single my_robot;

char x[5] = "";
char y[5] = "";
char w[5] = "";

String text = "";
//Encoder encoder;
String received = "";
String x_val = "0.00";
String y_val = "0.00";
String w_val = "0.00";
String cur_shape = "";
String next_shape = "";

int count = 0;
float kp= 0.1;
float kp1 = 0.01;
float cmd_x = 0;
float cmd_y = 0;
float cmd_w = 0;

float error_x;
float error_y;
float error_w;
void setup() {
  // put your setup code here, to run once:/Users/m.v.vijayagopalarao/Documents/Arduino/libraries/OTA/OTA.h
  Serial.begin(115200); 
  Serial.setTimeout(40);
  my_robot.BeginSmorphi_single();
  encoder_begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  //my_robot.MoveForward(10);
  
  evaluate_velocity_feedback();
   cur_shape = my_robot.sm_getShape();
   
   
  text = "";
  dtostrf(V_x,4,3,x);
  text += x;
  text += ",";
  dtostrf(V_y,4,3,y);
  text += y;
  text += ",";
  dtostrf(W_z,4,3,w);
  text += w;
  text+= ",";
  text+= cur_shape;
 
//Serial.println(text);
//if(Serial.available()){
received = Serial.readStringUntil('\n');

//Serial.println(received);
if(received.length()>5){
  int index1 = received.indexOf(",");
  x_val = received.substring(0,index1);

  String sub1 = received.substring(index1+1,received.length());
  int index2 = sub1.indexOf(",");
  y_val = sub1.substring(0,index2);


  String sub2 = sub1.substring(index2+1, sub1.length());
  int index3 = sub2.indexOf(",");
  w_val = sub2.substring(0,index3);

  String sub3 = sub2.substring(index3+1, sub2.length());
  int index4 = sub3.indexOf(",");
  
  next_shape = sub3.substring(0,index4);

//}

 

}
  
 text = text+","+x_val+","+y_val+","+w_val;
 
 Serial.println(text);
  //Serial.println(int(x_val.toFloat()*100));

  //if(next_shape != cur_shape){
//    if(next_shape == "1"){
//      my_robot.I();
//    }
//    else if(next_shape == "2"){
//      my_robot.O();
//    }
//    else if(next_shape == "3"){
//      my_robot.L();
//    }
  //}
  evaluate_velocity_feedback();
   error_x = kp*(x_val.toFloat() - V_x);
  error_y = kp*(y_val.toFloat() - V_y);
  error_w = kp1*(w_val.toFloat() - W_z);

  if(x_val.toFloat() == 0 &&  y_val.toFloat() == 0 && w_val.toFloat() == 0){
   
    my_robot.Move( 0,0,0,0,0,0,0,0,0,0);
  }
  else{
my_robot.Move( x_val.toFloat(), y_val.toFloat(), w_val.toFloat(),error_x,error_y,error_w,RPS_M1,RPS_M2,RPS_M3,RPS_M4);
  }
  
  //my_robot.Move(0,0.7,0);

//Serial.println(count);
}
