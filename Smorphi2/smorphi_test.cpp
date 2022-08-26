/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <smorphi.h>

//Define the I2C address for each slave board
Adafruit_MotorShield AFMS1 (0x60);
Adafruit_MotorShield AFMS2 (0x61);
Adafruit_MotorShield AFMS3 (0x62);
Adafruit_MotorShield AFMS4 (0x63);

//Initialization for I/O expander on each slave board
Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
Adafruit_MCP23X17 mcp3;
Adafruit_MCP23X17 mcp4;

//Adafruit calling (Swapped motor 3 & 4)
Adafruit_DCMotor *M11 = AFMS1.getMotor(1);
Adafruit_DCMotor *M12 = AFMS1.getMotor(2);
Adafruit_DCMotor *M13 = AFMS1.getMotor(4);
Adafruit_DCMotor *M14 = AFMS1.getMotor(3);

Adafruit_DCMotor *M21 = AFMS2.getMotor(1);
Adafruit_DCMotor *M22 = AFMS2.getMotor(2);
Adafruit_DCMotor *M23 = AFMS2.getMotor(4);
Adafruit_DCMotor *M24 = AFMS2.getMotor(3);

Adafruit_DCMotor *M31 = AFMS3.getMotor(1);
Adafruit_DCMotor *M32 = AFMS3.getMotor(2);
Adafruit_DCMotor *M33 = AFMS3.getMotor(4);
Adafruit_DCMotor *M34 = AFMS3.getMotor(3);

Adafruit_DCMotor *M41 = AFMS4.getMotor(1);
Adafruit_DCMotor *M42 = AFMS4.getMotor(2);
Adafruit_DCMotor *M43 = AFMS4.getMotor(4);
Adafruit_DCMotor *M44 = AFMS4.getMotor(3);



void Smorphi::BeginSmorphi()
{

//4 interrupt pins on master board
  pinMode(INT_PIN_1, INPUT); //for module 1
  pinMode(INT_PIN_2, INPUT); //for module 2
  pinMode(INT_PIN_3, INPUT); //for module 3
  pinMode(INT_PIN_4, INPUT); //for module 4

//begin the pwm driver
  AFMS1.begin();
  AFMS2.begin();
  AFMS3.begin();
  AFMS4.begin();

//begin the I/O expander
  mcp1.begin_I2C(0x20); //LSM bit swapped for GPIO expander and PWM driver
  mcp2.begin_I2C(0x21);
  mcp3.begin_I2C(0x22);
  mcp4.begin_I2C(0x23);

//setup the solenoids on each slave board
  mcp1.pinMode(14, INPUT_PULLUP);
  mcp1.pinMode(15, INPUT_PULLUP);

  mcp2.pinMode(14, INPUT_PULLUP);

  mcp3.pinMode(14, INPUT_PULLUP);
  mcp3.pinMode(15, INPUT_PULLUP);

  mcp4.pinMode(14, INPUT_PULLUP);

//setup for interrupts
  mcp1.setupInterrupts(true, false, LOW);
  mcp2.setupInterrupts(true, false, LOW);
  mcp3.setupInterrupts(true, false, LOW);
  mcp4.setupInterrupts(true, false, LOW);

  

//setup for sensor pins
  mcp1.pinMode(0, INPUT_PULLUP);
  mcp1.pinMode(2, INPUT_PULLUP);
  mcp1.pinMode(4, INPUT_PULLUP);
  mcp1.pinMode(6, INPUT_PULLUP);
  mcp1.pinMode(8, INPUT_PULLUP);
  mcp1.pinMode(10, INPUT_PULLUP);

  mcp2.pinMode(0, INPUT_PULLUP);
  mcp2.pinMode(2, INPUT_PULLUP);
  mcp2.pinMode(4, INPUT_PULLUP);
  mcp2.pinMode(6, INPUT_PULLUP);
  mcp2.pinMode(8, INPUT_PULLUP);
  mcp2.pinMode(10, INPUT_PULLUP);

  mcp3.pinMode(0, INPUT_PULLUP);
  mcp3.pinMode(2, INPUT_PULLUP);
  mcp3.pinMode(4, INPUT_PULLUP);
  mcp3.pinMode(6, INPUT_PULLUP);
  mcp3.pinMode(8, INPUT_PULLUP);
  mcp3.pinMode(10, INPUT_PULLUP);

  mcp4.pinMode(0, INPUT_PULLUP);
  mcp4.pinMode(2, INPUT_PULLUP);
  mcp4.pinMode(4, INPUT_PULLUP);
  mcp4.pinMode(6, INPUT_PULLUP);
  mcp4.pinMode(8, INPUT_PULLUP);
  mcp4.pinMode(10, INPUT_PULLUP);
}


