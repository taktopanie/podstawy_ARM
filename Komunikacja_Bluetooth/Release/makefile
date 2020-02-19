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
Komunikacja_Bluetooth.lss \

FLASH_IMAGE += \
Komunikacja_Bluetooth.hex \

EEPROM_IMAGE += \
Komunikacja_Bluetooth.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Komunikacja_Bluetooth.elf secondary-outputs

# Tool invocations
Komunikacja_Bluetooth.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Komunikacja_Bluetooth.map -mmcu=atmega16 -o "Komunikacja_Bluetooth.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Komunikacja_Bluetooth.lss: Komunikacja_Bluetooth.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Komunikacja_Bluetooth.elf  >"Komunikacja_Bluetooth.lss"
	@echo 'Finished building: $@'
	@echo ' '

Komunikacja_Bluetooth.hex: Komunikacja_Bluetooth.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Komunikacja_Bluetooth.elf  "Komunikacja_Bluetooth.hex"
	@echo 'Finished building: $@'
	@echo ' '

Komunikacja_Bluetooth.eep: Komunikacja_Bluetooth.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Komunikacja_Bluetooth.elf  "Komunikacja_Bluetooth.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Komunikacja_Bluetooth.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Komunikacja_Bluetooth.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Komunikacja_Bluetooth.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
