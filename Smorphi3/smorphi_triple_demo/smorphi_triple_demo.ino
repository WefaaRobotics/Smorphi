//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include <smorphi_triple.h>

Smorphi_triple my_robot;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String command = "";
String data_received = "";

void setup() {
  Serial.begin(115200); 
  my_robot.BeginSmorphiTriple();
  SerialBT.begin("smorphi3"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Wire.begin();   
//  Wire.setClock(400000); 
}

void i2c(){
   byte error, address; //variable for error and I2C address
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(500); // wait 5 seconds for the next I2C scan
}
 

void loop() {
//  i2c();
//  Serial.print(my_robot.sm_feedback(1));
//  Serial.print(my_robot.sm_feedback(2));
//  Serial.print(my_robot.sm_feedback(3));
//  Serial.print(my_robot.sm_feedback(4));
//  Serial.print(my_robot.sm_feedback(5));
//  Serial.println(my_robot.sm_feedback(6));
//  delay(10);

  while (SerialBT.available()) {

    data_received = data_received + char(SerialBT.read());

    if (data_received == "shape_i") {
      my_robot.I();  
      Serial.print("transmission complete!! ");
      Serial.println(data_received);
      data_received = "";
    }
    else if (data_received == "shape_o") {
      my_robot.J(); 
      Serial.print("transmission complete!! ");
      Serial.println(data_received);
      data_received = "";
    }
    
    
    else if (data_received == "forwardfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveForward(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "forwardmidfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveForward(75);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "forwardmidslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveForward(50);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "forwardslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveForward(25);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "backwardfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveBackward(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "backwardmidfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveBackward(75);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "backwardmidslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveBackward(50);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "backwardslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveBackward(25);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "leftfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveLeft(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "leftmidfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveLeft(75);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "leftmidslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveLeft(50);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "leftslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveLeft(25);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "rightfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveRight(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "rightmidfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveRight(75);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "rightmidslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveRight(50);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "rightslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveRight(25);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "upleftfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagUpLeft(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "upleftmidfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagUpLeft(75);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "upleftmidslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagUpLeft(50);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "upleftslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagUpLeft(25);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "uprightfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagUpRight(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "uprightmidfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagUpRight(75);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "uprightmidslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagUpRight(50);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "uprightslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagUpRight(25);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "downleftfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagDownLeft(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "downleftmidfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagDownLeft(75);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "downleftmidslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagDownLeft(50);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "downleftslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagDownLeft(25);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "downrightfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagDownRight(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "downrightmidfast"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagDownRight(75);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "downrightmidslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagDownRight(50);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "downrightslow"){
      // if(command.substring(11,12) == "#"){
        my_robot.MoveDiagDownRight(25);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }


    else if (data_received == "pivot_left"){
      // if(command.substring(11,12) == "#"){
        my_robot.CenterPivotLeft(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }

    else if (data_received == "pivot_right"){
      // if(command.substring(11,12) == "#"){
        my_robot.CenterPivotRight(100);
        data_received = "";
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        break;
      // }
    }
  
    else if (data_received == "st"){
      // if(command.substring(5,6) == "#"){
        my_robot.stopSmorphi();
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        data_received = "";
        break;
      // }
    }

    else if (data_received == "shape_1" || data_received == "shape_2"){
      // if(command.substring(5,6) == "#"){    
        Serial.print("transmission complete!! ");
        Serial.println(data_received);
        data_received = "";
        break;
      // }
    }


    my_robot.sm_reset_M1();
    my_robot.sm_reset_M2();
    my_robot.sm_reset_M3();

    
  }
  
  my_robot.sm_reset_M1();
  my_robot.sm_reset_M2();
  my_robot.sm_reset_M3();

  // delay(20);
}
