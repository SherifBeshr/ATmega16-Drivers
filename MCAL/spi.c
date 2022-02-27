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

/*
 * Description :
 * Initialize the SPI device as Master.
 */
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

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
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

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
	/* Initiate the communication and send data by SPI */
	SPDR = data;
	/* Wait until SPI interrupt flag SPIF = 1 (data has been sent/received correctly) */
	while (BIT_IS_CLEAR(SPSR,SPIF));
	/*
	 * Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	 * and then accessing SPDR like the below line.
	 */
	return SPDR;
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str)
{
	uint8 i = 0;
	uint8 received_data = 0;
	while (str[i] != '\0')
	{
		/*
		 * received_data contains the received data from the other device.
		 * It is a dummy data variable as we just need to send the string to other device.
		 */
		received_data = SPI_sendReceiveByte(str[i]);
		++i;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str)
{
	uint8 i = 0;

	/* Receive the first byte */
	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	/* Receive the whole string until the '#' */
	while(str[i] != '#')
	{
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}

