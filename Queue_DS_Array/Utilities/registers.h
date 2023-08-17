/*
 * registers.h
 *
 * Created: 11/22/2022 2:44:20 PM
 *  Author: Mahmoud
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "std_types.h"

/************************************************************************/
/* DIO Registers                                                        */
/************************************************************************/

/**PORTA Registers**/
#define PORTA		*((volatile uint8_t*)0x3B)
#define DDRA		*((volatile uint8_t*)0x3A)
#define PINA		*((volatile uint8_t*)0x39)

/**PORTB Registers**/
#define PORTB		*((volatile uint8_t*)0x38)
#define DDRB		*((volatile uint8_t*)0x37)
#define PINB		*((volatile uint8_t*)0x36)

/**PORTC Registers**/
#define PORTC		*((volatile uint8_t*)0x35)
#define DDRC		*((volatile uint8_t*)0x34)
#define PINC		*((volatile uint8_t*)0x33)

/**PORTD Registers**/
#define PORTD		*((volatile uint8_t*)0x32)
#define DDRD		*((volatile uint8_t*)0x31)
#define PIND		*((volatile uint8_t*)0x30)


/************************************************************************/
/* Timer Registers                                                      */
/************************************************************************/

/**Timer0 Registers**/
#define TCCR0		*((volatile uint8_t*)0x53)
#define TCNT0		*((volatile uint8_t*)0x52)
#define OCR0		*((volatile uint8_t*)0x5C)
#define TIMSK		*((volatile uint8_t*)0x59)

#define GICR		*((volatile uint8_t*)0x5B)
#define GIFR		*((volatile uint8_t*)0x5A)
#define TIFR		*((volatile uint8_t*)0x58)

/**States Register**/
#define SREG		*((volatile uint8_t*)0x5F)

/************************************************************************/
/* External Interrupts Registers                                        */
/************************************************************************/
#define MCUCR		*((volatile uint8_t*)0x55)
#define MCUCSR		*((volatile uint8_t*)0x54)
//#define GICR		*((volatile uint8_t*)0x5B)
//#define GIFR		*((volatile uint8_t*)0x5A)

/************************************************************************/
/* ADC Registers				                                        */
/************************************************************************/
#define SFIOR		*((volatile uint8_t*)0x50)
#define ADMUX		*((volatile uint8_t*)0x27)
#define ADCSRA		*((volatile uint8_t*)0x26)
#define ADCH		*((volatile uint8_t*)0x25)
#define ADCL		*((volatile uint8_t*)0x24)

/************************************************************************/
/* SPI Registers                                                        */
/************************************************************************/
#define	SPDR		*((volatile uint8_t*)0x2F)
#define	SPSR		*((volatile uint8_t*)0x2E)
#define	SPCR		*((volatile uint8_t*)0x2D)

#endif /* REGISTERS_H_ */