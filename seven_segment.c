/******************************************************************************************************
File Name	: seven_segment.c
Author		: Sherif Beshr
Description : 
*******************************************************************************************************/

#include "seven_segment.h"
#include "gpio.h"

void Seven_seg_init(uint8 Port_Pin1, uint8 Pin1, uint8 Port_Pin2, uint8 Pin2, uint8 Port_Pin3, uint8 Pin3, uint8 Port_Pin4, uint8 Pin4)
{
	GPIO_setupPinDirection(Port_Pin1, Pin1, PIN_OUTPUT);
	GPIO_setupPinDirection(Port_Pin2, Pin2, PIN_OUTPUT);
	GPIO_setupPinDirection(Port_Pin3, Pin3, PIN_OUTPUT);
	GPIO_setupPinDirection(Port_Pin4, Pin4, PIN_OUTPUT);

}
