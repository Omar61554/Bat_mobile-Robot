/***********************************************************************************************************************/
/************** AUTHOR: OMAR KHALED     ********************************************************************************/
/************** DATE: 11/26/2023        ********************************************************************************/
/************** VERSION: 0.1            ********************************************************************************/
/************** FILE: NAV_program.h     ********************************************************************************/
/***********************************************************************************************************************/

#include "NAV_interface.h"
#include "NAV_private.h"
#include "NAV_configure.h"
#include <Arduino.h>
// #include "../../LIB/STD_TYPES.h"

/**
 * @brief  this function is used to move the robot
 * @param NAV_Motor_R_Speed the speed of the right motor //higher to move left
 * @param NAV_Motor_L_Speed the speed of the left motor //higher to move right
 * @param direction the direction of the robot  //forward or backward    F or B
 * 
*/
void NAV_Move(int NAV_Motor_R_Speed, int NAV_Motor_L_Speed,char NAV_direction)
{

    analogWrite(NAV_Motor_L_Enable, NAV_Motor_L_Speed);
    analogWrite(NAV_Motor_R_Enable, NAV_Motor_R_Speed);
if(NAV_direction=='F')
{
    digitalWrite(NAV_Motor_L_Right, LOW); // direction 1 left motor
    digitalWrite(NAV_Motor_L_Left, HIGH); // direction 2 Left motor
    digitalWrite(NAV_Motor_R_Right, HIGH); // direction 1 Right motor
    digitalWrite(NAV_Motor_R_Left, LOW); // direction 2 Right motor
}
else if(NAV_direction=='B')
{
    digitalWrite(NAV_Motor_L_Right, HIGH); // direction 1 left motor
    digitalWrite(NAV_Motor_L_Left, LOW); // direction 2 Left motor
    digitalWrite(NAV_Motor_R_Right, LOW); // direction 1 Right motor
    digitalWrite(NAV_Motor_R_Left, HIGH); // direction 2 Right motor
}
else
{
    //do nothing

}
   
}


/**
 * @brief  this function is used to turn the robot right
 *  
 */

int NAV_getRed()
{
    digitalWrite(NAV_Color_s2, LOW);
    digitalWrite(NAV_Color_s3, LOW);
    int PW = pulseIn(NAV_colorSensor_out, LOW);
    PW = map(PW, 83, 302, 0, 255);
    return PW;
}

int NAV_getBlue()
{
    digitalWrite(NAV_Color_s2, LOW);
    digitalWrite(NAV_Color_s3, HIGH);
    int PW = pulseIn(NAV_colorSensor_out, LOW);
    PW = map(PW, 75, 251, 0, 255);
    return PW;
}
int NAV_getGreen()
{
    digitalWrite(NAV_Color_s2, HIGH);
    digitalWrite(NAV_Color_s3, HIGH);
    int PW = pulseIn(NAV_colorSensor_out, LOW);
    PW = map(PW, 84, 272, 0, 255);
    return PW;
}


/**
 * @brief  this function is used to setup the navigation module
 *
 */

void NAV_Setup()
{
    pinMode(NAV_Infrared_R, INPUT);      // IR Sensor 1
    pinMode(NAV_Infrared_L, INPUT);      // IR Sensor 2

    pinMode(NAV_Motor_R_Enable, OUTPUT); // Enable signal Right motor
    pinMode(NAV_Motor_R_Right, OUTPUT);  // direction 1 Right motor
    pinMode(NAV_Motor_R_Left, OUTPUT);   // direction 2 Right motor
    pinMode(NAV_Motor_L_Enable, OUTPUT); // Enable signal left motor
    pinMode(NAV_Motor_L_Right, OUTPUT);  // direction 1 left motor
    pinMode(NAV_Motor_L_Left, OUTPUT);   // direction 2 Left motor

    // color sensor
    pinMode(NAV_Modes_s0, OUTPUT);
    pinMode(NAV_Modes_s1, OUTPUT);
    pinMode(NAV_Color_s2, OUTPUT);
    pinMode(NAV_Color_s3, OUTPUT);
    pinMode(NAV_colorSensor_out, INPUT);


    // color sensor

    digitalWrite(NAV_Modes_s0, HIGH);
    digitalWrite(NAV_Modes_s1, LOW); // 20%
}

/**
 * @brief this function is the main function of the navigation module
 *
 */
void NAV_Main()
{
    int NAV_IR_Signal_R = digitalRead(NAV_Infrared_R);
    int NAV_IR_Signal_L = digitalRead(NAV_Infrared_L);

    if (!NAV_IR_Signal_R && !NAV_IR_Signal_L)
    {
        NAV_Move(100,100,'F'); // signal white //light -> no  signal

        // no signal black
    }
    else if (!NAV_IR_Signal_R && NAV_IR_Signal_L)
    {
        NAV_Move(50,100,'F'); 
    }
    else if (NAV_IR_Signal_R && !NAV_IR_Signal_L)
    {
        NAV_Move(100,50,'F');
    }
    else if (NAV_IR_Signal_R && NAV_IR_Signal_L)
    {
        NAV_Move(0,0,'F');
    }
    else
    {
        //do nothing
    }
}