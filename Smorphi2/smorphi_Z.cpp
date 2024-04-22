/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <Arduino.h>
#include <smorphi.h>

void Smorphi::Z()
{
  char cur_shape = sm_getShape();
  int flag = 2;
  double w = mapPosAng(350);
  unsigned long start_time = millis();


  if (cur_shape == 'i')
  {

    set_interrupt_pin();
    sm_solenoid_set(2,true);
    sm_solenoid_set(5,true);
    int solenoidstate3 = sm_feedback(3);
    int solenoidstate6 = sm_feedback(6);
    while(solenoidstate3==0 || solenoidstate6==0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(2,false);
        sm_solenoid_set(5,false);
      }
      //kinematic Equations
      // Module 1
      sm_lv_M1FL  =  (- ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1FR  =  (0.17 * w + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RL  =  (0.17 * w - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RR  =  (  ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;

      // Module 4
      sm_lv_M4FL  =  (- ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M4FR  =  (0.17 * (w) + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M4RL  =  (0.17 * (w) - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M4RR  =  (  ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_2) && !digitalRead(INT_PIN_4))
      {
        solenoidstate3 = sm_feedback(3);
        solenoidstate6 = sm_feedback(6);
      }
    }
    sm_solenoid_set(2,false);
    sm_solenoid_set(5,false);
  }  

  else if (cur_shape == 'l')
  {
    set_interrupt_pin();
    sm_solenoid_set(2,true);
    int solenoidstate3 = sm_feedback(3);
    while(solenoidstate3 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(2,false);
      }
      //kinematic Equation
      // Module 1
      sm_lv_M1FL  =  (- ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1FR  =  (0.17 * (w) + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RL  =  (0.17 * (w) - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RR  =  (  ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_2))
      {
        solenoidstate3 = sm_feedback(3);
      }
    }
    sm_solenoid_set(2,false);
  }  

  else if (cur_shape == 'o')
  {

    //O to I
    set_interrupt_pin();
    sm_solenoid_set(3,true);
    int solenoidstate4 = sm_feedback(4);
    while(solenoidstate4 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(3,false);
      }
      //kinematic Equations
      // Module 3
      sm_lv_M3FL  =  (-0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3FR  =  (  ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3RL  =  (- ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3RR  =  (-0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;

      // Module 4
      sm_lv_M4FL  =  (-0.34 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4FR  =  ( 0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RL  =  ( 0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RR  =  (-0.34 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;

      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_3))
      {
        solenoidstate4 = sm_feedback(4);
      }
    }
    sm_solenoid_set(3,false);

    stopSmorphi();
    delay(500);
    start_time = millis();

    set_interrupt_pin();
    //I to Z
    sm_solenoid_set(2,true);
    sm_solenoid_set(5,true);
    int solenoidstate3 = sm_feedback(3);
    int solenoidstate6 = sm_feedback(6);
    while((solenoidstate3==0 || solenoidstate6==0))
    {

      unsigned long check_time = millis();
      //kinematic Equations
      if (check_time - start_time >= 2000){
        sm_solenoid_set(2,false);
        sm_solenoid_set(5,false);
      }
      // Module 1
      sm_lv_M1FL  =  (- ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1FR  =  (0.17 * w + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RL  =  (0.17 * w - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RR  =  (  ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;

      // Reset Module 3
      sm_reset_M3();

      // Module 4
      sm_lv_M4FL  =  (- ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4FR  =  (0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RL  =  (0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RR  =  (  ( sm_wheel_x + sm_wheel_y) * w ) * 2;

      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_2) && !digitalRead(INT_PIN_4))
      {
        solenoidstate3 = sm_feedback(3);
        solenoidstate6 = sm_feedback(6);
      }
    }
    sm_solenoid_set(2,false);
    sm_solenoid_set(5,false);
  }  

  else if (cur_shape == 't')
  {
    set_interrupt_pin();
    sm_solenoid_set(3,true);
    sm_solenoid_set(5,true);
    int solenoidstate4 = sm_feedback(4);
    while(solenoidstate4 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(3,false);
        sm_solenoid_set(5,false);
      }
      //kinematic Equation
      // Module 3
      sm_lv_M3FL  =  (-0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3FR  =  (  ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3RL  =  (- ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3RR  =  (-0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;

      // Module 4
      sm_lv_M4FL  =  (0.34 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4FR  =  (0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RL  =  (0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RR  =  (0.34 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();
      if (!digitalRead(INT_PIN_3))
      {
        solenoidstate4 = sm_feedback(4);
      }
    }
    sm_solenoid_set(3,false);
    sm_solenoid_set(5,false);

    stopSmorphi();
    delay(500);

    set_interrupt_pin();
    int solenoidstate3 = sm_feedback(3);
    while(solenoidstate3 == 0)
    {
      sm_reset_M3();
      sm_reset_M4();

      // Module 1
      sm_lv_M1FL  =  (- ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1FR  =  (0.17 * w + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RL  =  (0.17 * w - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RR  =  (  ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_2))
      {
        solenoidstate3 = sm_feedback(3);
      }
    }

  }  

  else if (cur_shape == 's')
  {
    set_interrupt_pin();
    sm_solenoid_set(1,true);
    int solenoidstate4 = sm_feedback(4);
    while(solenoidstate4 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(1,false);
      }
      //kinematic Equation
      // Module 3
      sm_lv_M3FL  =  (-0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3FR  =  (  ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3RL  =  (- ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M3RR  =  (-0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;

      // Module 4
      sm_lv_M4FL  =  (-0.34 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4FR  =  (0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RL  =  (0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RR  =  (-0.34 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_3))
      {
        solenoidstate4 = sm_feedback(4);
      }
    }
    sm_solenoid_set(1,false);

    stopSmorphi();
    delay(500);
    start_time = millis();

    set_interrupt_pin();
    sm_solenoid_set(5,true);
    int solenoidstate6 = sm_feedback(6);
    while(sm_feedback(6) == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(5,false);
      }
      //kinematic Equation
      sm_reset_M3();

      // Module 4
      sm_lv_M4FL  =  (- ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M4FR  =  (0.17 * (w) + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M4RL  =  (0.17 * (w) - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M4RR  =  (  ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      
      
      sm_pwm_handler(flag);
      MotorDirection();
      if (!digitalRead(INT_PIN_4))
      {
        solenoidstate6 = sm_feedback(6);
      }
    }
    sm_solenoid_set(5,false);
  }  

  else if (cur_shape == 'j')
  {
    L();
    stopSmorphi();
    delay(500);
    start_time = millis();
    Z();
  }  

  //Reset Velocity
  sm_reset_M1();
  sm_reset_M2();
  sm_reset_M3();
  sm_reset_M4();

  stopSmorphi();
}