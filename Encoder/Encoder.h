#ifndef Encoder_H_
#define Encoder_H_


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_MCP23X17.h>
//#include <Adafruit_SSD1306.h>
uint32_t cp0_regs[18];

//Initialization for I/O expander on each slave board


// Connect Motor 1's two encoder outputs!
#define ENCODER_A_M1   16
#define ENCODER_B_M1   17
// Connect Motor 2's two encoder outputs!
#define ENCODER_A_M2   19
#define ENCODER_B_M2   18

// Connect Motor 3's two encoder outputs!
#define ENCODER_A_M3   25
#define ENCODER_B_M3   23

// Connect Motor 4's two encoder outputs!
#define ENCODER_A_M4   26
#define ENCODER_B_M4   27

// These let us convert ticks-to-RPM
#define GEARING     45 //20
#define ENCODERMULT 13 //12

int enc_cons1 = 60000000/(GEARING*ENCODERMULT);
float enc_cons = 1/273.0 *1000000;


// void IRAM_ATTR interruptA_M1();
// void IRAM_ATTR interruptA_M2();
// void IRAM_ATTR interruptA_M3();
// void IRAM_ATTR interruptA_M4();

volatile int counter = 0;

int arr[2] = {-1,1};
volatile float RPM_M1 = 0;
volatile float RPM_M2 = 0;
volatile float RPM_M3 = 0;
volatile float RPM_M4 = 0;
volatile float RPS_M1 = 0;
volatile float RPS_M2 = 0;
volatile float RPS_M3 = 0;
volatile float RPS_M4 = 0;
volatile float V_x = 0;
volatile float V_y = 0;
volatile float W_z = 0;
volatile uint32_t lastA_1 = 0;
volatile uint32_t lastA_2 = 0;
volatile uint32_t lastA_3 = 0;
volatile uint32_t lastA_4 = 0;
volatile bool motordir_M1 = FORWARD;
volatile bool motordir_M2 = FORWARD;
volatile bool motordir_M3 = FORWARD;
volatile bool motordir_M4 = FORWARD;
uint32_t currA_2;
uint32_t currA_1;
uint32_t currA_3;
uint32_t currA_4;