void Smorphi::set_interrupt_pin(){
//Initialize sensor pins
  mcp1.setupInterruptPin(0, LOW);
  mcp1.setupInterruptPin(2, LOW);
  mcp1.setupInterruptPin(4, LOW);
  mcp1.setupInterruptPin(6, LOW);
  mcp1.setupInterruptPin(8, LOW);
  mcp1.setupInterruptPin(10, LOW);

  mcp2.setupInterruptPin(0, LOW);
  mcp2.setupInterruptPin(2, LOW);
  mcp2.setupInterruptPin(4, LOW);
  mcp2.setupInterruptPin(6, LOW);
  mcp2.setupInterruptPin(8, LOW);
  mcp2.setupInterruptPin(10, LOW);

  mcp3.setupInterruptPin(0, LOW);
  mcp3.setupInterruptPin(2, LOW);
  mcp3.setupInterruptPin(4, LOW);
  mcp3.setupInterruptPin(6, LOW);
  mcp3.setupInterruptPin(8, LOW);
  mcp3.setupInterruptPin(10, LOW);

  mcp4.setupInterruptPin(0, LOW);
  mcp4.setupInterruptPin(2, LOW);
  mcp4.setupInterruptPin(4, LOW);
  mcp4.setupInterruptPin(6, LOW);
  mcp4.setupInterruptPin(8, LOW);
  mcp4.setupInterruptPin(10, LOW);

//Initialize solenoid status according to shapes
  if (sm_getShape() == 'o'){
    mcp1.setupInterruptPin(14, HIGH);
    mcp1.setupInterruptPin(15, LOW);
    mcp2.setupInterruptPin(14, LOW);
    mcp3.setupInterruptPin(14, HIGH);
    mcp3.setupInterruptPin(15, LOW);
    mcp4.setupInterruptPin(14, HIGH);
  }

  if (sm_getShape() == 'i'){
    mcp1.setupInterruptPin(14, HIGH);
    mcp1.setupInterruptPin(15, LOW);
    mcp2.setupInterruptPin(14, HIGH);
    mcp3.setupInterruptPin(14, LOW);
    mcp3.setupInterruptPin(15, LOW);
    mcp4.setupInterruptPin(14, HIGH);
  }

  if (sm_getShape() == 'l'){
    mcp1.setupInterruptPin(14, HIGH);
    mcp1.setupInterruptPin(15, LOW);
    mcp2.setupInterruptPin(14, HIGH);
    mcp3.setupInterruptPin(14, LOW);
    mcp3.setupInterruptPin(15, HIGH);
    mcp4.setupInterruptPin(14, LOW);
  }

  if (sm_getShape() == 'z'){
    mcp1.setupInterruptPin(14, HIGH);
    mcp1.setupInterruptPin(15, HIGH);
    mcp2.setupInterruptPin(14, LOW);
    mcp3.setupInterruptPin(14, LOW);
    mcp3.setupInterruptPin(15, HIGH);
    mcp4.setupInterruptPin(14, LOW);
  }

  if (sm_getShape() == 't'){
    mcp1.setupInterruptPin(14, HIGH);
    mcp1.setupInterruptPin(15, HIGH);
    mcp2.setupInterruptPin(14, LOW);
    mcp3.setupInterruptPin(14, HIGH);
    mcp3.setupInterruptPin(15, LOW);
    mcp4.setupInterruptPin(14, LOW);
  }

  if (sm_getShape() == 's'){
    mcp1.setupInterruptPin(14, LOW);
    mcp1.setupInterruptPin(15, HIGH);
    mcp2.setupInterruptPin(14, LOW);
    mcp3.setupInterruptPin(14, HIGH);
    mcp3.setupInterruptPin(15, LOW);
    mcp4.setupInterruptPin(14, HIGH);
  }

  if (sm_getShape() == 'j'){
    mcp1.setupInterruptPin(14, HIGH);
    mcp1.setupInterruptPin(15, LOW);
    mcp2.setupInterruptPin(14, LOW);
    mcp3.setupInterruptPin(14, HIGH);
    mcp3.setupInterruptPin(15, HIGH);
    mcp4.setupInterruptPin(14, LOW);
  }
}


// setup for sensor status check for module1

int Smorphi::module1_sensor_status(int pin_no){
  int pin_status;
  pin_status = mcp1.digitalRead(pin_no);
  return pin_status;
}

// setup for sensor status check for module2
int Smorphi::module2_sensor_status(int pin_no){
  int pin_status;
  pin_status = mcp2.digitalRead(pin_no);
  return pin_status;
}

// setup for sensor status check for module3
int Smorphi::module3_sensor_status(int pin_no){
  int pin_status;
  pin_status = mcp3.digitalRead(pin_no);
  return pin_status;
}

// setup for sensor status check for module4
int Smorphi::module4_sensor_status(int pin_no){
  int pin_status;
  pin_status = mcp4.digitalRead(pin_no);
  return pin_status;
}

//sensor with interrupt test on module 1
int Smorphi::module1_sensor_interrupt(){
  if (!digitalRead(INT_PIN_1)){
    // Serial.println(digitalRead(INT_PIN_1));
    int interrupt_pin_value = mcp1.getLastInterruptPin();
    return interrupt_pin_value;
  }
  else{
    // Serial.println(digitalRead(INT_PIN_1));
    return 255;
  }
}

// mapping fomula: (x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min
double Smorphi::mapPosRanges(int ipSpeed) //map user's input linear velocity to robot's actual positive linear velocity
{
  double mappedSpeed = ipSpeed * (sm_max_linear_speed) / 100;
  return mappedSpeed;
}

double Smorphi::mapNegRanges(int ipSpeed) //map user's input linear velocity to robot's actual negative linear velocity
{
  double mappedSpeed = ipSpeed * (-sm_max_linear_speed) / 100;
  return mappedSpeed;
}

double Smorphi::mapPosAng(int ipSpeed) //map user's input angular velocity to robot's actual positive angular velocity
{
  double mappedSpeed = ipSpeed * (sm_max_angular_speed) / 100;
  return mappedSpeed;
}

double Smorphi::mapNegAng(int ipSpeed) //map user's input angular velocity to robot's actual negative angular velocity
{
  double mappedSpeed = ipSpeed * (-sm_max_angular_speed) / 100;
  return mappedSpeed;
}

