/***********************************************************************************************************************/
/************** AUTHOR: Team 9          ********************************************************************************/
/************** DATE: 11/26/2023        ********************************************************************************/
/************** VERSION: 0.1            ********************************************************************************/
/************** FILE: SHOT_program.h  ********************************************************************************/
/***********************************************************************************************************************/

#include "SHOT_interface.h"
#include "Arduino.h"
#include <Servo.h>




void SHOT_shoot()
{
  // rotate dc motor to shoot the ball
    pinMode(SHOT_Motor_R_Enable, OUTPUT);
    pinMode(SHOT_Motor_R_Right, OUTPUT);
    pinMode(SHOT_Motor_R_Left, OUTPUT);

    digitalWrite(SHOT_Motor_R_Enable, HIGH);
    digitalWrite(SHOT_Motor_R_Right, HIGH);
    digitalWrite(SHOT_Motor_R_Left, LOW);

}

void SHOT_selectBall(char checkColor)
{
  //rotate servo motor to select the ball
    Servo servo1;
    servo1.attach(SHOT_servo);
    // if ball is red rotate servo to 90 degree
    if(checkColor=='J'){
    servo1.write(90);
    delay(1000);

    SHOT_shoot();
    Serial.write('D');  //signal to master arduino that the ball is shot & mission completed
    }
    // if ball is green rotate servo to -90 degree
    else if(checkColor=='R'){
    servo1.write(-90);
    delay(1000);

    SHOT_shoot();
    Serial.write('D');  //signal to master arduino that the ball is shot & mission completed
    }

}
