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
Wyswietlacz_alfanumeryczny.lss \

FLASH_IMAGE += \
Wyswietlacz_alfanumeryczny.hex \

EEPROM_IMAGE += \
Wyswietlacz_alfanumeryczny.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Wyswietlacz_alfanumeryczny.elf secondary-outputs

# Tool invocations
Wyswietlacz_alfanumeryczny.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Wyswietlacz_alfanumeryczny.map -mmcu=atmega328p -o "Wyswietlacz_alfanumeryczny.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Wyswietlacz_alfanumeryczny.lss: Wyswietlacz_alfanumeryczny.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Wyswietlacz_alfanumeryczny.elf  >"Wyswietlacz_alfanumeryczny.lss"
	@echo 'Finished building: $@'
	@echo ' '

Wyswietlacz_alfanumeryczny.hex: Wyswietlacz_alfanumeryczny.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Wyswietlacz_alfanumeryczny.elf  "Wyswietlacz_alfanumeryczny.hex"
	@echo 'Finished building: $@'
	@echo ' '

Wyswietlacz_alfanumeryczny.eep: Wyswietlacz_alfanumeryczny.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Wyswietlacz_alfanumeryczny.elf  "Wyswietlacz_alfanumeryczny.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Wyswietlacz_alfanumeryczny.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Wyswietlacz_alfanumeryczny.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Wyswietlacz_alfanumeryczny.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
