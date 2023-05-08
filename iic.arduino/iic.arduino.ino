#include <Wire.h>
int LED = 13;
int x = 0;

void setup() 
{
  pinMode (LED, OUTPUT);
  Wire.begin(0x24); 
  Wire.onReceive(receiveEvent);
  Serial.begin(100000);
}

void receiveEvent(int bytes) 
{
   x = Wire.read();
   digitalWrite(LED, LOW);
   delay(200000);
   digitalWrite(LED, HIGH);
   Serial.print(x);
}

void loop() 
{
  
//  if (x <= 3) 
//  {
    digitalWrite(LED, HIGH);
//  }
//  else 
//  {
//    digitalWrite(LED, LOW);
//  }
}
