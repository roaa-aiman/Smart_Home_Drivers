#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "Timer0_interface.h"
#include "FAN_interface.h"
#include "FAN_config.h"

void HFAN_voidInit(void)
{
	MDIO_voidSetPinDirection(FAN_PORT, FAN_PIN, OUTPUT);
	MTIMER0_voidInitialize();
}

void HFAN_voidSpeedControl(u8 Copy_u8Speed)
{
	MTIMER0_voidSetCompareMatchValue(Copy_u8Speed);
}
