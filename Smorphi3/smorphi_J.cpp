/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <Arduino.h>
#include <smorphi_triple.h>

void Smorphi_triple::J()
{
  char cur_shape = sm_getShape();
  int flag = 2;
  double w = mapPosAng(80);
  unsigned long start_time = millis();

  if (cur_shape == 'i')
  {
    set_interrupt_pin();
    sm_solenoid_set(4,true);
    int solenoidsat3 = sm_feedback(3);
    while (solenoidsat3 == 0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(4,false);
      }
      
      //kinematic Equations
      // Module 3
      sm_lv_M3FL  =  (-0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3FR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3RL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M3RR  =  (-0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

      // Module 4
      // sm_lv_M4FL  =  (-0.34 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      // sm_lv_M4FR  =  ( 0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      // sm_lv_M4RL  =  ( 0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      // sm_lv_M4RR  =  (-0.34 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_2))
      {
        solenoidsat3 = sm_feedback(3);
      }
    }
    sm_solenoid_set(4,false);

  } 

  // if (cur_shape == 'l')
  // {
  //   set_interrupt_pin();
  //   sm_solenoid_set(6,true);
  //   int solenoidstate5 = sm_feedback(5);
  //   while(solenoidstate5 == 0)
  //   {
  //     unsigned long check_time = millis();
  //     if (check_time - start_time >= 2000){
  //       sm_solenoid_set(6,false);
  //     }
  //     //kinematic Equations
  //     // Module 4
  //     sm_lv_M4FL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4FR  =  (0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4RL  =  (0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4RR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

  //     sm_pwm_handler(flag);
  //     MotorDirection();

  //     if (!digitalRead(INT_PIN_3))
  //     {
  //       solenoidstate5 = sm_feedback(5);
  //     }
  //   }
  //   sm_solenoid_set(6,false);
    
  //   stopSmorphi();
  //   delay(500);
  //   start_time = millis();

  //   set_interrupt_pin();
  //   sm_solenoid_set(4,true);
  //   int solenoidstate3 = sm_feedback(3);
  //   while(solenoidstate3 == 0)
  //   {
  //     unsigned long check_time = millis();
  //     if (check_time - start_time >= 2000){
  //       sm_solenoid_set(4,false);
  //     }
  //     //kinematic Equations
  //     // Module 3
  //     sm_lv_M3FL  =  (-0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M3FR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M3RL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M3RR  =  (-0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

  //     // Module 4
  //     sm_lv_M4FL  =  (-0.34 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4FR  =  ( 0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4RL  =  ( 0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4RR  =  (-0.34 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

  //     sm_pwm_handler(flag);
  //     MotorDirection();

  //     if (!digitalRead(INT_PIN_2))
  //     {
  //       solenoidstate3 = sm_feedback(3);
  //     }
  //   }
  //   sm_solenoid_set(4,false);
  // }

  // if (cur_shape == 'z')
  // {
  //   //Z to I
  //   I();
    
  //   stopSmorphi();
  //   delay(500);
  //   start_time = millis();

  //   //I to O
  //   O();
  // } 

  // if (cur_shape == 't')
  // {
  //   J();
    
  //   stopSmorphi();
  //   delay(500);
  //   start_time = millis();

  //   O();
  // } 

  // if (cur_shape == 's')
  // {
  //   I();

  //   stopSmorphi();
  //   delay(500);
  //   start_time = millis();

  //   O();
  // } 

  // if (cur_shape == 'j')
  // {
  //   set_interrupt_pin();
  //   sm_solenoid_set(6,true);
  //   int solenoidstate5 = sm_feedback(5);
  //   while(sm_feedback(5) == 0)
  //   {
  //     unsigned long check_time = millis();
  //     if (check_time - start_time >= 2000){
  //       sm_solenoid_set(6,false);
  //     }
  //     //kinematic Equations
  //     // Module 4(one module moves)
  //     sm_lv_M4FL  =  ( - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4FR  =  (0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4RL  =  (0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
  //     sm_lv_M4RR  =  (   ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      
  //     sm_pwm_handler(flag);
  //     MotorDirection();

  //     if (!digitalRead(INT_PIN_3))
  //     {
  //       solenoidstate5 = sm_feedback(5);
  //     }
  //   }
  //   sm_solenoid_set(6,false);
  // } 

  //Reset Velocity
  sm_reset_M1();
  sm_reset_M2();
  sm_reset_M3();
  // sm_reset_M4();

  stopSmorphi();
}