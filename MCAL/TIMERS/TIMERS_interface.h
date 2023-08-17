/*
 * TIMERS_interface.h
 *
 *  Created on: Aug 15, 2023
 *      Author: one
 */

#ifndef MCAL_TIMERS_TIMERS_INTERFACE_H_
#define MCAL_TIMERS_TIMERS_INTERFACE_H_

/*
 * OVF mode
 * Prescaler 8
 * Tick time = 1 / 8 MHz = 1 micro sec
 * Time OF = 1 micro sec * 256 = 256 micro sec
 * desired time = 1 sec
 *
 *
 * */

typedef enum{
	Normal_mode,
	PWM_phase_corr,
	Compare_mode,
	Fast_PWM
}TIM0_mode_t;

typedef enum{
	Disconnected_OC0, Toggle_OC0,
	Clear_OC0, Set_OC0
}TIM0_OC0_NonPWM_t;

typedef enum{
	NoCLK_SRC,
	T0_FCPU,
	T0_FCPU_8,
	T0_FCPU_64,
	T0_FCPU_256,
	T0_FCPU_1024,
	EXTERNAL_FALLING,
	EXTERNAL_RISING
}TIM0_CLKSelect_t;
typedef enum{
	Polling, Interrupt
}TIM0_Technique;
typedef struct{
	TIM0_mode_t 		Mode;
	TIM0_OC0_NonPWM_t 	OC0_Option;
	TIM0_CLKSelect_t 	ClockSelect;
	TIM0_Technique 		Technique;
	u8					PreloadValue;
	u8					CompareValue;



}TIM0_Conf_t;
typedef struct{
	TIM0_mode_t 		Mode;
	TIM0_OC0_NonPWM_t 	OC0_Option;
	TIM0_CLKSelect_t 	ClockSelect;
	TIM0_Technique 		Technique;
	u8					PreloadValue;
	u8					CompareValue;



}TIM1_Conf_t;

void TIMERS_voidTIM0Init(TIM0_Conf_t *);
void TIMERS_voidTIM0Start(TIM0_Conf_t * );
void TIMERS_voidTIM0Disable();
void TIMERS_voidTIM0SetCallBackFunction(void (*ptrToFun) (void));

void TIMERS_voidTIM1Init();
void TIMERS_voidSetCompareMatchValueT1A(u16 Copy_u16CompareMatchValue);
void TIMERS_voidSetICRValueT1(u16 Copy_u16ICRValue);


#endif /* MCAL_TIMERS_TIMERS_INTERFACE_H_ */
