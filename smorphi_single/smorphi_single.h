
#ifndef Smorphi_single_H_
#define Smorphi_single_H_

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Adafruit_MCP23X17.h>


class Smorphi_single
{
public:

  //Define the interrupt pins on master board
  #define INT_PIN_1 32 //for module 1
  #define INT_PIN_2 33 //for module 2
  #define INT_PIN_3 34 //for module 3
  #define INT_PIN_4 35 //for module 4
  // #define INT_PIN_2 33 //for module 2


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
   double sm_PWM_M1FR = 0.0, sm_PWM_M1FL = 0.0, sm_PWM_M1RR = 0.0, sm_PWM_M1RL = 0.0, sm_PWM_M2FR = 0.0, sm_PWM_M2FL = 0.0, sm_PWM_M2RR = 0.0, sm_PWM_M2RL = 0.0, sm_PWM_M3FR = 0.0, sm_PWM_M3FL = 0.0, sm_PWM_M3RR = 0.0, sm_PWM_M3RL = 0.0, sm_PWM_M4FR = 0.0, sm_PWM_M4FL = 0.0, sm_PWM_M4RR = 0.0, sm_PWM_M4RL = 0.0;

  //Each wheel velocity in m/s
  double sm_lv_M1FR = 0.0, sm_lv_M1FL = 0.0, sm_lv_M1RR = 0.0, sm_lv_M1RL = 0.0, sm_lv_M2FR = 0.0, sm_lv_M2FL = 0.0, sm_lv_M2RR = 0.0, sm_lv_M2RL = 0.0, sm_lv_M3FR = 0.0, sm_lv_M3FL = 0.0, sm_lv_M3RR = 0.0, sm_lv_M3RL = 0.0, sm_lv_M4FR = 0.0, sm_lv_M4FL = 0.0, sm_lv_M4RR = 0.0, sm_lv_M4RL = 0.0;


  //PWM Lower and Upper Limits
  float sm_pwm_lower_limit = 20;
  float sm_pwm_upper_limit = 255;

  //Polarity
  int sm_polarity = 1;

  //Initializing the Robot
  void BeginSmorphi_single();

  // Velocity Handler
  void sm_velocity_handler(float sm_req_linear_speed_x, float sm_req_linear_speed_y, float sm_req_angular_speed, float RPS_M1,float RPS_M2, float RPS_M3,float RPS_M4);

  //PWM Handler
  void sm_pwm_handler(int flag);

  // Locomotion
  void Move(const float Speed_x,const float Speed_y,const float Speed_w,const float error_x,const float error_y, const float error_w,const float RPS_M1,const float RPS_M2,const float RPS_M3, const float RPS_M4);
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
  //Stop Smorphi_mini
  void stopSmorphi_single();
  //Reset lv
  void sm_reset_M1();

  // Interrup functions
  static void interrupt_val();
  void interrupt_test();
  void set_interrupt_pin(); 
  int module1_sensor_interrupt();
  int module2_sensor_interrupt();
  int module3_sensor_interrupt();
  int module4_sensor_interrupt();
  

  // Helper Functions
  char sm_getShape();
  void SetSmorphi_singleSpeed(double pwm[1][4]);
  double mapPosRanges(int ipSpeed);
  double mapNegRanges(int ipSpeed);
  int map_lv_PWM(double ipSpeed);
  int map_ang_PWM(double ipSpeed);
  int map_turn_PWM(double ipSpeed);
  double mapPosAng(int ipSpeed);
  double mapNegAng(int ipSpeed);
  void MotorDirection();
  int sgn(double val);

  void shape1();
  // void shape2();


// Sensors
  // Ultrasonic Sensor

  // Infrared Sensor
   // Module 1
  int module1_sensor_status(int pin_no);
  int module2_sensor_status(int pin_no);
  int module3_sensor_status(int pin_no);
  int module4_sensor_status(int pin_no);

   

  // Camera

  // IMU Sensor

  // Temperature Sensor

private:
  int speed, feedback_val;
  char robot_shape;

  float w11, w12, w13, w14, w21, w22, w23, w24, w31, w32, w33, w34, w44, w41, w42, w43;
  float v_x = 0.0, v_y = 0.0, w = 0.0;

};

#endif 
