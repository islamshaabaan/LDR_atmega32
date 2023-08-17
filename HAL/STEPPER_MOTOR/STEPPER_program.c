/*
 * STEPPER_program.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Islam Shaaban
 */


#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MACROS.h"
#include"../../MCAL/DIO/DIO_interface.h"
#include"../../MCAL/DIO/DIO_private.h"
#include"STEPPER_interface.h"
#include"STEPPER_config.h"
#include"STEPPER_private.h"
#include<util/delay.h>


void STEPPER_voidInit( void )
{
	//MAKING ALL PINS OUTPUT
	DIO_voidSetupPinDirection(STEPPER_PORT, STEPPER_BLUE_PIN  , DIO_OUTPUT);
	DIO_voidSetupPinDirection(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_OUTPUT);
	DIO_voidSetupPinDirection(STEPPER_PORT, STEPPER_PINK_PIN  , DIO_OUTPUT);
	DIO_voidSetupPinDirection(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_OUTPUT);

	//DISABLE ALL PINS
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN, DIO_HIGH);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN, DIO_HIGH);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
}

void STEPPER_voidOn ( u8 Copy_u8StepType , u8 Copy_u8Direction , u16 Copy_u16Degree)
{
	/* Explanation:
	 * from data sheet of 28byj48 stepper
	 * freq = 100Hz
	 *	stride angle = smallest angle per half step.
	 * 				= 5.625 / 64 = 0.08789 degree.
	 * resolution = degree per step = stride * 2 = 0.17578 degree.
	 * 1 step  ------> 0.17578 degree.
	 * X steps ------> 360 	   degree.
	 * X = 2048 steps: for make 360 degrees
	 * now, we need make the angle is an input.
	 * so: the X steps = ( ( (angle * 2048) / 360 ) / 4 )
	 * this 4 is because the full step is consists from 4 steps.
	 *
	 *
	 * NOTE: in our Kit the unipolar stepper with 2 coils are
	 * 		  common top connected to Vcc so the activated state = LOW
	 * */

	u16 Local_u16Counter=0;
	u32 Local_u16FullSteps = ( ( 2048*Copy_u16Degree ) / 360 );
	if(Copy_u8StepType == STEPPER_FULL_STEP)
	{
		if (Copy_u8Direction == STEPPER_CLOCK_WISE)
		{
			for (Local_u16Counter=0 ; Local_u16Counter < ( Local_u16FullSteps / 4 )  ; Local_u16Counter++)
			{
				//STEP1
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP2
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP3
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP4
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_LOW);
				_delay_ms(20);
			}
		}
		else if(Copy_u8Direction == STEPPER_COUNTER_CLOCK_WISE)
		{
			for (Local_u16Counter=0 ; Local_u16Counter< ((64*Copy_u16Degree)/45) ; Local_u16Counter++)
			{
				//STEP1
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_LOW);
				_delay_ms(20);

				//STEP2
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP3
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP4
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);
			}
		}
	}

	else if(Copy_u8StepType == STEPPER_HALF_STEP)
	{
		u16 Local_u16Counter=0;
		if (Copy_u8Direction == STEPPER_CLOCK_WISE)
		{
			for (Local_u16Counter =0; Local_u16Counter< ((32*Copy_u16Degree)/45) ; Local_u16Counter++)
			{
				//STEP1 : ACTIVATE COIL1 ONLY
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP2 ACTIVATE COIL 1 AND COIL2
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP3 ACTIVATE COIL2 ONLY
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP4 : ACTIVATE COIL2 AND COIL3
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP5 : ACTIVATE COIL3 ONLY:
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP6 :ACTIVATE COIL3 AND COIL4:
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_LOW);
				_delay_ms(20);

				//STEP7: ACTIVATE COIL4 ONLY:
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_LOW);
				_delay_ms(20);

				//STEP8: ACTIVATE COIL4 AND COIL1:
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_LOW);
				_delay_ms(20);
			}

		}
		else if(Copy_u8Direction == STEPPER_COUNTER_CLOCK_WISE)
		{
			for (Local_u16Counter =0; Local_u16Counter< ((32*Copy_u16Degree)/45) ; Local_u16Counter++)
			{
				//STEP1: ACTIVATE COIL4 AND COIL1:
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_LOW);
				_delay_ms(20);

				//STEP2: ACTIVATE COIL4 ONLY:
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_LOW);
				_delay_ms(20);

				//STEP3 :ACTIVATE COIL3 AND COIL4:
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_LOW);
				_delay_ms(20);

				//STEP4 : ACTIVATE COIL3 ONLY:
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP5 : ACTIVATE COIL2 AND COIL3
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP6 ACTIVATE COIL2 ONLY
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP7 ACTIVATE COIL 1 AND COIL2
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);

				//STEP1 : ACTIVATE COIL1 ONLY
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_LOW);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
				DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
				_delay_ms(20);
			}
		}
	}
}

void STEPPER_voidOff( void )
{
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_BLUE_PIN,   DIO_HIGH);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_PINK_PIN,   DIO_HIGH);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_YELLOW_PIN, DIO_HIGH);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_ORANGE_PIN, DIO_HIGH);
}

void STEPPER_voidRotate ( u8 Copy_u8Direction ){
	if (Copy_u8Direction == STEPPER_COUNTER_CLOCK_WISE)
	{


		//STEP2
		ASSIGN_REG(PORTC_REG, 0x03);
		_delay_ms(2000);

		//STEP3
		ASSIGN_REG(PORTC_REG, 0x06);
		_delay_ms(2000);

		//STEP4
		ASSIGN_REG(PORTC_REG, 0x0c);
		_delay_ms(2000);

		//STEP1
		ASSIGN_REG(PORTC_REG,0x09);
		_delay_ms(2000);

	}
	else if(Copy_u8Direction == STEPPER_CLOCK_WISE)
	{

		//STEP4
		ASSIGN_REG(PORTC_REG, 0x09);
		_delay_ms(2000);

		//STEP3
		ASSIGN_REG(PORTC_REG, 0x0c);
		_delay_ms(2000);

		//STEP2
		ASSIGN_REG(PORTC_REG, 0x06);
		_delay_ms(2000);

		//STEP1
		ASSIGN_REG(PORTC_REG, 0x03);
		_delay_ms(2000);

		ASSIGN_REG(PORTC_REG, 0x09);
		_delay_ms(2000);


	}


}
