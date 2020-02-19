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
Pierwszy_dioda.lss \

FLASH_IMAGE += \
Pierwszy_dioda.hex \

EEPROM_IMAGE += \
Pierwszy_dioda.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Pierwszy_dioda.elf secondary-outputs

# Tool invocations
Pierwszy_dioda.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Pierwszy_dioda.map -mmcu=atmega328p -o "Pierwszy_dioda.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Pierwszy_dioda.lss: Pierwszy_dioda.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Pierwszy_dioda.elf  >"Pierwszy_dioda.lss"
	@echo 'Finished building: $@'
	@echo ' '

Pierwszy_dioda.hex: Pierwszy_dioda.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Pierwszy_dioda.elf  "Pierwszy_dioda.hex"
	@echo 'Finished building: $@'
	@echo ' '

Pierwszy_dioda.eep: Pierwszy_dioda.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Pierwszy_dioda.elf  "Pierwszy_dioda.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Pierwszy_dioda.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Pierwszy_dioda.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Pierwszy_dioda.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