int Smorphi::map_lv_PWM(double ipSpeed) //map robot's linear velocity to PWM
{
  if (ipSpeed == 0)
  {
    int mappedPWM = 0;
    return mappedPWM;
  }
  else
  {
    int mappedPWM = ipSpeed * (sm_pwm_upper_limit - sm_pwm_lower_limit) / sm_max_linear_speed + sm_pwm_lower_limit;
    return mappedPWM;
  }
  
}

int Smorphi::map_ang_PWM(double ipSpeed) //map robot's angular velocity to PWM
{
  if (ipSpeed == 0)
  {
    int mappedPWM = 0;
    return mappedPWM;
  }
  else
  {
    int mappedPWM = ipSpeed * (sm_pwm_upper_limit - sm_pwm_lower_limit) / sm_max_angular_speed + sm_pwm_lower_limit;
    return mappedPWM;
  }
  
}

int Smorphi::map_turn_PWM(double ipSpeed) //map robot's curve velocity to PWM
{
  if (ipSpeed == 0)
  {
    int mappedPWM = 0;
    return mappedPWM;
  }
  else
  {
    int mappedPWM = ipSpeed * (sm_pwm_upper_limit - sm_pwm_lower_limit) / sm_max_curve_speed + sm_pwm_lower_limit; 
    return mappedPWM;
  }
  
}

//get solenoid feedback
int Smorphi::sm_feedback(int solenoid_feedback){ 
  if (solenoid_feedback == 1){
    feedback_val = mcp1.digitalRead(14);
  }
  else if (solenoid_feedback == 2) {
    feedback_val = mcp1.digitalRead(15);
  }
  else if (solenoid_feedback == 3) {
    feedback_val = mcp2.digitalRead(14);
  }
  else if (solenoid_feedback == 4) {
    feedback_val = mcp3.digitalRead(14);
  }
  else if (solenoid_feedback == 5) {
    feedback_val = mcp3.digitalRead(15);
  }
  else if (solenoid_feedback == 6) {
    feedback_val = mcp4.digitalRead(14);
  }
  
  return feedback_val;
}

//set HIGH or LOW to the solenoid
void Smorphi::sm_solenoid_set(int solenoid_unlock, bool status){ 
  if (solenoid_unlock == 1){
    AFMS1.setPin(0, status);
  }
  else if (solenoid_unlock == 2){
    AFMS1.setPin(1, status);
  }
  else if (solenoid_unlock == 3){
    AFMS2.setPin(0, status);
  }
  else if (solenoid_unlock == 4){
    AFMS3.setPin(0, status);
  }
  else if (solenoid_unlock == 5){
    AFMS3.setPin(1, status);
  }
  else if (solenoid_unlock == 6){
    AFMS4.setPin(0, status);
  }
  
}

//get the current shape 
char Smorphi::sm_getShape(){ 
  if (sm_feedback(1)==0 && sm_feedback(2)==1 && sm_feedback(3)==0 && sm_feedback(4)==1 && sm_feedback(5)==1 && sm_feedback(6)==0){
    robot_shape = 'i';
  }

  else if ((sm_feedback(1)==0 && sm_feedback(2)==1 && sm_feedback(3)==0 && sm_feedback(4)==1 && sm_feedback(5)==0 && sm_feedback(6)==1)){
    robot_shape = 'l';
  }

  else if (sm_feedback(1)==0 && sm_feedback(2)==0 && sm_feedback(3)==1 && sm_feedback(4)==1 && sm_feedback(5)==0 && sm_feedback(6)==1){
    robot_shape = 'z';
  }

  else if (sm_feedback(1)==0 && sm_feedback(2)==1 && sm_feedback(3)==1 && sm_feedback(4)==0 && sm_feedback(5)==1 && sm_feedback(6)==0){
    robot_shape = 'o';
  }

  else if (sm_feedback(1)==0 && sm_feedback(2)==0 && sm_feedback(3)==1 && sm_feedback(4)==0 && sm_feedback(5)==1 && sm_feedback(6)==1){
    robot_shape = 't';
  }

  else if (sm_feedback(1)==1 && sm_feedback(2)==0 && sm_feedback(3)==1 && sm_feedback(4)==0 && sm_feedback(5)==1 && sm_feedback(6)==0){
    robot_shape = 's';
  }

  else if (sm_feedback(1)==0 && sm_feedback(2)==1 && sm_feedback(3)==1 && sm_feedback(4)==0 && sm_feedback(5)==0 && sm_feedback(6)==1){
    robot_shape = 'j';
  }

  return robot_shape;
}

