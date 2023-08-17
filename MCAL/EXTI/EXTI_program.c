/*
 * EXTI_program.c
 *
 *  Created on: Aug 12, 2023
 *      Author: First
 */
/*	Include LIB	*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MACROS.h"

/* EXTI includes */

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


static void (*Glo_ApfNotification [3] ) ( void ) = { NULL , NULL , NULL } ;

void EXTI0_voidInit	(	void	)
{

	/*	Choose Sense Control  EXTI0
	 *  7	6	5	4	 3	   2	 1	   0
	 * [SE,SM2,SM1,SM0,ISC11,ISC10,ISC01,ISC00]
	 * 	 * So we need to configure Bits[1,0]
	 *
	 * */
#if SENSE_CONTROL_EXTI0 == EXTI_FALLING_EDGE
	// EXTI0 --> Falling Edge
	CLR_BIT(MCUCR_REG , 0);
	SET_BIT(MCUCR_REG , 1 );
#elif	SENSE_CONTROL_EXTI0 == EXTI_RAISING_EDGE
	SET_BIT(MCUCR_REG , 0);
	SET_BIT(MCUCR_REG , 1 );
#elif SENSE_CONTROL_EXTI0 == EXTI_ON_CHANGE
	SET_BIT(MCUCR_REG , 0 );
	CLR_BIT(MCUCR_REG , 1);
#elif	SENSE_CONTROL_EXTI0 == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR_REG , 0);
	CLR_BIT(MCUCR_REG , 1);

#endif

	/* Enable PIE for EXTI0
	 * 	 7    6    5    4   3   2    1    0
	 * [INT1,INT0,INT2, - , - , - ,IVSEL,IVCE]
	 * So, we configure Bit[6]
	 * */
	SET_BIT(GICR_REG , 6 );
}
void EXTI1_voidInit	(	void	)
{

	/*	Choose Sense Control  EXTI1
	 *  7	6	5	4	 3	   2	 1	   0
	 * [SE,SM2,SM1,SM0,ISC11,ISC10,ISC01,ISC00]
	 * So we need to configure Bits[2,3]
	 * */
#if SENSE_CONTROL_EXTI1 == EXTI_FALLING_EDGE
	// EXTI0 --> Falling Edge
	CLR_BIT(MCUCR_REG , 2);
	SET_BIT(MCUCR_REG , 3);
#elif	SENSE_CONTROL_EXTI1 == EXTI_RAISING_EDGE
	SET_BIT(MCUCR_REG , 2 );
	SET_BIT(MCUCR_REG , 3);
#elif SENSE_CONTROL_EXTI1 == EXTI_ON_CHANGE
	SET_BIT(MCUCR_REG , 2 );
	CLR_BIT(MCUCR_REG , 3);
#elif	SENSE_CONTROL_EXTI1 == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR_REG , 2);
	CLR_BIT(MCUCR_REG , 3);

#endif

	/* Enable PIE for EXTI1
	 * 	 7    6    5    4   3   2    1    0
	 * [INT1,INT0,INT2, - , - , - ,IVSEL,IVCE]
	 * So, we configure Bit[7]
	 * */
	SET_BIT(GICR_REG , 7 );
}
void EXTI2_voidInit	(	void	)
{

	/*	Choose Sense Control  EXTI2
	 *   7	 6	  5	  4	   3	2	  1	   0
	 * [JTD,ISC2, - ,JTRF,WDRF,BORF,EXTRF,PORF]
	 * So we need to configure Bits[6]
	 * */
#if SENSE_CONTROL_EXTI2 == EXTI_FALLING_EDGE
	// EXTI0 --> Falling Edge
	CLR_BIT(MCUCSR_REG , 6);
#elif	SENSE_CONTROL_EXTI2 == EXTI_RAISING_EDGE
	SET_BIT(MCUCSR_REG , 6 );

#endif

	/* Enable PIE for EXTI2
	 * 	 7    6    5    4   3   2    1    0
	 * [INT1,INT0,INT2, - , - , - ,IVSEL,IVCE]
	 * So, we configure Bit[5]
	 * */
	SET_BIT(GICR_REG , 5 );
}


