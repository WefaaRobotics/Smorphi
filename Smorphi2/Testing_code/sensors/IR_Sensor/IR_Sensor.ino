void setup() {
  // put your setup code here, to run once:
pinMode(16,INPUT);
Serial.begin(115200);
//pinMode(12,OUTPUT);//LED
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println(digitalRead(16));
}
