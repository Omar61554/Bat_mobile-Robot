#include "NAV_interface.h"
#include "SHOT_interface.h"
#include "BLUE_interface.h"


void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
 
}

void loop() {
  //check ultrasonic sensor
BLUE_checkBarrier();
  if (Serial.available() > 0) { // Check if there is any data available on the serial port
    char command = Serial.read(); // Read the incoming command
    
    if (command=='J'){
    //implement jokerMission  
    SHOT_selectBall(command);
    delay(1000);
    SHOT_shoot();
   
    else if (command == 'R') { // If the command is '0', turn the lights off
    //implement riddlerMission
    SHOT_selectBall(command);
    delay(1000);
    SHOT_shoot();
    }
     
}




}