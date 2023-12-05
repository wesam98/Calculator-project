/*
 * Array_Based_Stack.h
 *
 *  Created on: Dec 2, 2023
 *      Author: METRA
 */

#ifndef ARRAY_BASED_STACK_H_
#define ARRAY_BASED_STACK_H_

#include "../Libirarys/StdTypes.h"

#define MAX_SIZE 20
#define StackEntry s16

typedef struct stack
{
    int top;

    StackEntry Array[MAX_SIZE];
}Stack;


void CreateStack (Stack *Ps);
void Push(Stack*Ps,StackEntry element);
void Pop (Stack*Ps);
u8 Stack_Empty (Stack*Ps);
u8 Stack_Full (Stack*Ps);
StackEntry Stack_Top (Stack *ps);
u8 StackSize(Stack *Ps);
void Stack_Disply(Stack *Ps);


#endif /* ARRAY_BASED_STACK_H_ */
