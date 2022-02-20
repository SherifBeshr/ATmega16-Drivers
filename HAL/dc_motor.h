/******************************************************************************************************
File Name	: dc_motor.h
Author		: Sherif Beshr
Description : header file for the DC Motor driver
*******************************************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/***************************************************************************************************
 *                                		Definitions                                  			   *
 ***************************************************************************************************/

#define DC_MOTOR_PORT_ID			PORTB_ID
#define DC_MOTOR_PIN1_ID			PIN0_ID
#define DC_MOTOR_PIN2_ID			PIN1_ID

/***************************************************************************************************
 *                                		Types Declaration                                  	   	   *
 ***************************************************************************************************/

typedef enum {
	CW, ACW, STOP
}DcMotor_State;

/***************************************************************************************************
 *                                		Functions Prototypes                                  	   *
 ***************************************************************************************************/

/*
 * Description :
 * Initialize the DC Motor:
 * 1. Setup the DC Motor pins directions by using the GPIO driver.
 * 2. Initialize the DC Motor to STOP.
 */
void DcMotor_Init(void);

/*
 * Description :
 * Set the DC Motor State and speed:
 * 1. Set the Motor State ( STOP --> PIN1=0 & PIN2=0  ,  CW --> PIN1=0 & PIN2=1 ,  ACW --> PIN1=1 & PIN2=0 )
 * 2. Set the Motor Speed by passing duty cycle to the PWM function.
 * Input: State ( CW or ACW or STOP ) , Speed = duty cycle
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
