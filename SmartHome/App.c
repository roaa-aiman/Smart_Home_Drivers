/*
 * App.c
 *
 *  Created on: Sep 14, 2021
 *      Author: Sara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "USART_interface.h"
#include "FAN_interface.h"
#include "DOOR_interface.h"
#include "BUZZER_interface.h"

void order(u8 Copy_u8OrderID);
void Menu_HomeSmart(void);
u8 compareStrings(u8 *Ptr_u8String1,u8 *Ptr_u8String2);

#define MAX_USERS   			10
#define NAME_LIMIT   			20
#define MAX_NUMBER_OF_TRIALS	3


typedef struct {
	char name[NAME_LIMIT];

}name;

typedef struct {
	char password[NAME_LIMIT];

}pass;


name UsersArray[MAX_USERS]={
		{"Sara Ahmed"},
		{"Roaa Ayman"},
		{"Alaa Magdy"},
		{"Rana Hatem"},
		{"Mohamed Ahmed"},
		{"Laila Tarek"},
		{"Yassin Edris"},
		{"Malak Mahmoud"},
		{"Eyad EL-Sayed"},
		{"Maria Magdey" },
};

pass UsersArrayPass[MAX_USERS]={
		{"Sara Ahmed"},
		{"Roaa Ayman"},
		{"Alaa Magdy"},
		{"Rana Hatem"},
		{"Mohamed Ahmed"},
		{"Laila Tarek"},
		{"Yassin Edris"},
		{"Malak Mahmoud"},
		{"Eyad EL-Sayed"},
		{"Maria Magdey" },
};


int main(void)
{
	//Set Rx as input and Tx as outout
	MDIO_voidSetPinDirection(PORTD, PIN0, INPUT);
	MDIO_voidSetPinDirection(PORTD, PIN1, OUTPUT);
	//set led as output
	MDIO_voidSetPinDirection(PORTB, PIN0, OUTPUT);

	MUSART_voidInit();
	HFAN_voidInit();
	HDoor_voidInit();
	H_BUZZER_void_Init();

	u8 local_u8NoOfUserNameTrial =0
	,local_u8NoPasswordTrials =0
	,local_u8UserIndex=0
	,Local_stringPassword[NAME_LIMIT]
	,Local_stringUserName[NAME_LIMIT]
	,flagPass=0
	,flagName=0
	,Local_u8TaskID[5]
	,local_u8Continue[5];

	/*Entrant System*/
	MUSART_voidSendMsg("Welcome to SmartHome...");

	/*Loop for 3 trials of entering UserName*/
	while(flagName != 1 && local_u8NoOfUserNameTrial < MAX_NUMBER_OF_TRIALS )
	{
		MUSART_voidSendMsg("\r\nPlease enter your USERNAME: ");
		MUSART_voidReceiveMsg(&Local_stringUserName[0]);

		for(local_u8UserIndex=0;local_u8UserIndex<MAX_USERS;local_u8UserIndex++)
		{
			if(compareStrings(&Local_stringUserName, UsersArray[local_u8UserIndex].name)==0)
			{	/*found*/
				MUSART_voidSendMsg("\r\nCorrect User Name...");
				flagName = 1;
				break;
			}
		}

		 if (flagName !=1 && local_u8NoOfUserNameTrial<2)
		 {
			 MUSART_voidSendMsg("Wrong User Name... Try again \r\n ");
		 }
		 else if (local_u8NoOfUserNameTrial >= 2)
		{
			MUSART_voidSendMsg("Wrong User Name, NO MORE TRIALS ,TRY TO RESET\r\n ");
			H_BUZZER_void_TurnOn();
			while(1); //Block system until restarting again
		}
		 else
		 {

		 }
			local_u8NoOfUserNameTrial++;
	}


	/*loop for 3 trials of entering Password*/
	while(flagPass != 1 && local_u8NoPasswordTrials < MAX_NUMBER_OF_TRIALS)
	{
		MUSART_voidSendMsg("\r\nPlease enter your PASSWORD: \r\n");
		MUSART_voidReceiveMsg(&Local_stringPassword[0]);


		/*Checking if the entered Password is correct*/
		if(compareStrings(&Local_stringUserName[0], UsersArrayPass[local_u8UserIndex].password) == 0)
		{
			MUSART_voidSendMsg("\r\nCorrect Password");
			flagPass=1; /*Correct Pass*/
		}

		else if (local_u8NoPasswordTrials<2)
		{   /*If the Entered PASSWORD is WRONG 1st time still have 2 more trials*/
			MUSART_voidSendMsg("Try again");
		}
		else
		{
			MUSART_voidSendMsg("Wrong Password NO MORE TRIALS ,TRY TO RESET ");
			H_BUZZER_void_TurnOn();
			while(1); //Block system until restarting again
		}
		local_u8NoPasswordTrials++;
	}




	while(1)
	{

		//while(flag of pass and name == 1){ do control system }
		Menu_HomeSmart();
		MUSART_voidSendMsg("Please Enter task :");
		MUSART_voidReceiveMsg(&Local_u8TaskID);
		MUSART_voidSendData(&Local_u8TaskID[0]);

		order(Local_u8TaskID[0]);
		MUSART_voidSendMsg("\r\n *if you want to do another order press y ");
		MUSART_voidReceiveMsg(&local_u8Continue);
		MUSART_voidSendData(&local_u8Continue[0]);
		while(local_u8Continue[0] != 'y')
		{
			MUSART_voidReceiveData(&local_u8Continue);
		}

	}
	return 0;
}
void Menu_HomeSmart(void)
{
	MUSART_voidSendMsg("\r\n___Menu___\r\n");
	MUSART_voidSendMsg("1-Close the Door\r\n");
	MUSART_voidSendMsg("2-Open the LED\r\n");
	MUSART_voidSendMsg("3-Close the LED\r\n");
	MUSART_voidSendMsg("4-Turn Fan on Speed 1\r\n");
	MUSART_voidSendMsg("5-Turn Fan ON Speed 2\r\n");
	MUSART_voidSendMsg("6-Turn Fan OFF\r\n");
	MUSART_voidSendMsg("7-Open the Door\r\n");
}

