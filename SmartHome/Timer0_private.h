#ifndef Timer0_PRIVATE_H
#define Timer0_PRIVATE_H

/*Options for Clock Select*/
#define TIMER0_NO_CLK					0
#define TIMER0_CLK_NO_PRESCALER			1
#define TIMER0_CLK_DIVIDED_BY_8			2
#define TIMER0_CLK_DIVIDED_BY_64		3
#define TIMER0_CLK_DIVIDED_BY_256		4
#define TIMER0_CLK_DIVIDED_BY_1024		5
#define TIMER0_CLK_ON_FALLING_EDGE		6
#define TIMER0_CLK_ON_RISING_EDGE		7

/*Options for Waveform Generation*/
#define TIMER0_NORMAL_MODE		1
#define TIMER0_CTC_MODE			2
#define TIMER0_PWM_MODE			3
#define TIMER0_FAST_PWM_MODE	4

#define	TIMER0_NORMAL_MODE_FAST_PWM			0
#define	TIMER0_CLEAR_ON_COMPARE_FAST_PWM	1
#define	TIMER0_SET_ON_COMPARE_FAST_PWM		2

#define  TIMER0_COMPAR_MATCH_INTERRUPT_ENABLE	1
#define  TIMER0_OVERFLOW_INTERRUPT_ENABLE		2

void __vector_10(void) __attribute__((signal));
void __vector_11(void) __attribute__((signal));

#endif



