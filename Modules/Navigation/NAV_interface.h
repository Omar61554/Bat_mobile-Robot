/***********************************************************************************************************************/
/************** AUTHOR: OMAR KHALED     ********************************************************************************/
/************** DATE: 11/26/2023        ********************************************************************************/
/************** VERSION: 0.1            ********************************************************************************/
/************** FILE: NAV_interface.h   ********************************************************************************/
/***********************************************************************************************************************/


#ifndef NAV_INTERFACE_H_
#define NAV_INTERFACE_H_

// defines of NAV_pins

//Motor pins
#define NAV_Motor_R_Enable 6 //Enable signal Right motor
#define NAV_Motor_R_Right 7 //direction 1 Right motor
#define NAV_Motor_R_Left 8 //direction 2 Right motor
#define NAV_Motor_L_Enable 11 //Enable signal left motor
#define NAV_Motor_L_Right 12 //direction 1 left motor
#define NAV_Motor_L_Left 13 //direction 2 Left motor

//IR Sensor pins
#define NAV_Infrared_R 2 //signal pin from IR Sensor 1
#define NAV_Infrared_L 3 //signal pin from IR Sensor 2

//IR Sensor values
#define NAV_IRSignal_High 0 //high signal from IR Sensor
#define NAV_IRSignal_Low 1 //low signal from IR Sensor

//int NAV_IR_Signal_R;
//int NAV_IR_Signal_L;


/**
 * @brief  this function is used to turn the robot right
 *  
 */
void NAV_TurnRight();

/**
 * @brief  this function is used to move the robot straight
 * 
 */
void NAV_MoveStraight();

/**
 * @brief  this function is used to turn the robot left
 * 
 */
void NAV_TurnLeft();

/**
 * @brief  this function is used to move the robot backward
 * 
 */
void NAV_Backward();

/**
 * @brief  this function is used to stop the robot
 * 
 */
void NAV_Stop();


/**
 * @brief  this function is used to setup the navigation module
 * 
 */
void NAV_Setup();

/**
 * @brief  this function is the main function of the navigation module
 * 
 */
void NAV_Main();


#endif /* NAV_INTERFACE_H_ */