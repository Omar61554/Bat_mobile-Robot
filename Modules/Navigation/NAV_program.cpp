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
//#include "../../LIB/STD_TYPES.h"



/**
 * @brief  this function is used to turn the robot right
 * 
 */
void NAV_TurnRight(){
    
    
    analogWrite(NAV_Motor_L_Enable, 100);
    analogWrite(NAV_Motor_R_Enable, 0);
    
}

/**
 * @brief  this function is used to turn the robot left
 * 
 */

void NAV_TurnLeft(){
    
    
    analogWrite(NAV_Motor_L_Enable, 0);
    analogWrite(NAV_Motor_R_Enable, 100);
}

/**
 * @brief  this function is used to move the robot straight
 * 
 */

void NAV_MoveStraight(){
    analogWrite(NAV_Motor_L_Enable, 100);
    analogWrite(NAV_Motor_R_Enable, 100);
}


/**
 * @brief  this function is used to move the robot backward
 * 
 */
void NAV_Backward(){
    analogWrite(NAV_Motor_L_Enable, 0);
    analogWrite(NAV_Motor_R_Enable, 0);
}


/**
 * @brief  this function is used to stop the navigation module
 * 
 */
void NAV_Stop(){
    analogWrite(NAV_Motor_L_Enable, 0);
    analogWrite(NAV_Motor_R_Enable, 0);
}

/**
 * @brief  this function is used to setup the navigation module
 * 
 */

void NAV_Setup(){
    pinMode(NAV_Infrared_R, INPUT); //IR Sensor 1
    pinMode(NAV_Infrared_L, INPUT); //IR Sensor 2
    pinMode(NAV_Motor_R_Enable, OUTPUT);//Enable signal Right motor
    pinMode(NAV_Motor_R_Right, OUTPUT); //direction 1 Right motor
    pinMode(NAV_Motor_R_Left, OUTPUT); //direction 2 Right motor
    pinMode(NAV_Motor_L_Enable, OUTPUT); //Enable signal left motor
    pinMode(NAV_Motor_L_Right, OUTPUT); //direction 1 left motor
    pinMode(NAV_Motor_L_Left, OUTPUT); //direction 2 Left motor

    
    digitalWrite(NAV_Motor_R_Right, LOW); //direction 1 Right motor
    digitalWrite(NAV_Motor_L_Left, HIGH); //direction 2 Left motor
    digitalWrite(NAV_Motor_R_Left, HIGH); //direction 2 Right motor 
    digitalWrite(NAV_Motor_L_Right, LOW); //direction 1 left motor
    
}

/**
 * @brief this function is the main function of the navigation module
 * 
 */
void NAV_Main(){
    int NAV_IR_Signal_R = digitalRead(NAV_Infrared_R);
    int NAV_IR_Signal_L = digitalRead(NAV_Infrared_L);
    if(!NAV_IR_Signal_R && !NAV_IR_Signal_L){
        NAV_MoveStraight();
    }
    else if(!NAV_IR_Signal_R && NAV_IR_Signal_L){
        NAV_TurnRight();
    }
    else if(NAV_IR_Signal_R && !NAV_IR_Signal_L){
        NAV_TurnLeft();
    }
    else if(NAV_IR_Signal_R && NAV_IR_Signal_L){
        NAV_Backward();
    }
    else{
        NAV_Stop();
    }
}