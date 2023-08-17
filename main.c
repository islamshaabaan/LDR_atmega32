/*
 * Main.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Islam Shaaban
 */

#include <util/delay.h>

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MACROS.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "HAL/LED/LED_interface.h"
#include "HAL/SSD/SSD_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "HAL/KPAD/KPAD_interface.h"
#include "HAL/DC_MOTOR/DCMOTOR_interface.h"
#include "HAL/STEPPER_MOTOR/STEPPER_interface.h"

#define LDR_Test		0
#define LM35D_Test		1

#define F_CPU		8000000UL
#define DEFAULT_PW 1234
u8 WakePerson[]= {
		0x0E,
		0x0A,
		0x0E,
		0x04,
		0x1F,
		0x15,
		0x0E,
		0x11
};
u8 SleepPerson[]= {
		0x00,
		0x00,
		0x0B,
		0x1F,
		0x0B,
		0x00,
		0x00,
		0x00
};

int main(void){

	DIO_voidSetupPinDirection(DIO_PORTA, DIO_PIN0, DIO_INPUT);

	CLCD_voidInit();
	CLCD_voidStoreExtraChar(0,WakePerson);
	CLCD_voidStoreExtraChar(1,SleepPerson);
	KPAD_voidInit();
	ADC_Conf_t ADC= {
			.Vref=AVCC,
			.Prescaler=FCPU_128,
			.Adjust_Option = RIGHT_ADJUST
	};
	ADC_voidInit(&ADC);

	u32 Local_u8Password = 0;
	u8 Logged=0;


	CLCD_voidSetPosition(1,1);
	CLCD_voidSendString((u8 *)"Welcome to Sys");
	_delay_ms(1000);
	CLCD_voidCLearDisplay();
	CLCD_voidSendString((u8 *)" Enter your PW");
	_delay_ms(1000);
	CLCD_voidCLearDisplay();
	CLCD_voidSendString((u8 *)" Then Press ON");
	_delay_ms(1000);
	CLCD_voidCLearDisplay();
	CLCD_voidSendString((u8 *)" Password: ");
	u8 Local_u8Pressed = 0xff;




	u16 Local_DigitalValue;
	u16 Local_Analog;
	u16 Local_u16OldValue = 0;

	while(1){
		//while still not logged, try to get the password
		while(Logged== 0){
			Local_u8Pressed = KPAD_u8GetPressed();
			CLCD_voidSetPosition(2,2);

			while(Local_u8Pressed != 'C' && Local_u8Pressed != 0xff){
				CLCD_voidSendData('*');
				Local_u8Password = (Local_u8Password * 10) + (Local_u8Pressed - 48);
				Local_u8Pressed = KPAD_u8GetPressed();
				// while the button is not pressed,
				// wait until get the pressed button.
				while(Local_u8Pressed == 0xff){
					Local_u8Pressed = KPAD_u8GetPressed();
				}
			}
			if(Local_u8Pressed=='C'){
				if(Local_u8Password == DEFAULT_PW)
				{
					Local_u8Password=0; // Reset PW
					CLCD_voidCLearDisplay();
					Logged =1;
				}
				else{
					// if PW is wrong.
					Local_u8Password=0; // Reset PW
					CLCD_voidCLearDisplay();
					CLCD_voidSendString((u8 *)" Wronge PW");
					_delay_ms(2000);
					CLCD_voidCLearDisplay();
					CLCD_voidSendString((u8 *)" Password: ");
				}
			}
		}

		Local_DigitalValue = ADC_u16ReadChannelPolling(ADC0);
		_delay_ms(10);
		Local_Analog = ((u32)Local_DigitalValue * 5000 ) / 1024 ;
		CLCD_voidCLearDisplay();

		if(Local_Analog < 3000){
			CLCD_voidSetPosition(1,1);
			CLCD_voidSendString((u8 *)"Light");
			_delay_ms(200);
			Local_u16OldValue = Local_Analog;
			CLCD_voidCLearDisplay();
			CLCD_voidSetPosition(1,1);
			CLCD_voidSendString((u8 *)"Good Morning..");
			for(int i=1; i<6; i++){
				CLCD_voidSetPosition(2,i);
				CLCD_voidSendData(0);
			}
			_delay_ms(200);
		}
		else{
			CLCD_voidSetPosition(1,1);
			CLCD_voidSendString((u8 *)"Dark");
			_delay_ms(200);
			CLCD_voidCLearDisplay();
			Local_u16OldValue = Local_Analog;
			CLCD_voidSetPosition(1,5);
			CLCD_voidSendString((u8 *)"Good Night..");
			for(int i=1; i<6; i++){

				CLCD_voidSetPosition(2,i);
				CLCD_voidSendData(1);
			}
			_delay_ms(200);
		}

		//CLCD_voidCLearDisplay();



	}


	return 1;
}
