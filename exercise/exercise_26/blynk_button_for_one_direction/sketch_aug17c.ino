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

 
BLYNK_CONNECTED() {
  //get latest value from v2
  Blynk.syncVirtual(button2_vpin);
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

 
 
void setup()
{
  my_robot.BeginSmorphi();
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 
}
 
void loop()
{
  Blynk.run();//to run blynk
  timer.run();
  Blynk.setProperty(V2, "isDisabled", false);

}
