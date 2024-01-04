#include "NAV_interface.h"
#include "SHOT_interface.h"


void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  SoftwareSerial mySerial(BLUE_RX, BLUE_TX); // RX, TX
  mySerial.begin(9600);
}

void loop() {
  
  Serial.println("Outside Loop");
  BLUE_checkBarrier();
  if (Serial.available() > 0) { // Check if there is any data available on the serial port
    char command = Serial.read(); // Read the incoming command
    Serial.print("Recieved Message : ");
    Serial.println(command);
    if (command == 'U') { // If the command is 'U', signal from ultrasonic
      //implemnt ultrasonic code
      Serial.println("Ultrasonic message");
    }
    else if (command=='J'){
    //implement jokerMission  
        Serial.println("Joker mission");
        
        SHOT_selectBall('J');
        SHOT_shoot();
        digitalWrite(13,LOW);
        delay(100);
        digitalWrite(13,HIGH);
        delay(200);
        digitalWrite(13,LOW);
        delay(300);
        digitalWrite(13,HIGH);
        
        delay(1000);
        digitalWrite(13,LOW);
        unsigned long tick = millis();
        unsigned long tock = millis();
        while((tock - tick) <5000){        
        Serial.write('D');
        tock = millis();}
    }
    else if (command == 'R') { //implement riddlerMission  
        Serial.println("Riddler mission");
        
        SHOT_selectBall('R');
        SHOT_shoot();
        digitalWrite(13,LOW);
        delay(100);
        digitalWrite(13,HIGH);
        delay(200);
        digitalWrite(13,LOW);
        delay(300);
        digitalWrite(13,HIGH);
        
        delay(1000);
        digitalWrite(13,LOW);
        unsigned long tick = millis();
        unsigned long tock = millis();
        while((tock - tick) <5000){        
        Serial.write('D');
        tock = millis();}
        }
     }
}