// class ENCODER{
//   public:

    void interruptA_M1();
    void interruptA_M2();
    void interruptA_M3();
    void interruptA_M4();


    void encoder_begin() {
      // Serial.begin(9600);           // set up Serial library at 9600 bps
    //  pinMode(LED_BUILTIN, OUTPUT);
    //  digitalWrite(LED_BUILTIN, LOW);
     
      pinMode(ENCODER_B_M1, INPUT_PULLUP);
      pinMode(ENCODER_A_M1, INPUT_PULLUP);
      pinMode(ENCODER_B_M2, INPUT_PULLUP);
      pinMode(ENCODER_A_M2, INPUT_PULLUP);
      pinMode(ENCODER_B_M3, INPUT_PULLUP);
      pinMode(ENCODER_A_M3, INPUT_PULLUP);
      pinMode(ENCODER_B_M4, INPUT_PULLUP);
      pinMode(ENCODER_A_M4, INPUT_PULLUP);
      attachInterrupt(ENCODER_A_M1, interruptA_M1, RISING);
      attachInterrupt(ENCODER_A_M2, interruptA_M2, RISING);
      attachInterrupt(ENCODER_A_M3, interruptA_M3, RISING);
      attachInterrupt(ENCODER_A_M4, interruptA_M4, RISING);

    
    }


  
   
   
   
    // void printRPM_1() {
    // //    display.clearDisplay();
    // //    display.setCursor(0,0);

    //     Serial.print("M1_Direction: ");
    //     if (motordir_M1) {
    // //      display.println("Forward");
    //       Serial.println("M1_forward @ ");
    //     } else {
    // //      display.println("Backward");
    //       Serial.println("M1_backward @ ");
    //     }
    // //    display.print((int)RPM); display.println(" RPM");
    // //    Serial.print((int)RPM_M1); Serial.println(" M1_RPM");
    //       Serial.print((float)RPS_M1); Serial.println(" M1_RPS");
    // //    display.display();
    // }

    // void printRPM_2() {
    // //    display.clearDisplay();
    // //    display.setCursor(0,0);

    //     Serial.print("M2_Direction: ");
    //     if (motordir_M2) {
    // //      display.println("Forward");
    //       Serial.println("M2_forward @ ");
    //     } else {
    // //      display.println("Backward");
    //       Serial.println("M2_backward @ ");
    //     }
    // //    display.print((int)RPM); display.println(" RPM");
    // //    Serial.print((int)RPM_M2); Serial.println(" M2_RPM");
    //       Serial.print((float)RPS_M2); Serial.println(" M2_RPS");
    // //    display.display();
    // }

    // void printRPM_3() {
    // //    display.clearDisplay();
    // //    display.setCursor(0,0);

    //     Serial.print("M3_Direction: ");
    //     if (motordir_M3) {
    // //      display.println("Forward");
    //       Serial.println("M3_forward @ ");
    //     } else {
    // //      display.println("Backward");
    //       Serial.println("M3_backward @ ");
    //     }
    // //    display.print((int)RPM); display.println(" RPM");
    // //    Serial.print((int)RPM_M3); Serial.println(" M3_RPM");
    //       Serial.print((float)RPS_M3); Serial.println(" M3_RPS");
    // //    display.display();
    // }

    // void printRPM_4() {
    // //    display.clearDisplay();
    // //    display.setCursor(0,0);

    //     Serial.print("M4_Direction: ");
    //     if (motordir_M4) {
    // //      display.println("Forward");
    //       Serial.println("M4_forward @ ");
    //     } else {
    // //      display.println("Backward");
    //       Serial.println("M4_backward @ ");
    //     }
    // //    display.print((int)RPM); display.println(" RPM");
    // //    Serial.print((int)RPM_M4); Serial.println(" M4_RPM");
    //       Serial.print((float)RPS_M4); Serial.println(" M4_RPS");
    // //    display.display();
    // }

  void interruptA_M1() {
     counter++;
    uint32_t cp_state = xthal_get_cpenable();
    if(cp_state){
      xthal_save_cp0(cp0_regs);
    }
    else{
      xthal_set_cpenable(1);
    }
    
    motordir_M1 = digitalRead(ENCODER_B_M1);

    

  //  digitalWrite(LED_BUILTIN, HIGH);
     currA_1 = micros();

    
    if (lastA_1 < currA_1) {
      // did not wrap around
      float rev_1 = currA_1 - lastA_1;  // us
  //    rev_1 = 1.0 / rev_1;            // rev per us
  //    rev_1 *= 1000000;             // rev per sec
  //    rev_1 *= 60;                  // rev per min
  //    rev_1 /= GEARING;             // account for gear ratio
  //    rev_1 /= ENCODERMULT;         // account for multiple ticks per rotation
  //    rev_1 *=enc_cons;
      RPS_M1 = enc_cons/rev_1;
      
      RPS_M1 = RPS_M1 * arr[motordir_M1];
      //RPM_M1 = RPS_M1 * 60;
      RPS_M1 = RPS_M1*2*3.14;
  //    Serial.println(rev_1);
      if(cp_state){
        xthal_restore_cp0(cp0_regs);
      }
    else{
        xthal_set_cpenable(0);
      }

  //    rev = 1.0 / rev;            // rev per us
  //    rev /= 1000000;             // rev per sec
  //    rev /= 60;                  // rev per min
  //    rev *= GEARING;             // account for gear ratio
  //    rev *= ENCODERMULT;         // account for multiple ticks per rotation
  //    RPM = rev;
    }
    lastA_1 = currA_1;
  //  digitalWrite(LED_BUILTIN, LOW);
  //Serial.println(rev_1);
  
}


    void evaluate_velocity_feedback() {
    //    display.clearDisplay();
    //    display.setCursor(0,0);
    
    uint32_t current_time = micros();
    if (current_time - currA_1 > 10000 && current_time - currA_2 > 10000 && current_time - currA_3 > 10000 && current_time - currA_4 > 10000){
    RPS_M1 = RPS_M2 =RPS_M3=RPS_M4 = 0;
    }
        V_x = (RPS_M1+RPS_M2+RPS_M4+RPS_M3)*0.0075;
        V_y = (-RPS_M1+RPS_M2+RPS_M4-RPS_M3)*0.0075;
        W_z = (-RPS_M1+RPS_M2-RPS_M4+RPS_M3)*0.000797;

    //    Serial.print("V_x: ");
    //    if (motordir_M4) {
    ////      display.println("Forward");
    //      Serial.println("M4_forward @ ");
    //    } else {
    ////      display.println("Backward");
    //      Serial.println("M4_backward @ ");
    //    }
    //    display.print((int)RPM); display.println(" RPM");
    //    Serial.print((int)RPM_M4); Serial.println(" M4_RPM");
          // Serial.print((float)V_x); Serial.println("V_x");
          // Serial.print((float)V_y); Serial.println("V_y");
          // Serial.print((float)W_z); Serial.println("W_z");
    //    display.display();
    }

    // #include<ENCODER.h>
