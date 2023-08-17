/*
 * SSD_program.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Islam Shaaban
 */


#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MACROS.h"

#include "..\..\MCAL\DIO\DIO_interface.h"

#include "SSD_interface.h"



void SSD_voidInit(SSD_t * SSDPtr){

	DIO_voidSetPortDirection(SSDPtr->Port, DIO_OUTPUT);
	switch (SSDPtr->CommonState ){

	case SSD_COMMON_CATHODE:
		DIO_voidSetPortValue(SSDPtr -> Port, 0xff);
		break;
	case SSD_COMMON_ANODE:
		DIO_voidSetPortValue(SSDPtr -> Port, 0x00);
		break;
	}

}

void SSD_voidEnable(SSD_t * SSDPtr, u8 Copy_u8Number){
	switch(SSDPtr -> CommonState){
	case SSD_COMMON_CATHODE:
		DIO_voidSetPortValue(SSDPtr->Port, array[Copy_u8Number]);
		break;
	case SSD_COMMON_ANODE:
		DIO_voidSetPortValue(SSDPtr->Port, ~array[Copy_u8Number]);
		break;
	}

}



void SSD_voidDisable(SSD_t * SSDPtr){

	switch (SSDPtr->CommonState ){

	case SSD_COMMON_CATHODE:
		DIO_voidSetPortValue(SSDPtr -> Port, 0xff);
		break;
	case SSD_COMMON_ANODE:
		DIO_voidSetPortValue(SSDPtr -> Port, 0x00);
		break;
	}
}
