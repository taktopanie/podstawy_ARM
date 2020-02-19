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
Przekaznik_Bluetooth.lss \

FLASH_IMAGE += \
Przekaznik_Bluetooth.hex \

EEPROM_IMAGE += \
Przekaznik_Bluetooth.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Przekaznik_Bluetooth.elf secondary-outputs

# Tool invocations
Przekaznik_Bluetooth.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Przekaznik_Bluetooth.map -mmcu=atmega328p -o "Przekaznik_Bluetooth.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Przekaznik_Bluetooth.lss: Przekaznik_Bluetooth.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Przekaznik_Bluetooth.elf  >"Przekaznik_Bluetooth.lss"
	@echo 'Finished building: $@'
	@echo ' '

Przekaznik_Bluetooth.hex: Przekaznik_Bluetooth.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Przekaznik_Bluetooth.elf  "Przekaznik_Bluetooth.hex"
	@echo 'Finished building: $@'
	@echo ' '

Przekaznik_Bluetooth.eep: Przekaznik_Bluetooth.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Przekaznik_Bluetooth.elf  "Przekaznik_Bluetooth.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Przekaznik_Bluetooth.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Przekaznik_Bluetooth.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Przekaznik_Bluetooth.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
