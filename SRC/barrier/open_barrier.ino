#include "NAV_interface.h"
#include "SHOT_interface.h"
#include "BLUE_interface.h"


void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
 
}

void loop() {
//open barrier from bluetooth
  if (Serial.available() > 0) { // Check if there is any data available on the serial port
    char command = Serial.read(); // Read the incoming command
    BLUE_Barrier(command);
    
    // if (command=='O'){
    // //open barrier 
    
    // }

    // else{} 
    //   //do nothing
      
    // }

}