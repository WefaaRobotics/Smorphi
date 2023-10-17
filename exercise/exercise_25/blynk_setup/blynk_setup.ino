/*************************************************************

  This is a simple demo of sending and receiving some data.
  
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6s3bkEJxD"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "dR-liEEld3wXXf3JBRaawOuhJsE_Pdpd"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WEFAA_Office";
char pass[] = "Wefaa_2023";

BlynkTimer timer;

//led and button pins
#define button2_pin 10
#define led2_pin 2
int led2_state = 1;
#define button2_vpin    V2

//smorphi Library needed
#include <OneWire.h>
#include <DallasTemperature.h>
#include <smorphi.h>
#define ONE_WIRE_BUS 16
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Smorphi my_robot;
//************************************************

//function sends arduino to virtual pin 16
//this core function sense temperature
void sendSensor()
{ 
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  Blynk.virtualWrite(V16, tempC); //v16 temperature sensor 
}

BLYNK_WRITE(button2_vpin) {
  led2_state = param.asInt();
  digitalWrite(led2_pin, led2_state);
}


//function sends arduino to virtual pin 16
//this core function sense temperature
BLYNK_WRITE(V16)
{
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  Blynk.virtualWrite(V16, tempC); //v16 temperature sensor 
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(button2_vpin);
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup()
{
  Serial.begin(115200);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  pinMode(button2_pin, INPUT_PULLUP);
  pinMode(led2_pin, OUTPUT);
  digitalWrite(led2_pin, HIGH);
  delay(200);
  listen_push_buttons();

  // Setup a function to be called every second
  sensors.begin();
   timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    
    // if temperature is more than 30°C, what will happen?
    if (tempC > 29) {
      Blynk.setProperty(V2, "isDisabled", false);
      digitalWrite(led2_pin, led2_state);
       delay(200);
      }
    // if temperature is less than 30°C, what will happen?
    else {
      digitalWrite(led2_pin, LOW);
      // your code
     Blynk.setProperty(V2, "isDisabled", true);
     delay(200);
      
    }
  }

  // happens when reading is unsuccesful
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
}

void listen_push_buttons(){
    if(digitalRead(button2_pin) == LOW){
      control_led(2);
      delay(200);
      Blynk.virtualWrite(button2_vpin, led2_state); 
    }
    else{
      
    }
}
 
void control_led(int led){
 
  if(led == 2){
    led2_state = !led2_state;
    digitalWrite(led2_pin, led2_state);
    Serial.print("led2 State = ");
    Serial.println(led2_state);
    delay(50);
  }
  else{
    
  }
  
}
