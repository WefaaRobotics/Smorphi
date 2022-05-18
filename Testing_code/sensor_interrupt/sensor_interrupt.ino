#include <Adafruit_MCP23X17.h>
#include <Wire.h>
#include <smorphi.h>

Smorphi my_robot;
Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(115200);
  my_robot.BeginSmorphi();
}

void loop() {
//    Serial.println(my_robot.sm_getShape());
    my_robot.set_interrupt_pin();
    int interrupt_pin_value = my_robot.module1_sensor_interrupt();
//    Serial.println(interrupt_pin_value);
    if (interrupt_pin_value == 255){
      Serial.println("no interrupt");
      my_robot.stopSmorphi();
      my_robot.interrupt_test();
    }
    else if (interrupt_pin_value == 0){
      Serial.println("detected interrupt");
      my_robot.MoveForward(70);
      my_robot.interrupt_test();
    }

    delay(100);
}
