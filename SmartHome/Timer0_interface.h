#ifndef Timer0_INTERFACE_H
#define Timer0_INTERFACE_H

void MTIMER0_voidInitialize(void);
void MTIMER0_voidSetCompareMatchValue(u8 Copy_u8CompValue);
u8 MTIMER0_u8SetCallBack(void (*Copy_voidCallBackFunction)(void));

#endif

