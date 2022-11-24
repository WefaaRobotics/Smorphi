// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <smorphi.h>

// Data wire is plugged into port 1 on the Arduino
#define ONE_WIRE_BUS 16

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Initialise the robot
Smorphi my_robot;

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    
    // if temperature is more than 30°C, Smorphi moves forward
    if (tempC > 30) 
    {
      my_robot.MoveForward(10);
    }
    // if temperature is less than 30°C, Smorphi stops
    else
    {
      my_robot.stopSmorphi();
    }
  } 
  
  else
  {
    Serial.println("Error: Could not read temperature data");
  }

  
}
