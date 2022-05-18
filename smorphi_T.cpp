/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <Arduino.h>
#include <smorphi.h>

void Smorphi::T()
{
  char cur_shape = sm_getShape();
  int flag = 2;
  double w = mapPosAng(80);
  unsigned long start_time = millis();

  if (cur_shape == 'i')
  {
    L();
    stopSmorphi();
    delay(500);
    start_time = millis();
    J();
    stopSmorphi();
    delay(500);
    start_time = millis();
    T();
  }  

  else if (cur_shape == 'l')
  {
    
    J();
    stopSmorphi();
    delay(500);
    start_time = millis();
    T();
  }  

  else if (cur_shape == 'z')
  {
    
    L();
    stopSmorphi();
    delay(500);
    start_time = millis();
    J();
    stopSmorphi();
    delay(500);
    start_time = millis();
    T();
  }  

  else if (cur_shape == 'o')
  {
    
    J();

    stopSmorphi();
    delay(100);
    start_time = millis();

    sm_solenoid_set(2,true);
    int solenoidstate5 = sm_feedback(5);
    while(solenoidstate5 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(2,false);
      }
      //kinematic Equation
      sm_lv_M1FL  =  ( - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1FR  =  (0.17 * (w) + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RL  =  (0.17 * (w) - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RR  =  (   ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();
      if (!digitalRead(INT_PIN_3))
      {
        solenoidstate5 = sm_feedback(5);
      }
    }
    sm_solenoid_set(2,false);
  }  

  else if (cur_shape == 's')
  {
    J();
    stopSmorphi();
    delay(500);
    start_time = millis();
    T();
  }

  else if (cur_shape == 'j')
  {
    set_interrupt_pin();
    sm_solenoid_set(2,true);
    int solenoidstate5 = sm_feedback(5);
    while(solenoidstate5 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(2,false);
      }
      
      //kinematic Equation
      sm_lv_M1FL  =  ( - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1FR  =  (0.17 * (w) + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RL  =  (0.17 * (w) - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RR  =  (   ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_3))
      {
        solenoidstate5 = sm_feedback(5);
      }
    }

    sm_solenoid_set(2,false);
  }  
  
  //Reset Velocity
  sm_reset_M1();
  sm_reset_M2();
  sm_reset_M3();
  sm_reset_M4();

  stopSmorphi();
}