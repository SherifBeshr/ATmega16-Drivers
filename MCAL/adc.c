/******************************************************************************************************
File Name	: adc.c
Author		: Sherif Beshr
Description : Source file for the AVR ADC driver supports both Polling & interrupt modes
*******************************************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */



/*
 * In polling mode the interrupt.h file is not included.
 */
#if (ADC_INTERRUPT_0_POLLING_1 == 0)
#include <avr/interrupt.h>
volatile uint16 g_ADC;
#endif


/****************************************************************************************************
 *                      				Functions Definitions                                  		*
 ****************************************************************************************************/

#if (ADC_INTERRUPT_0_POLLING_1 == 0)
ISR(ADC_vect)
{
	g_ADC = ADC;
}
#endif


void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0  to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = ((Config_Ptr->ref_volt) << REFS0);		/* Adjust REFS1:0 bits in ADMUX Register */

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 (Configurable) to choose ADC_Clock = F_CPU/pre-scalar --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) | ((Config_Ptr->prescaler) << ADPS0);

#if (ADC_INTERRUPT_0_POLLING_1 == 0)				/* Interrupt mode ADC */
	ADCSRA |= (1<<ADIE);							/* Enable ADC Interrupt module*/
#endif
}

/* Input channel number must be from 0 --> 7 */
uint16 ADC_readChannel(ADC_Channel channel_num)
{

	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x7); 	/* Choose the correct channel by setting the channel number
													 * in MUX4:0 bits and Clear first 5 bits in the ADMUX
													 * (channel number MUX4:0 bits)  before set the required channel */
	SET_BIT(ADCSRA,ADSC); 							/* Start conversion write '1' to ADSC */

#if (ADC_INTERRUPT_0_POLLING_1 == 0)				/* Interrupt mode ADC */
	return g_ADC;									/* Return the global variable value in ISR */
#else												/* Polling mode ADC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); 				/* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); 							/* Clear ADIF by write '1' to it */
	return ADC;										/* Read the digital value from the data register */
#endif
}