void order(u8 Copy_u8OrderID)
{
	if (Copy_u8OrderID == '1')
	{
		HDoor_voidClose();
		MUSART_voidSendMsg("Door closed");
	}
	else if (Copy_u8OrderID == '2')
	{
		MDIO_voidSetPinValue(PORTB, PIN0, HIGH);
		MUSART_voidSendMsg("Led ON");

	}
	else if (Copy_u8OrderID == '3')
	{
		MDIO_voidSetPinValue(PORTB, PIN0, LOW);
		MUSART_voidSendMsg("Led off");

	}
	else if (Copy_u8OrderID == '4')
	{
		HFAN_voidSpeedControl(FAN_SPEED1);
		MUSART_voidSendMsg("Fan on Speed 1");

	}
	else if (Copy_u8OrderID == '5')
	{
		HFAN_voidSpeedControl(FAN_SPEED2);
		MUSART_voidSendMsg("Fan on Speed 2");
	}
	else if (Copy_u8OrderID == '6')
	{
		HFAN_voidSpeedControl(0);
		MUSART_voidSendMsg("Fan Off");
	}
	else if (Copy_u8OrderID == '7')
	{
		HDoor_voidOpen();
		MUSART_voidSendMsg("Door opened");
	}
//	else
//	{
//		MUSART_voidSendMsg("Wrong Input");
//	}

}

/*check if two string are equal */
u8 compareStrings(u8 *Ptr_u8String1,u8 *Ptr_u8String2)
{
	u8 flag=0,i=0;
	while(Ptr_u8String1[i]!='\0' &&Ptr_u8String2[i]!='\0')
	{
		if(Ptr_u8String1[i]!=Ptr_u8String2[i])
		{
			flag=1;
			break;
		}
		i++;
	}
	/*return 1 if not equal
	 *       0 if equal      */
	if(flag==0)
		return 0;
	else
		return 1;
}

