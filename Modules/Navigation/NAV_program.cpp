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
//#include "../STD_ATYPES.hpp"
int IR1,IR2,IR3,IR4,IR5;

int calibValueRed = 140;
int calibValueGreen = 140;
int calibValueBlue = 140;
/**
 * @brief  this function is used to move the robot
 * @param NAV_Motor_R_Speed the speed of the right motor //higher to move left
 * @param NAV_Motor_L_Speed the speed of the left motor //higher to move right
 * @param direction the direction of the robot  //forward or backward    'F' or 'B'
 *
 */
void NAV_Move(int NAV_Motor_R_Speed, int NAV_Motor_L_Speed, char NAV_direction)
{

    analogWrite(NAV_Motor_L_Enable, NAV_Motor_L_Speed);
    analogWrite(NAV_Motor_R_Enable, NAV_Motor_R_Speed);
    
    if (NAV_direction == 'F')
    {
        digitalWrite(NAV_Motor_L_Right, LOW);  // direction 1 left motor
        digitalWrite(NAV_Motor_L_Left, HIGH);  // direction 2 Left motor
        digitalWrite(NAV_Motor_R_Right, HIGH); // direction 1 Right motor
        digitalWrite(NAV_Motor_R_Left, LOW);   // direction 2 Right motor
    }
    else if (NAV_direction == 'B')
    {
        digitalWrite(NAV_Motor_L_Right, HIGH); // direction 1 left motor
        digitalWrite(NAV_Motor_L_Left, LOW);   // direction 2 Left motor
        digitalWrite(NAV_Motor_R_Right, LOW);  // direction 1 Right motor
        digitalWrite(NAV_Motor_R_Left, HIGH);  // direction 2 Right motor
    }
    else
    {
        // do nothing
    }
}

int NAV_getRed()
{
    digitalWrite(NAV_Color_s2, LOW);
    digitalWrite(NAV_Color_s3, LOW);
    int PW = pulseIn(NAV_colorSensor_out, LOW);
    PW = map(PW, 79, 215, 255, 0);
    return PW;
}
int NAV_getBlue()
{
    digitalWrite(NAV_Color_s2, LOW);
    digitalWrite(NAV_Color_s3, HIGH);
    int PW = pulseIn(NAV_colorSensor_out, LOW);
    PW = map(PW, 65, 171, 255, 0);
    return PW;
}
int NAV_getGreen()
{
    digitalWrite(NAV_Color_s2, HIGH);
    digitalWrite(NAV_Color_s3, HIGH); // white R= 79 G =74 B =65
                                      //  black R= 215 G =202 B =171
    int PW = pulseIn(NAV_colorSensor_out, LOW);
    PW = map(PW, 74, 202, 255, 0);
    return PW;
}

/**
 * @brief  this function is used to setup the navigation module
 *
 */

