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
    IR_Sensor_Priority(1.5);
    int mission =NAV_Color_Sensor();
    missionSelector(mission);








    

  // put your main code here, to run repeatedly:
  // Serial.println(pulseIn(NAV_colorSensor_out,LOW));
   //NAV_Main(); //navigation module main function
//   int R = NAV_getRed();
//   int G = NAV_getGreen();
//   int B = NAV_getBlue();  
//   Serial.print("R= ");
//   Serial.print(R);
//   Serial.print(" G =");
//   Serial.print(G);                           
//   Serial.print(" B =");  //(140<G)  (R>160)
//   Serial.println(B); 

  /*
   int NAV_IR_Signal_R = digitalRead(NAV_Infrared_R);
    int NAV_IR_Signal_L = digitalRead(NAV_Infrared_L);

    if (NAV_IR_Signal_R && NAV_IR_Signal_L)
    {
        NAV_Move(70*1.5, 70*1.5, 'F'); // signal white //light -> no  signal

        // no signal black
    }
    else if (!NAV_IR_Signal_R && NAV_IR_Signal_L)
    {
        NAV_Move(40*1.5, 70*1.5, 'F');
        delay(100);
    }
    else if (NAV_IR_Signal_R && !NAV_IR_Signal_L)
    {
        NAV_Move(70*1.5, 40*1.5, 'F');
        delay(100);
    }
    else if (!NAV_IR_Signal_R && !NAV_IR_Signal_L)
    {
        NAV_Move(70*1.5, 70*1.5, 'B');
        delay(200);
    }
    else
    {
        // do nothing
    }  */
}   
