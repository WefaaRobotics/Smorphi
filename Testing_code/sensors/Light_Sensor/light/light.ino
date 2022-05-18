//#include <AStar32U4.h>
int LDRSensor = 16;
 
void setup()
 {
  //Initialize Sensor (pin3) as an INPUT.
  pinMode (LDRSensor, INPUT_PULLUP);
  //Define baud rate for serial communication
  Serial.begin (115200);
 }
 
void loop()
 {
  //Read Digital output value from sensor using digitalRead()function
  int Sensordata = digitalRead (LDRSensor);
  //Print the sensor value on your serial  monitor window
  Serial.print("Sensor value:");
  Serial.println(Sensordata);
  //Delay for 1 second to get clear output on the serial monitor
  delay(100);
 }
