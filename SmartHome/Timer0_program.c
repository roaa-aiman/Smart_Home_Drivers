#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Timer0_interface.h"
#include "Timer0_private.h"
#include "Timer0_register.h"
#include "Timer0_config.h"

void (*GTimer0_voidCallBack)(void) = NULL;


void MTIMER0_voidInitialize(void)
{
	/*Select Timer0 Mode*/

#if TIMER0_MODE == TIMER0_NORMAL_MODE
	CLR_BIT(TCCR0, TCCR0_WGM00);
	CLR_BIT(TCCR0, TCCR0_WGM01);
	TCNT0 = TIMER0_PRELOAD_VALUE;

#elif TIMER0_MODE == TIMER0_PWM_MODE
	SET_BIT(TCCR0, TCCR0_WGM00);
	CLR_BIT(TCCR0, TCCR0_WGM01);

#elif TIMER0_MODE == TIMER0_CTC_MODE
	CLR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
	TCNT0 = TIMER0_PRELOAD_VALUE;
	
#elif TIMER0_MODE == TIMER0_FAST_PWM_MODE
	SET_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
#else
	//error
#endif

	/*Set Fast PWM Mode*/

#if TIMER0_FAST_PWM_MODE_SELECT == TIMER0_NORMAL_MODE_FAST_PWM
	CLR_BIT(TCCR0, TCCR0_COM00);
	CLR_BIT(TCCR0, TCCR0_COM01);
#elif TIMER0_FAST_PWM_MODE_SELECT == TIMER0_CLEAR_ON_COMPARE_FAST_PWM
	CLR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#elif TIMER0_FAST_PWM_MODE_SELECT == TIMER0_SET_ON_COMPARE_FAST_PWM
	SET_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#else
	//error
#endif


/*Select Clock Prescaler*/
#if TIMER0_SELECT_CLK == TIMER0_NO_CLK
	CLR_BIT(TCCR0, TCCR0_CS00);
	CLR_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);

#elif TIMER0_SELECT_CLK == TIMER0_CLK_NO_PRESCALER
	SET_BIT(TCCR0, TCCR0_CS00);
	CLR_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);

#elif TIMER0_SELECT_CLK == TIMER0_CLK_DIVIDED_BY_8
	CLR_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);

#elif TIMER0_SELECT_CLK == TIMER0_CLK_DIVIDED_BY_64
	SET_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);


#elif TIMER0_SELECT_CLK == TIMER0_CLK_DIVIDED_BY_256
	CLR_BIT(TCCR0, TCCR0_CS00);
	CLR_BIT(TCCR0, TCCR0_CS01);
	SET_BIT(TCCR0, TCCR0_CS02);

#elif TIMER0_SELECT_CLK == TIMER0_CLK_DIVIDED_BY_1024
	SET_BIT(TCCR0, TCCR0_CS00);
	CLR_BIT(TCCR0, TCCR0_CS01);
	SET_BIT(TCCR0, TCCR0_CS02);

#elif TIMER0_SELECT_CLK == TIMER0_CLK_ON_FALLING_EDGE
	CLR_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	SET_BIT(TCCR0, TCCR0_CS02);

#elif TIMER0_SELECT_CLK == TIMER0_CLK_ON_RISING_EDGE
	SET_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	SET_BIT(TCCR0, TCCR0_CS02);
#else
	//error
#endif

/*Can be replaced with this only*/
//TCCR0 = (TCCR0 & 0xF8) | TIMER0_SELECT_CLK;

}

void MTIMER0_voidSetCompareMatchValue(u8 Copy_u8CompValue)
{
	OCR0 = Copy_u8CompValue;
}

u8 MTIMER0_u8SetCallBack(void (*Copy_voidCallBackFunction)(void))
{
	/*Enable Mode of Interrupt*/
	#if TIMER0_INTERRUPT_ENABLE == TIMER0_COMPAR_MATCH_INTERRUPT_ENABLE
		SET_BIT(TIMSK, TIMSK_OCIE0);
	#elif TIMER0_INTERRUPT_ENABLE == TIMER0_OVERFLOW_INTERRUPT_ENABLE
		SET_BIT(TIMSK, TIMSK_TOIE0);

	#else
		//error
	#endif

	u8 Local_u8ErrorStatus = OK;
	if (Copy_voidCallBackFunction != NULL)
	{
		GTimer0_voidCallBack = Copy_voidCallBackFunction;
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;

}

void __vector_10(void)
{
	static volatile u32 Local_u32CTC_Counter = 0;
	Local_u32CTC_Counter++;
	if (Local_u32CTC_Counter == TIMER0_DESIRED_OVERFLOW)
	{
		TCNT0 = TIMER0_PRELOAD_VALUE;
		if (GTimer0_voidCallBack != NULL)
		{
			GTimer0_voidCallBack();
		}
		else
		{
			// Error
		}
		Local_u32CTC_Counter = 0;
	}

}

void __vector_11(void)
{
	static volatile u32 Local_u32OF_Counter = 0;
	Local_u32OF_Counter ++;
	if (Local_u32OF_Counter == TIMER0_DESIRED_OVERFLOW)
	{
		TCNT0 = TIMER0_PRELOAD_VALUE;
		if (GTimer0_voidCallBack != NULL)
		{
			GTimer0_voidCallBack();
		}
		else
		{
			// Error
		}
		Local_u32OF_Counter = 0;
	}

}
