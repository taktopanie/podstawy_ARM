################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Servo+UART.lss \

FLASH_IMAGE += \
Servo+UART.hex \

EEPROM_IMAGE += \
Servo+UART.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Servo+UART.elf secondary-outputs

# Tool invocations
Servo+UART.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Servo+UART.map -mmcu=atmega328p -o "Servo+UART.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Servo+UART.lss: Servo+UART.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Servo+UART.elf  >"Servo+UART.lss"
	@echo 'Finished building: $@'
	@echo ' '

Servo+UART.hex: Servo+UART.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Servo+UART.elf  "Servo+UART.hex"
	@echo 'Finished building: $@'
	@echo ' '

Servo+UART.eep: Servo+UART.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Servo+UART.elf  "Servo+UART.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Servo+UART.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Servo+UART.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Servo+UART.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
