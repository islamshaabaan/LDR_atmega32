/*******************************************************/
/****   Author : Islam Shaaban      ******************/
/****   SWC:          CLCD             ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/
#ifndef HAL_CLCD_CLCD_CONFIG_H_
#define HAL_CLCD_CLCD_CONFIG_H_


/*
 -----------                   ----------
 | ATmega32  |                 |   LCD    |
 |           |                 |          |
 |		  GND|<----------------|VSS       |
 |        VCC|<----------------|VDD       |
 | VarRES|VCC|<----------------|V0        |
 |        PA7|---------------->|D7        |
 |        PA6|---------------->|D6        |
 |        PA5|---------------->|D5        |
 |        PA4|---------------->|D4        |
 |        PA3|---------------->|D3        |
 |        PA2|---------------->|D2        |
 |        PA1|---------------->|D1        |
 |        PA0|---------------->|D0        |
 |           |                 |          |
 |        PC5|---------------->|E         |
 |        PC6|---------------->|RW        |
 |        PC7|---------------->|RS        |
 -----------                   ----------
 */
/*
 Options:
 1.	 DIO_PORTA
 2.	 DIO_PORTB
 3.	 DIO_PORTC
 4.	 DIO_PORTD
 * */
#define CLCD_DATA_PORT			DIO_PORTD

#define CLCD_CTRL_PORT			DIO_PORTC

/*
 Options:
 1.	 DIO_PIN0
 2.	 DIO_PIN1
 3.	 DIO_PIN2
 4.	 DIO_PIN3
 5.  DIO_PIN4
 .
.
.

 * */
#define CLCD_RS_PIN				DIO_PIN7
#define CLCD_RW_PIN				DIO_PIN6
#define CLCD_EN_PIN				DIO_PIN5



#endif /* HAL_CLCD_CLCD_CONFIG_H_ */
