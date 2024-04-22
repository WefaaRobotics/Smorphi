/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <Arduino.h>
#include <smorphi.h>

void Smorphi::S()
{
  char cur_shape = sm_getShape();
  int flag = 2;
  double w = mapPosAng(350);
  unsigned long start_time = millis();

  if (cur_shape == 'i')
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
      sm_lv_M1FL  =  ( - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1FR  =  ( 0.17 * (w) + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RL  =  ( 0.17 * (w) - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RR  =  ( ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();
      if (!digitalRead(INT_PIN_2))
      {
        solenoidstate3 = sm_feedback(3);
      }
    }
    sm_solenoid_set(2,false);

    
    stopSmorphi();
    delay(500);
    start_time = millis();

    set_interrupt_pin();
    sm_solenoid_set(4,true);
    int solenoidstate1 = sm_feedback(1);
    while(solenoidstate1 == 0)
    {
      sm_reset_M1();
      unsigned long check_time_1 = millis();
      if (check_time_1 - start_time >= 2000){
        sm_solenoid_set(4,false);
      }
      
      //kinematic Equation
      // Module 3
      sm_lv_M3FL  =  (-0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3FR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3RL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3RR  =  (-0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

      // Module 4
      sm_lv_M4FL  =  (-0.34 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4FR  =  ( 0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RL  =  ( 0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RR  =  (-0.34 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_1))
      {
        solenoidstate1 = sm_feedback(1);
      }
    }
    sm_solenoid_set(4,false);
  }  

  else if (cur_shape == 'l')
  {
    Z();
    //Z shape

    stopSmorphi();
    delay(500);
    start_time = millis();

    set_interrupt_pin();
    sm_solenoid_set(6,true);
    int solenoidstate5 = sm_feedback(5);
    while(solenoidstate5 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(6,false);
      }
      //kinematic Equation
      // Module 4
      sm_lv_M4FL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4FR  =  (0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RL  =  (0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_3))
      {
        solenoidstate5 = sm_feedback(5);
      }
    }
    sm_solenoid_set(6,false);
    stopSmorphi();
    delay(500);
    start_time = millis();
    
    set_interrupt_pin();
    sm_solenoid_set(4,true);
    int solenoidstate1 = sm_feedback(1);
    while(solenoidstate1 == 0)
    {

      unsigned long check_time1 = millis();
      if (check_time1 - start_time >= 2000){
        sm_solenoid_set(4,false);
      }
      //kinematic Equation
      // Module 3
      sm_lv_M3FL  =  (-0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3FR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3RL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3RR  =  (-0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

      // Module 4
      sm_lv_M4FL  =  (-0.34 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4FR  =  ( 0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RL  =  ( 0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RR  =  (-0.34 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_1))
      {
        solenoidstate1 = sm_feedback(1);
      }
    }
    sm_solenoid_set(4,false);
  }  

  else if (cur_shape == 'z')
  {
    set_interrupt_pin();
    sm_solenoid_set(6,true);
    int solenoidstate5 = sm_feedback(5);
    while(solenoidstate5 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(6,false);
      }
      //kinematic Equation
      // Module 4
      sm_lv_M4FL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4FR  =  (0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RL  =  (0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_3))
      {
        solenoidstate5 = sm_feedback(5);
      }
    }
    sm_solenoid_set(6,false);

    stopSmorphi();
    delay(500);
    start_time = millis();

    set_interrupt_pin();
    sm_solenoid_set(4,true);
    int solenoidstate1 = sm_feedback(1);
    while(solenoidstate1 == 0)
    {

      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(4,false);
      }
      //kinematic Equation
      // Module 3
      sm_lv_M3FL  =  (-0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3FR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3RL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3RR  =  (-0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

      // Module 4
      sm_lv_M4FL  =  (-0.34 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4FR  =  ( 0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RL  =  ( 0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RR  =  (-0.34 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_1))
      {
        solenoidstate1 = sm_feedback(1);
      }
    }
    sm_solenoid_set(4,false);
  }  

  else if (cur_shape == 'o')
  {
    I();
    
    stopSmorphi();
    delay(500);
    start_time = millis();

    S();
  }  

  else if (cur_shape == 't')
  {
    Z();
    
    stopSmorphi();
    delay(500);
    start_time = millis();

    S();
  }  

  else if (cur_shape == 'j')
  {
   O();

   stopSmorphi();
   delay(500);
   start_time = millis();

   I();

   stopSmorphi();
   delay(500);
   start_time = millis();

   S();
  }  

  //Reset Velocity
  sm_reset_M1();
  sm_reset_M2();
  sm_reset_M3();
  sm_reset_M4();

  stopSmorphi();
}