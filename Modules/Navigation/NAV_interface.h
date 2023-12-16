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
#define NAV_Motor_R_Enable 9 //Enable signal Right motor //white
#define NAV_Motor_R_Right 7 //direction 1 Right motor   //black
#define NAV_Motor_R_Left 8 //direction 2 Right motor    //yellow
#define NAV_Motor_L_Enable 11 //Enable signal left motor // violet
#define NAV_Motor_L_Right 12 //direction 1 left motor    //blue
#define NAV_Motor_L_Left 13 //direction 2 Left motor    // green

//IR Sensor pins
#define NAV_Infrared_1 0 //signal pin from IR Sensor 1
#define NAV_Infrared_2 1 //signal pin from IR Sensor 2
#define NAV_Infrared_3 2 //signal pin from IR Sensor 3
#define NAV_Infrared_4 3 //signal pin from IR Sensor 4
#define NAV_Infrared_5 4 //signal pin from IR Sensor 5

//IR Sensor values
// int IR1;
// int IR2;
// int IR3;
// // int IR4;
// int IR5;

//IR Sensor values
#define NAV_IRSignal_High 0 //high signal from IR Sensor
#define NAV_IRSignal_Low 1 //low signal from IR Sensor

//int NAV_IR_Signal_R;
//int NAV_IR_Signal_L;

//color sensor pins 
#define NAV_Modes_s0 6
#define NAV_Modes_s1 10
#define NAV_Color_s2 4
#define NAV_Color_s3 5
#define NAV_colorSensor_out  A0

//color sensor values
// int calibValueRed ;
// int calibValueGreen ;
// int calibValueBlue ;










/////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * 
*/
void NAV_Move(int NAV_Motor_R_Speed, int NAV_Motor_L_Speed, char NAV_direction);



/**
 * 
*/
int NAV_getRed();



/**
 * 
 * 
*/
int NAV_getGreen();



/**
 * 
*/
int NAV_getBlue();



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


void IR_Sensor_Priority();

void NAV_IR_TEST();

int NAV_Color_Sensor();

void missionSelector(int colorValue);

void jokerMission();

void riddlerMission();

void policeChaseMission();


#endif /* NAV_INTERFACE_H_ */