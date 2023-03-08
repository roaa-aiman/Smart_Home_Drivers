/*
 * Inclusion of files 
 */
/* Library files */
#include "STD_TYPES.h"
#include "BIT_MATH.h" 

/* DIO file */
#include "DIO_interface.h"

/* LED files */
#include "BUZZER_interface.h"
#include "BUZZER_config.h"

/* 
 * Public Function Prototype 
 */

void H_BUZZER_void_Init   (){
	MDIO_voidSetPinDirection(BUZZER_PORT,BUZZER_PIN,OUTPUT);
}

void H_BUZZER_void_TurnOn (){
	MDIO_voidSetPinValue(BUZZER_PORT,BUZZER_PIN,HIGH);
}

void H_BUZZER_void_TurnOff(){
	MDIO_voidSetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);
}

void H_BUZZER_void_Toggle (){
	MDIO_voidTogPinValue(BUZZER_PORT,BUZZER_PIN);
}
