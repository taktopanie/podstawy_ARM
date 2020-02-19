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
WYSWIETLACZ_DIODOWY.lss \

FLASH_IMAGE += \
WYSWIETLACZ_DIODOWY.hex \

EEPROM_IMAGE += \
WYSWIETLACZ_DIODOWY.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: WYSWIETLACZ_DIODOWY.elf secondary-outputs

# Tool invocations
WYSWIETLACZ_DIODOWY.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,WYSWIETLACZ_DIODOWY.map -mmcu=atmega328p -o "WYSWIETLACZ_DIODOWY.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

WYSWIETLACZ_DIODOWY.lss: WYSWIETLACZ_DIODOWY.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S WYSWIETLACZ_DIODOWY.elf  >"WYSWIETLACZ_DIODOWY.lss"
	@echo 'Finished building: $@'
	@echo ' '

WYSWIETLACZ_DIODOWY.hex: WYSWIETLACZ_DIODOWY.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex WYSWIETLACZ_DIODOWY.elf  "WYSWIETLACZ_DIODOWY.hex"
	@echo 'Finished building: $@'
	@echo ' '

WYSWIETLACZ_DIODOWY.eep: WYSWIETLACZ_DIODOWY.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex WYSWIETLACZ_DIODOWY.elf  "WYSWIETLACZ_DIODOWY.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: WYSWIETLACZ_DIODOWY.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p WYSWIETLACZ_DIODOWY.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) WYSWIETLACZ_DIODOWY.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
