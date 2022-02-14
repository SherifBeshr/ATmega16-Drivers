/******************************************************************************************************
File Name	: seven_segment.c
Author		: Sherif Beshr
Description : Source file for the 7-Segment Driver
*******************************************************************************************************/

#include "seven_segment.h"
#include "gpio.h"
#include "common_macros.h"

#define Port_Pin1		PORTB_ID
#define Port_Pin2		PORTB_ID
#define Port_Pin3		PORTB_ID
#define Port_Pin4		PORTB_ID

#define Pin1			PIN0_ID
#define Pin2			PIN1_ID
#define Pin3			PIN2_ID
#define Pin4			PIN3_ID

/*
 * Description :
 * Setup the direction for pins used by the 7-segment as Output
 */
void Seven_seg_init(void)
{
	GPIO_setupPinDirection(Port_Pin1, Pin1, PIN_OUTPUT);
	GPIO_setupPinDirection(Port_Pin2, Pin2, PIN_OUTPUT);
	GPIO_setupPinDirection(Port_Pin3, Pin3, PIN_OUTPUT);
	GPIO_setupPinDirection(Port_Pin4, Pin4, PIN_OUTPUT);
}

/*
 * Description :
 * Check the number binary and set the equivalent pin
 * Example: Num = 5 (0101) --> Pin1 = 1, Pin2 = 0, Pin3 = 1, Pin4 = 0
 */
void Seven_seg_display (uint8 Num)
{
	BIT_IS_SET(Num,0) ? GPIO_writePin(Port_Pin1,Pin1,LOGIC_HIGH) : GPIO_writePin(Port_Pin1,Pin1,LOGIC_LOW);
	BIT_IS_SET(Num,1) ? GPIO_writePin(Port_Pin2,Pin2,LOGIC_HIGH) : GPIO_writePin(Port_Pin2,Pin2,LOGIC_LOW);
	BIT_IS_SET(Num,2) ? GPIO_writePin(Port_Pin3,Pin3,LOGIC_HIGH) : GPIO_writePin(Port_Pin3,Pin3,LOGIC_LOW);
	BIT_IS_SET(Num,3) ? GPIO_writePin(Port_Pin4,Pin4,LOGIC_HIGH) : GPIO_writePin(Port_Pin4,Pin4,LOGIC_LOW);

}