void NAV_Setup()
{
    pinMode(NAV_Infrared_1, INPUT); // IR Sensor 1
    pinMode(NAV_Infrared_2, INPUT); // IR Sensor 2
    pinMode(NAV_Infrared_3, INPUT); // IR Sensor 3
    pinMode(NAV_Infrared_4, INPUT); // IR Sensor 4
    pinMode(NAV_Infrared_5, INPUT); // IR Sensor 5

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
// void NAV_Main()
// {
//     int NAV_IR_Signal_R = digitalRead(NAV_Infrared_R);
//     int NAV_IR_Signal_L = digitalRead(NAV_Infrared_L);

//     if (NAV_IR_Signal_R && NAV_IR_Signal_L)
//     {
//         NAV_Move(70*1.5, 70*1.5, 'F'); // signal white //light -> no  signal

//         // no signal black
//     }
//     else if (!NAV_IR_Signal_R && NAV_IR_Signal_L)
//     {
//         NAV_Move(50*1.5, 70*1.5, 'F');
//     }
//     else if (NAV_IR_Signal_R && !NAV_IR_Signal_L)
//     {
//         NAV_Move(70*1.5, 50*1.5, 'F');
//     }
//     else if (!NAV_IR_Signal_R && !NAV_IR_Signal_L)
//     {
//         NAV_Move(60*1.5, 60*1.5, 'B');
//     }
//     else
//     {
//         // do nothing
//     }
// }

void NAV_COLORSENSOR_TEST(){

    NAV_getBlue();

    NAV_getGreen();

    NAV_getRed();



}

void IR_Sensor_Priority(){
    // IR5 IR4 IR3 IR2 IR1 //
    IR1 = digitalRead(NAV_Infrared_1);
    IR2 = digitalRead(NAV_Infrared_2);
    IR3 = digitalRead(NAV_Infrared_3);
    IR4 = digitalRead(NAV_Infrared_4);
    IR5 = digitalRead(NAV_Infrared_5);
    
    if (IR1 && !IR5){
        Serial.println("Big Turn Right");   //big turn right
        NAV_Move(70*1.5, 50*1.5, 'F');
        delay(100);
    }
    else if (!IR1 && IR5){

        Serial.println("Big Turn Left");   //big turn left
        NAV_Move(50*1.5, 70*1.5, 'F');
        delay(100);
    }
    else if((!IR1) && (!IR4) && (!IR5) && IR2){
        Serial.println("Small Turn Right");  //small turn right
        NAV_Move(70*1.5, 60*1.5, 'F');
        delay(100);
    }
    else if((!IR1) && (!IR2) && (!IR5) && IR4){
        Serial.println("Small Turn Left");//small turn left
        NAV_Move(60*1.5, 70*1.5, 'F');
        delay(100);
    }
    else if(IR3 || (IR2&&IR4) || (IR1&&IR5)){
        Serial.println("Straight Line");//straight line
        NAV_Move(70*1.5, 70*1.5, 'F');
        delay(200);
    }
    else if((!IR1) && (!IR2) && (!IR3) && (!IR4) && (!IR5)){
        Serial.println("Stop");//stop
        NAV_Move(0, 0, 'F');

    }
//    
    // big_turn_right = IR1.not(IR5)
    // big_turn_left = IR5.not(IR1)
    
    // stop = not(IR1.IR2.IR3.IR4.I5)

    // small_turn_right = not(IR1).IR2.not(IR4).not(IR5)
    // small_turn_left = not(IR1).not(IR2).not(IR5).IR4

    // straight = IR1.IR5 or IR3 or IR2.IR4

    // if IR5 or IR1 is true
    //     sharp turn left or right
    
    // if IR2 true
    //     turn right slightly
    // if IR4 true
    //     turn left slightly
    // if IR2 & IR3 true
    //     turn left more
    // if IR4 & IR3 true
    //     turn right more
    // digitalRead(IR1);
    // digitalRead(IR2);
    // read IR3
    // read IR4
    // read IR5

}

void NAV_IR_TEST(){
    // IR5 IR4 IR3 IR2 IR1 //
    IR1 = digitalRead(NAV_Infrared_1);
    IR2 = digitalRead(NAV_Infrared_2);
    IR3 = digitalRead(NAV_Infrared_3);
    IR4 = digitalRead(NAV_Infrared_4);
    IR5 = digitalRead(NAV_Infrared_5);
    Serial.print("IR1 = ");
    Serial.print(IR1);
    Serial.print(" IR2 = ");
    Serial.print(IR2);
    Serial.print(" IR3 = ");
    Serial.print(IR3);
    Serial.print(" IR4 = ");
    Serial.print(IR4);
    Serial.print(" IR5 = ");
    Serial.println(IR5);
    delay(1000);
}

int NAV_Color_Sensor(){
    /*
    0=white
    1=red
    2=green
    3=blue
    4=yellow
    5=black
    */
    int R = NAV_getRed();
    int G = NAV_getGreen();
    int B = NAV_getBlue();  
    if (R > calibValueRed && G > calibValueGreen && B > calibValueBlue){
        //white
        return 0;
    }
    else if (R > calibValueRed){
        //red
        return 1;
    }
    else if (G > calibValueGreen){
        //green
        return 2;
    }
    else if (B > calibValueBlue){
        //blue
        return 3;
    }
    else if (R > calibValueRed && G > calibValueGreen){
        //yellow
        return 4;
    }
    
    else{
        //black
        return 5;
    }
}

void missionSelector(int colorValue){
    switch (colorValue)
    {
    case 0:
        //white
        break;
    case 1:
        jokerMission();    //red
        break;
    case 2:
        riddlerMission();//green
        break;
    case 3:
        //blue
        break;
    case 4:
        policeChaseMission();//yellow
        //check for second time it detects yellow to end the mission
        break;
    default:
        break;
    }
}

void jokerMission(){
    Serial.println("Joker Mission");
    // implement joker mission here
}

void riddlerMission(){
    Serial.println("Riddler Mission");
    // implement riddler mission here
}

void policeChaseMission(){
    Serial.println("Police Chase Mission");
    // implement police chase mission here
}