/*
 * APP.h
 *
 *  Created on: Dec 3, 2023
 *      Author: METRA
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "../Libirarys/StdTypes.h"

#define DATA_SIZE 15

void input();
void process();
s16 calc( u8*data);
void reset_data(u8 *data);
void Clear_display();
u8 isOperator(u8 x);
u8 is_digit(u8 x);


#endif /* APP_APP_H_ */
