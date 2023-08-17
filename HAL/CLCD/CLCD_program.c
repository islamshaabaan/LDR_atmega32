/*******************************************************/
/****   Author : Islam Shaaban      ******************/
/****   SWC:          CLCD             ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/

/*	Includes */
	/*Libraries*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MACROS.h"
#define F_CPU 8000000UL
#include <util/delay.h>
/*MCAL*/
#include "../../MCAL/DIO/DIO_interface.h"

/*CLCD*/
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

void CLCD_voidInit		(	void	)
{
	// Data Port --> OUTPUT
	DIO_voidSetPortDirection(CLCD_DATA_PORT , DIO_OUTPUT);
	// RS , RW , EN --> OUTPUT
	DIO_voidSetupPinDirection(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_OUTPUT);
	DIO_voidSetupPinDirection(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_OUTPUT);
	DIO_voidSetupPinDirection(CLCD_CTRL_PORT , CLCD_EN_PIN , DIO_OUTPUT);

	/* Initialization Sequence */
	_delay_ms(50);
	/*Function Set */
	CLCD_voidSendCommand(CLCD_FUNCTIONSET8bit);
	_delay_us(50);
	/*Display ON/OFF*/
	CLCD_voidSendCommand(CLCD_DISPLAYON_OFF);
	_delay_us(50);
	/*Display Clear */
	CLCD_voidSendCommand(CLCD_CLR_DISPLAY);
	_delay_ms(2);
	/*Entry Mode Set */
	CLCD_voidSendCommand(CLCD_ENTRYMODE);

}

void CLCD_voidSendCommand	(u8 Copy_u8Command	)
{
	/*RS -> Low (To Send Command )*/
	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_LOW);
	/*RW -> Low	(To Write)*/
	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_LOW);
	/*	Send Command */
	DIO_voidSetPortValue(CLCD_DATA_PORT , Copy_u8Command);
	/*Enable Sequence */
	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_EN_PIN , DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_EN_PIN , DIO_LOW);
	_delay_us(50);

}
void CLCD_voidSendData		(u8 Copy_u8Data		)
{
	/*RS -> High (To Send Data )*/
		DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_HIGH);
		/*RW -> Low	(To Write)*/
		DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_LOW);
		/*	Send Command */
		DIO_voidSetPortValue(CLCD_DATA_PORT , Copy_u8Data);
		/*Enable Sequence */
		DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_EN_PIN , DIO_HIGH);
		_delay_us(1);
		DIO_voidSetPinValue(CLCD_CTRL_PORT , CLCD_EN_PIN , DIO_LOW);
		_delay_us(50);

}

void CLCD_voidSetPosition	(u8 Copy_u8Row , u8 Copy_u8Col)
{
	switch(Copy_u8Row)
	{
	case CLCD_ROW_1:	CLCD_voidSendCommand(	FIRST_PLACE_IN_ROW1 + Copy_u8Col - 1);
		break;
	case CLCD_ROW_2 :	CLCD_voidSendCommand(	FIRST_PLACE_IN_ROW2 + Copy_u8Col - 1);
		break ;
	default :
		break;
	}
}

void CLCD_voidSendExtraChar	(u8 Copy_u8PatternLocation , u8 * Copy_pu8ExtraChar , u8 Copy_u8Row , u8 Copy_u8Col )
{
	u8 Local_u8Address_INCREMENT = 0 ;
	Local_u8Address_INCREMENT = Copy_u8PatternLocation * PATTERNS_NUM; // Loc * 8 ;
	/*Go To CGRAM*/
	CLCD_voidSendCommand( FIRST_PLACE_IN_CGRAM + Local_u8Address_INCREMENT );
	/*Generate Character  inside CGRAM*/
	for(u8 i = 0 ; i < PATTERNS_NUM ; i++)
	{
		CLCD_voidSendData(Copy_pu8ExtraChar[i]);
	}
	/*Back to DDRAM */
	CLCD_voidSetPosition(Copy_u8Row , Copy_u8Col);
	/*Draw Character on display */
	CLCD_voidSendData(Copy_u8PatternLocation);
}
void CLCD_voidStoreExtraChar(u8 Copy_u8PatternLocation , u8 * Copy_pu8ExtraChar )
{
	u8 Local_u8Address_INCREMENT = 0 ;
	Local_u8Address_INCREMENT = Copy_u8PatternLocation * PATTERNS_NUM; // Loc * 8 ;
	/*Go To CGRAM*/
	CLCD_voidSendCommand( FIRST_PLACE_IN_CGRAM + Local_u8Address_INCREMENT );
	/*Generate Character  inside CGRAM*/
	for(u8 i = 0 ; i < PATTERNS_NUM ; i++){
		CLCD_voidSendData(Copy_pu8ExtraChar[i]);
	}


}
void CLCD_voidSendString	(u8 *Copy_pu8String )
{
	u8 Local_u8Iterator = 0 ;
	while(Copy_pu8String[Local_u8Iterator] != '\0')
	{
		CLCD_voidSendData(Copy_pu8String[Local_u8Iterator]);
		Local_u8Iterator ++ ;
		/* Delay to let the LCD show the character */
		_delay_ms(2);
	}
}

void CLCD_voidSendu32Number (u32 Copy_u32Number){
	if(Copy_u32Number!=0)
	{
		u8 arr[11];
		u32 temp;
		u8 Local_u8Iterator=0,Itr1=0,Itr2=0;
		// filling array with number reversed in order
		while(Copy_u32Number!=0)
		{
			temp=Copy_u32Number%10;
			arr[Local_u8Iterator]=temp;
			Local_u8Iterator++;
			Copy_u32Number/=10;
		}
		arr[Local_u8Iterator]='x'; // null char
		Local_u8Iterator--;
		// re arrange the array
		while(Itr1<Local_u8Iterator)
		{
			// swap
			temp=arr[Itr1];
			arr[Itr1]=arr[Local_u8Iterator];
			arr[Local_u8Iterator]=temp;
			Itr1++;
			Local_u8Iterator--;
		}
		while(arr[Itr2]!='x')
		{
			CLCD_voidSendData(arr[Itr2]+'0');
			Itr2++;
		}
	}
	else{
		CLCD_voidSendData('0');
	}
}
void CLCD_voidCLearDisplay(void){
	CLCD_voidSendCommand(CLCD_CLR_DISPLAY);

}

/*
void LCD_wirte_number_float(f32 Num)
{
	if(Num!=0)
	{
		u8 arr_Dec[3];
		u8 arr_int[11];
		u32 temp,temp2,i=0,j=0,w=0;
		// storing floating numbs in arr_Dec
		temp=Num*100;
		arr_Dec[1]=temp%10;
		temp/=10;
		arr_Dec[0]=temp%10;
		temp/=10;
		arr_Dec[2]='x';
		while(temp!=0)
		{
			temp2=temp%10;
			arr_int[i]=temp2;
			i++;
			temp/=10;
		}
		arr_int[i]='x';
		i--;
		// re arrange the array
		while(j<i)
		{
			// swap
			temp2=arr_int[j];
			arr_int[j]=arr_int[i];
			arr_int[i]=temp2;
			j++;
			i--;
		}
		while(arr_int[w]!='x')
		{
			LCD_void_wirte_data(arr_int[w]+'0');

			w++;
		}
		LCD_void_wirte_data('.');

		w=0;
		while(arr_Dec[w]!='x')
		{
			LCD_void_wirte_data(arr_Dec[w]+'0');
			w++;
		}
	}else{
		LCD_void_wirte_data('0');
	}
}*/