void EXTI_voidChangeSenseControl	(u8 Copy_u8IntId	,	u8 Copy_u8SenseControl	)
{

	switch (Copy_u8IntId)
	{
	case EXTI_INT0 :

		switch ( Copy_u8SenseControl )
		{
		case EXTI_FALLING_EDGE :
			SET_BIT(MCUCR_REG , 1 );
			CLR_BIT(MCUCR_REG , 0);
			break;
		case EXTI_RAISING_EDGE:
			SET_BIT(MCUCR_REG , 1 );
			SET_BIT(MCUCR_REG , 0);
			break;
		case EXTI_LOW_LEVEL :
			CLR_BIT(MCUCR_REG , 1 );
			CLR_BIT(MCUCR_REG , 0);
			break ;
		case EXTI_ON_CHANGE :
			CLR_BIT(MCUCR_REG , 1 );
			SET_BIT(MCUCR_REG , 0);

			break ;
		default :
			break ;
		}
		break;
		case EXTI_INT1 :
			switch ( Copy_u8SenseControl )
			{
			case EXTI_FALLING_EDGE :
				SET_BIT(MCUCR_REG , 3 );
				CLR_BIT(MCUCR_REG , 2);
				break;
			case EXTI_RAISING_EDGE:
				SET_BIT(MCUCR_REG , 3 );
				SET_BIT(MCUCR_REG , 2);
				break;
			case EXTI_LOW_LEVEL :
				CLR_BIT(MCUCR_REG , 3 );
				CLR_BIT(MCUCR_REG , 2);
				break ;
			case EXTI_ON_CHANGE :
				CLR_BIT(MCUCR_REG , 3 );
				SET_BIT(MCUCR_REG , 2);

				break ;
			default :
				break ;
			}
			break;
			case EXTI_INT2 :
				switch ( Copy_u8SenseControl)
				{
				case EXTI_RAISING_EDGE :
					SET_BIT(MCUCSR_REG , 6 );
					break;
				case EXTI_FALLING_EDGE:
					CLR_BIT(MCUCSR_REG , 6 );
					break;
				default :break;
				}
				break;
			default:
				break;

	}



}
void EXTI_voidEnable	(u8 Copy_u8IntId)
{
	switch(Copy_u8IntId)
	{
	case EXTI_INT0 :
		SET_BIT(GICR_REG , EXTI_INT0_BIT );
		break;
	case EXTI_INT1:
		SET_BIT(GICR_REG , EXTI_INT1_BIT );

		break;
	case EXTI_INT2:
		SET_BIT(GICR_REG , EXTI_INT2_BIT );
		break ;
	}
}
void EXTI_voidDisable	(u8 Copy_u8IntId)
{
	switch(Copy_u8IntId)
		{
		case EXTI_INT0 :
			CLR_BIT(GICR_REG , EXTI_INT0_BIT );
			break;
		case EXTI_INT1:
			CLR_BIT(GICR_REG , EXTI_INT1_BIT );
			break;
		case EXTI_INT2:
			CLR_BIT(GICR_REG , EXTI_INT2_BIT );
			break ;
		}
}

void EXTI_voidSetCallBack	(u8 Copy_u8IntId , void (*Pf) (void)	)
{
	if ( Pf != NULL )
	{
		switch( Copy_u8IntId )
		{
		case EXTI_INT0 :
			Glo_ApfNotification[0] = Pf ;
			break ;
		case EXTI_INT1 :
			Glo_ApfNotification[1] = Pf ;

			break ;
		case EXTI_INT2 :
			Glo_ApfNotification[2] = Pf ;

			break ;
		default:
			break;
		}
	}
}
/* ISR for INT0.
 * Check Vector Table in Datasheet Page 44 to get vector number.
 * NOTE = vector number should decreased by 1.
 *  */
void __vector_1	(void)	__attribute__((signal)); // to tell the processor that the hw will handle it.
void __vector_1	(void)
{
	if (Glo_ApfNotification[0] != NULL)
	{
		Glo_ApfNotification[0]();
	}


}
/* ISR for INT1 */
void __vector_2	(void)	__attribute__((signal));
void __vector_2	(void)
{
	if (Glo_ApfNotification[1] != NULL)
	{
		Glo_ApfNotification[1]();
	}
}
/* ISR for INT2 */
void __vector_3	(void)	__attribute__((signal));
void __vector_3	(void)
{
	if (Glo_ApfNotification[2] != NULL)
	{
		Glo_ApfNotification[2]();
	}


}
