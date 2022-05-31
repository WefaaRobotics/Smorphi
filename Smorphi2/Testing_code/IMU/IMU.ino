#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);

float x_rot;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("test");
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.update();
  Serial.print("X : ");
  Serial.print(mpu.getAngleX());
  Serial.print("\tY : ");
  Serial.print(mpu.getAngleY());
  Serial.print("\tZ : ");
  Serial.println(mpu.getAngleZ());
  x_rot = mpu.getAngleX();
  Serial.println(x_rot);
  delay(50);
}



//#include <Wire.h> //include Wire.h library
//
//void setup()
//{
//  Wire.begin(21, 22); // Wire communication begin
//  Serial.begin(9600); // The baudrate of Serial monitor is set in 9600
//  while (!Serial); // Waiting for Serial Monitor
//  Serial.println("\nI2C Scanner");
//}
//
//void loop()
//{
//  byte error, address; //variable for error and I2C address
//  int nDevices;
//
//  Serial.println("Scanning...");
//
//  nDevices = 0;
//  for (address = 1; address < 127; address++ )
//  {
//    // The i2c_scanner uses the return value of
//    // the Write.endTransmisstion to see if
//    // a device did acknowledge to the address.
//    Wire.beginTransmission(address);
//    error = Wire.endTransmission();
//
//    if (error == 0)
//    {
//      Serial.print("I2C device found at address 0x");
//      if (address < 16)
//        Serial.print("0");
//      Serial.print(address, HEX);
//      Serial.println("  !");
//      nDevices++;
//    }
//    else if (error == 4)
//    {
//      Serial.print("Unknown error at address 0x");
//      if (address < 16)
//        Serial.print("0");
//      Serial.println(address, HEX);
//    }
//  }
//  if (nDevices == 0)
//    Serial.println("No I2C devices found\n");
//  else
//    Serial.println("done\n");
//
//  delay(5000); // wait 5 seconds for the next I2C scan
//}
