#include "NAV_interface.h"
#include "SHOT_interface.h"


void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
 
}

void loop() {
  if (Serial.available() > 0) { // Check if there is any data available on the serial port
    char command = Serial.read(); // Read the incoming command
    if (command == 'U') { // If the command is 'U', signal from ultrasonic
      //implemnt ultrasonic code
      //
    }
    else if (command=='J'){
    //implement jokerMission  
    }
    else if (command == 'R') { // If the command is '0', turn the lights off
    //implement riddlerMission
     
    }
     
}}