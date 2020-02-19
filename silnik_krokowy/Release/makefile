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
silnik_krokowy.lss \

FLASH_IMAGE += \
silnik_krokowy.hex \

EEPROM_IMAGE += \
silnik_krokowy.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: silnik_krokowy.elf secondary-outputs

# Tool invocations
silnik_krokowy.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,silnik_krokowy.map -mmcu=atmega328p -o "silnik_krokowy.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

silnik_krokowy.lss: silnik_krokowy.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S silnik_krokowy.elf  >"silnik_krokowy.lss"
	@echo 'Finished building: $@'
	@echo ' '

silnik_krokowy.hex: silnik_krokowy.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex silnik_krokowy.elf  "silnik_krokowy.hex"
	@echo 'Finished building: $@'
	@echo ' '

silnik_krokowy.eep: silnik_krokowy.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex silnik_krokowy.elf  "silnik_krokowy.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: silnik_krokowy.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p silnik_krokowy.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) silnik_krokowy.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
