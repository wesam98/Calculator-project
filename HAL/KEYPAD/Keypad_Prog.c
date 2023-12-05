/*
 * Keypad_Prog.c
 *
 *  Created on: Nov 27, 2023
 *      Author: METRA
 */


#include "../../Libirarys/StdTypes.h"
#include "../../Libirarys/ErrorStates.h"

#include "../../MCAL/DIO_Int.h"
#include "../../MCAL/DIO_Config.h"


#include "Keypad_Config.h"
#include "Keypad_Private.h"

ES_t Keypad_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	//set Columns pins Direction as OUTPUT
	Local_enuErrorState = DIO_enuSetPinDirection(Keypad_C1PORT,Keypad_C1PIN,DIO_u8OUTPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(Keypad_C2PORT,Keypad_C2PIN,DIO_u8OUTPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(Keypad_C3PORT,Keypad_C3PIN,DIO_u8OUTPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(Keypad_C4PORT,Keypad_C4PIN,DIO_u8OUTPUT);
	//Set Rows Pins Direction as INPUT
	Local_enuErrorState = DIO_enuSetPinDirection(Keypad_R1PORT,Keypad_R1PIN,DIO_u8INPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(Keypad_R2PORT,Keypad_R2PIN,DIO_u8INPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(Keypad_R3PORT,Keypad_R3PIN,DIO_u8INPUT);
	Local_enuErrorState = DIO_enuSetPinDirection(Keypad_R4PORT,Keypad_R4PIN,DIO_u8INPUT);
	//Set Columns Value as High
	Local_enuErrorState = DIO_enuSetPinValue(Keypad_C1PORT,Keypad_C1PIN,DIO_u8HIGH);
	Local_enuErrorState = DIO_enuSetPinValue(Keypad_C2PORT,Keypad_C2PIN,DIO_u8HIGH);
	Local_enuErrorState = DIO_enuSetPinValue(Keypad_C3PORT,Keypad_C3PIN,DIO_u8HIGH);
	Local_enuErrorState = DIO_enuSetPinValue(Keypad_C4PORT,Keypad_C4PIN,DIO_u8HIGH);
	//Set Raws value As Pull up
	Local_enuErrorState = DIO_enuSetPinValue(Keypad_R1PORT,Keypad_R1PIN,DIO_u8PULL_UP);
	Local_enuErrorState = DIO_enuSetPinValue(Keypad_R2PORT,Keypad_R2PIN,DIO_u8PULL_UP);
	Local_enuErrorState = DIO_enuSetPinValue(Keypad_R3PORT,Keypad_R3PIN,DIO_u8PULL_UP);
	Local_enuErrorState = DIO_enuSetPinValue(Keypad_R4PORT,Keypad_R4PIN,DIO_u8PULL_UP);

	return Local_enuErrorState;
}
ES_t Keypad_u8GetPressedkey(u8 * Copy_pu8PressedKey)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu8PressedKey != NULL)
	{
	u8 Local_u8PressedKey = NOT_PRESSED , Col_Index , Row_Index , Local_u8pinState;
	* Copy_pu8PressedKey = NOT_PRESSED;

	u8 Local_u8KPAD_ARR[ROW_NUM][COLUMN_NUM]=KPD_Arr_Val;

	static u8 Local_u8ColPinsArr[COLUMN_NUM]={Keypad_C1PIN,Keypad_C2PIN,Keypad_C3PIN,Keypad_C4PIN};
	static u8 Local_u8ColPortArr[COLUMN_NUM]={Keypad_C1PORT,Keypad_C2PORT,Keypad_C3PORT,Keypad_C4PORT};

	static u8 Local_u8RowPinsArr[ROW_NUM]={Keypad_R1PIN, Keypad_R2PIN, Keypad_R3PIN, Keypad_R4PIN};
	static u8 Local_u8RowPortArr[ROW_NUM]={Keypad_R1PORT,Keypad_R2PORT,Keypad_R3PORT,Keypad_R4PORT};

	for(Col_Index=0;Col_Index<COLUMN_NUM;Col_Index++)
	{
		//Activate Current Columns
		Local_enuErrorState = DIO_enuSetPinValue(Local_u8ColPortArr[Col_Index],Local_u8ColPinsArr[Col_Index],DIO_u8LOW);
		for(Row_Index=0;Row_Index<ROW_NUM;Row_Index++)
		{
			DIO_enuGetPinValue(Local_u8RowPortArr[Row_Index],Local_u8RowPinsArr[Row_Index],&Local_u8pinState);
			//Check is switch is pressed
			if(DIO_u8LOW == Local_u8pinState )
			{
				//Polling --> Busy waiting until key is released
				while(DIO_u8LOW == Local_u8pinState)
				{
					DIO_enuGetPinValue(Local_u8RowPortArr[Row_Index],Local_u8RowPinsArr[Row_Index],&Local_u8pinState);
				}
				*Copy_pu8PressedKey = Local_u8KPAD_ARR[Row_Index][Col_Index];
				return Local_enuErrorState = ES_OK;

			}
		}
		//Deactivate Current column
		DIO_enuSetPinValue(Local_u8ColPortArr[Col_Index],Local_u8ColPinsArr[Col_Index],DIO_u8HIGH);
	}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}
