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

//********************************************************************************************************************//
int IR1,IR2,IR3,IR4,IR5;

int calibValueRed = 140;
int calibValueGreen = 140;
int calibValueBlue = 140;

char last_move='W'; // R or L  don't let them know your next move


//********************************************************************************************************************//



/**
 * @brief  this function is used to move the robot
 * @param NAV_Motor_R_Speed the speed of the right motor //higher to move left
 * @param NAV_Motor_L_Speed the speed of the left motor //higher to move right
 * @param direction the direction of the robot  //forward or backward    'F' or 'B'
 *
 */
class Car{
private:
    int missionFlag; // 0 = no mission, 1 = joker, 2 = riddler, 3 = police chase
    int IR1,IR2,IR3,IR4,IR5; // sensors from right to left: IR1 IR2 IR3 IR4 IR5
    int calibValuesPoliceChase[3]; // {red, green, blue}   
    int calibValuesJoker[3]; // {red, green, blue}
    int calibValuesRiddler[3]; // {red, green, blue}
    int calibValuesWhite[3]; // {red, green, blue}
    //if abs(reading-calib value) < 20 -> select mission
    int NAV_Motor_R_Speed;
    int NAV_Motor_L_Speed;
    char NAV_direction; 

    float speedFactor; // multiply speed of motors by this value


public:
    //Constructor
    Car(){
        int missionFlag = 0;
        int calibValuesPoliceChase[] = {255,255,255};
        int calibValuesJoker[] = {155,155,155};
        int calibValuesRiddler[] = {140, 150, 160};
        int NAV_Motor_L_Speed = 0;
        int NAV_Motor_R_Speed = 0;
        char NAV_direction = 'f';
        float speedFactor = 1.8;
    }
    
