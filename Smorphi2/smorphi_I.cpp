/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <Arduino.h>
#include <smorphi.h>

void Smorphi::I()
{
  //check the current shape
  char cur_shape = sm_getShape();
  int flag = 2;
  //map the velocity
  double w = mapPosAng(350);
  //get the current time
  unsigned long start_time = millis();

  if (cur_shape == 'l')
  {
    //initialize the interrupt pins
    set_interrupt_pin();
    //release the corresponding solenoid
    sm_solenoid_set(6, true);
    //get the target solenoid status
    int solenoidstate5 = sm_feedback(5);
    //if the target solenoid is not locked
    while(solenoidstate5 == 0)
    { 
      //make sure the solenoid would not be high for more than 2s
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(6,false);
      }
      // Module 4
      sm_lv_M4FL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4FR  =  (0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RL  =  (0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_pwm_handler(flag);
      MotorDirection();

      //update the target solenoid status when the corresponding interrupt pin is triggered
      if (!digitalRead(INT_PIN_3))
      {
        solenoidstate5 = sm_feedback(5);
      }
    }

    //make sure the solenoid is LOW 
    sm_solenoid_set(6,false);
  } 

  if (cur_shape == 'z')
  {
    set_interrupt_pin();
    sm_solenoid_set(3,true);
    sm_solenoid_set(6,true);
    int solenoidstate2 = sm_feedback(2);
    int solenoidstate5 = sm_feedback(5);
    while(solenoidstate2==0 || solenoidstate5==0)
    {
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(3,false);
        sm_solenoid_set(6,false);
      }
      //kinematic Equations
      // Module 1
      sm_lv_M1FL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1FR  =  (0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1RL  =  (0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1RR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

      // Module 4
      sm_lv_M4FL  =  (- ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4FR  =  (0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RL  =  (0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M4RR  =  (  ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      
      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_1) && !digitalRead(INT_PIN_3))
      {
        solenoidstate2 = sm_feedback(2);
        solenoidstate5 = sm_feedback(5);
      }
    }
    sm_solenoid_set(3,false);
    sm_solenoid_set(6,false);
  }


  if (cur_shape == 'o')
  {
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
      sm_lv_M4FR  =  (0.17 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RL  =  (0.17 * w - ( sm_wheel_x + sm_wheel_y) * w ) * 2;
      sm_lv_M4RR  =  (-0.34 * w + ( sm_wheel_x + sm_wheel_y) * w ) * 2;

      sm_pwm_handler(flag);
      MotorDirection();

      if (!digitalRead(INT_PIN_3))
      {
        Serial.print("Interrupt is trigerred!!!!!!");
        Serial.println(digitalRead(INT_PIN_3));
        solenoidstate4 = sm_feedback(4);
      }

      Serial.println(digitalRead(INT_PIN_3));
    }
    sm_solenoid_set(3,false);
  }

  if (cur_shape == 't')
  {
    J();

    stopSmorphi();
    delay(500);
    start_time = millis();

    I();
  }

  if (cur_shape == 's')
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
      //kinematic Equations

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
    //stopSmorphi();
    //delay(500);

    set_interrupt_pin();
    Serial.println("prepare to unlatch");
    sm_solenoid_set(3,true);
    Serial.println("finish unlatching");

    int solenoidstate2 = sm_feedback(2);
    while(solenoidstate2 == 0)
    {
      sm_reset_M3();
      sm_reset_M4();
      unsigned long check_time = millis();
      if (check_time - start_time >= 2000){
        sm_solenoid_set(3,false);
      }

      // Module 1
      sm_lv_M1FL  =  ( - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1FR  =  ( 0.17 * (-w) + ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1RL  =  ( 0.17 * (-w) - ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;
      sm_lv_M1RR  =  ( ( sm_wheel_x + sm_wheel_y) * (-w) ) * 2;

      sm_pwm_handler(flag);
      MotorDirection();
      if (!digitalRead(INT_PIN_1))
      {
        solenoidstate2 = sm_feedback(2);
      }
    }
  }

  if (cur_shape == 'j')
  {
    O();
    
    stopSmorphi();
    delay(500);
    start_time = millis();

    I();
  }

  //Reset Velocity
  sm_reset_M1();
  sm_reset_M2();
  sm_reset_M3();
  sm_reset_M4();

  stopSmorphi();

}
