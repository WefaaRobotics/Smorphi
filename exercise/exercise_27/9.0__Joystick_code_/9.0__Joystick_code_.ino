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

void setup()
{
  my_robot.BeginSmorphi();
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


void loop()
{
  Blynk.run();//run blynk
}
