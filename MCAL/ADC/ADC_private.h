/*
 * ADC_prv.h
 *
 *  Created on: Aug 13, 2023
 *      Author: Dell
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

/* Define for ADC Registers */
#define ADC_ADMUX_REG          *((volatile u8 *)0x27)
#define ADC_ADCSRA_REG         *((volatile u8 *)0x26)
#define ADC_ADCH_REG           *((volatile u8 *)0x25)
#define ADC_ADCL_REG           *((volatile u8 *)0x24)

#define ADC_ADC_REG            *((volatile u16 *)0x24)

#define ADC_SFIOR_REG          *((volatile u8 *)0x50)

#define ADC_ADEN_BIT    7 // ADC enable
#define ADC_ADIE_BIT    3 // enable adc interrupt
#define ADC_ADSC_BIT    6 // start conversion bit
#define ADC_ADIF_BIT    4

#define ADC_ADATE_BIT	5
// to select Voltage Ref
#define ADC_REFS1_BIT 7
#define ADC_REFS0_BIT 6

// ADCSRA bits: to select prescaler

#define ADC_ADPS0 0
#define ADC_ADPS1 1
#define ADC_ADPS2 2


// to select adjust
#define ADC_ADLAR_BIT  5
#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
