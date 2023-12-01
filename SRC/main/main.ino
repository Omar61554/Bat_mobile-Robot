// #include <Arduino.h>
#include "NAV_interface.h"

void setup()
{
  // put your setup code here, to run once:

  NAV_Setup(); // navigation module setup function
  Serial.begin(9600);
  // digitalWrite(NAV_Color_s2,HIGH);
  // digitalWrite(NAV_Color_s3,LOW);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Serial.println(pulseIn(NAV_colorSensor_out,LOW));
  // NAV_Main(); //navigation module main function
  int R = NAV_getRed();
  int G = NAV_getGreen();
  int B = NAV_getBlue();
  Serial.print("R= ");
  Serial.print(R);
  Serial.print(" G =");
  Serial.print(G);                           
  Serial.print(" B =");
  Serial.println(B);
}
