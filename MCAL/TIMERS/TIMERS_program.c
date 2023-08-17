/*
 * TIMERS_program.c
 *
 *  Created on: Aug 15, 2023
 *      Author: Islam Shaaban
 */


#include "../../LIB/BIT_MACROS.h"
#include "../../LIB/STD_TYPES.h"

#include "TIMERS_private.h"
#include "TIMERS_config.h"
#include "TIMERS_interface.h"

#include <avr/interrupt.h>

void TIMERS_voidTIM0Init(TIM0_Conf_t * PtrToConfigStruct){
	if(PtrToConfigStruct->Mode == Normal_mode || PtrToConfigStruct->Mode == Compare_mode){
		SET_BIT(TCCR0_REG,FOC0_BIT);
	}
	else{
		CLR_BIT(TCCR0_REG,FOC0_BIT);
	}
	// Configure the mode
	switch(PtrToConfigStruct->Mode){
	case Normal_mode:
		//OVF MODE
		CLR_BIT(TCCR0_REG,WGM00_BIT);
		CLR_BIT(TCCR0_REG,WGM01_BIT);
		break;
	case Compare_mode:
		//CTC MODE
		CLR_BIT(TCCR0_REG,WGM00_BIT);
		SET_BIT(TCCR0_REG,WGM01_BIT);
		break;
	case PWM_phase_corr:
		SET_BIT(TCCR0_REG , WGM00_BIT);
		CLR_BIT(TCCR0_REG , WGM01_BIT);
		break;
	case Fast_PWM:
		SET_BIT(TCCR0_REG , WGM00_BIT);
		SET_BIT(TCCR0_REG , WGM01_BIT);
		break;
	default:
		break;

	}

	TCCR0_REG &= 0xcf;
	TCCR0_REG |= ((PtrToConfigStruct->OC0_Option) <<4);
	//CLEAR LS 3 BITS BITS
	TCCR0_REG &= 0xF8;
	//Configure THE REQUIRED Clock select
	TCCR0_REG |= ((PtrToConfigStruct->ClockSelect) &0x07);

	//Configure the technique
	switch(PtrToConfigStruct->Technique){
	case Polling:
		break;
	case Interrupt:
		switch(PtrToConfigStruct->Mode){
		case Normal_mode:
			//Enable OFlow PIE
			SET_BIT(TIMSK_REG,TOIE0_BIT);
			break;
		case Compare_mode:
			//Enable CTC PIE
			SET_BIT(TIMSK_REG,OCIE0_BIT);
			break;
		default:
			break;
		}
		break;
		default:
			break;
	}

	TCNT0_REG = 0;

}
void TIMERS_voidTIM0Start(TIM0_Conf_t * PtrToConfigStruct){
	switch(PtrToConfigStruct->Mode){
	case Normal_mode:
		TCNT0_REG = PtrToConfigStruct->PreloadValue;
		// Configure the flag
		switch(PtrToConfigStruct->Technique){
		case Polling:
			//WAITing until timer finish counting
			while(GET_BIT(TIFR0_REG,TOV0_BIT)==0);
			// set it to clear the flag
			SET_BIT(TIFR0_REG,TOV0_BIT);
			break;
		case Interrupt:
			break;
		default:
			break;

		}
		break;
		case Compare_mode:
			TCNT0_REG = PtrToConfigStruct->PreloadValue;
			OCR0_REG =PtrToConfigStruct->CompareValue;
			switch(PtrToConfigStruct->Technique){
			case Polling:
				//WAITing until timer finish counting
				while(GET_BIT(TIFR0_REG,OCF0_BIT) == 0);
				SET_BIT(TIFR0_REG,OCF0_BIT);
				break;
			case Interrupt:
				break;
			default:
				break;
			}
			break;
			default:
				break;

	}
}
void TIMERS_voidTIM0Disable(){
	//clear all 5reg
	TCCR0_REG =0;
	TCNT0_REG=0;
	TIMSK_REG&= 0xFC;
}
void TIMERS_voidTIM1Init(){

	// Fast PWM
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);

	//Non Inverted Mode
	SET_BIT(TCCR1A,7);
	CLR_BIT(TCCR1A,6);

	// SET ICR1 (TOP)
	TIMERS_voidSetICRValueT1(20000);

	//Prescaler /8
	CLR_BIT(TCCR1B_REG,0);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,2);

}

void TIMERS_voidSetCompareMatchValueT1A(u16 Copy_u16CompareMatchValue){
	/* for setting Duty Cycle */
	OCR1A_REG = Copy_u16CompareMatchValue;
}

void TIMERS_voidSetICRValueT1(u16 Copy_u16ICRValue){
	ICR1_REG = Copy_u16ICRValue;
}




static void (*Global_PtrToFun)(void) = NULL;
//REGISTERING FUNCTION
void TIMERS_voidTIM0SetCallBackFunction(void (*ptrToFun) (void)){
	Global_PtrToFun = ptrToFun;
}

ISR(TIMER0_OVF_vect){
	if(Global_PtrToFun!= NULL){
		(*Global_PtrToFun)();
	}

	//	(*Global_PtrToFun)();

}

ISR(TIMER0_COMP_vect){
	if(Global_PtrToFun!= NULL){
		Global_PtrToFun();
	}

}
