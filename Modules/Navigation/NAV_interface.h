/***********************************************************************************************************************/
/************** AUTHOR: Team 9         ********************************************************************************/
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

//Speed factors
#define normalSpeed 1.7
#define maximumSpeed 1.9

//IR Sensor values
#define NAV_IRSignal_High 0 //high signal from IR Sensor
#define NAV_IRSignal_Low 1 //low signal from IR Sensor



class Car{
private:
    int missionFlag; // 0 = no mission, 1 = joker, 2 = riddler, 3 = police chase
    int IR1,IR2,IR3,IR4,IR5; // sensors from right to left: IR1 IR2 IR3 IR4 IR5
    
    int NAV_Motor_R_Speed;
    int NAV_Motor_L_Speed;
    char NAV_direction; 

    float speedFactor = normalSpeed; // multiply speed of motors by this value

    bool policeFlag; // true if detected first yellow color , false by default
    bool jokerMissionFlag;
    bool riddlerMissionFlag;
    char caveSignal;
    bool caveOpened;

    char last_move;
     

public:
    //Constructor
    int signalFromSlave;
    int calibValuesPoliceChase[3] ={352,326,269}; // {271,255,205}; //R > 340 && G > 320 && B < 290
    int calibValuesJoker[3] = {335,202,210}; //(R > 310 && G < 270 && B < 270)
    int calibValuesRiddler[3] = {197, 276, 217}; //(G > 300 && R < 300 && B < 260){ R= 197 G =276 B =217

    int calibValuesWhite[3]; // {red, green, blue}

    Car(){
        int missionFlag = 0;
        int calibValuesPoliceChase[3] ={352,326,269}; // {271,255,205}; //R > 340 && G > 320 && B < 290
        int calibValuesJoker[3] = {335,202,210}; //(R > 310 && G < 270 && B < 270)
        int calibValuesRiddler[3] = {279, 312, 239}; //(G > 300 && R < 300 && B < 260){
        int NAV_Motor_L_Speed = 0;
        int NAV_Motor_R_Speed = 0;
        char NAV_direction = 'F';
        float speedFactor = normalSpeed;
        
        bool policeFlag = false;
        bool jokerMissionFlag = false;
        bool riddlerMissionFlag = false;

        bool caveOpened = false;
        char signalFromSlave = 'k';
        char caveSignal = 'p';

        char last_move='w';

    }
    
    //Functions
    /**
     * @brief Get the Speed object
     * 
     */
    void getSpeed();

    /**
     * @brief Get the Direction object
     * @param speed of motors
     * @param direction of motors
     */
     */
    void NAV_Move(int rightMotorSpeed, int leftMotorSpeed, char NAV_direction);

    /**
     * @brief setup of pins
     * 
     */
    void setup();

    /**
     * @brief Get the IR Sensor object
     * 
     */
    void colorSensorCalibration();
    
    /**
     * @brief recieve signal from slave arduino
     * 
     */
    void slaveReciever();


    /**
     * @brief control the car
     * 
     */
    void controller();

    /**
     * @brief Get the IR Sensor object
     * 
     */
    int IR_Sensor_Priority();

    /**
     * @brief Get the IR Sensor object
     * 
     */
    void NAV_IR_TEST();

    /**
     * @brief volor sensor calibration
     * 
     */

    int NAV_Color_Sensor();

    /**
     * @brief select mission from color sensor
     * 
     */
    void missionSelector();


    /**
     * @brief joker mission implementation
     * 
     */
    void jokerMission();

    /**
     * @brief riddler mission implementation
     * 
     */

    void riddlerMission();

    /**
     * @brief police chase mission implementation
     * 
     */

    void policeChaseMission();

    /**
     * @brief move the car after mission
     * @param signal from slave arduino
     */
    void startMoving(int signal);

    /**
     * @brief Get the Red object
     * 
     * @return int 
     */
    int NAV_getRed();

    /**
     * @brief Get the Blue object
     * 
     * @return int 
     */
    int NAV_getBlue();

    /**
     * @brief Get the Green object
     * 
     * @return int 
     */
    int NAV_getGreen();

    /**
     * @brief Get the Mission Flag object
     * 
     */

    void caveEntering();
};

#endif /* NAV_INTERFACE_H_ */
