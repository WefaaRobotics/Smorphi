/* Copyright (C) Singapore University of Technology and Design - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Zeng Zimou <zimou_zeng@sutd.edu.sg>, August 2021
 */

#include <smorphi_mini.h>

//Define the I2C address for each slave board
Adafruit_MotorShield AFMS1 (0x60);
Adafruit_MotorShield AFMS2 (0x61);


//Initialization for I/O expander on each slave board
Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;


//Adafruit calling (Swapped motor 3 & 4)
Adafruit_DCMotor *M11 = AFMS1.getMotor(1);
Adafruit_DCMotor *M12 = AFMS1.getMotor(2);
Adafruit_DCMotor *M13 = AFMS1.getMotor(4);
Adafruit_DCMotor *M14 = AFMS1.getMotor(3);

Adafruit_DCMotor *M21 = AFMS2.getMotor(1);
Adafruit_DCMotor *M22 = AFMS2.getMotor(2);
Adafruit_DCMotor *M23 = AFMS2.getMotor(4);
Adafruit_DCMotor *M24 = AFMS2.getMotor(3);



void Smorphi_mini::BeginSmorphi_mini()
{

//4 interrupt pins on master board
  pinMode(INT_PIN_1, INPUT); //for module 1
  pinMode(INT_PIN_2, INPUT); //for module 2


//begin the pwm driver
  AFMS1.begin();
  AFMS2.begin();


//begin the I/O expander
  mcp1.begin_I2C(0x20); //LSM bit swapped for GPIO expander and PWM driver
  mcp2.begin_I2C(0x21);


//setup the solenoids on each slave board
  mcp1.pinMode(14, INPUT_PULLUP);
  mcp2.pinMode(14, INPUT_PULLUP);



//setup for interrupts
  mcp1.setupInterrupts(true, false, LOW);
  mcp2.setupInterrupts(true, false, LOW);


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


}


void Smorphi_mini::set_interrupt_pin(){
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

  if (sm_getShape() == '1'){
    mcp1.setupInterruptPin(14, HIGH);
    mcp2.setupInterruptPin(14, HIGH);
  }

  if (sm_getShape() == '2'){
    mcp1.setupInterruptPin(14, HIGH);
    mcp2.setupInterruptPin(14, LOW);
  }
}

int Smorphi_mini::module1_sensor_status(int pin_no){
  int pin_status;
  pin_status = mcp1.digitalRead(pin_no);
  return pin_status;
}

int Smorphi_mini::module2_sensor_status(int pin_no){
  int pin_status;
  pin_status = mcp2.digitalRead(pin_no);
  return pin_status;
}

