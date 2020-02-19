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
Dioda_test.lss \

FLASH_IMAGE += \
Dioda_test.hex \

EEPROM_IMAGE += \
Dioda_test.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Dioda_test.elf secondary-outputs

# Tool invocations
Dioda_test.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Dioda_test.map -mmcu=atmega328p -o "Dioda_test.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Dioda_test.lss: Dioda_test.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Dioda_test.elf  >"Dioda_test.lss"
	@echo 'Finished building: $@'
	@echo ' '

Dioda_test.hex: Dioda_test.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Dioda_test.elf  "Dioda_test.hex"
	@echo 'Finished building: $@'
	@echo ' '

Dioda_test.eep: Dioda_test.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Dioda_test.elf  "Dioda_test.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Dioda_test.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Dioda_test.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Dioda_test.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
