#include "HUSKYLENS.h"      // Library for HuskyLens
#include "SoftwareSerial.h" // Library for Software Serial
#include <smorphi.h>        // Library for Smorphi

Smorphi my_robot;  
HUSKYLENS huskylens;        // Create an object for HuskyLens

SoftwareSerial myHuskySerial(26, 27); // RX is Pin 26, TX is Pin 27

void printResult(HUSKYLENSResult result); //Function for serial print results from the sensor

void setup() {
    Serial.begin(115200);
    myHuskySerial.begin(9600);         //Baud rate for HuskyLens communication. Can change from GUI of the HuskyLens
    my_robot.BeginSmorphi();
    while (!huskylens.begin(myHuskySerial)) //Establishing communication with HuskyLens
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void loop() {
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result); //Displaying results through serial monitor
            if (result.ID == 1 && result.command == COMMAND_RETURN_BLOCK) //If the learned face is detected and recognized as ID 1
            {
                Serial.println("I know the person"); //Display in serial monitor
                my_robot.O(); //If the learned face is detected and recognized, Smorphi will reconfigure to 'O' shape.
            }   
        }    
    }
}

void printResult(HUSKYLENSResult result){                    //This is to display results through serial monitor. 
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}
