/*
 * Keypad_Int.h
 *
 *  Created on: Nov 27, 2023
 *      Author: METRA
 */

#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_
#include "../../Libirarys/ErrorStates.h"
#include "../../Libirarys/StdTypes.h"

ES_t Keypad_enuInit(void);
ES_t Keypad_u8GetPressedkey(u8 *Local_u8pPressedKey);


#endif /* KEYPAD_INT_H_ */