    void NAV_Move(int NAV_Motor_R_Speed, int NAV_Motor_L_Speed, char NAV_direction){

        analogWrite(NAV_Motor_L_Enable, NAV_Motor_L_Speed);
        analogWrite(NAV_Motor_R_Enable, NAV_Motor_R_Speed);
        
        if (NAV_direction == 'F')
        {
            digitalWrite(NAV_Motor_L_Right, HIGH);  // direction 1 left motor
            digitalWrite(NAV_Motor_L_Left, LOW);  // direction 2 Left motor
            digitalWrite(NAV_Motor_R_Right, LOW); // direction 1 Right motor
            digitalWrite(NAV_Motor_R_Left, HIGH);   // direction 2 Right motor
        }
        else if (NAV_direction == 'B')
        {
            digitalWrite(NAV_Motor_L_Right, LOW); // direction 1 left motor
            digitalWrite(NAV_Motor_L_Left, HIGH);   // direction 2 Left motor
            digitalWrite(NAV_Motor_R_Right, HIGH);  // direction 1 Right motor
            digitalWrite(NAV_Motor_R_Left, LOW);  // direction 2 Right motor
        }
        else
        {
            // do nothing
        }
    }
    void controller(){

        //ir sensors readings
        int IRReading = IR_Sensor_Priority();

        int colorValue = NAV_Color_Sensor();
        missionSelector(colorValue);
        
        //color sensors readings
        //mission selector
        //nav move
        //
    }
    int IR_Sensor_Priority(){
        // IR5 IR4 IR3 IR2 IR1 //
        /*
        0 = Reverse
        1 = Straight line
        2 = Big turn right
        3 = Big turn left
        4 = Small turn right
        5 = Small turn left
        */

        IR1 = digitalRead(NAV_Infrared_1);
        IR2 = digitalRead(NAV_Infrared_2);
        IR3 = digitalRead(NAV_Infrared_3);    // black IR reading 1 and no light
        IR4 = digitalRead(NAV_Infrared_4);    // white IR reading 0 and light
        IR5 = digitalRead(NAV_Infrared_5);

        if (IR1 && !IR5){
            Serial.println("Big Turn Right");   //big turn right
            return 2; //big turn right
            NAV_Move(50*speedFactor, 70*speedFactor, 'F');
            delay(300);
            last_move='R';
        }
        else if (!IR1 && IR5){

            Serial.println("Big Turn Left");   //big turn left
            return 3; //big turn left
            NAV_Move(70*speedFactor ,30*speedFactor, 'F');
            delay(300);
            last_move='L';
        }
        else if((!IR1) && (!IR4) && (!IR5) && IR2){
            Serial.println("Small Turn Right");  //small turn right
            return 4; //Small turn right
            NAV_Move(50*speedFactor, 70*speedFactor, 'F');
            delay(100);
        }
        else if((!IR1) && (!IR2) && (!IR5) && IR4){
            Serial.println("Small Turn Left");//small turn left
            return 5; //Small turn left
            NAV_Move(70*speedFactor, 50*speedFactor, 'F');
            delay(100);
        }
        // else if(IR3 || (IR2&&IR4) || (IR1&&IR5)){
        //     Serial.println("Straight Line");//straight line
        //     NAV_Move(70*F, 70*F, 'F');
        //     delay(200);
        // }
        else if(IR3&&IR2&&IR4 ){
            Serial.println("Straight Line");//straight line
            return 1; //straight line code
            NAV_Move(70*speedFactor, 70*speedFactor, 'F');
            delay(200);
        }
        else if((!IR1) && (!IR2) && (!IR3) && (!IR4) && (!IR5)){
            Serial.println("REVERSE");//REVERSE
            return 0;
            NAV_Move(70*speedFactor, 70*speedFactor, 'B');
            delay(200);
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
    //if (R > calibValueRed && G > calibValueGreen && B > calibValueBlue){
    
    //else if (R > calibValueRed){
    if (abs(R-calibValuesJoker[0]) < 20 
     && abs(G-calibValuesJoker[1]) < 20 
     && abs(G-calibValuesJoker[2]) < 20){//(R > 310 && G < 270 && B < 270){
        //red
        return 1;
    }
    //else if (G > calibValueGreen){
    else if(abs(R-calibValuesRiddler[0]) < 20 
         && abs(G-calibValuesRiddler[1]) < 20 
         && abs(G-calibValuesRiddler[2]) < 20){;
        //(G > 300 && R < 300 && B < 260){
    
        //green
        return 2;
    }
    //else if (B > calibValueBlue){
    // else if()
    //     //blue
    //     return 3;
    // }
    //else if (R > calibValueRed && G > calibValueGreen){
    else if(abs(R-calibValuesPoliceChase[0]) < 20 
         && abs(G-calibValuesPoliceChase[1]) < 20 
         && abs(G-calibValuesPoliceChase[2]) < 20){
        //(R > 340 && G > 320 && B < 290){
        //yellow
        return 4;
    }
    else if(abs(R-calibValuesWhite[0]) < 20 
         && abs(G-calibValuesWhite[1]) < 20 
         && abs(G-calibValuesWhite[2]) < 20){
        //(R > 310 && G > 320 && B > 320)
        //white
        return 0;
    }
    else{
        //black
        return 5;
    }
    }

    void missionSelector(int colorValue = NAV_Color_Sensor()){
        switch (missionFlag)
        {
        case 0:
            Serial.println("White");//white
            break;
        case 1:
            jokerMission();     //red
            break;
        case 2:
            riddlerMission();   //green
            break;
        case 3:
            //blue
            break;
        case 4:
            policeChaseMission();//yellow
            //check for second time it detects yellow to end the mission
            break;
        default:
            Serial.println("black");
            break;
        }
    }

    void jokerMission(){
        Serial.println("Joker Mission");
        // implement joker mission here
        if(last_move='R'){
            NAV_Move(70*1.8, 70*1.8, 'B');
            delay(600);
            NAV_Move(10*1.8, 70*1.8, 'B');
            delay(500);
        }
        else if(last_move='L'){
            NAV_Move(70*1.8, 70*1.8, 'B');
            delay(600);
            NAV_Move(70*1.8, 10*1.8, 'B');
            delay(500);
        }
        else{
            //do nothing
        }
        }

    void riddlerMission(){
        Serial.println("Riddler Mission");
        // implement riddler mission here
        if(last_move='R'){
            NAV_Move(70*1.8, 70*1.8, 'B');
            delay(600);
            NAV_Move(10*1.8, 70*1.8, 'B');
            delay(500);
        }
        else if(last_move='L'){
            NAV_Move(70*1.8, 70*1.8, 'B');
            delay(600);
            NAV_Move(70*1.8, 10*1.8, 'B');
            delay(500);
        }
        else{
            //do nothing
        }
    }

    void policeChaseMission(){
        Serial.println("Police Chase Mission");
        // implement police chase mission here
        speedFactor = 2.2;
        
        if()
        //IR_Sensor_Priority(2.2);
    }

};

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

void setup()
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
void start()
{
        IR1 = digitalRead(NAV_Infrared_1);
        IR2 = digitalRead(NAV_Infrared_2);
        IR3 = digitalRead(NAV_Infrared_3);    // black IR reading 1 and no light
        IR4 = digitalRead(NAV_Infrared_4);    // white IR reading 0 and light
        IR5 = digitalRead(NAV_Infrared_5);

        if (IR1 && !IR5){
            Serial.println("Big Turn Right");   //big turn right
            NAV_Move(50*speedFactor, 70*speedFactor, 'F');
            delay(300);
            last_move='R';
        }
        else if (!IR1 && IR5){

            Serial.println("Big Turn Left");   //big turn left
            NAV_Move(70*speedFactor ,30*speedFactor, 'F');
            delay(300);
            last_move='L';
        }
        else if((!IR1) && (!IR4) && (!IR5) && IR2){
            Serial.println("Small Turn Right");  //small turn right
            NAV_Move(50*speedFactor, 70*speedFactor, 'F');
            delay(100);
        }
        else if((!IR1) && (!IR2) && (!IR5) && IR4){
            Serial.println("Small Turn Left");//small turn left
            NAV_Move(70*speedFactor, 50*speedFactor, 'F');
            delay(100);
        }
        // else if(IR3 || (IR2&&IR4) || (IR1&&IR5)){
        //     Serial.println("Straight Line");//straight line
        //     NAV_Move(70*F, 70*F, 'F');
        //     delay(200);
        // }
        else if(IR3&&IR2&&IR4 ){
            Serial.println("Straight Line");//straight line
            NAV_Move(70*speedFactor, 70*speedFactor, 'F');
            delay(200);
        }
        else if((!IR1) && (!IR2) && (!IR3) && (!IR4) && (!IR5)){
            Serial.println("REVERSE");//REVERSE
            NAV_Move(70*speedFactor, 70*speedFactor, 'B');
            delay(200);
        }
}

void NAV_COLORSENSOR_TEST(){

    NAV_getBlue();

    NAV_getGreen();

    NAV_getRed();



}









