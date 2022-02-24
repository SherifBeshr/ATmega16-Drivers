/******************************************************************************************************
File Name	: spi.c
Author		: Sherif Beshr
Description : 
*******************************************************************************************************/

#include "common_macros.h"
#include "spi.h"
#include "gpio.h"
#include <avr/io.h>		/* To use SPI registers */



/***************************************************************************************************
 *                                		Function Definitions                                  	   *
 ***************************************************************************************************/

void SPI_initMaster(const SPI_ConfigType* Config_Ptr)
{
	/* SPI Enable */
	SET_BIT(SPCR,SPE);

	/* Enable Master mode */
	SET_BIT(SPCR,MSTR);

	GPIO_setupPinDirection(SPI_PORT, SPI_MOSI, PIN_OUTPUT);			/* MOSI -> Output */
	GPIO_setupPinDirection(SPI_PORT, SPI_SCK, PIN_OUTPUT);			/* SCK  -> Output */
	GPIO_setupPinDirection(SPI_PORT, SPI_SS, PIN_OUTPUT);			/* SS   -> Output */
	GPIO_setupPinDirection(SPI_PORT, SPI_MISO, PIN_INPUT);			/* MISO -> Input */


	/*	Set Data order MSB or LSB first*/
	SPCR = (SPCR & 0xDF) | ((Config_Ptr->SPI_DataOrder)<<DORD);

	/*	Set Clock Polarity */
	SPCR = (SPCR & 0xF7) | ((Config_Ptr->SPI_ClockPolarity)<<CPOL);

	/*	Set Clock Phase */
	SPCR = (SPCR & 0xFB) | ((Config_Ptr->SPI_ClockPhase)<<CPHA);

	/*	Set Clock Rate */
	SPCR = (SPCR & 0xFC) | ((Config_Ptr->SPI_Clock)<<SPR0);

	/*	Set Double Speed */
	SPSR = (SPSR & 0xFE) | ((Config_Ptr->SPI_DoubleSpeed)<<SPI2X);
}

void SPI_initSlave(const SPI_ConfigType* Config_Ptr)
{
	/* SPI Enable */
	SET_BIT(SPCR,SPE);

	/* Enable Slave mode */
	CLEAR_BIT(SPCR,MSTR);

	GPIO_setupPinDirection(SPI_PORT, SPI_MOSI, PIN_INPUT);			/* MOSI -> Input */
	GPIO_setupPinDirection(SPI_PORT, SPI_SCK, PIN_INPUT);			/* SCK  -> Input */
	GPIO_setupPinDirection(SPI_PORT, SPI_SS, PIN_INPUT);			/* SS   -> Input */
	GPIO_setupPinDirection(SPI_PORT, SPI_MISO, PIN_OUTPUT);			/* MISO -> Output */



	/*	Set Data order MSB or LSB first*/
	SPCR = (SPCR & 0xDF) | ((Config_Ptr->SPI_DataOrder)<<DORD);

	/*	Set Clock Polarity */
	SPCR = (SPCR & 0xF7) | ((Config_Ptr->SPI_ClockPolarity)<<CPOL);

	/*	Set Clock Phase */
	SPCR = (SPCR & 0xFB) | ((Config_Ptr->SPI_ClockPhase)<<CPHA);

	/*	Set Clock Rate */
	SPCR = (SPCR & 0xFC) | ((Config_Ptr->SPI_Clock)<<SPR0);

	/*	Set Double Speed */
	SPSR = (SPSR & 0xFE) | ((Config_Ptr->SPI_DoubleSpeed)<<SPI2X);
}

uint8 SPI_sendReceiveByte(uint8 data)
{
	SPDR = data;
	while (BIT_IS_CLEAR(SPSR,SPIF));
	return SPDR;
}
