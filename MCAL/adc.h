/******************************************************************************************************
File Name	: adc.h
Author		: Sherif Beshr
Description : Header file for the AVR ADC driver supports both Polling & interrupt modes
*******************************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

#define INTERRUPT				0
#define POLLING					1
/*
 * (Configurable)
 * ADC_MODE = 0 --> ( Interrupt Mode )
 * ADC_MODE = 1 --> ( Polling Mode )
 */
#define ADC_MODE				INTERRUPT

/***************************************************************************************************
 *                                		Definitions                                  			   *
 ***************************************************************************************************/
#define ADC_MAXIMUM_VALUE    	1023
#define ADC_REF_VOLT_VALUE   	5

/***************************************************************************************************
 *                                		Types Declaration                                  	   	   *
 ***************************************************************************************************/
typedef enum
{
	ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2, ADC_CHANNEL_3, ADC_CHANNEL_4, ADC_CHANNEL_5, ADC_CHANNEL_6, ADC_CHANNEL_7
}ADC_Channel;

typedef enum
{
	AREF, AVCC, INTERNAL_2_56V = 3
}ADC_ReferenceVolatge;

typedef enum
{
	FCPU_2, FCPU_4 = 2, FCPU_8, FCPU_16, FCPU_32, FCPU_64, FCPU_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

#if (ADC_MODE == 0)
volatile extern uint16 g_ADC;
#endif

/***************************************************************************************************
 *                                		Functions Prototypes                                  	   *
 ***************************************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(ADC_Channel channel_num);

#endif /* ADC_H_ */
