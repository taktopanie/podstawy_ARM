################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Biblioteki/SoftwarePWM.c \
../Biblioteki/UART_obsluga.c 

OBJS += \
./Biblioteki/SoftwarePWM.o \
./Biblioteki/UART_obsluga.o 

C_DEPS += \
./Biblioteki/SoftwarePWM.d \
./Biblioteki/UART_obsluga.d 


# Each subdirectory must supply rules for building sources it contributes
Biblioteki/%.o: ../Biblioteki/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


