/***********************************************************************************************************************/
/************** AUTHOR: Team 9          ********************************************************************************/
/************** DATE: 11/26/2023        ********************************************************************************/
/************** VERSION: 0.1            ********************************************************************************/
/************** FILE: NAV_program.h     ********************************************************************************/
/***********************************************************************************************************************/

#include "NAV_interface.h"
#include <math.h>
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




    //Constructor
    // Car::Car(){
    //     int missionFlag = 0;
    //     int calibValuesPoliceChase[3] ={352,326,269}; // {271,255,205}; //R > 340 && G > 320 && B < 290
    //     int calibValuesJoker[3] = {335,202,210}; //(R > 310 && G < 270 && B < 270)
    //     int calibValuesRiddler[3] = {279, 312, 239}; //(G > 300 && R < 300 && B < 260){
    //     int NAV_Motor_L_Speed = 0;
    //     int NAV_Motor_R_Speed = 0;
    //     char NAV_direction = 'F';
    //     float speedFactor = normalSpeed;
        
    //     bool policeFlag = false;
    //     bool jokerMissionFlag = false;
    //     bool riddlerMissionFlag = false;

    //     bool caveOpened = false;
    //     char signalFromSlave = 'k';
    //     char caveSignal = 'p';
    // }
    void Car::getSpeed(){
        Serial.print("Right speed: ");
        Serial.print(NAV_Motor_R_Speed);
        Serial.print("  Left speed: ");
        Serial.println(NAV_Motor_L_Speed);

        Serial.print("Speed Factor: " );
        Serial.println(speedFactor);
    }
    
    void Car::colorSensorCalibration(){
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
    void Car::NAV_Move(int rightMotorSpeed, int leftMotorSpeed, char NAV_direction){
        NAV_Motor_L_Speed = leftMotorSpeed;
        NAV_Motor_R_Speed = rightMotorSpeed;
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
    
    void Car::setup(){
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
    
    void Car::controller(){

        int IRReading = IR_Sensor_Priority();
        
        //(0 = no mission, 1 = joker, 2 = riddler, 3 = police chase)
        missionFlag = NAV_Color_Sensor();
    
        //Selects mission based on mission flag and initiates the mission
        missionSelector();

        //Takes control actions from IR_Sensor_Priority and outputs motor signals & speeds
        startMoving(IRReading);

        caveEntering();

        Serial.write('e');
    }
    int Car::IR_Sensor_Priority(){  // outputs control actions (staight line, big turn right)
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
        IR3 = !digitalRead(NAV_Infrared_3);    // black IR reading 1 and no light
        IR4 = digitalRead(NAV_Infrared_4);    // white IR reading 0 and light
        IR5 = digitalRead(NAV_Infrared_5);

        if (IR1 && !IR5){
            Serial.println("Big Turn Right");   //big turn right
            return 2;
        }
        else if (!IR1 && IR5){

            Serial.println("Big Turn Left");   //big turn left
            return 3;
        }
        else if((!IR1) && (!IR4) && (!IR5) && IR2){
            Serial.println("Small Turn Right");  //small turn right
            return 4; 
        }
        else if((!IR1) && (!IR2) && (!IR5) && IR4){
            Serial.println("Small Turn Left");//small turn left
            return 5; 
        }
        else if(IR3&&IR2&&IR4 ){
            Serial.println("Straight Line");//straight line
            return 1;
        }
        else if((!IR1) && (!IR2) && (!IR4) && (!IR5)){
            Serial.println("REVERSE");//REVERSE or do nothing
            return 0;
            
        }
      }

    void Car::NAV_IR_TEST(){
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

    int Car::NAV_Color_Sensor(){
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
    
    if (abs(R-calibValuesJoker[0]) < 35 
     && abs(G-calibValuesJoker[1]) < 35 
     && abs(G-calibValuesJoker[2]) < 35){
        //red
        return 1;
    }
    else if(abs(R-calibValuesRiddler[0]) < 35 
         && abs(G-calibValuesRiddler[1]) < 35 
         && abs(B-calibValuesRiddler[2]) < 35){;
        //green
        return 2;
    }
    else if(abs(R-calibValuesPoliceChase[0]) < 35 
         && abs(G-calibValuesPoliceChase[1]) < 35 
         && abs(B-calibValuesPoliceChase[2]) < 35){
        //yellow
        return 3;
    }
    else{
        //black
        return 5;
    }
}

    void Car::missionSelector(){
        switch (missionFlag)
        {
        case 0:
            Serial.println("White");//white
            break;
        case 1:
            Serial.println("Joker Mission");
            jokerMission();     //red
            break;
        case 2:
            Serial.println("Riddler Mission");
            riddlerMission();   //green
            break;
        case 3:
            Serial.println("Police Chase Mission");
            policeChaseMission();//yellow
            //check for second time it detects yellow to end the mission
            break;
        case 4:
            Serial.println("Black real");//black
            break;
        default:
            Serial.println("no color detected");
            break;
        }
    }

    void Car::slaveReciever(){
        
        if(Serial.available() > 0){
            signalFromSlave = Serial.read();
        }
        else{
            //do nothing
        }
    }

    void Car::jokerMission(){
        //stop 
        //send flag to slave to initiate shooting mechanism
        //wait for signal from slave to continue

        unsigned long tick = millis();
        unsigned long tock = millis();

        //time 3ada 12 secs aw signal men elslave == D -> break || signalFromSlave != 'D'
        
        if (jokerMissionFlag == false){
  
            while(signalFromSlave != 'D'){
                
                NAV_Move(0, 0, 'F');
                
                //Send flag to slave to initiate shooting mechanism
                Serial.write('J'); //start shooting mechanism for joker mission
                
                // ~recieve signal from slave~
                //wait for signal from slave to continue
                slaveReciever();
                
                tock = millis();
                if((tock - tick > 12000) ){
                    signalFromSlave = 'D';
                    //time exceeded, move on
                }
                
                if(last_move=='L' && (signalFromSlave == 'D')){
                    NAV_Move(70,70,'B'); //turn 180???
                    delay(1500);
                    NAV_Move(70,0,'B'); //turn 90 left
                    delay(1500);
                }
                else if(last_move=='R' && (signalFromSlave == 'D')){
                    NAV_Move(70,70,'B'); //turn 180???
                    delay(1500);
                    NAV_Move(0,70,'B'); //turn 90 right
                    delay(1500);
                }
                else{
                    //do nothing
                }
                delay(100); 
                jokerMissionFlag = true;
                // if(signalFromSlave == 'D'){
                //     //turn 180 dont accept green signals again
                //     NAV_Move(70,0,'B'); //turn 180???
                //     delay(1000);
                //     NAV_Move(70,70,'F'); //move forward to get away from green circle
                //     delay(100); 
                //     jokerMissionFlag = true;
                // }
                
            }
            
        }
        else{
            //do nothing
            Serial.println("Joker Mission Ended");
        }
        
        }

    void Car::riddlerMission(){
        //stop 
        //send flag to slave to initiate shooting mechanism
        //wait for signal from slave to continue

        unsigned long tick = millis();
        unsigned long tock = millis();

        
        if (riddlerMissionFlag == false){
  
            while(signalFromSlave != 'D'){
                
                NAV_Move(0, 0, 'F');
                
                //Send flag to slave to initiate shooting mechanism
                Serial.write('R'); //start shooting mechanism for riddler mission
                
                // ~recieve signal from slave~
                //wait for signal from slave to continue
                slaveReciever();
                
                tock = millis();
                if((tock - tick > 12000) ){
                    signalFromSlave = 'D';
                    //time exceeded, move on
                }
                
                if(last_move=='L' && (signalFromSlave == 'D')){
                    NAV_Move(70,70,'B'); //turn 180???
                    delay(1500);
                    NAV_Move(70,0,'B'); //turn 90 left
                    delay(1500);
                }
                else if(last_move=='R' && (signalFromSlave == 'D')){
                    NAV_Move(70,70,'B'); //turn 180???
                    delay(1500);
                    NAV_Move(0,70,'B'); //turn 90 right
                    delay(1500);
                }
                else{
                    //do nothing
                }
                delay(100); 
                riddlerMissionFlag = true;
                
            }
            
        }
        else{
            //do nothing
            Serial.println("Riddler Mission Ended");
        }
        
        
    }

    void Car::policeChaseMission(){
    // implement police chase mission here
    unsigned long tick;
    
    tick = millis();
    
    if(policeFlag == true){
        speedFactor = normalSpeed; //regular speed
        //mission ended
        //2nd time yellow is detected -> end mission
    }
    unsigned long counter = 800L + tick;
    if (!policeFlag){
        while(tick < counter){

            //Increase speed of motors
            speedFactor = maximumSpeed;
            
            int signal = IR_Sensor_Priority();
            startMoving(signal);
            //hinders signal from color sensor for 'counter' seconds to make sure the robot passes 
            //the first yellow line
            }
    }
    //if color sensor detects yellow again -> end mission
    policeFlag = true;
    }

    void Car::startMoving(int signal){ //gives signals to motors with speed
        /*
        0 = Reverse
        1 = Straight line
        2 = Big turn right
        3 = Big turn left
        4 = Small turn right
        5 = Small turn left
        */
        switch(signal){
        case 0:
            
            // Serial.println("REVERSE"); //REVERSE
            // NAV_Move(60*speedFactor, 60*speedFactor, 'B');
            // delay(30);
            break;
        
        case 1:
            //straight line
            Serial.println("Straight Line"); //straight line
            NAV_Move(70*speedFactor, 70*speedFactor, 'F');
            delay(80);
            break;
        
        case 2:
            //big turn right
            Serial.println("Big Turn Right");   //big turn right
            NAV_Move(40*speedFactor, 90*speedFactor, 'F');
            delay(300);
            last_move='R';
            break;
        case 3:
            //big turn left
            Serial.println("Big Turn Left");   //big turn left
            NAV_Move(90*speedFactor ,40*speedFactor, 'F');
            delay(300);
            last_move='L';
            break;

        case 4:
            //small turn right
            Serial.println("Small Turn Right");  //small turn right
            NAV_Move(50*speedFactor, 80*speedFactor, 'F');
            delay(120);
            break;

        case 5:
            //small turn left
            Serial.println("Small Turn Left");//small turn left
            NAV_Move(80*speedFactor, 50*speedFactor, 'F');
            delay(120);
            break;
        
        default:
            NAV_Move(40*speedFactor, 40*speedFactor, 'F');
            delay(100);
            //do nothing
            break;
        }
    }
    int Car::NAV_getRed()
    {
        digitalWrite(NAV_Color_s2, LOW);
        digitalWrite(NAV_Color_s3, LOW);
        int PW = pulseIn(NAV_colorSensor_out, LOW,5000);
        PW = map(PW, 79, 215, 255, 0);
        return PW;
    }
    int Car::NAV_getBlue()
    {
        digitalWrite(NAV_Color_s2, LOW);
        digitalWrite(NAV_Color_s3, HIGH);
        int PW = pulseIn(NAV_colorSensor_out, LOW,5000);
        PW = map(PW, 65, 171, 255, 0);
        return PW;
    }
    int Car::NAV_getGreen()
    {
        digitalWrite(NAV_Color_s2, HIGH);
        digitalWrite(NAV_Color_s3, HIGH); // white R= 79 G =74 B =65
                                        //  black R= 215 G =202 B =171
        int PW = pulseIn(NAV_colorSensor_out, LOW,5000);//analogRead(NAV_colorSensor_out);//pulseIn(NAV_colorSensor_out, LOW);
        PW = map(PW, 74, 202, 255, 0);
        return PW;
    }

    void Car::caveEntering(){
        if(caveSignal == 'O'){
            if(!caveOpened){
                NAV_Move(0,0,'F');
                delay(5000);
            }
            caveOpened = true;
        }   
    }
/*
Master:
-IR sensors -> (Directions)
-Color sensor -> (Mission Selector)
-Wheel motors -> (Start moving)
Send to Slave : (MissionFlag)
Recieve from Slave : (missionFinisher) - (Cave Gate Signal 'O')

Slave:
-Loading Servo -> (takes mission flag)
-Shooting motor -> (Takes signal from loading servo, outputs missionFinisher to master Arduino)
-Ultrasonic ->(Gives signal 'O' to master arduino)

Messages:
'O' : Cave is near, Open gate(laptop) , Stop for 2 seconds (Master)
'J' : Detected jokerMission(Red), Stop and wait for finisherFlag(Master), initiate Loading 
and shooting the red ball (Slave)
'R' : Detected jokerMission(Green), Stop and wait for finisherFlag(Master), initiate Loading 
and shooting the green ball (Slave)
'D' : missionFinisher flag from either joker or riddler, recieve char to continue (Master)
 
*/