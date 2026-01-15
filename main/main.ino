/*
ESP Gauge Init no.01 - ESP32 board init. 
-----------------------------------------------------

Initilaze ESP32 board with basic Serial communication. 

*/

void setup(void) 
{
  Serial.begin(115200); 
}

void loop() 
{
  Serial.println("Hello, wrold!");
  delay(2000);
}