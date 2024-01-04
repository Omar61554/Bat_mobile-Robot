/***********************************************************************************************************************/
/************** AUTHOR: Team 9          ********************************************************************************/
/************** DATE: 11/26/2023        ********************************************************************************/
/************** VERSION: 0.1            ********************************************************************************/
/************** FILE: BLUE_interface.h  ********************************************************************************/
/***********************************************************************************************************************/


#ifndef BLUE_INTERFACE_H_
#define BLUE_INTERFACE_H_
#define calibDistance 100 
//bluetooth pins
#define BLUE_RX 2
#define BLUE_TX 3

//ultrasonic pins 
#define BLUE_Trig 10
#define BLUE_Echo 11
//servo motor pins
#define BLUE_servo 12


//functions

/**
 * @brief check if the barrier is close or not
 * 
 * @return char 
 */
char BLUE_checkBarrier();

/**
 * @brief open the barrier
 * 
 * @param checkBarrier 
 */
void BLUE_Barrier(char checkBarrier);





#endif /* BLUE_INTERFACE_H_ */