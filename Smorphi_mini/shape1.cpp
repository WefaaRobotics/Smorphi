/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <Arduino.h>
#include <smorphi_mini.h>

void Smorphi_mini::shape1()
{
  //check the current shape
  char cur_shape = sm_getShape();
  int flag = 2;
  //map the velocity
  double w = mapPosAng(350);
  //get the current time
  unsigned long start_time = millis();


  if (cur_shape == '2')
  {
    set_interrupt_pin();
    sm_solenoid_set(2,true);
    int solenoidstate1 = sm_feedback(1);
    while(solenoidstate1==0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(2,false);
      }
      //kinematic Equations
      // Module 1
      sm_lv_M1FL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1FR  =  (0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1RL  =  (0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1RR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_1))
      {
        solenoidstate1 = sm_feedback(1);
      }
    }
    sm_solenoid_set(2,false);
  }

  //Reset Velocity
  sm_reset_M1();
  sm_reset_M2();

  stopSmorphi_mini();
}
