/*
 * TIMERS_private.h
 *
 *  Created on: Aug 15, 2023
 *      Author: one
 */

#ifndef MCAL_TIMERS_TIMERS_PRIVATE_H_
#define MCAL_TIMERS_TIMERS_PRIVATE_H_

/*Timer 0*/
#define TCCR0_REG 	*((volatile u8 *)0x53)
#define TCNT0_REG 	*((volatile u8 *)0x52)
#define OCR0_REG 	*((volatile u8 *)0x5C)
#define TIFR0_REG 	*((volatile u8 *)0x58)


/*Timer 1*/
#define TCCR1A_REG 	*((volatile u8 *)0x4F)
#define TCCR1B_REG 	*((volatile u8 *)0x4E)
#define TCNT1_REG 	*((volatile u16 *)0x4C)
#define OCR1A_REG 	*((volatile u16 *)0x4A)
#define OCR1B_REG	*((volatile u16 *)0x48)
#define ICR1_REG	*((volatile u16 *)0x46)




#define TIMSK_REG 	*((volatile u8 *)0x59)
//TCNT0
#define FOC0_BIT 7
#define WGM01_BIT 3
#define WGM00_BIT 6
//TIMSK
#define TOIE0_BIT 0
#define OCIE0_BIT 1
//TIFR
#define TOV0_BIT 0
#define OCF0_BIT 1

#endif /* MCAL_TIMERS_TIMERS_PRIVATE_H_ */
