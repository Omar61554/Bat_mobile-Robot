/***********************************************************************************************************************/
/************** AUTHOR: OMAR KHALED     ********************************************************************************/
/************** DATE: 11/26/2023        ********************************************************************************/
/************** VERSION: 0.1            ********************************************************************************/
/************** FILE: NAV_program.h     ********************************************************************************/
/***********************************************************************************************************************/

#include "NAV_interface.h"
#include "NAV_private.h"
#include "NAV_configure.h"
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
   Car::Car(){
        int missionFlag = 0;
        
        // R= 271 G =255 B =205 yellow
        // R= 270 G =116 B =159 red
        // R= 290 G =302 B =279 green

        //red R= 335 G =202 B =210
//green R= 279 G =312 B =239
//yellow R= 352 G =326 B =269
//white R= 360 G =360 B =368
//black R= 23 G =44 B =63


        int calibValuesPoliceChase[3] ={352,326,269}; // {271,255,205}; //R > 340 && G > 320 && B < 290
        int calibValuesJoker[3] = {335,202,210}; //(R > 310 && G < 270 && B < 270)
        int calibValuesRiddler[3] = {279, 312, 239}; //(G > 300 && R < 300 && B < 260){
        int NAV_Motor_L_Speed = 0;
        int NAV_Motor_R_Speed = 0;
        char NAV_direction = 'F';
        float speedFactor = 1.0;
        
        bool policeFlag = false;
        bool jokerMissionFlag = false;
        bool riddlerMissionFlag = false;
        char signalFromSlave = 'k';
    }
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
        
        /*
        IR readings -> (outputs control actions (staight line, big turn right))
        startMoving takes in IR readings -> outputs motor signals  
        */
        //Reads from the 5 IR sensors and outputs control actions (staight line, big turn right)
        // 0 = Reverse 1 = Straight line 2 = Big turn right 
        // 3 = Big turn left 4 = Small turn right 5 = Small turn left
        unsigned long tick = millis();
        unsigned long tock = millis();
        
        //tock = millis();
        //Serial.print("Loop start time: ");
        //Serial.println(tock - tick);

        int IRReading = IR_Sensor_Priority();
        
        // tock = millis();
        // Serial.print("Time taken in IR priority: ");
        // Serial.println(tock - tick);
        //Reads from the color sensor and outputs mission flag 
        //(0 = no mission, 1 = joker, 2 = riddler, 3 = police chase)
        missionFlag = NAV_Color_Sensor();
        //missionFlag = 0;
        // tock = millis();
        // Serial.print("Time taken in color sensor function: ");
        // Serial.println(tock - tick);

        //Selects mission based on mission flag and initiates the mission
        missionSelector();

        // tock = millis();
        // Serial.print("Time taken in mission selector function: ");
        // Serial.println(tock - tick);

        //Takes control actions from IR_Sensor_Priority and outputs motor signals & speeds
        startMoving(IRReading);

        // tock = millis();
        // Serial.print("Time taken in start moving function: ");
        // Serial.println(tock - tick);
        //color sensors readings
        //mission selector
        //nav move
        //
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
            return 2; //big turn right
            // NAV_Move(50*speedFactor, 70*speedFactor, 'F');
            // delay(300);
            // last_move='R';
        }
        else if (!IR1 && IR5){

            Serial.println("Big Turn Left");   //big turn left
            return 3; //big turn left
            // NAV_Move(70*speedFactor ,30*speedFactor, 'F');
            // delay(300);
            // last_move='L';
        }
        else if((!IR1) && (!IR4) && (!IR5) && IR2){
            Serial.println("Small Turn Right");  //small turn right
            return 4; //Small turn right
            // NAV_Move(50*speedFactor, 70*speedFactor, 'F');
            // delay(100);
        }
        else if((!IR1) && (!IR2) && (!IR5) && IR4){
            Serial.println("Small Turn Left");//small turn left
            return 5; //Small turn left
            // NAV_Move(70*speedFactor, 50*speedFactor, 'F');
            // delay(100);
        }
        // else if(IR3 || (IR2&&IR4) || (IR1&&IR5)){
        //     Serial.println("Straight Line");//straight line
        //     NAV_Move(70*F, 70*F, 'F');
        //     delay(200);
        // }
        else if(IR3&&IR2&&IR4 ){
            Serial.println("Straight Line");//straight line
            return 1; //straight line code
            // NAV_Move(70*speedFactor, 70*speedFactor, 'F');
            // delay(200);
        }
        else if((!IR1) && (!IR2) && (!IR4) && (!IR5)){ // (!IR3) && (Removed IR3 sensor because it is not working!!)
            Serial.println("REVERSE");//REVERSE or do nothing
            return 0;
            // NAV_Move(70*speedFactor, 70*speedFactor, 'B');
            // delay(200);
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
    unsigned long shik = millis();
    unsigned long shak = millis();

    int R = NAV_getRed();
    // shak = millis();
    // Serial.print("Get red time: ");
    // Serial.println(shak - shik);
    // shik = millis();

    int G = NAV_getGreen();
    // shak = millis();
    // Serial.print("Get green time: ");
    // Serial.println(shak - shik);
    // shik = millis();

    int B = NAV_getBlue();  
    // shak = millis();
    // Serial.print("Get blue time: ");
    // Serial.println(shak - shik);
    // shik = millis();
    //if (R > calibValueRed && G > calibValueGreen && B > calibValueBlue){
    
    //else if (R > calibValueRed){
    if (abs(R-calibValuesJoker[0]) < 25 
     && abs(G-calibValuesJoker[1]) < 25 
     && abs(G-calibValuesJoker[2]) < 25){//(R > 310 && G < 270 && B < 270){
        //red
        return 1;
    }
    //else if (G > calibValueGreen){
    else if(abs(R-calibValuesRiddler[0]) < 25 
         && abs(G-calibValuesRiddler[1]) < 25 
         && abs(B-calibValuesRiddler[2]) < 25){;
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
    else if(abs(R-calibValuesPoliceChase[0]) < 25 
         && abs(G-calibValuesPoliceChase[1]) < 25 
         && abs(B-calibValuesPoliceChase[2]) < 25){
        //(R > 340 && G > 320 && B < 290){
        //yellow
        return 3;
    }
    // else if(abs(R-calibValuesWhite[0]) < 35
    //      && abs(G-calibValuesWhite[1]) < 35 
    //      && abs(G-calibValuesWhite[2]) < 35){
    //     //(R > 310 && G > 320 && B > 320)
    //     //white
    //     return 0;
    // }
    else{
        //black
        return 5;
    }


}

// void Car::missionSelector(){
//     switch (colorValue)
//     {
//     case 0:
//         Serial.println("Whiteee");//white
//         break;
//     case 1:
//         jokerMission();     //red
//         break;
//     case 2:
//         riddlerMission();   //green
//         break;
//     case 3:
//         //blue
//         break;
//     case 4:
//         //yellow

//         policeChaseMission();
        
        
//         //check for second time it detects yellow to end the mission
//         break;
//     default:
//         Serial.println("black");
//         break;

//     }
// }
    void Car::missionSelector(){
        switch (missionFlag)
        {
        case 0:
            Serial.println("White");//white
            
            break;
        case 1:
            Serial.println("Joker Mission");
            // if(!jokerMissionFlag){NAV_Move(0,0,'F');
            // delay(4000);}
            // jokerMissionFlag = true;
            //Serial.begin(9600);
            jokerMission();     //red
            break;
        case 2:
            Serial.println("Riddler Mission");
            // if(!riddlerMissionFlag){NAV_Move(0,0,'F');
            // delay(4000);}
            // riddlerMissionFlag = true;
            //riddlerMission();   //green
            break;
        case 3:
            Serial.println("Police Chase Mission");
            // if(!policeFlag){
            //     NAV_Move(0,0,'F');
            //     delay(4000);}
            // policeFlag = true;
            policeChaseMission();//yellow
            //check for second time it detects yellow to end the mission
            break;
        case 4:
            Serial.println("Blackkkkk real");//black
            break;
        default:
            Serial.println("black");
            break;
        }
    }

    void Car::slaveReciever(){
        //recieve signal from slave
        //signalFromSlave = Serial.read();
        //signalFromSlave += 1;
        //Serial.println(signalFromSlave);
        if(Serial.available() > 0){
            signalFromSlave = Serial.read();
            //Serial.println(signalFromSlave);
        }
        else{
            //do nothing
        }
    }

    void Car::jokerMission(){
        
        //stop 
        //send flag to slave to initiate shooting mechanism
        //wait for signal from slave to continue
        NAV_Move(0, 0, 'F');
        delay(4000);
        if (jokerMissionFlag == false){
            while(signalFromSlave != 'D'){
                //stop
                NAV_Move(0, 0, 'F');
                //getSpeed();
                // Serial.println("inside signal slave loop");
                //send flag to slave to initiate shooting mechanism
                Serial.write('J'); //start shooting mechanism for joker mission
                
                // ~recieve signal from slave~
                //wait for signal from slave to continue
                slaveReciever();
                delay(1000);
                NAV_Move(70,70,'B'); //turn 180???
                delay(1000);
                if(last_move=='R'){
                    NAV_Move(70,0,'L'); //turn 90 left
                    delay(1000);
                }
                else if(last_move=='L'){
                    NAV_Move(0,70,'R'); //turn 90 right
                    delay(1000);
                }
                else{
                    //do nothing
                }
                //NAV_Move(70,70,'F'); //move forward to get away from green circle
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
                delay(100);
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
        if (riddlerMissionFlag == false){
            while(signalFromSlave != 'D'){
                //stop
                NAV_Move(0, 0, 'F');
                getSpeed();
                Serial.println("inside signal slave loop");
                //send flag to slave to initiate shooting mechanism
                Serial.write('S'); //start shooting mechanism for joker mission
                
                // ~recieve signal from slave~
                //wait for signal from slave to continue
                slaveReciever();
                if(signalFromSlave == 'D'){
                    //turn 180 dont accept green signals again
                    NAV_Move(70,0,'B'); //turn 180???
                    delay(1000);
                    NAV_Move(70,70,'F'); //move forward to get away from green circle
                    delay(100); 
                    riddlerMissionFlag = true;
                }
                delay(100);
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
        speedFactor = 1.2; //regular speed
        //mission ended
        //2nd time yellow is detected -> end mission
    }
    unsigned long counter = 1000L + tick;
    if (!policeFlag){
        while(tick < counter){
            //move forward
            //Increase speed of motors
            speedFactor = 1.6;
            //IR_Sensor_Priority(2.2);
            int signal = IR_Sensor_Priority();
            startMoving(signal);
            Serial.println("still inside loop");
            getSpeed();
            //hinders signal from color sensor for 3 seconds to make sure the robot passes 
            //the first yellow line
            
            Serial.print("  tick before updating: ");
            Serial.println(tick);
            tick = millis();
            Serial.print("tick after updating: ");
            Serial.println(tick);
            }
        }
    
    //if color sensor detects yellow again -> end mission
    Serial.println("outside loop");
    policeFlag = true;
    // else{
    //     //end mission
    //     speedFactor = 1.7;
    //     //IR_Sensor_Priority(1.0);
    // }
    // policeFlag = true;
    
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
            
            Serial.println("REVERSE"); //REVERSE
            NAV_Move(60*speedFactor, 60*speedFactor, 'B');
            delay(80);
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
            NAV_Move(40*speedFactor, 70*speedFactor, 'F');
            delay(630);
            last_move='R';
            break;
        case 3:
            //big turn left
            Serial.println("Big Turn Left");   //big turn left
            NAV_Move(70*speedFactor ,40*speedFactor, 'F');
            delay(630);
            last_move='L';
            break;

        case 4:
            //small turn right
            Serial.println("Small Turn Right");  //small turn right
            NAV_Move(50*speedFactor, 70*speedFactor, 'F');
            delay(30);
            break;

        case 5:
            //small turn left
            Serial.println("Small Turn Left");//small turn left
            NAV_Move(70*speedFactor, 50*speedFactor, 'F');
            delay(30);
            break;
        
        default:
            NAV_Move(20*speedFactor, 20*speedFactor, 'F');
            delay(100);
            //do nothing
            break;
        }
};

int NAV_getRed()
{
    digitalWrite(NAV_Color_s2, LOW);
    digitalWrite(NAV_Color_s3, LOW);
    int PW = pulseIn(NAV_colorSensor_out, LOW,5000);
    PW = map(PW, 79, 215, 255, 0);
    return PW;
}
int NAV_getBlue()
{
    digitalWrite(NAV_Color_s2, LOW);
    digitalWrite(NAV_Color_s3, HIGH);
    int PW = pulseIn(NAV_colorSensor_out, LOW,5000);
    PW = map(PW, 65, 171, 255, 0);
    return PW;
}
int NAV_getGreen()
{
    digitalWrite(NAV_Color_s2, HIGH);
    digitalWrite(NAV_Color_s3, HIGH); // white R= 79 G =74 B =65
                                      //  black R= 215 G =202 B =171
    int PW = pulseIn(NAV_colorSensor_out, LOW,5000);//analogRead(NAV_colorSensor_out);//pulseIn(NAV_colorSensor_out, LOW);
    PW = map(PW, 74, 202, 255, 0);
    return PW;
}

/**
 * @brief  this function is used to setup the navigation module
 *
 */


/**
 * @brief this function is the main function of the navigation module
 *
 */


void NAV_COLORSENSOR_TEST(){

    NAV_getBlue();

    NAV_getGreen();

    NAV_getRed();



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