#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void MUSART_voidInit(void);

void MUSART_voidSendData(u8 Copy_u8SendData);
void MUSART_voidReceiveData(u8 *Ptr_u8ReceiveData);
void MUSART_voidSendMsg(u8 *Ptr_u8SendMsg);
void MUSART_voidReceiveMsg(u8 *Ptr_u8ReceiveMsg);

#endif

