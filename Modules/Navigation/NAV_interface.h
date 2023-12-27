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
#define NAV_Motor_R_Enable 5 //Enable signal Right motor //white
#define NAV_Motor_R_Right 8 //direction 1 Right motor   //black
#define NAV_Motor_R_Left 7 //direction 2 Right motor    //yellow
#define NAV_Motor_L_Enable 3 //Enable signal left motor // violet
#define NAV_Motor_L_Right 4 //direction 1 left motor    //blue
#define NAV_Motor_L_Left 2 //direction 2 Left motor    // green

//IR Sensor pins
#define NAV_Infrared_1 9 //signal pin from IR Sensor 1
#define NAV_Infrared_2 10 //signal pin from IR Sensor 2
#define NAV_Infrared_3 11 //signal pin from IR Sensor 3
#define NAV_Infrared_4 12 //signal pin from IR Sensor 4
#define NAV_Infrared_5 13 //signal pin from IR Sensor 5

//color sensor pins 
#define NAV_Modes_s0 A5
 #define NAV_Modes_s1 A4
 #define NAV_Color_s2 A2
 #define NAV_Color_s3 A1
 #define NAV_colorSensor_out  A3
// #define NAV_Modes_s0 9
// #define NAV_Modes_s1 8
// #define NAV_Color_s2 6
// #define NAV_Color_s3 5
// #define NAV_colorSensor_out A5

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
class Car{
private:
    int missionFlag; // 0 = no mission, 1 = joker, 2 = riddler, 3 = police chase
    int IR1,IR2,IR3,IR4,IR5; // sensors from right to left: IR1 IR2 IR3 IR4 IR5
    
    //if abs(reading-calib value) < 20 -> select mission
    int NAV_Motor_R_Speed;
    int NAV_Motor_L_Speed;
    char NAV_direction; 

    float speedFactor = 1.1; // multiply speed of motors by this value

    bool policeFlag; // true if detected first yellow color , false by default
    bool jokerMissionFlag;
    bool riddlerMissionFlag;

public:
    //Constructor
    int signalFromSlave;
    int calibValuesPoliceChase[3] ={352,326,269}; // {271,255,205}; //R > 340 && G > 320 && B < 290
    int calibValuesJoker[3] = {335,202,210}; //(R > 310 && G < 270 && B < 270)
    int calibValuesRiddler[3] = {279, 312, 239}; //(G > 300 && R < 300 && B < 260){
    int calibValuesWhite[3]; // {red, green, blue}
    Car();
    
    void getSpeed();
    void NAV_Move(int rightMotorSpeed, int leftMotorSpeed, char NAV_direction);
    void setup();
    void colorSensorCalibration();
    
    void slaveReciever();

    void controller();
    int IR_Sensor_Priority();
    void NAV_IR_TEST();

    int NAV_Color_Sensor();
    void missionSelector();

    void jokerMission();

    void riddlerMission();

    void policeChaseMission();
    void startMoving(int signal);
};

int NAV_getRed();
int NAV_getBlue();
int NAV_getGreen();

/**
 * @brief  this function is used to setup the navigation module
 *
 */


/**
 * @brief this function is the main function of the navigation module
 *
 */


//void NAV_COLORSENSOR_TEST();












//color sensor values
// int calibValueRed ;
// int calibValueGreen ;
// int calibValueBlue ;










/////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief this function is used to move the robot
*/
void NAV_Move(int NAV_Motor_R_Speed, int NAV_Motor_L_Speed, char NAV_direction);



/**
 * @brief this function is used to get the red value from the color sensor
*/
int NAV_getRed();



/**
 * @brief this function is used to get the green value from the color sensor
 * 
*/
int NAV_getGreen();



/**
 *@brief this function is used to get the blue value from the color sensor
*/
int NAV_getBlue();



/**
 * @brief  this function is used to setup the navigation module
 * 
 */
void NAV_Setup();



/**
 * @brief  this function is a test function for the motors
 * 
 */
//void NAV_Main();

/**
 * @brief  this function is the main function of the line follower
 * 
 */
//void IR_Sensor_Priority(float F);

/**
 * @brief  this function is used to test IR sensors
 * 
 */
//void NAV_IR_TEST();

/**
 * @brief  this function is used to detect the color
 * 
 */
//int NAV_Color_Sensor();

/**
 * @brief  this function is used to select mission 
 * 
 */
//void missionSelector(int colorValue);

/**
 * @brief  this function is used to call joker mission
 * 
 */
void jokerMission();

/**
 * @brief  this function is used to call riddler mission
 * 
 */
void riddlerMission();

/**
 * @brief  this function is used to call the police chase mission
 * 
 */
void policeChaseMission();


#endif /* NAV_INTERFACE_H_ */
