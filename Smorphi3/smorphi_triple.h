/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#ifndef Smorphi_triple_H_
#define Smorphi_triple_H_

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Adafruit_MCP23X17.h>


class Smorphi_triple
{
public:

  //Define the interrupt pins on master board
  #define INT_PIN_1 32 //for module 1
  #define INT_PIN_2 33 //for module 2
  #define INT_PIN_3 34 //for module 3
  // #define INT_PIN_4 35 //for module 4

  // //Define the encoder pins(MASTERBOARD)
  // //Register for encoder interrupt
  // uint32_t cp0_regs[18];
  // // Connect Motor 1's two encoder pins!
  // #define ENCODER_A_M1   26
  // #define ENCODER_B_M1   27

  // // Connect Motor 2's two encoder pins!
  // #define ENCODER_A_M2   25
  // #define ENCODER_B_M2   23

  // // Connect Motor 3's two encoder pins!
  // #define ENCODER_A_M3   19
  // #define ENCODER_B_M3   18

  // // Connect Motor 4's two encoder pins!
  // #define ENCODER_A_M4   16
  // #define ENCODER_B_M4   17

  // // These let us convert ticks-to-RPM
  // #define GEARING     45 //20
  // #define ENCODERMULT 13 //12
  // //Calculations for constant value to be accounted with RPS(Radians per Second)
  // int enc_cons = 60000000/(GEARING*ENCODERMULT);


  //Kinematics constants (All the calculations made in SI units)
  const double sm_wheel_radius = 0.03;
  const double sm_wheelbase = 0.7;
  const double sm_speed_to_pwm_ratio = 0.01231; //Need to finalize this value
  const double sm_wheel_x = 0.05925; //l_x
  const double sm_wheel_y = 0.035; //l_y

  //Adafruit Constants


  //Speed constants
  const double sm_max_linear_speed = 1.1; //Need to be varified according to robot
  const double sm_max_angular_speed = 2.12; // Need to be varified according to robot
  const double sm_max_curve_speed = 1.78; // Need to be varified according to robot
  const double sm_min_speed = 0.0; // Need to be varified according to robot

  // Speed variables
  double sm_req_linear_speed_x = 0.0;
  double sm_req_linear_speed_y = 0.0;
  double sm_req_angular_speed = 0.0;

  //Each PWM values that are to be sent to the motors
  double sm_PWM_M1FR = 0.0, sm_PWM_M1FL = 0.0, sm_PWM_M1RR = 0.0, sm_PWM_M1RL = 0.0, sm_PWM_M2FR = 0.0, sm_PWM_M2FL = 0.0, sm_PWM_M2RR = 0.0, sm_PWM_M2RL = 0.0, sm_PWM_M3FR = 0.0, sm_PWM_M3FL = 0.0, sm_PWM_M3RR = 0.0, sm_PWM_M3RL = 0.0; //sm_PWM_M4FR = 0.0, sm_PWM_M4FL = 0.0, sm_PWM_M4RR = 0.0, sm_PWM_M4RL = 0.0;

  //Each wheel velocity in m/s
  double sm_lv_M1FR = 0.0, sm_lv_M1FL = 0.0, sm_lv_M1RR = 0.0, sm_lv_M1RL = 0.0, sm_lv_M2FR = 0.0, sm_lv_M2FL = 0.0, sm_lv_M2RR = 0.0, sm_lv_M2RL = 0.0, sm_lv_M3FR = 0.0, sm_lv_M3FL = 0.0, sm_lv_M3RR = 0.0, sm_lv_M3RL = 0.0;//sm_lv_M4FR = 0.0, sm_lv_M4FL = 0.0, sm_lv_M4RR = 0.0, sm_lv_M4RL = 0.0;

  //PWM Lower and Upper Limits
  float sm_pwm_lower_limit = 20;
  float sm_pwm_upper_limit = 255;

  //Polarity
  int sm_polarity = 1;

