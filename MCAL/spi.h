/******************************************************************************************************
File Name	: spi.h
Author		: Sherif Beshr
Description : 
*******************************************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"

#define SPI_PORT		PORTB_ID
#define SPI_SS			PIN4_ID
#define SPI_MOSI		PIN5_ID
#define SPI_MISO		PIN6_ID
#define SPI_SCK			PIN7_ID



/***************************************************************************************************
 *                                		Types Decelerations                                  	   *
 ***************************************************************************************************/


/*	Clock of SPI module	*/
typedef enum
{
	SPI_Clock_4, SPI_Clock_16, SPI_Clock_64, SPI_Clock_128
}SPI_Clock;

/*	Choose if you want SPI clock speed to be doubled	*/
typedef enum
{
	SPI_Speed_Normal, SPI_Speed_Double
}SPI_DoubleSpeed;

/*	Choose what to transmit first the MSB or LSB	*/
typedef enum
{
	SPI_MSB, SPI_LSB
}SPI_DataOrder;

/*	Logic of clock to start from if CPOL=0 start clock from logical zero
 *	if CPOL = 1 start clock from logical one
 */
typedef enum
{
	Clock_Low, Clock_high
}SPI_ClockPolarity;

/*	Determine when the data needs to be sampled/captured at leading or falling edge	*/
typedef enum
{
	Leading_Edge, Trailing_Edge
}SPI_ClockPhase;

/*	Structure accessed to choose the SPI different modes selecting
 *  1- Clock rate
 *  2- Double the clock rate or no
 *  3- MSB or LSB first
 *  4- Start clock from logic low or logic high
 *  5- Determine when data to be sampled
 */

typedef struct
{
	SPI_Clock			SPI_Clock;
	SPI_DoubleSpeed		SPI_DoubleSpeed;
	SPI_DataOrder		SPI_DataOrder;
	SPI_ClockPolarity	SPI_ClockPolarity;
	SPI_ClockPhase		SPI_ClockPhase;
}SPI_ConfigType;

/***************************************************************************************************
 *                                		Function Prototypes                                  	   *
 ***************************************************************************************************/

void SPI_initMaster(const SPI_ConfigType* Config_Ptr);

void SPI_initSlave(const SPI_ConfigType* Config_Ptr);

uint8 SPI_sendReceiveByte(uint8 data);

void SPI_sendString();

void SPI_receiveString();

#endif /* SPI_H_ */
