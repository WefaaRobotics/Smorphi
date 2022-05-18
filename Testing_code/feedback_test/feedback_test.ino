#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mcp1.begin_I2C(0x23);
  mcp1.pinMode(14, INPUT_PULLUP);
  mcp1.pinMode(15, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(mcp1.digitalRead(14));
  Serial.println(mcp1.digitalRead(15));
}