  // //Encoder Variables
  // volatile float RPM_M1 = 0;
  // volatile float RPM_M2 = 0;
  // volatile float RPM_M3 = 0;
  // volatile float RPM_M4 = 0;
  // volatile float RPS_M1 = 0;
  // volatile float RPS_M2 = 0;
  // volatile float RPS_M3 = 0;
  // volatile float RPS_M4 = 0;
  // volatile float V_x = 0;
  // volatile float V_y = 0;
  // volatile float W_z = 0;
  // volatile uint32_t lastA_1 = 0;
  // volatile uint32_t lastA_2 = 0;
  // volatile uint32_t lastA_3 = 0;
  // volatile uint32_t lastA_4 = 0;
  // volatile bool motordir_M1 = FORWARD;
  // volatile bool motordir_M2 = FORWARD;
  // volatile bool motordir_M3 = FORWARD;
  // volatile bool motordir_M4 = FORWARD;

  //Initializing the Robot
  void BeginSmorphiTriple();

  // //Initializing the Robot with Encoder
  // void BeginSmorphi_encoder();

  // Velocity Handler
  void sm_velocity_handler(float sm_req_linear_speed_x, float sm_req_linear_speed_y, float sm_req_angular_speed);

  //PWM Handler
  void sm_pwm_handler(int flag);

  // Locomotion
  void MoveForward(int Speed);
  void MoveBackward(int Speed);
  void MoveRight(int Speed);
  void MoveLeft(int Speed);
  //Diagonal Locomotion
  void MoveDiagUpRight(int Speed);
  void MoveDiagUpLeft(int Speed);
  void MoveDiagDownRight(int Speed);
  void MoveDiagDownLeft(int Speed);
  //Curve Locomotion
  void MoveTurnUpRight(int Speed, int angular_velocity);
  void MoveTurnUpLeft(int Speed, int angular_velocity);
  void MoveTurnDownRight(int Speed, int angular_velocity);
  void MoveTurnDownLeft(int Speed, int angular_velocity);
  //Center Pivot Locomotion
  void CenterPivotLeft(int Speed);
  void CenterPivotRight(int Speed);
  //Check the feedback of solenoid
  int sm_feedback(int solenoid_feedback);
  //Unlock certain solenoid
  void sm_solenoid_set(int solenoid_unlock, bool status);
  //Stop Smorphi
  void stopSmorphi();
  //Reset lv
  void sm_reset_M1();
  void sm_reset_M2();
  void sm_reset_M3();
  // void sm_reset_M4();
  // Interrup functions
  void interrupt_test();
  void set_interrupt_pin(); 
  int module1_sensor_interrupt();
  

  // Helper Functions
  char sm_getShape();
  void SetSmorphiSpeed(double pwm[3][4]);
  double mapPosRanges(int ipSpeed);
  double mapNegRanges(int ipSpeed);
  int map_lv_PWM(double ipSpeed);
  int map_ang_PWM(double ipSpeed);
  int map_turn_PWM(double ipSpeed);
  double mapPosAng(int ipSpeed);
  double mapNegAng(int ipSpeed);
  void MotorDirection();

  void I();
  // void O();
  void J();
  // void T();
  // void L();
  // void S();
  // void Z();


// Sensors
  // Ultrasonic Sensor

  // Infrared Sensor
   // Module 1
  int module1_sensor_status(int pin_no);
  
   // Module 2
  int module2_sensor_status(int pin_no);
  
   // Module 3
  int module3_sensor_status(int pin_no);
  
   // Module 4
  // int module4_sensor_status(int pin_no);
  

  // Camera

  // IMU Sensor

  // Temperature Sensor


// //Encoder Functions
//   //Motor_1 Encoder Func
//   void interruptA_M1();
//   //Motor_2 Encoder Func
//   void interruptA_M2();
//   //Motor_3 Encoder Func
//   void interruptA_M3();
//   //Motor_4 Encoder Func
//   void interruptA_M4();


private:
  int speed, feedback_val;
  char robot_shape;

  float w11, w12, w13, w14, w21, w22, w23, w24, w31, w32, w33, w34; //w44, w41, w42, w43;
  float v_x = 0.0, v_y = 0.0, w = 0.0;

};

#endif 
