/*
 * LCD_Int.h
 *
 *  Created on: Nov 28, 2023
 *      Author: METRA
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_


ES_t LCD_enuInit(void);

ES_t LCD_enuDisplayChar(u8 Copy_u8Data);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);


ES_t LCD_enuDisplayExtraChar(u8* Copy_pu8Character,u8 Copy_u8CharNum ,u8 Copy_u8Position , u8 Copy_u8Entry);


ES_t LCD_enuDisplayIntegerNum(s32 Copy_s32Num);

#endif /* LCD_INT_H_ */
