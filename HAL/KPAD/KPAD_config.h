/*
 * KPAD_config.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Islam Shaaban Hussein
 */

#ifndef HAL_KPAD_KPAD_CONFIG_H_
#define HAL_KPAD_KPAD_CONFIG_H_

u8 KPAD_Au8Values[4][4] ={
                            {'7','8','9','/'}, //Row 0
                            {'4','5','6','x'}, //Row 1
                            {'1','2','3','-'}, //Row 2
                            {'C','0','=','+'}  //Row 3
                            };


#define KPAD_PORT           DIO_PORTB

#define KPAD_ROW_INIT       DIO_PIN0
#define KPAD_ROW_END        DIO_PIN3

#define KPAD_COL_INIT       DIO_PIN4
#define KPAD_COL_END        DIO_PIN7


#define KPAD_R0             DIO_PIN0
#define KPAD_R1             DIO_PIN1
#define KPAD_R2             DIO_PIN2
#define KPAD_R3             DIO_PIN3

#define KPAD_C0             DIO_PIN4
#define KPAD_C1             DIO_PIN5
#define KPAD_C2             DIO_PIN6
#define KPAD_C3             DIO_PIN7







#endif /* HAL_KPAD_KPAD_CONFIG_H_ */
