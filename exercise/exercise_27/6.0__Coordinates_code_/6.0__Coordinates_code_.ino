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

BLYNK_WRITE(V3) {
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);
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
