/******************************************************************************************************
File Name	: adc.h
Author		: Sherif Beshr
Description : Header file for the AVR ADC driver supports both Polling & interrupt modes
*******************************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/***************************************************************************************************
 *                                		Definitions                                  			   *
 ***************************************************************************************************/
#define ADC_MAXIMUM_VALUE    	1023
#define ADC_REF_VOLT_VALUE   	5

#define ADC_CHANNEL_0			0
#define ADC_CHANNEL_1			1
#define ADC_CHANNEL_2			2
#define ADC_CHANNEL_3			3
#define ADC_CHANNEL_4			4
#define ADC_CHANNEL_5			5
#define ADC_CHANNEL_6			6
#define ADC_CHANNEL_7			7
/***************************************************************************************************
 *                                		Types Declaration                                  	   *
 ***************************************************************************************************/
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

extern uint16 g_ADC;

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
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
