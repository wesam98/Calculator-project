/*
 * LCD_Private.h
 *
 *  Created on: Nov 29, 2023
 *      Author: METRA
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define  EIGHT_BIT  9
#define  FOUR_BIT   10

//local periodic function prototype

static inline void LCD_invidSendCommend(u8 Copy_u8Command);

static void LCD_vidLatch(u8 Copy_u8Data);

#endif /* LCD_PRIVATE_H_ */
