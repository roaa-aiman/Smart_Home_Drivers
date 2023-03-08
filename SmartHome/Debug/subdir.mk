################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App.c \
../BUZZER_program.c \
../DIO_program.c \
../DOOR_program.c \
../FAN_program.c \
../Timer0_program.c \
../Timer1_program.c \
../USART_program.c 

OBJS += \
./App.o \
./BUZZER_program.o \
./DIO_program.o \
./DOOR_program.o \
./FAN_program.o \
./Timer0_program.o \
./Timer1_program.o \
./USART_program.o 

C_DEPS += \
./App.d \
./BUZZER_program.d \
./DIO_program.d \
./DOOR_program.d \
./FAN_program.d \
./Timer0_program.d \
./Timer1_program.d \
./USART_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


