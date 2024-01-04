
#ifndef SHOT_INTERFACE_H_
#define SHOT_INTERFACE_H_

//define motor pins
#define SHOT_Motor_R_Enable 9 //Enable signal Right motor //white
#define SHOT_Motor_R_Right 7 //direction 1 Right motor   //black
#define SHOT_Motor_R_Left 8 //direction 2 Right motor    //yellow

//define servo motor pins
#define SHOT_servo 12


//functions

//shot the ball
/**
 * @brief 
 * 
 */
void SHOT_shoot();

//select the ball
/**
 * @brief 
 * 
 */
void SHOT_selectBall(char checkColor);




#endif /* SHOT_INTERFACE_H_ */