void interruptA_M2() {

  uint32_t cp_state = xthal_get_cpenable();
  if(cp_state){
    xthal_save_cp0(cp0_regs);
  }
  else{
    xthal_set_cpenable(1);
  }
  
  motordir_M2 = digitalRead(ENCODER_B_M2);

  

//  digitalWrite(LED_BUILTIN, HIGH);
   currA_2 = micros();
  
  if (lastA_2 < currA_2) {
    // did not wrap around
    float rev_2 = currA_2 - lastA_2;  // us
//    rev_2 = 1.0 / rev_2;            // rev per us
//    rev_2 *= 1000000;             // rev per sec
//    rev_2 *= 60;                  // rev per min
//    rev_2 /= GEARING;             // account for gear ratio
//    rev_2 /= ENCODERMULT;         // account for multiple ticks per rotation
      RPS_M2 = enc_cons/rev_2;
      
      RPS_M2 = RPS_M2 * arr[motordir_M2];
      RPS_M2 = RPS_M2 * 2 *3.14;
      //RPM_M2 = RPS_M2 * 60;
    if(cp_state){
      xthal_restore_cp0(cp0_regs);
    }
   else{
      xthal_set_cpenable(0);
    }

//    rev = 1.0 / rev;            // rev per us
//    rev /= 1000000;             // rev per sec
//    rev /= 60;                  // rev per min
//    rev *= GEARING;             // account for gear ratio
//    rev *= ENCODERMULT;         // account for multiple ticks per rotation
//    RPM = rev;
  }
  lastA_2 = currA_2;
//  digitalWrite(LED_BUILTIN, LOW);
}

// #include<ENCODER.h>
void interruptA_M3() {

  uint32_t cp_state = xthal_get_cpenable();
  if(cp_state){
    xthal_save_cp0(cp0_regs);
  }
  else{
    xthal_set_cpenable(1);
  }
  
  motordir_M3 = digitalRead(ENCODER_B_M3);

  

//  digitalWrite(LED_BUILTIN, HIGH);
   currA_3 = micros();
  
  if (lastA_3 < currA_3) {
    // did not wrap around
    float rev_3 = currA_3 - lastA_3;  // us
//    rev_3 = 1.0 / rev_3;            // rev per us
//    rev_3 *= 1000000;             // rev per sec
//    rev_3 *= 60;                  // rev per min
//    rev_3 /= GEARING;             // account for gear ratio
//    rev_3 /= ENCODERMULT;         // account for multiple ticks per rotation
    RPS_M3 = enc_cons/rev_3;
    RPS_M3 = RPS_M3 * arr[motordir_M3];
    RPS_M3 = RPS_M3 * 2*3.14;
    if(cp_state){
      xthal_restore_cp0(cp0_regs);
    }
   else{
      xthal_set_cpenable(0);
    }

//    rev = 1.0 / rev;            // rev per us
//    rev /= 1000000;             // rev per sec
//    rev /= 60;                  // rev per min
//    rev *= GEARING;             // account for gear ratio
//    rev *= ENCODERMULT;         // account for multiple ticks per rotation
//    RPM = rev;
  }
  lastA_3 = currA_3;
//  digitalWrite(LED_BUILTIN, LOW);
}

// #include<ENCODER.h>
void interruptA_M4() {

  uint32_t cp_state = xthal_get_cpenable();
  if(cp_state){
    xthal_save_cp0(cp0_regs);
  }
  else{
    xthal_set_cpenable(1);
  }
  
  motordir_M4 = digitalRead(ENCODER_B_M4);

  

//  digitalWrite(LED_BUILTIN, HIGH);
   currA_4 = micros();
  
  if (lastA_4 < currA_4) {
    // did not wrap around
    float rev_4 = currA_4 - lastA_4;  // us
//    rev_4 = 1.0 / rev_4;            // rev per us
//    rev_4 *= 1000000;             // rev per sec
//    rev_4 *= 60;                  // rev per min
//    rev_4 /= GEARING;             // account for gear ratio
//    rev_4 /= ENCODERMULT;         // account for multiple ticks per rotation
    RPS_M4 = enc_cons/rev_4;
    RPS_M4 = RPS_M4 * arr[motordir_M4];
    RPS_M4 = RPS_M4 * 2*3.14;
    if(cp_state){
      xthal_restore_cp0(cp0_regs);
    }
   else{
      xthal_set_cpenable(0);
    }

//    rev = 1.0 / rev;            // rev per us
//    rev /= 1000000;             // rev per sec
//    rev /= 60;                  // rev per min
//    rev *= GEARING;             // account for gear ratio
//    rev *= ENCODERMULT;         // account for multiple ticks per rotation
//    RPM = rev;
  }
  lastA_4 = currA_4;
//  digitalWrite(LED_BUILTIN, LOW);
}

// };


#endif
