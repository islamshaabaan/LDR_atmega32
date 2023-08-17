/*
 * ADC_Int.h
 *
 *  Created on: Aug 13, 2023
 *      Author: Dell
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

typedef enum{
	AREF, AVCC, INTERNAL=3
}ADC_RefSelect_t;

typedef enum{
	FCPU_2 = 1 , FCPU_4, FCPU_8,
	FCPU_16 ,    FCPU_32, FCPU_64,
	FCPU_128
}ADC_Prescaler_t;

typedef enum{
	ADC0 , ADC1, ADC2, ADC3,
	ADC4,  ADC5 ,ADC6, ADC7
}ADC_Channel_t;
typedef enum{
	LEFT_ADJUST,RIGHT_ADJUST
}ADC_ADJ_Option_t;

typedef struct{

	ADC_RefSelect_t   Vref;
	ADC_Prescaler_t   Prescaler;
	ADC_ADJ_Option_t	Adjust_Option;
}ADC_Conf_t;
void ADC_voidInit(ADC_Conf_t*);
u16 ADC_u16ReadChannelPolling(ADC_Channel_t channel_num);
void ADC_voidReadChannelInterrupt(ADC_Channel_t channel_num);

void ADC_voidSetCallBackFunction(void (*ptrToFun) (void));

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
