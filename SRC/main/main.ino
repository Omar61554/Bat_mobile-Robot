int rightEnable = 6; //Enable signal Right motor
int rightRightPow = 7; //direction 1 Right motor
int rightLeftPow = 8; //direction 2 Right motor
int leftEnable = 11; //Enable signal left motor
int leftRightPow = 12; //direction 1 left motor
int leftLeftPow = 13; //direction 2 Left motor
int infraSignal = 2; //signal pin from IR Sensor 1
bool IRSIG; //signal coming from IR 
void turnRight();
void moveStraight();
void turnLeft();
void setup() {
  // put your setup code here, to run once:
  //right motor 2 etgah , 1 enable ### left motor 2 etgah , 1 enable
   Serial.begin(9600);
  pinMode(infraSignal, INPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(rightRightPow, OUTPUT);
  pinMode(rightLeftPow, OUTPUT);
  pinMode(leftEnable, OUTPUT);
  pinMode(leftRightPow, OUTPUT);
  pinMode(leftLeftPow, OUTPUT);
  digitalWrite(rightRightPow, LOW);
  digitalWrite(leftLeftPow, HIGH);
  digitalWrite(rightLeftPow, HIGH);
  digitalWrite(leftRightPow, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  IRSIG = digitalRead(infraSignal);
  if(!IRSIG){
    turnLeft();
    Serial.println("signal");
    delay(800);}
  else{
    Serial.println("no signal");
    moveStraight();
    delay(800);
    }
  
  //turnLeft();
  //Serial.println("turn Left?");
  //delay(4000);
}

void turnRight(){
    
    
    analogWrite(leftEnable, 100);
    analogWrite(rightEnable, 0);
    
  }

void turnLeft(){
    
    
    analogWrite(leftEnable, 0);
    analogWrite(rightEnable, 100);
}

void moveStraight(){
    analogWrite(leftEnable, 100);
    analogWrite(rightEnable, 100);
  }