//sensor with interrupt test on module 1
int Smorphi_mini::module1_sensor_interrupt(){
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
double Smorphi_mini::mapPosRanges(int ipSpeed) //map user's input linear velocity to robot's actual positive linear velocity
{
  double mappedSpeed = ipSpeed * (sm_max_linear_speed) / 100;
  return mappedSpeed;
}

double Smorphi_mini::mapNegRanges(int ipSpeed) //map user's input linear velocity to robot's actual negative linear velocity
{
  double mappedSpeed = ipSpeed * (-sm_max_linear_speed) / 100;
  return mappedSpeed;
}

double Smorphi_mini::mapPosAng(int ipSpeed) //map user's input angular velocity to robot's actual positive angular velocity
{
  double mappedSpeed = ipSpeed * (sm_max_angular_speed) / 100;
  return mappedSpeed;
}

double Smorphi_mini::mapNegAng(int ipSpeed) //map user's input angular velocity to robot's actual negative angular velocity
{
  double mappedSpeed = ipSpeed * (-sm_max_angular_speed) / 100;
  return mappedSpeed;
}

int Smorphi_mini::map_lv_PWM(double ipSpeed) //map robot's linear velocity to PWM
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

int Smorphi_mini::map_ang_PWM(double ipSpeed) //map robot's angular velocity to PWM
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

int Smorphi_mini::map_turn_PWM(double ipSpeed) //map robot's curve velocity to PWM
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
int Smorphi_mini::sm_feedback(int solenoid_feedback){ 
  if (solenoid_feedback == 1){
    feedback_val = mcp1.digitalRead(14);
  }

  else if (solenoid_feedback == 2) {
    feedback_val = mcp2.digitalRead(14);
  }
  
  return feedback_val;
}

//set HIGH or LOW to the solenoid
void Smorphi_mini::sm_solenoid_set(int solenoid_unlock, bool status){ 
  if (solenoid_unlock == 1){
    AFMS1.setPin(0, status);
  }

  else if (solenoid_unlock == 2){
    AFMS2.setPin(0, status);
  }
  
}

//get the current shape 
char Smorphi_mini::sm_getShape(){ 
  if (sm_feedback(1)==1 && sm_feedback(2)==0){
    robot_shape = '1';
  }

  else if (sm_feedback(1)==0 && sm_feedback(2)==1){
    robot_shape = '2';
  }


  return robot_shape;
}

//Kinematic equations for all shapes
void Smorphi_mini::sm_velocity_handler(float sm_req_linear_speed_x, float sm_req_linear_speed_y, float sm_req_angular_speed)
{
  float v_x = sm_req_linear_speed_x;
  float v_y = sm_req_linear_speed_y;
  float w   = sm_req_angular_speed;

  char shape = sm_getShape();

  if (shape == '2')
  {
    // Module 1
    sm_lv_M1FL  =  (-v_x + v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FR  =  (-v_x - v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RL  =  (-v_x - v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RR  =  (-v_x + v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );


    // Module 2
    sm_lv_M2FL  =  (v_x - v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  (v_x + v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  (v_x + v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  (v_x - v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );



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
    // Serial.println("=========Linear_Velocity==========");

  }

  else if (shape == '1')
  {
    // Module 1
    sm_lv_M1FL  =  ( v_x - v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1FR  =  ( v_x + v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RL  =  ( v_x + v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M1RR  =  ( v_x - v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );

    // Module 2
    sm_lv_M2FL  =  ( v_x - v_y + 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2FR  =  ( v_x + v_y - 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RL  =  ( v_x + v_y - 0.085 * w - ( sm_wheel_x + sm_wheel_y) * w );
    sm_lv_M2RR  =  ( v_x - v_y + 0.085 * w + ( sm_wheel_x + sm_wheel_y) * w );


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
    // Serial.println("=========Linear_Velocity==========");

  }

}

int Smorphi_mini::sgn(double val)
{
  int ans;
  if (val == 0)
  {
    ans = 0;
  }
  else if (val>0)
  {
    ans = 1;
  }
  else{
    ans = -1;
  }
  return ans;
}

//map velocity after kinematics to pwm
void Smorphi_mini::sm_pwm_handler(int flag)
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
    // Serial.println("================PWM================");

    //store all the pwm values inside an array
    double sm_PWMs[2][4] = {{sm_PWM_M1FL, sm_PWM_M1FR, sm_PWM_M1RL, sm_PWM_M1RR},
              {sm_PWM_M2FL, sm_PWM_M2FR, sm_PWM_M2RL, sm_PWM_M2RR}
            };
    //set speed to each motor
    SetSmorphi_miniSpeed(sm_PWMs);
}



void Smorphi_mini::SetSmorphi_miniSpeed(double pwm[2][4])
{

  M11->setSpeed(pwm[0][0]);
  M12->setSpeed(pwm[0][1]);
  M13->setSpeed(pwm[0][2]);
  M14->setSpeed(pwm[0][3]);

  M21->setSpeed(pwm[1][0]);
  M22->setSpeed(pwm[1][1]);
  M23->setSpeed(pwm[1][2]);
  M24->setSpeed(pwm[1][3]);

}

//handle the motor driving direction
void Smorphi_mini::MotorDirection(){

  double sm_lvs[2][4] = {{sm_lv_M1FL,sm_lv_M1FR,sm_lv_M1RL,sm_lv_M1RR},
                    {sm_lv_M2FL,sm_lv_M2FR,sm_lv_M2RL,sm_lv_M2RR}};

  Adafruit_DCMotor *sm_motors[2][4] = {{M11,M12,M13,M14},
                      {M21,M22,M23,M24}};

  for (int i=0; i<2; i++){
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
void Smorphi_mini::MoveForward(const int Speed)
{
  double vel_speed = mapPosRanges(Speed);
  sm_velocity_handler(vel_speed, 0, 0);
  int flag = 0;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi_mini::MoveBackward(const int Speed)
{
  double vel_speed = mapNegRanges(Speed);
  sm_velocity_handler(vel_speed, 0, 0);
  int flag = 0;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi_mini::MoveRight(const int Speed)
{
  double vel_speed = mapNegRanges(Speed);
  sm_velocity_handler(0, vel_speed, 0);
  int flag = 0;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi_mini::MoveLeft(const int Speed)
{
  double vel_speed = mapPosRanges(Speed);
  sm_velocity_handler(0, vel_speed, 0);
  int flag = 0;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi_mini::MoveDiagUpRight(const int Speed)
{
  double vel_speed_x = mapPosRanges(Speed)/2;
  double vel_speed_y = mapNegRanges(Speed)/2;
  sm_velocity_handler(vel_speed_x+0.001, vel_speed_y, 0);
  int flag = 3;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi_mini::MoveDiagUpLeft(const int Speed)
{
  double vel_speed = mapPosRanges(Speed)/2;
  sm_velocity_handler(vel_speed+0.001, vel_speed, 0);
  int flag = 3;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi_mini::MoveDiagDownRight(const int Speed)
{

  double vel_speed = mapNegRanges(Speed)/2;
  sm_velocity_handler(vel_speed-0.001, vel_speed, 0);
  int flag = 3;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi_mini::MoveDiagDownLeft(const int Speed)
{
  
  double vel_speed_x = mapNegRanges(Speed)/2;
  double vel_speed_y = mapPosRanges(Speed)/2;
  sm_velocity_handler(vel_speed_x-0.001, vel_speed_y, 0);
  int flag = 3;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi_mini::MoveTurnUpRight(const int Speed, const int angular_velocity)
{
  
  double vel_speed = mapPosRanges(Speed);
  double ang_speed = mapNegAng(angular_velocity);
  sm_velocity_handler(vel_speed, 0, ang_speed);
  int flag = 1;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi_mini::MoveTurnUpLeft(const int Speed, const int angular_velocity)
{
  
  double vel_speed = mapPosRanges(Speed);
  double ang_speed = mapPosAng(angular_velocity);
  sm_velocity_handler(vel_speed, 0, ang_speed);
  int flag = 1;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi_mini::MoveTurnDownRight(const int Speed, const int angular_velocity)
{
  
  double vel_speed = mapNegRanges(Speed);
  double ang_speed = mapNegAng(angular_velocity);
  sm_velocity_handler(vel_speed, 0, ang_speed);
  int flag = 1;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi_mini::MoveTurnDownLeft(const int Speed, const int angular_velocity)
{
  double vel_speed = mapNegRanges(Speed);
  double ang_speed = mapPosAng(angular_velocity);
  sm_velocity_handler(vel_speed, 0, ang_speed);
  int flag = 1;
  sm_pwm_handler(flag);
  MotorDirection();

}

void Smorphi_mini::stopSmorphi_mini()
{ 

  M11->run(RELEASE);
  M12->run(RELEASE);
  M13->run(RELEASE);
  M14->run(RELEASE);

  M21->run(RELEASE);
  M22->run(RELEASE);
  M23->run(RELEASE);
  M24->run(RELEASE);

}

void Smorphi_mini::CenterPivotLeft(const int angular_velocity)
{
  
  double ang_speed = mapPosAng(angular_velocity);
  sm_velocity_handler(0, 0, ang_speed);
  int flag = 2;
  sm_pwm_handler(flag);
  MotorDirection();
}

void Smorphi_mini::CenterPivotRight(const int angular_velocity)
{
  double ang_speed = mapNegAng(angular_velocity);
  sm_velocity_handler(0, 0, ang_speed);
  int flag = 2;
  sm_pwm_handler(flag);
  MotorDirection();
}

//clear the velocity variables for each module 
void Smorphi_mini::sm_reset_M1()
{
  sm_lv_M1FL  =  0;
  sm_lv_M1FR  =  0;
  sm_lv_M1RL  =  0;
  sm_lv_M1RR  =  0;
}

void Smorphi_mini::sm_reset_M2()
{
  sm_lv_M2FL  =  0;
  sm_lv_M2FR  =  0;
  sm_lv_M2RL  =  0;
  sm_lv_M2RR  =  0;
}


//interrupt testing
void Smorphi_mini::interrupt_test()
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
}
