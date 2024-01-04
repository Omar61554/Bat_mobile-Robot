#include "BLUE_interface.h"
#include "SoftwareSerial.h"
#include <Servo.h>

/*
Slave: 
Sensors: Ultrasonic (Gives distance) -> Check Barrier (outputs distance// 'O')
Motors: Servo(Sorting) , DC Motor(Shooting)
UART connections: Takes characters (J,R) ->starts shooting based on character
*/


char BLUE_checkBarrier()
{
    //check if the barrier is open or not
    //if the barrier is open return true
    //else return false
    //implement the ultra sonic sensor detection then sends the command to the arduino to open the barrier

    //ultrasonic sensor
    pinMode(BLUE_Trig, OUTPUT);
    pinMode(BLUE_Echo, INPUT);

    long duration, distance;
    digitalWrite(BLUE_Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(BLUE_Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(BLUE_Trig, LOW);
    duration = pulseIn(BLUE_Echo, HIGH);
    distance = (duration / 2) / 29.1; // 29.1 is the speed of sound in cm/ms
    Serial.print(distance);
    Serial.println(" cm");
    delay(1000);


    if(distance<calibDistance)
    {
        //send signal to arduino to open the barrier
        //create new serial for pins 2 and 3 from function software serial
    
            // send via bluetooth module to arduino to open the barrier
            myserial.write('O');

            Serial.begin(9600);
            Serial.write('O'); //recieve this message in master arduino to stop the car for a moment
        return 'O';
    }
    else
    {
        mySerial.write('g');
        return 'g';
    }


        return true;
}

void BLUE_Barrier(char checkBarrier)
{
    //open the barrier
    //implement the servo motor to open the barrier to rotate 90 degrees
    //servo motor
    Servo BLUE_servo;
    BLUE_servo.attach(BLUE_servo);
    if(checkBarrier == 'O')
    {
        BLUE_servo.write(90);
    }
    else
    {
        BLUE_servo.write(0);

}



}