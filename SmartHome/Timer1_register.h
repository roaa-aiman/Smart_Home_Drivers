#ifndef TIMER1_REGISTER_H
#define TIMER1_REGISTER_H

/*Timer/Counter1 Control Register A*/
#define	TCCR1A	*((volatile u8*)0x4F)
#define	TCCR1A_COM1A1	7
#define	TCCR1A_COM1A0	6
#define	TCCR1A_COM1B1	5
#define	TCCR1A_COM1B0	4
#define	TCCR1A_FOC1A	3
#define	TCCR1A_FOC1B	2
#define	TCCR1A_WGM11	1
#define	TCCR1A_WGM10	0

/*Timer/Counter1 Control Register B*/
#define	TCCR1B	*((volatile u8*)0x4E)
#define	TCCR1B_ICNC1	7
#define	TCCR1B_ICES1	6
/*Bit 5 is reversed */
#define	TCCR1B_WGM13	4
#define	TCCR1B_WGM12	3
#define	TCCR1B_CS12		2
#define	TCCR1B_CS11		1
#define	TCCR1B_CS10		0

#define	TCNT1H	*((volatile u8*)0x4D)
#define	TCNT1L	*((volatile u8*)0x4C)

/*Output Compare Register 1 A*/

#define	OCR1AL	*((volatile u16*)0x4A)

/*Output Compare Register 1 B*/
#define	OCR1BH	*((volatile u8*)0x49)
#define	OCR1BL	*((volatile u8*)0x48)

/*Input Capture Register 1 */
#define ICR1L	*((volatile u16*)0x46)

/*Timer/Counter Interrupt Mask Register*/
#define	TIMSK	*((volatile u8*)0x59)
#define	TIMSK_TICIE1	5		
#define	TIMSK_OCIE1A	4
#define	TIMSK_OCIE1B	3
#define	TIMSK_TOIE1		2

/*Timer/Counter Interrupt Flag Register */
#define	TIFR	*((volatile u8*)0x58)
#define	TIFR_ICF1		5		
#define	TIFR_OCF1A		4
#define	TIFR_OCF1B		3
#define	TIFR_TOV1		2

#endif
