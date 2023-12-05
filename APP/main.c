/*
 * main.c
 *
 *  Created on: Dec 4, 2023
 *      Author: METRA
 */

#include "../MCAL/DIO_Int.h"

#include "../HAL/KEYPAD/Keypad_Int.h"
#include "../HAL/LCD/LCD_Int.h"

#include "APP.h"

int main(void)
{

	DIO_enuInit();
	Keypad_enuInit();
	LCD_enuInit();

	while(1)
	{

		input();
		process();

	}

	return 0;
}



