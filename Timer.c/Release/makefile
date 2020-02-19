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
Timer.c.lss \

FLASH_IMAGE += \
Timer.c.hex \

EEPROM_IMAGE += \
Timer.c.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Timer.c.elf secondary-outputs

# Tool invocations
Timer.c.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Timer.c.map -mmcu=atmega328p -o "Timer.c.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Timer.c.lss: Timer.c.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Timer.c.elf  >"Timer.c.lss"
	@echo 'Finished building: $@'
	@echo ' '

Timer.c.hex: Timer.c.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Timer.c.elf  "Timer.c.hex"
	@echo 'Finished building: $@'
	@echo ' '

Timer.c.eep: Timer.c.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Timer.c.elf  "Timer.c.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Timer.c.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Timer.c.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Timer.c.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
