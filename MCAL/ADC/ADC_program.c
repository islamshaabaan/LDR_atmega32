/*
 * ADC_Prog.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Dell
 */


#include <avr/interrupt.h>
#include "../../LIB/BIT_MACROS.h"
#include "../../LIB/STD_TYPES.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"

void ADC_voidInit(ADC_Conf_t * ADC_ptr)
{
	//CLEAR REFS1 AND REFS0 BITS
	ADC_ADMUX_REG &= 0x3f;
	//INSERT THE REQUIRED VOLTAGE REFERENCE
	ADC_ADMUX_REG |= (ADC_ptr->Vref << 6);

	//CLEAR LEAST SIG 3 BITS
	ADC_ADCSRA_REG &= 0xf8;
	//INSERT THE REQUIRED PRESCALER
	ADC_ADCSRA_REG |= ADC_ptr->Prescaler;

	//ENABLING ADC
	SET_BIT(ADC_ADCSRA_REG, ADC_ADEN_BIT);

	//CONFIGURE ADJUSTMENT
	switch(ADC_ptr->Adjust_Option)
	{
	case LEFT_ADJUST:
		SET_BIT(ADC_ADMUX_REG,ADC_ADLAR_BIT);
		break;
	case RIGHT_ADJUST:
		CLR_BIT(ADC_ADMUX_REG,ADC_ADLAR_BIT);
		break;
	}
#if ADC_MECHANISM == ADC_POLLING
	//DISABLE INTERRUPT OF ADC
	CLR_BIT(ADC_ADCSRA_REG,ADC_ADIE_BIT);
#elif ADC_MECHANISM == ADC_INTERRUPT
	SET_BIT(ADC_ADCSRA_REG,ADC_ADIE_BIT);
#endif
}

void ADC_Init1(){
	ADC_ADMUX_REG = 0b01000000;
	ADC_ADCSRA_REG = 0b10010111;
}
u16 ADC_ReadChannel1(){
	u16 res;
	SET_BIT(ADC_ADCSRA_REG,6);
	while(GET_BIT(ADC_ADCSRA_REG,4)==0);

	SET_BIT(ADC_ADCSRA_REG,4);

	res= (ADC_ADCL_REG)|(ADC_ADCH_REG << 8);
	return res;

}

u16 ADC_u16ReadChannelPolling(ADC_Channel_t channel_num)
{
	u16 res;

	//CLEARING LEAST SIG 5 BITS
	ADC_ADMUX_REG &= 0xE0;
	//INSERT THE REQUIRED CHANNEL
	ADC_ADMUX_REG |= (channel_num & 0x07);
	//START CONVERSION
	SET_BIT(ADC_ADCSRA_REG , ADC_ADSC_BIT);
	//WAIT UNTIL FLAG IS HIGH = CONVERSION IS DONE
	while(GET_BIT(ADC_ADCSRA_REG, ADC_ADIF_BIT) == 0);

	//SET THE FLAG TO CLEAR IT TO ZERO
	SET_BIT(ADC_ADCSRA_REG, ADC_ADIF_BIT);

	if(GET_BIT(ADC_ADMUX_REG,5)==1) // LEFT ADJ
	{
		res =( ADC_ADCL_REG >> 6);
		res |= (( (u16)ADC_ADCH_REG) << (2) );
		return res;
	}
	else{ //RIGHT_ADJUST:
		//GET THE DIGITAL READING , MERGING THE TWO REG(ADCL,ADCH) TO U16 REG.
		return (ADC_ADC_REG);
	}

}
u16 ADC_u16ReadCh(void){
	u16 res;
	if(GET_BIT(ADC_ADMUX_REG,5)==1) // LEFT ADJ
		{
			res =( ADC_ADCL_REG >> 6);
			res |= (( (u16)ADC_ADCH_REG) << (2) );
			return res;
		}
		else{ //RIGHT_ADJUST:
			//GET THE DIGITAL READING , MERGING THE TWO REG(ADCL,ADCH) TO U16 REG.
			return (ADC_ADC_REG);
		}

}
void ADC_voidReadChannelInterrupt(ADC_Channel_t channel_num){

	// set the wanted channel based on input without losing the origin value
	ADC_ADMUX_REG &= 0b11100000;
	ADC_ADMUX_REG |=channel_num;

	// ADC Interrupt Enable
	SET_BIT(ADC_ADCSRA_REG,ADC_ADIE_BIT);


	// start  conversion
	SET_BIT(ADC_ADCSRA_REG,ADC_ADSC_BIT);

	//ADC Auto Trigger Enable
	SET_BIT(ADC_ADCSRA_REG,ADC_ADATE_BIT);
}


static void (*Global_PtrToFun)(void) = NULL;
//REGISTERING FUNCTION
void ADC_voidSetCallBackFunction(void (*ptrToFun) (void)){
	Global_PtrToFun = ptrToFun;
}

ISR(ADC_vect){
	if(Global_PtrToFun!= NULL){
		(*Global_PtrToFun)();
	}

	//	(*Global_PtrToFun)();

}

