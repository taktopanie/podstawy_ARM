################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include INT/subdir.mk
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
EEPROM_ZAPIS_ZMIENNYCH.lss \

FLASH_IMAGE += \
EEPROM_ZAPIS_ZMIENNYCH.hex \

EEPROM_IMAGE += \
EEPROM_ZAPIS_ZMIENNYCH.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: EEPROM_ZAPIS_ZMIENNYCH.elf secondary-outputs

# Tool invocations
EEPROM_ZAPIS_ZMIENNYCH.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,EEPROM_ZAPIS_ZMIENNYCH.map -mmcu=atmega328p -o "EEPROM_ZAPIS_ZMIENNYCH.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

EEPROM_ZAPIS_ZMIENNYCH.lss: EEPROM_ZAPIS_ZMIENNYCH.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S EEPROM_ZAPIS_ZMIENNYCH.elf  >"EEPROM_ZAPIS_ZMIENNYCH.lss"
	@echo 'Finished building: $@'
	@echo ' '

EEPROM_ZAPIS_ZMIENNYCH.hex: EEPROM_ZAPIS_ZMIENNYCH.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex EEPROM_ZAPIS_ZMIENNYCH.elf  "EEPROM_ZAPIS_ZMIENNYCH.hex"
	@echo 'Finished building: $@'
	@echo ' '

EEPROM_ZAPIS_ZMIENNYCH.eep: EEPROM_ZAPIS_ZMIENNYCH.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex EEPROM_ZAPIS_ZMIENNYCH.elf  "EEPROM_ZAPIS_ZMIENNYCH.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: EEPROM_ZAPIS_ZMIENNYCH.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p EEPROM_ZAPIS_ZMIENNYCH.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) EEPROM_ZAPIS_ZMIENNYCH.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
