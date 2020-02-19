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
WYSWIETLACZ_NUMERYCZNY.lss \

FLASH_IMAGE += \
WYSWIETLACZ_NUMERYCZNY.hex \

EEPROM_IMAGE += \
WYSWIETLACZ_NUMERYCZNY.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: WYSWIETLACZ_NUMERYCZNY.elf secondary-outputs

# Tool invocations
WYSWIETLACZ_NUMERYCZNY.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,WYSWIETLACZ_NUMERYCZNY.map -mmcu=atmega328p -o "WYSWIETLACZ_NUMERYCZNY.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

WYSWIETLACZ_NUMERYCZNY.lss: WYSWIETLACZ_NUMERYCZNY.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S WYSWIETLACZ_NUMERYCZNY.elf  >"WYSWIETLACZ_NUMERYCZNY.lss"
	@echo 'Finished building: $@'
	@echo ' '

WYSWIETLACZ_NUMERYCZNY.hex: WYSWIETLACZ_NUMERYCZNY.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex WYSWIETLACZ_NUMERYCZNY.elf  "WYSWIETLACZ_NUMERYCZNY.hex"
	@echo 'Finished building: $@'
	@echo ' '

WYSWIETLACZ_NUMERYCZNY.eep: WYSWIETLACZ_NUMERYCZNY.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex WYSWIETLACZ_NUMERYCZNY.elf  "WYSWIETLACZ_NUMERYCZNY.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: WYSWIETLACZ_NUMERYCZNY.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p WYSWIETLACZ_NUMERYCZNY.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) WYSWIETLACZ_NUMERYCZNY.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
