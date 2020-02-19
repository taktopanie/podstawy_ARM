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
Miganie_diodami.lss \

FLASH_IMAGE += \
Miganie_diodami.hex \

EEPROM_IMAGE += \
Miganie_diodami.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Miganie_diodami.elf secondary-outputs

# Tool invocations
Miganie_diodami.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Miganie_diodami.map -mmcu=atmega328p -o "Miganie_diodami.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Miganie_diodami.lss: Miganie_diodami.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Miganie_diodami.elf  >"Miganie_diodami.lss"
	@echo 'Finished building: $@'
	@echo ' '

Miganie_diodami.hex: Miganie_diodami.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Miganie_diodami.elf  "Miganie_diodami.hex"
	@echo 'Finished building: $@'
	@echo ' '

Miganie_diodami.eep: Miganie_diodami.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Miganie_diodami.elf  "Miganie_diodami.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Miganie_diodami.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Miganie_diodami.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Miganie_diodami.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
