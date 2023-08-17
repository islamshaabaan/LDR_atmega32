#include <util/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MACROS.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "KPAD_interface.h"
#include "KPAD_config.h"
#include "KPAD_private.h"


void KPAD_voidInit      (void)
{
    /* Set Rows To Input*/
    DIO_voidSetupPinDirection (KPAD_PORT , KPAD_R0 , DIO_INPUT);
    DIO_voidSetupPinDirection (KPAD_PORT , KPAD_R1 , DIO_INPUT);
    DIO_voidSetupPinDirection (KPAD_PORT , KPAD_R2 , DIO_INPUT);
    DIO_voidSetupPinDirection (KPAD_PORT , KPAD_R3 , DIO_INPUT);
    /* Set Rows as PULL UP*/
    DIO_voidSetPinValue (KPAD_PORT , KPAD_R0 , DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT , KPAD_R1 , DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT , KPAD_R2 , DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT , KPAD_R3 , DIO_HIGH);

    /*Set Cols to OUTPUT*/
    DIO_voidSetupPinDirection (KPAD_PORT , KPAD_C0 , DIO_OUTPUT);
    DIO_voidSetupPinDirection (KPAD_PORT , KPAD_C1 , DIO_OUTPUT);
    DIO_voidSetupPinDirection (KPAD_PORT , KPAD_C2 , DIO_OUTPUT);
    DIO_voidSetupPinDirection (KPAD_PORT , KPAD_C3 , DIO_OUTPUT);
//
    DIO_voidSetPinValue (KPAD_PORT , KPAD_C0 , DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT , KPAD_C1 , DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT , KPAD_C2 , DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT , KPAD_C3 , DIO_HIGH);
}

u8 KPAD_u8GetPressed    (void)
{
    u8 Local_u8RetrunedValue = 255 ;
    u8 Local_u8GetPressed   ;
    u8 Local_u8Col            ;
    u8 Local_u8Row          ;

    for(Local_u8Col = 0 + KPAD_COL_INIT ; Local_u8Col < KPAD_COL_END + 1 ; Local_u8Col++ )
    {
        DIO_voidSetPinValue(KPAD_PORT , Local_u8Col , DIO_LOW);
        for(Local_u8Row = 0 + KPAD_ROW_INIT ; Local_u8Row < KPAD_ROW_END + 1 ; Local_u8Row++)
        {

           Local_u8GetPressed = DIO_u8GetPinValue(KPAD_PORT , Local_u8Row);
           if(Local_u8GetPressed == 0)
           {
            /*  Debouncing */
            _delay_ms(50);
            Local_u8GetPressed = DIO_u8GetPinValue(KPAD_PORT , Local_u8Row);
            if(Local_u8GetPressed == 0)
            {
                Local_u8RetrunedValue = KPAD_Au8Values[Local_u8Row - KPAD_ROW_INIT][Local_u8Col - KPAD_COL_INIT];
            }
            while(Local_u8GetPressed ==0 )
            {
                Local_u8GetPressed = DIO_u8GetPinValue(KPAD_PORT , Local_u8Row);

            }

           }

        }

        DIO_voidSetPinValue(KPAD_PORT , Local_u8Col , DIO_HIGH);
    }


    return Local_u8RetrunedValue ;
}