//Kinematic equations for all shapes
void Smorphi::sm_velocity_handler(float sm_req_linear_speed_x, float sm_req_linear_speed_y, float sm_req_angular_speed)
{
  float v_x = sm_req_linear_speed_x;
  float v_y = sm_req_linear_speed_y;
  float w   = sm_req_angular_speed;

  char shape = sm_getShape();

  if (shape == 'o')
  {
    //Module 1 
    sm_lv_M1FL  =  ( v_x - v_y - ( sm_wheel_x + sm_wheel_y) * w ); 
    sm_lv_M1FR  =  ( v_x + v_y + 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ); 
    sm_lv_M1RL  =  ( v_x + v_y + 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ); 
    sm_lv_M1RR  =  ( v_x - v_y + ( sm_wheel_x + sm_wheel_y) * w ); 

    // Module 2
    sm_lv_M2FL  =  ( v_x - v_y + 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  ( v_x + v_y + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  ( v_x + v_y - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  ( v_x - v_y + 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 3
    sm_lv_M3FL  =  ( v_x - v_y - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3FR  =  ( v_x + v_y - 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RL  =  ( v_x + v_y - 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RR  =  ( v_x - v_y + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 4
    sm_lv_M4FL  =  ( v_x - v_y - 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4FR  =  ( v_x + v_y + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RL  =  ( v_x + v_y - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RR  =  ( v_x - v_y - 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w );
    

    // Serial.println("=========Linear_Velocity==========");
    // Serial.println(sm_lv_M1FL,3);
    // Serial.println(sm_lv_M1FR,3);
    // Serial.println(sm_lv_M1RL,3);
    // Serial.println(sm_lv_M1RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M2FL,3);
    // Serial.println(sm_lv_M2FR,3);
    // Serial.println(sm_lv_M2RL,3);
    // Serial.println(sm_lv_M2RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M3FL,3);
    // Serial.println(sm_lv_M3FR,3);
    // Serial.println(sm_lv_M3RL,3);
    // Serial.println(sm_lv_M3RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M4FL,3);
    // Serial.println(sm_lv_M4FR,3);
    // Serial.println(sm_lv_M4RL,3);
    // Serial.println(sm_lv_M4RR,3); 
    // Serial.println("=========Linear_Velocity==========");

  }

  else if (shape == 's')
  {
    // Module 1
    sm_lv_M1FL  =  (-v_x + v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FR  =  (-v_x - v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RL  =  (-v_x - v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RR  =  (-v_x + v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );


    // Module 2
    sm_lv_M2FL  =  (v_x - v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  (v_x + v_y + 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  (v_x + v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  (v_x - v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );


    // Module 3
    sm_lv_M3FL  =  ( v_x + v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3FR  =  (-v_x + v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RL  =  (-v_x + v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RR  =  ( v_x + v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );


    // Module 4
    sm_lv_M4FL  =  ( v_x + v_y - 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4FR  =  (-v_x + v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RL  =  (-v_x + v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RR  =  ( v_x + v_y - 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Serial.println("=========Linear_Velocity==========");
    // Serial.println(sm_lv_M1FL,3);
    // Serial.println(sm_lv_M1FR,3);
    // Serial.println(sm_lv_M1RL,3);
    // Serial.println(sm_lv_M1RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M2FL,3);
    // Serial.println(sm_lv_M2FR,3);
    // Serial.println(sm_lv_M2RL,3);
    // Serial.println(sm_lv_M2RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M3FL,3);
    // Serial.println(sm_lv_M3FR,3);
    // Serial.println(sm_lv_M3RL,3);
    // Serial.println(sm_lv_M3RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M4FL,3);
    // Serial.println(sm_lv_M4FR,3);
    // Serial.println(sm_lv_M4RL,3);
    // Serial.println(sm_lv_M4RR,3); 
    // Serial.println("=========Linear_Velocity==========");
    

  }

  else if (shape == 'z')
  {
    // Module 1
    sm_lv_M1FL  =  (-v_x + v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FR  =  (-v_x - v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RL  =  (-v_x - v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RR  =  (-v_x + v_y + 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );


    // Module 2
    sm_lv_M2FL  =  (v_x - v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  (v_x + v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  (v_x + v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  (v_x - v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );


    // Module 3
    sm_lv_M3FL  =  (-v_x + v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3FR  =  (-v_x - v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RL  =  (-v_x - v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RR  =  (-v_x + v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );


    // Module 4
    sm_lv_M4FL  =  (v_x - v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4FR  =  (v_x + v_y + 0.085  * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RL  =  (v_x + v_y + 0.085  * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RR  =  (v_x - v_y + 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Serial.println("=========Linear_Velocity==========");
    // Serial.println(sm_lv_M1FL,3);
    // Serial.println(sm_lv_M1FR,3);
    // Serial.println(sm_lv_M1RL,3);
    // Serial.println(sm_lv_M1RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M2FL,3);
    // Serial.println(sm_lv_M2FR,3);
    // Serial.println(sm_lv_M2RL,3);
    // Serial.println(sm_lv_M2RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M3FL,3);
    // Serial.println(sm_lv_M3FR,3);
    // Serial.println(sm_lv_M3RL,3);
    // Serial.println(sm_lv_M3RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M4FL,3);
    // Serial.println(sm_lv_M4FR,3);
    // Serial.println(sm_lv_M4RL,3);
    // Serial.println(sm_lv_M4RR,3); 
    // Serial.println("=========Linear_Velocity==========");

  }

  else if (shape == 'i')
  {
    // Module 1
    sm_lv_M1FL  =  ( v_x - v_y - 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FR  =  ( v_x + v_y + 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RL  =  ( v_x + v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RR  =  ( v_x - v_y - 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 2
    sm_lv_M2FL  =  ( v_x - v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  ( v_x + v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  ( v_x + v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  ( v_x - v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 3
    sm_lv_M3FL  =  ( -v_x + v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3FR  =  ( -v_x - v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RL  =  ( -v_x - v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RR  =  ( -v_x + v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 4
    sm_lv_M4FL  =  ( -v_x + v_y - 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4FR  =  ( -v_x - v_y + 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RL  =  ( -v_x - v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RR  =  ( -v_x + v_y - 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Serial.println("=========Linear_Velocity==========");
    // Serial.println(sm_lv_M1FL,3);
    // Serial.println(sm_lv_M1FR,3);
    // Serial.println(sm_lv_M1RL,3);
    // Serial.println(sm_lv_M1RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M2FL,3);
    // Serial.println(sm_lv_M2FR,3);
    // Serial.println(sm_lv_M2RL,3);
    // Serial.println(sm_lv_M2RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M3FL,3);
    // Serial.println(sm_lv_M3FR,3);
    // Serial.println(sm_lv_M3RL,3);
    // Serial.println(sm_lv_M3RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M4FL,3);
    // Serial.println(sm_lv_M4FR,3);
    // Serial.println(sm_lv_M4RL,3);
    // Serial.println(sm_lv_M4RR,3); 
    // Serial.println("=========Linear_Velocity==========");

  }



  else if (shape == 'l')
  {
    // Module 1
    sm_lv_M1FL  =  ( v_x - v_y - 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FR  =  ( v_x + v_y + 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RL  =  ( v_x + v_y + 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RR  =  ( v_x - v_y - 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 2
    sm_lv_M2FL  =  ( v_x - v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  ( v_x + v_y + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  ( v_x + v_y - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  ( v_x - v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 3
    sm_lv_M3FL  =  ( -v_x + v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3FR  =  ( -v_x - v_y + 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RL  =  ( -v_x - v_y + 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RR  =  ( -v_x + v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 4
    sm_lv_M4FL  =  ( v_x - v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4FR  =  ( v_x + v_y + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RL  =  ( v_x + v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RR  =  ( v_x - v_y + 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Serial.println("=========Linear_Velocity==========");
    // Serial.println(sm_lv_M1FL,3);
    // Serial.println(sm_lv_M1FR,3);
    // Serial.println(sm_lv_M1RL,3);
    // Serial.println(sm_lv_M1RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M2FL,3);
    // Serial.println(sm_lv_M2FR,3);
    // Serial.println(sm_lv_M2RL,3);
    // Serial.println(sm_lv_M2RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M3FL,3);
    // Serial.println(sm_lv_M3FR,3);
    // Serial.println(sm_lv_M3RL,3);
    // Serial.println(sm_lv_M3RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M4FL,3);
    // Serial.println(sm_lv_M4FR,3);
    // Serial.println(sm_lv_M4RL,3);
    // Serial.println(sm_lv_M4RR,3); 
    // Serial.println("=========Linear_Velocity==========");

  }

  else if (shape == 'j')
  {
    // Module 1
    sm_lv_M1FL  =  ( v_x - v_y - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FR  =  ( v_x + v_y + 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RL  =  ( v_x + v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RR  =  ( v_x - v_y + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 2
    sm_lv_M2FL  =  ( v_x - v_y + 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  ( v_x + v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  ( v_x + v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  ( v_x - v_y + 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 3
    sm_lv_M3FL  =  ( v_x - v_y - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3FR  =  ( v_x + v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RL  =  ( v_x + v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RR  =  ( v_x - v_y + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 4
    sm_lv_M4FL  =  (-v_x + v_y + 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4FR  =  (-v_x - v_y + 0.255 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RL  =  (-v_x - v_y + 0.255 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RR  =  (-v_x + v_y + 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Serial.println("=========Linear_Velocity==========");
    // Serial.println(sm_lv_M1FL,3);
    // Serial.println(sm_lv_M1FR,3);
    // Serial.println(sm_lv_M1RL,3);
    // Serial.println(sm_lv_M1RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M2FL,3);
    // Serial.println(sm_lv_M2FR,3);
    // Serial.println(sm_lv_M2RL,3);
    // Serial.println(sm_lv_M2RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M3FL,3);
    // Serial.println(sm_lv_M3FR,3);
    // Serial.println(sm_lv_M3RL,3);
    // Serial.println(sm_lv_M3RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M4FL,3);
    // Serial.println(sm_lv_M4FR,3);
    // Serial.println(sm_lv_M4RL,3);
    // Serial.println(sm_lv_M4RR,3); 
    // Serial.println("=========Linear_Velocity==========");

  }

  else if (shape == 't')
  {
    // Module 1
    // sm_lv_M1FL  =  -(-v_x - v_y - 0.1275 * w - ( sm_wheel_x + sm_wheel_y) * w );
    // sm_lv_M1FR  =  -( v_x - v_y - 0.1275 * w + ( sm_wheel_x + sm_wheel_y) * w );
    // sm_lv_M1RL  =  -( v_x - v_y - 0.1275 * w - ( sm_wheel_x + sm_wheel_y) * w );
    // sm_lv_M1RR  =  -(-v_x - v_y - 0.1275 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FL  =  ( v_x + v_y + 0.1275 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FR  =  (-v_x + v_y + 0.1275 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RL  =  (-v_x + v_y + 0.1275 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RR  =  ( v_x + v_y + 0.1275 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 2
    sm_lv_M2FL  =  (v_x - v_y + 0.2125 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  (v_x + v_y + 0.1275 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  (v_x + v_y + 0.1275 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  (v_x - v_y + 0.2125 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 3
    sm_lv_M3FL  =  (v_x - v_y + 0.0425  * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3FR  =  (v_x + v_y - 0.0425  * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RL  =  (v_x + v_y - 0.0425  * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M3RR  =  (v_x - v_y + 0.0425  * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 4
    sm_lv_M4FL  =  (-v_x + v_y + 0.1275 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4FR  =  (-v_x - v_y + 0.2125 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RL  =  (-v_x - v_y + 0.2125 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M4RR  =  (-v_x + v_y + 0.1275 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Serial.println("==========Linear_Velocity==========");
    // Serial.println(sm_lv_M1FL,3);
    // Serial.println(sm_lv_M1FR,3);
    // Serial.println(sm_lv_M1RL,3);
    // Serial.println(sm_lv_M1RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M2FL,3);
    // Serial.println(sm_lv_M2FR,3);
    // Serial.println(sm_lv_M2RL,3);
    // Serial.println(sm_lv_M2RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M3FL,3);
    // Serial.println(sm_lv_M3FR,3);
    // Serial.println(sm_lv_M3RL,3);
    // Serial.println(sm_lv_M3RR,3);
    // Serial.println("------------------");
    // Serial.println(sm_lv_M4FL,3);
    // Serial.println(sm_lv_M4FR,3);
    // Serial.println(sm_lv_M4RL,3);
    // Serial.println(sm_lv_M4RR,3); 
    // Serial.println("==========Linear_Velocity==========");

  }

}


//map velocity after kinematics to pwm
void Smorphi::sm_pwm_handler(int flag)
{
    // Serial.println("Entered PWM Handler");

    if(flag==0){
      //Module 1
      sm_PWM_M1FL = map_lv_PWM(abs(sm_lv_M1FL));
      sm_PWM_M1FR = map_lv_PWM(abs(sm_lv_M1FR));
      sm_PWM_M1RR = map_lv_PWM(abs(sm_lv_M1RR));
      sm_PWM_M1RL = map_lv_PWM(abs(sm_lv_M1RL));

      //Module 2
      sm_PWM_M2FL = map_lv_PWM(abs(sm_lv_M2FL));
      sm_PWM_M2FR = map_lv_PWM(abs(sm_lv_M2FR));
      sm_PWM_M2RR = map_lv_PWM(abs(sm_lv_M2RR));
      sm_PWM_M2RL = map_lv_PWM(abs(sm_lv_M2RL));

      //Module 3
      sm_PWM_M3FL = map_lv_PWM(abs(sm_lv_M3FL));
      sm_PWM_M3FR = map_lv_PWM(abs(sm_lv_M3FR));
      sm_PWM_M3RR = map_lv_PWM(abs(sm_lv_M3RR));
      sm_PWM_M3RL = map_lv_PWM(abs(sm_lv_M3RL));


      //Module 4
      sm_PWM_M4FL = map_lv_PWM(abs(sm_lv_M4FL));
      sm_PWM_M4FR = map_lv_PWM(abs(sm_lv_M4FR));
      sm_PWM_M4RR = map_lv_PWM(abs(sm_lv_M4RR));
      sm_PWM_M4RL = map_lv_PWM(abs(sm_lv_M4RL));
    }

    else if(flag==1){
      //Module 1
      sm_PWM_M1FL = map_turn_PWM(abs(sm_lv_M1FL));
      sm_PWM_M1FR = map_turn_PWM(abs(sm_lv_M1FR));
      sm_PWM_M1RR = map_turn_PWM(abs(sm_lv_M1RR));
      sm_PWM_M1RL = map_turn_PWM(abs(sm_lv_M1RL));

      //Module 2
      sm_PWM_M2FL = map_turn_PWM(abs(sm_lv_M2FL));
      sm_PWM_M2FR = map_turn_PWM(abs(sm_lv_M2FR));
      sm_PWM_M2RR = map_turn_PWM(abs(sm_lv_M2RR));
      sm_PWM_M2RL = map_turn_PWM(abs(sm_lv_M2RL));

      //Module 3
      sm_PWM_M3FL = map_turn_PWM(abs(sm_lv_M3FL));
      sm_PWM_M3FR = map_turn_PWM(abs(sm_lv_M3FR));
      sm_PWM_M3RR = map_turn_PWM(abs(sm_lv_M3RR));
      sm_PWM_M3RL = map_turn_PWM(abs(sm_lv_M3RL));


      //Module 4
      sm_PWM_M4FL = map_turn_PWM(abs(sm_lv_M4FL));
      sm_PWM_M4FR = map_turn_PWM(abs(sm_lv_M4FR));
      sm_PWM_M4RR = map_turn_PWM(abs(sm_lv_M4RR));
      sm_PWM_M4RL = map_turn_PWM(abs(sm_lv_M4RL));
    }

    else if(flag==2){
      //Module 1
      sm_PWM_M1FL = map_ang_PWM(abs(sm_lv_M1FL));
      sm_PWM_M1FR = map_ang_PWM(abs(sm_lv_M1FR));
      sm_PWM_M1RR = map_ang_PWM(abs(sm_lv_M1RR));
      sm_PWM_M1RL = map_ang_PWM(abs(sm_lv_M1RL));

      //Module 2
      sm_PWM_M2FL = map_ang_PWM(abs(sm_lv_M2FL));
      sm_PWM_M2FR = map_ang_PWM(abs(sm_lv_M2FR));
      sm_PWM_M2RR = map_ang_PWM(abs(sm_lv_M2RR));
      sm_PWM_M2RL = map_ang_PWM(abs(sm_lv_M2RL));

      //Module 3
      sm_PWM_M3FL = map_ang_PWM(abs(sm_lv_M3FL));
      sm_PWM_M3FR = map_ang_PWM(abs(sm_lv_M3FR));
      sm_PWM_M3RR = map_ang_PWM(abs(sm_lv_M3RR));
      sm_PWM_M3RL = map_ang_PWM(abs(sm_lv_M3RL));


      //Module 4
      sm_PWM_M4FL = map_ang_PWM(abs(sm_lv_M4FL));
      sm_PWM_M4FR = map_ang_PWM(abs(sm_lv_M4FR));
      sm_PWM_M4RR = map_ang_PWM(abs(sm_lv_M4RR));
      sm_PWM_M4RL = map_ang_PWM(abs(sm_lv_M4RL));
    }

    else if(flag==3){
      //Module 1
      sm_PWM_M1FL = map_lv_PWM(abs(sm_lv_M1FL)) - sm_pwm_lower_limit;
      sm_PWM_M1FR = map_lv_PWM(abs(sm_lv_M1FR)) - sm_pwm_lower_limit;
      sm_PWM_M1RR = map_lv_PWM(abs(sm_lv_M1RR)) - sm_pwm_lower_limit;
      sm_PWM_M1RL = map_lv_PWM(abs(sm_lv_M1RL)) - sm_pwm_lower_limit;

      //Module 2
      sm_PWM_M2FL = map_lv_PWM(abs(sm_lv_M2FL)) - sm_pwm_lower_limit;
      sm_PWM_M2FR = map_lv_PWM(abs(sm_lv_M2FR)) - sm_pwm_lower_limit;
      sm_PWM_M2RR = map_lv_PWM(abs(sm_lv_M2RR)) - sm_pwm_lower_limit;
      sm_PWM_M2RL = map_lv_PWM(abs(sm_lv_M2RL)) - sm_pwm_lower_limit;

      //Module 3
      sm_PWM_M3FL = map_lv_PWM(abs(sm_lv_M3FL)) - sm_pwm_lower_limit;
      sm_PWM_M3FR = map_lv_PWM(abs(sm_lv_M3FR)) - sm_pwm_lower_limit;
      sm_PWM_M3RR = map_lv_PWM(abs(sm_lv_M3RR)) - sm_pwm_lower_limit;
      sm_PWM_M3RL = map_lv_PWM(abs(sm_lv_M3RL)) - sm_pwm_lower_limit;


      //Module 4
      sm_PWM_M4FL = map_lv_PWM(abs(sm_lv_M4FL)) - sm_pwm_lower_limit;
      sm_PWM_M4FR = map_lv_PWM(abs(sm_lv_M4FR)) - sm_pwm_lower_limit;
      sm_PWM_M4RR = map_lv_PWM(abs(sm_lv_M4RR)) - sm_pwm_lower_limit;
      sm_PWM_M4RL = map_lv_PWM(abs(sm_lv_M4RL)) - sm_pwm_lower_limit;
    }
    
    // Serial.println("================PWM================");
    // Serial.println(sm_PWM_M1FL);
    // Serial.println(sm_PWM_M1FR);
    // Serial.println(sm_PWM_M1RL);
    // Serial.println(sm_PWM_M1RR);
    // Serial.println("------------------");
    // Serial.println(sm_PWM_M2FL);
    // Serial.println(sm_PWM_M2FR);
    // Serial.println(sm_PWM_M2RL);
    // Serial.println(sm_PWM_M2RR);
    // Serial.println("------------------");
    // Serial.println(sm_PWM_M3FL);
    // Serial.println(sm_PWM_M3FR);
    // Serial.println(sm_PWM_M3RL);
    // Serial.println(sm_PWM_M3RR);
    // Serial.println("------------------");
    // Serial.println(sm_PWM_M4FL);
    // Serial.println(sm_PWM_M4FR);
    // Serial.println(sm_PWM_M4RL);
    // Serial.println(sm_PWM_M4RR);
    // Serial.println("================PWM================");

    //store all the pwm values inside an array
    double sm_PWMs[4][4] = {{sm_PWM_M1FL, sm_PWM_M1FR, sm_PWM_M1RL, sm_PWM_M1RR},
              {sm_PWM_M2FL, sm_PWM_M2FR, sm_PWM_M2RL, sm_PWM_M2RR},
              {sm_PWM_M3FL, sm_PWM_M3FR, sm_PWM_M3RL, sm_PWM_M3RR},
              {sm_PWM_M4FL, sm_PWM_M4FR, sm_PWM_M4RL, sm_PWM_M4RR}
            };
    //set speed to each motor
    SetSmorphiSpeed(sm_PWMs);
}



void Smorphi::SetSmorphiSpeed(double pwm[4][4])
{

  M11->setSpeed(pwm[0][0]);
  M12->setSpeed(pwm[0][1]);
  M13->setSpeed(pwm[0][2]);
  M14->setSpeed(pwm[0][3]);

  M21->setSpeed(pwm[1][0]);
  M22->setSpeed(pwm[1][1]);
  M23->setSpeed(pwm[1][2]);
  M24->setSpeed(pwm[1][3]);

  M31->setSpeed(pwm[2][0]);
  M32->setSpeed(pwm[2][1]);
  M33->setSpeed(pwm[2][2]);
  M34->setSpeed(pwm[2][3]);

  M41->setSpeed(pwm[3][0]);
  M42->setSpeed(pwm[3][1]);
  M43->setSpeed(pwm[3][2]);
  M44->setSpeed(pwm[3][3]);

}

//handle the motor driving direction
void Smorphi::MotorDirection(){

  double sm_lvs[4][4] = {{sm_lv_M1FL,sm_lv_M1FR,sm_lv_M1RL,sm_lv_M1RR},
                    {sm_lv_M2FL,sm_lv_M2FR,sm_lv_M2RL,sm_lv_M2RR},
                    {sm_lv_M3FL,sm_lv_M3FR,sm_lv_M3RL,sm_lv_M3RR},
                    {sm_lv_M4FL,sm_lv_M4FR,sm_lv_M4RL,sm_lv_M4RR}};

  Adafruit_DCMotor *sm_motors[4][4] = {{M11,M12,M13,M14},
                      {M21,M22,M23,M24},
                      {M31,M32,M33,M34},
                      {M41,M42,M43,M44}};

  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      if (sm_lvs[i][j] > 0.001) {
        sm_motors[i][j]->run(FORWARD);
      }
      if (sm_lvs[i][j] == 0) {
        sm_motors[i][j]->run(RELEASE);
      }
      if (sm_lvs[i][j] < -0.001) {
        sm_motors[i][j]->run(BACKWARD);
      }
    }
  }
}

//Locomotion functions
void Smorphi::MoveForward(const int Speed)
{
  double vel_speed = mapPosRanges(Speed);
  sm_velocity_handler(vel_speed, 0, 0);
  int flag = 0;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi::MoveBackward(const int Speed)
{
  double vel_speed = mapNegRanges(Speed);
  sm_velocity_handler(vel_speed, 0, 0);
  int flag = 0;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi::MoveRight(const int Speed)
{
  double vel_speed = mapNegRanges(Speed);
  sm_velocity_handler(0, vel_speed, 0);
  int flag = 0;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi::MoveLeft(const int Speed)
{
  double vel_speed = mapPosRanges(Speed);
  sm_velocity_handler(0, vel_speed, 0);
  int flag = 0;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi::MoveDiagUpRight(const int Speed)
{
  double vel_speed_x = mapPosRanges(Speed)/2;
  double vel_speed_y = mapNegRanges(Speed)/2;
  sm_velocity_handler(vel_speed_x+0.001, vel_speed_y, 0);
  int flag = 3;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi::MoveDiagUpLeft(const int Speed)
{
  double vel_speed = mapPosRanges(Speed)/2;
  sm_velocity_handler(vel_speed+0.001, vel_speed, 0);
  int flag = 3;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi::MoveDiagDownRight(const int Speed)
{

  double vel_speed = mapNegRanges(Speed)/2;
  sm_velocity_handler(vel_speed-0.001, vel_speed, 0);
  int flag = 3;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi::MoveDiagDownLeft(const int Speed)
{
  
  double vel_speed_x = mapNegRanges(Speed)/2;
  double vel_speed_y = mapPosRanges(Speed)/2;
  sm_velocity_handler(vel_speed_x-0.001, vel_speed_y, 0);
  int flag = 3;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi::MoveTurnUpRight(const int Speed, const int angular_velocity)
{
  
  double vel_speed = mapPosRanges(Speed);
  double ang_speed = mapNegAng(angular_velocity);
  sm_velocity_handler(vel_speed, 0, ang_speed);
  int flag = 1;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi::MoveTurnUpLeft(const int Speed, const int angular_velocity)
{
  
  double vel_speed = mapPosRanges(Speed);
  double ang_speed = mapPosAng(angular_velocity);
  sm_velocity_handler(vel_speed, 0, ang_speed);
  int flag = 1;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi::MoveTurnDownRight(const int Speed, const int angular_velocity)
{
  
  double vel_speed = mapNegRanges(Speed);
  double ang_speed = mapNegAng(angular_velocity);
  sm_velocity_handler(vel_speed, 0, ang_speed);
  int flag = 1;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi::MoveTurnDownLeft(const int Speed, const int angular_velocity)
{
  double vel_speed = mapNegRanges(Speed);
  double ang_speed = mapPosAng(angular_velocity);
  sm_velocity_handler(vel_speed, 0, ang_speed);
  int flag = 1;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi::stopSmorphi()
{ 

  M11->run(RELEASE);
  M12->run(RELEASE);
  M13->run(RELEASE);
  M14->run(RELEASE);

  M21->run(RELEASE);
  M22->run(RELEASE);
  M23->run(RELEASE);
  M24->run(RELEASE);

  M31->run(RELEASE);
  M32->run(RELEASE);
  M33->run(RELEASE);
  M34->run(RELEASE);

  M41->run(RELEASE);
  M42->run(RELEASE);
  M43->run(RELEASE);
  M44->run(RELEASE);

}

void Smorphi::CenterPivotLeft(const int angular_velocity)
{
  
  double ang_speed = mapPosAng(angular_velocity);
  sm_velocity_handler(0, 0, ang_speed);
  int flag = 2;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi::CenterPivotRight(const int angular_velocity)
{
  double ang_speed = mapNegAng(angular_velocity);
  sm_velocity_handler(0, 0, ang_speed);
  int flag = 2;
  sm_pwm_handler(flag);
  MotorDirection();
}

//clear the velocity variables for each module 
void Smorphi::sm_reset_M1()
{
  sm_lv_M1FL  =  0;
  sm_lv_M1FR  =  0;
  sm_lv_M1RL  =  0;
  sm_lv_M1RR  =  0;
}

void Smorphi::sm_reset_M2()
{
  sm_lv_M2FL  =  0;
  sm_lv_M2FR  =  0;
  sm_lv_M2RL  =  0;
  sm_lv_M2RR  =  0;
}

void Smorphi::sm_reset_M3()
{
  sm_lv_M3FL  =  0;
  sm_lv_M3FR  =  0;
  sm_lv_M3RL  =  0;
  sm_lv_M3RR  =  0;
}

void Smorphi::sm_reset_M4()
{
  sm_lv_M4FL  =  0;
  sm_lv_M4FR  =  0;
  sm_lv_M4RL  =  0;
  sm_lv_M4RR  =  0;
}

//interrupt testing
void Smorphi::interrupt_test()
{
  if(!digitalRead(INT_PIN_1))
  {
  Serial.print("Interrupt detected on mcp1 pin: ");
  Serial.println(mcp1.getLastInterruptPin());
  }
  if(!digitalRead(INT_PIN_2))
  {
  Serial.print("Interrupt detected on mcp2 pin: ");
  Serial.println(mcp2.getLastInterruptPin());
  }
  if(!digitalRead(INT_PIN_3))
  {
  Serial.print("Interrupt detected on mcp3 pin: ");
  Serial.println(mcp3.getLastInterruptPin());
  }
  if(!digitalRead(INT_PIN_4))
  {
  Serial.print("Interrupt detected on mcp4 pin: ");
  Serial.println(mcp4.getLastInterruptPin());
  }
}
