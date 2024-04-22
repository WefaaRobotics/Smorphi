/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <Arduino.h>
#include <smorphi_mini.h>

void Smorphi_mini::shape2()
{
  char cur_shape = sm_getShape();
  int flag = 2;
  double w = mapPosAng(350);
  unsigned long start_time = millis();


  if (cur_shape == '1')
  {

    set_interrupt_pin();
    sm_solenoid_set(1,true);
    int solenoidstate2 = sm_feedback(2);
    while(solenoidstate2==0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(1,false);
      }
      //kinematic Equations
      // Module 1
      sm_lv_M1FL  =  (- ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1FR  =  (0.17 * w + ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RL  =  (0.17 * w - ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;
      sm_lv_M1RR  =  (  ( sm_wheel_x + sm_wheel_y) * (w) ) * 2;

      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_2))
      {
        solenoidstate2 = sm_feedback(2);
      }
    }
    sm_solenoid_set(1,false);
  }  

  //Reset Velocity
  sm_reset_M1();
  sm_reset_M2();

  stopSmorphi_mini();
}