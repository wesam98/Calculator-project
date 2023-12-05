/*
 * Array_Based_Stack.c
 *
 *  Created on: Dec 2, 2023
 *      Author: METRA
 */


//
// Created by METRA on 11/13/2023.
//



#include "Array_Based_Stack.h"

void CreateStack (Stack *Ps){

    Ps->top = 0;
}


void Push(Stack *ps,StackEntry element)
{

    ps->Array[ps->top] = element;
    ps->top=ps->top+1;


}


void Pop (Stack *Ps)
{
    Ps->top--;

}


u8 Stack_Empty (Stack *Ps)
{

    return ( Ps->top == 0);
}



u8 Stack_Full (Stack *Ps)
{
    return Ps->top == MAX_SIZE;
}



StackEntry Stack_Top (Stack *ps)
{
    return ps->Array[ps->top-1];
}



u8 StackSize(Stack *Ps)
{
    return Ps->top;
}

