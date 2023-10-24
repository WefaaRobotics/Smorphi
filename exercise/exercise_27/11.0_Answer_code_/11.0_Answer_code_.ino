/*Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6s3bkEJxD"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "dR-liEEld3wXXf3JBRaawOuhJsE_Pdpd"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WEFAA_Office";
char pass[] = "Wefaa_2023";

BlynkTimer timer;

//smorphi library
#include <smorphi.h>
Smorphi my_robot;

// Variables for the Blynk widget values
int x = 50;
int y = 50;

#define button2_vpin    V2
#define button3_vpin    V7
#define button4_vpin    V8   
#define button5_vpin    V9
#define button6_vpin    V10
#define button7_vpin    V11  
#define button8_vpin    V12


BLYNK_CONNECTED() {
  //get latest value from all the data stream
  Blynk.syncVirtual(button2_vpin);
  Blynk.syncVirtual(button3_vpin);
  Blynk.syncVirtual(button4_vpin);
  Blynk.syncVirtual(button5_vpin);
  Blynk.syncVirtual(button6_vpin);
  Blynk.syncVirtual(button7_vpin);
  Blynk.syncVirtual(button8_vpin);

}


BLYNK_WRITE(V3) {
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

  if ( y >128 && x>=80 && x<=176){
    my_robot.MoveForward(10);
    Serial.println("carForward");
  }
  else if (y<128 && x>=80 && x<=176){
    my_robot.MoveBackward(10);
    Serial.println("carBackward");
  } 
  else if (y>=80 && y<=176 && x>128){
    my_robot.MoveRight(10);
    Serial.println("carRight");
  }
  else if (y>=80 && y<=176 && x<128){
    my_robot.MoveLeft(10);
    Serial.println("carLeft");
  }
  else if (y>128 && x>0 && x<80){
    my_robot.MoveDiagUpLeft(30);
    Serial.println("carUpLeft ");
  }
  else if (y>128 && x>176 && x<255){
    my_robot.MoveDiagUpRight(30);
    Serial.println("carUpRight ");
  }
  else if (y<128 && x>0 && x<80){
    my_robot.MoveDiagDownLeft(30);
    Serial.println("carDownLeft ");
  }
  else if (y<128 && x>176 && x<255){
    my_robot.MoveDiagDownRight(30);
    Serial.println("carDownRight ");
  }
  else if (y==128 && x== 128){
    my_robot.sm_reset_M1();
    my_robot.sm_reset_M2();
    my_robot.sm_reset_M3();
    my_robot.sm_reset_M4();
    my_robot.stopSmorphi();
    Serial.println("carstop");
  } 

}

BLYNK_WRITE(button2_vpin) {
  int shapeI = param.asInt();
  
  if ( shapeI == 1){
   // do something when button is pressed;
   my_robot.sm_reset_M1();
   my_robot.sm_reset_M2();
   my_robot.sm_reset_M3();
   my_robot.sm_reset_M4();
   my_robot.I();
  } else if (shapeI == 0) {
   // do something when button is released;
  }
  Blynk.virtualWrite(button2_vpin,shapeI);
  Serial.print("V2 button value is: "); // printing value to serial monitor
  Serial.println(shapeI);
}

BLYNK_WRITE(button3_vpin) {
  int shapeO = param.asInt();
  
  if ( shapeO == 1){
   // do something when button is pressed;
   my_robot.sm_reset_M1();
   my_robot.sm_reset_M2();
   my_robot.sm_reset_M3();
   my_robot.sm_reset_M4();
   my_robot.O();
  } else if (shapeO == 0) {
   // do something when button is released;
  }
  Blynk.virtualWrite(button3_vpin,shapeO);
  Serial.print("V7 button value is: "); // printing value to serial monitor
  Serial.println(shapeO);
}

BLYNK_WRITE(button4_vpin) {
  int shapeL = param.asInt();
  
  if ( shapeL == 1){
   // do something when button is pressed;
   my_robot.sm_reset_M1();
   my_robot.sm_reset_M2();
   my_robot.sm_reset_M3();
   my_robot.sm_reset_M4();
   my_robot.L();
  } else if (shapeL == 0) {
   // do something when button is released;
  }
  Blynk.virtualWrite(button4_vpin,shapeL);
  Serial.print("V8 button value is: "); // printing value to serial monitor
  Serial.println(shapeL);
}

BLYNK_WRITE(button5_vpin) {
  int shapeJ = param.asInt();
  
  if ( shapeJ == 1){
   // do something when button is pressed;
   my_robot.sm_reset_M1();
   my_robot.sm_reset_M2();
   my_robot.sm_reset_M3();
   my_robot.sm_reset_M4();
   my_robot.J();
  } else if (shapeJ == 0) {
   // do something when button is released;
  }
  Blynk.virtualWrite(button5_vpin,shapeJ);
  Serial.print("V9 button value is: "); // printing value to serial monitor
  Serial.println(shapeJ);
}

BLYNK_WRITE(button6_vpin) {
  int shapeZ = param.asInt();
  
  if ( shapeZ == 1){
   // do something when button is pressed;
   my_robot.sm_reset_M1();
   my_robot.sm_reset_M2();
   my_robot.sm_reset_M3();
   my_robot.sm_reset_M4();
   my_robot.Z();
  } else if (shapeZ == 0) {
   // do something when button is released;
  }
  Blynk.virtualWrite(button6_vpin,shapeZ);
  Serial.print("V10 button value is: "); // printing value to serial monitor
  Serial.println(shapeZ);
}

BLYNK_WRITE(button7_vpin) {
  int shapeS = param.asInt();
  
  if ( shapeS == 1){
   // do something when button is pressed;
   my_robot.sm_reset_M1();
   my_robot.sm_reset_M2();
   my_robot.sm_reset_M3();
   my_robot.sm_reset_M4();
   my_robot.S();
  } else if (shapeS == 0) {
   // do something when button is released;
  }
  Blynk.virtualWrite(button7_vpin,shapeS);
  Serial.print("V11 button value is: "); // printing value to serial monitor
  Serial.println(shapeS);
}

BLYNK_WRITE(button8_vpin) {
  int shapeT = param.asInt();
  
  if ( shapeT == 1){
   // do something when button is pressed;
   my_robot.sm_reset_M1();
   my_robot.sm_reset_M2();
   my_robot.sm_reset_M3();
   my_robot.sm_reset_M4();
   my_robot.T();
  } else if (shapeT == 0) {
   // do something when button is released;
  }
  Blynk.virtualWrite(button8_vpin,shapeT);
  Serial.print("V12 button value is: "); // printing value to serial monitor
  Serial.println(shapeT);
}

void setup()
{
  my_robot.BeginSmorphi();
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


void loop()
{
  Blynk.run();//run blynk
  Blynk.setProperty(V2, "isDisabled", false);
}
