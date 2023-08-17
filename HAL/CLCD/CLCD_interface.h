/*******************************************************/
/****   Author : Islam Shaaban      ******************/
/****   SWC:          CLCD             ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/
#ifndef HAL_CLCD_CLCD_INTERFACE_H_
#define HAL_CLCD_CLCD_INTERFACE_H_
/***************************************************************************************/

/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/


#define CLCD_ROW_1		1
#define CLCD_ROW_2		2

#define CLCD_COL_1		1
#define CLCD_COL_2		2
#define CLCD_COL_3		3
#define CLCD_COL_4		4
#define CLCD_COL_5		5
#define CLCD_COL_6		6
#define CLCD_COL_7		7
#define CLCD_COL_8		8
#define CLCD_COL_9		9
#define CLCD_COL_10		10
#define CLCD_COL_11		11
#define CLCD_COL_12		12
#define CLCD_COL_13		13
#define CLCD_COL_14		14
#define CLCD_COL_15		15
#define CLCD_COL_16		16

#define PATTERNS_NUM 			8
#define NUMBER_OF_PIXELS        16

#define CLCD_FUNCTIONSET8bit 	0b00111000        	// 8-bit data, D4(DL=DataLength) - D3(N) #lines display- D2(F) 5 x 7 font.
#define CLCD_DISPLAYON_OFF      0b00001100          // D2(D)display on, D1(C)cursor off, D0(B)don't blink character
#define CLCD_CLR_DISPLAY		0b00000001
#define CLCD_ENTRYMODE       	0b00000110          // D1(I/D)- D0(SH) shift cursor/lcd from left to right on read/write
#define FIRST_PLACE_IN_ROW1     0b10000000
#define FIRST_PLACE_IN_ROW2     0b11000000			// 0b10000000(0x80) + 0b01000000(0x40)
#define FIRST_PLACE_IN_CGRAM    0b01000000			// 0b01(AC5-AC4-AC3-AC2-AC1-AC0)
#define CLCD_HOME           0x02          /* return cursor to first position on first line                   */
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_SetCursor       0x80          // set cursor position

void CLCD_voidInit		(	void	);

void CLCD_voidSendCommand	(u8 Copy_u8Command	);
void CLCD_voidSendData		(u8 Copy_u8Data		);

void CLCD_voidSetPosition	(u8 Copy_u8Row , u8 Copy_u8Col);

void CLCD_voidSendExtraChar	(u8 Copy_u8PatternLocation , u8 * Copy_pu8ExtraChar , u8 Copy_u8Row , u8 Copy_u8Col );

void CLCD_voidStoreExtraChar(u8 Copy_u8PatternLocation , u8 * Copy_pu8ExtraChar );
void CLCD_voidSendString	(u8 *Copy_pu8String );

void CLCD_voidSendu32Number (u32 Copy_u32Number);

void CLCD_voidCLearDisplay(void);

#endif /* HAL_CLCD_CLCD_INTERFACE_H_ */
