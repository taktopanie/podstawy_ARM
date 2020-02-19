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
Zegarek+LCD.lss \

FLASH_IMAGE += \
Zegarek+LCD.hex \

EEPROM_IMAGE += \
Zegarek+LCD.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Zegarek+LCD.elf secondary-outputs

# Tool invocations
Zegarek+LCD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Zegarek+LCD.map -L"D:\Projekty\MOJE BIBLIOTEKI" -mmcu=atmega328p -o "Zegarek+LCD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Zegarek+LCD.lss: Zegarek+LCD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Zegarek+LCD.elf  >"Zegarek+LCD.lss"
	@echo 'Finished building: $@'
	@echo ' '

Zegarek+LCD.hex: Zegarek+LCD.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Zegarek+LCD.elf  "Zegarek+LCD.hex"
	@echo 'Finished building: $@'
	@echo ' '

Zegarek+LCD.eep: Zegarek+LCD.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Zegarek+LCD.elf  "Zegarek+LCD.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Zegarek+LCD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Zegarek+LCD.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Zegarek+LCD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
