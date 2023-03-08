#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_register.h"
#include "USART_config.h"
void (*ADC_CallBack)(void);

void MUSART_voidInit(void)
{
	/*Boud Rate to 9600*/
	UBRRL = USART_BAUD_RATE_9600;

	u8 Local_u8_UCSRC_Variable;
	//set UCSRC to be enabled first
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_URSEL);

	//Select number of stop bits
#if USART_STOP_BIT_SELECTION == USART_STOP_BIT_SELECTION_ONE
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_USBS);

#elif USART_STOP_BIT_SELECTION == USART_STOP_BIT_SELECTION_TWO
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_USBS);
#endif


	/*Number of data bits is 8 bits*/
#if USART_CHARACTER_SIZE_SELECTION == USART_CHARACTER_SIZE_SELECTION_5_BIT
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ0);
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
#elif USART_CHARACTER_SIZE_SELECTION == USART_CHARACTER_SIZE_SELECTION_6_BIT
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ0);
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
#elif USART_CHARACTER_SIZE_SELECTION == USART_CHARACTER_SIZE_SELECTION_7_BIT
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ0);
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
#elif USART_CHARACTER_SIZE_SELECTION == USART_CHARACTER_SIZE_SELECTION_8_BIT
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ0);
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
#elif USART_CHARACTER_SIZE_SELECTION == USART_CHARACTER_SIZE_SELECTION_9_BIT
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ0);
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UCSZ1);
	SET_BIT(UCSRB, UCSRB_UCSZ2);
#endif

	/*Parity mode selection*/
#if USART_PARITY_MODE_SELECTION == USART_PARITY_MODE_DISABLE
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_UPM0);
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_UPM1);

#elif USART_PARITY_MODE_SELECTION == USART_PARITY_MODE_EVEN_ENABLE
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_UPM0);
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UPM1);
#elif USART_PARITY_MODE_SELECTION == USART_PARITY_MODE_ODD_ENABLE
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UPM0);
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UPM1);
#endif

	//Select Synchronous or Asynchronous
#if USART_MODE_SELECTION == USART_ASYNCHROUNOUS_OPERATION
	CLR_BIT(Local_u8_UCSRC_Variable, UCSRC_UMSEL);
	//Enable Tx, Rx
	SET_BIT(UCSRB, UCSRB_RXEN);
	SET_BIT(UCSRB, UCSRB_TXEN);
#elif USART_MODE_SELECTION == USART_SYNCHROUNOUS_OPERATION
	SET_BIT(Local_u8_UCSRC_Variable, UCSRC_UMSEL);
#endif
	UCSRC = Local_u8_UCSRC_Variable;
}


void MUSART_voidSendData(u8 Copy_u8SendData)
{
	//wait until Transmit buffer is empty
	while(GET_BIT(UCSRA, UCSRA_UDRE) !=1);
	UDR = Copy_u8SendData;
}
void MUSART_voidReceiveData(u8 *Ptr_u8ReceiveData)
{
	while(GET_BIT(UCSRA, UCSRA_RXC) !=1);
	*Ptr_u8ReceiveData = UDR;
}

void MUSART_voidSendMsg(u8 *Ptr_u8SendMsg)
{
	u8 i=0;
	while(Ptr_u8SendMsg[i] != '\0')
	{
		MUSART_voidSendData(Ptr_u8SendMsg[i]);
		i++;
	}
}

void MUSART_voidReceiveMsg(u8 *Ptr_u8ReceiveMsg)
{
	u8 Local_u8Character;
	u8 i =0;
	do
		{
			 MUSART_voidReceiveData(&Local_u8Character);
			 Ptr_u8ReceiveMsg[i] = Local_u8Character;
			 //MUSART_voidSendData(Ptr_u8ReceiveMsg[i]);
			 i++;
		}while(Local_u8Character != ENTER_PRESS);
}
