/******************************************************************************************************
File Name	: pwm.c
Author		: Sherif Beshr
Description : source file for the PWM driver
*******************************************************************************************************/

#include <avr/io.h>
#include "pwm.h"
#include "gpio.h"

/*
 * Description :
 * Function responsible to calculate the ON_time of PWM with the duty cycle.
 * FAST PWM mode (WGM01 = 1, WGM00 = 1)
 * Non-Inverting  Clear OC0 On Compare ( COM01 = 1 )
 * Pre-scalar = 8 ( CS01 = 1 )
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	uint8 ON_time = (uint8)((uint16)(PWM_MAX_VALUE * duty_cycle ) / 100);
	TCNT0 = 0;
	OCR0 = ON_time;
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);		/* Non- Inverting Fast PWM ( Prescalar = 8 ) */
}
