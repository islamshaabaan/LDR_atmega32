/*
 * DCMOTOR_interface.h
 *
 *  Created on: Aug 11, 2023
 *      Author: one
 */

#ifndef HAL_DC_MOTOR_DCMOTOR_INTERFACE_H_
#define HAL_DC_MOTOR_DCMOTOR_INTERFACE_H_

#define DCMOTOR_PORT DIO_PORTD
#define DCMOTOR_HB_PIN0 DIO_PIN0
#define DCMOTOR_HB_PIN1 DIO_PIN1
void DCMOTOR_voidInit();
void DCMOTOR_voidCWRotate();
void DCMOTOR_voidCCWRotate();
void DCMOTOR_voidStop();


#endif /* HAL_DC_MOTOR_DCMOTOR_INTERFACE_H_ */
