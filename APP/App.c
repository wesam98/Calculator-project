/*
 * App.c
 *
 *  Created on: Dec 4, 2023
 *      Author: METRA
 */

#include "../HAL/KEYPAD/Keypad_Config.h"
#include "../HAL/KEYPAD/Keypad_Int.h"

#include "../HAL/LCD/LCD_Int.h"

#include "APP.h"
#include "Array_Based_Stack.h"

s16 result = 0,error = 0,pos = 0;
u8 Key =0;
u8 data[DATA_SIZE] = {'\0'};


//take input from keypad and if it isn't equal to'=' then store it in data array
void input(){

	do
	{
		Keypad_u8GetPressedkey(&Key);
	}while( Key == NOT_PRESSED );
	LCD_enuDisplayChar(Key);

	if(Key!='=')
		data[pos++]=Key;
}


//calculate math expression entered by user
s16 calc( u8*data)
{
	result=0;
	s16 number = 0, j = 0;
	//Create stack used to store result of (* or \)operations and operands of(+ or -)operations
	Stack stack;
	CreateStack(&stack);
	//Create char array to store (+ or -) in expression and initialize it
	char operators[10] = {'\0'};



	//loop on expression and finish (* or / ) operations and push its result in stack
	// if there is + or - add it to operations array
	// and push their operands in stack too
	for (u8 i = 0;   data[i] != '\0' ; i++)
	{
		// to take number consist of more than 1 digit
		if (is_digit(data[i])) {
			number = number * 10 + (data[i] - '0');

		}

		if(! is_digit(data[i+1]) || data[i+1] == '\0'){

			Push(&stack,number);
			number=0;
		}

		if(isOperator(data[i]) ){

			if (data[i] == '+' || data[i] == '-')
				operators[j++] = data[i];
			//if it is * operation pop last element in stack then (*) it and the next number to operator
			//then push result in stack again

			else if (data[i] == '*') {
				s16 temp=0,x=0,j=2;

				//if second operand of * consist of more than one digit
				x=(data[i+1]-'0');
				while(is_digit(data[i+j])){

					x = (x *10) + (data[i+j] - '0');
					j++;
				}
				i+=j-2;

				temp = Stack_Top(&stack) * x;
				Pop(&stack);
				Push(&stack, temp);
				i++;
			}

			//if it is / operation pop last element in stack then (/) it and the next number to operator
			//then push result in stack again
			else if (data[i] == '/') {
				s16 temp=0,x=0,j=2;
				//if second operand of / consist of more than one digit
				x=(data[i+1]-'0');
				while(is_digit(data[i+j])){

					x = (x *10) + (data[i+j] - '0');
					j++;
				}
				i+=j-2;
				//detect if 2nd operand equals to 0 set error flag to 1
				if(x == 0){
					error = 1;
					return 0;
				}
				//if it'snot zero do devision and push result in stack
				temp = Stack_Top(&stack) / x;
				Pop(&stack);
				Push(&stack, temp);
				i++;
			}
		}
	}

	//reverse stack to match sequence of operators stored in operators array

	Stack reversed;
	CreateStack(&reversed);
	while(!Stack_Empty(&stack)) {

		Push(&reversed, Stack_Top(&stack));
		Pop(&stack);
	}

	//finish (+ or -) operations and push result in stack again

	if (operators[0] != '\0') {
		for (u8 i = 0;  operators[i] != '\0' ; i++) {
			if (operators[i] == '+') {
				s16 x = Stack_Top(&reversed);
				Pop(&reversed);
				s16 y = Stack_Top(&reversed);
				Pop(&reversed);
				Push(&reversed, x + y);
			}
			if (operators[i] == '-') {
				s16 x = Stack_Top(&reversed);
				Pop(&reversed);
				s16 y = Stack_Top(&reversed);
				Pop(&reversed);
				Push(&reversed, (x-y));
			}
		}
	}
	// pop remaining elements in stack(add them to result variable)
	while (StackSize(&reversed) > 0) {
		result += Stack_Top(&reversed);
		Pop(&reversed);
	}


	return result;

}



//process function manages operations due to key pressed
void process(){

	// if key pressed is equal to on/c clear display and reset data for next operation
	if (Key == 'C')
	{
		reset_data(data);
		Clear_display();
	}
	// if key pressed is equal to = call calc function and display result of current expression
	else if (Key == '=')
	{
		result = calc(data);
		LCD_enuSendCommand(0xC0);
		//check error flag if it's 0 then display result
		if(error ==0){
			if(result == 0)
				LCD_enuDisplayChar('0');
			else
				LCD_enuDisplayIntegerNum(result);
		}
		//if error flag == 1 it indicates devision by 0
		// so display error message
		else
		{
			LCD_enuDisplayChar('E');
			LCD_enuDisplayChar('R');
			LCD_enuDisplayChar('R');
			LCD_enuDisplayChar('O');
			LCD_enuDisplayChar('R');
			LCD_enuDisplayChar('!');
		}

		reset_data(data);
	}

}


//after finishing any expression reset data for next one
void reset_data(u8* data){

	result = 0;
	error = 0;
	pos = 0;
	// loop on data array and assign each element to '\0'
	for(u8 i=0;i<DATA_SIZE;i++)
		data[i]='\0';

}


void Clear_display(){

	LCD_enuSendCommand(0x01);
}


u8 isOperator(u8 ch){

	return (ch == '+' || ch == '-' || ch == '*' || ch == '/'
			|| ch == '^');
}




u8 is_digit(u8 x){

	return (x>='0' && x<='9');
}



