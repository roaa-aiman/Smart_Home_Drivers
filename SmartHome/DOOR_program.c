#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "Timer1_interface.h"
#include "DOOR_interface.h"
#include "DOOR_config.h"
#include "DOOR_private.h"

void HDoor_voidInit(void)
{
	MTimer1_voidInit();
	MTimer1_voidSetICR(MAX_DUTY_CYCLE);
}

void HDoor_voidOpen(void)
{
	MTimer1_voidSetDutyCycle(MAX_DOOR_ANGLE);
}

void HDoor_voidClose(void)
{
	MTimer1_voidSetDutyCycle(MIN_DOOR_ANGLE);
}
