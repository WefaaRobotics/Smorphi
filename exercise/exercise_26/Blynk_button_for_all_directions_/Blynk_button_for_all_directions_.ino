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
 

#define button2_vpin    V2
#define button3_vpin    V7
#define button4_vpin    V8   
#define button5_vpin    V9

 
BLYNK_CONNECTED() {
  //get latest value from v2,v10,v11,v12
  Blynk.syncVirtual(button2_vpin);
  Blynk.syncVirtual(button3_vpin);
  Blynk.syncVirtual(button4_vpin);
  Blynk.syncVirtual(button5_vpin);
}
 
BLYNK_WRITE(button2_vpin) {
  int forward = param.asInt();
  
  if ( forward == 1){
   // do something when button is pressed;
   my_robot.MoveForward(10);
  } else if (forward == 0) {
   // do something when button is released;
    my_robot.sm_reset_M1();
    my_robot.sm_reset_M2();
    my_robot.sm_reset_M3();
    my_robot.sm_reset_M4();
    my_robot.stopSmorphi();
  }
  Blynk.virtualWrite(button2_vpin,forward);
  Serial.print("V2 button value is: "); // printing value to serial monitor
  Serial.println(forward);
}

BLYNK_WRITE(button3_vpin) {
  int left = param.asInt();
  
  if ( left == 1){
   // do something when button is pressed;
   my_robot.MoveLeft(10);
  } else if (left == 0) {
   // do something when button is released;
    my_robot.sm_reset_M1();
    my_robot.sm_reset_M2();
    my_robot.sm_reset_M3();
    my_robot.sm_reset_M4();
    my_robot.stopSmorphi();
  }
  Blynk.virtualWrite(button3_vpin,left);
  Serial.print("V10 button value is: "); // printing value to serial monitor
  Serial.println(left);
}

BLYNK_WRITE(button4_vpin) {
  int right = param.asInt();
  
  if ( right == 1){
   // do something when button is pressed;
   my_robot.MoveRight(10);
  } else if (right == 0) {
   // do something when button is released;
    my_robot.sm_reset_M1();
    my_robot.sm_reset_M2();
    my_robot.sm_reset_M3();
    my_robot.sm_reset_M4();
    my_robot.stopSmorphi();
  }
  Blynk.virtualWrite(button4_vpin,right);
  Serial.print("V11 button value is: "); // printing value to serial monitor
  Serial.println(right);
}

BLYNK_WRITE(button5_vpin) {
  int back = param.asInt();
  
  if ( back == 1){
   // do something when button is pressed;
   my_robot.MoveBackward(10);
  } else if (back == 0) {
   // do something when button is released;
    my_robot.sm_reset_M1();
    my_robot.sm_reset_M2();
    my_robot.sm_reset_M3();
    my_robot.sm_reset_M4();
    my_robot.stopSmorphi();
  }
  Blynk.virtualWrite(button5_vpin,back);
  Serial.print("V12 button value is: "); // printing value to serial monitor
  Serial.println(back);
}
 
 
void setup()
{
  my_robot.BeginSmorphi();
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 
}
 
void loop()
{
  Blynk.run(); //to tun blynk
  timer.run();
  Blynk.setProperty(V2, "isDisabled", false);

}
