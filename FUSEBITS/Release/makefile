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
FUSEBITS.lss \

FLASH_IMAGE += \
FUSEBITS.hex \

EEPROM_IMAGE += \
FUSEBITS.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: FUSEBITS.elf secondary-outputs

# Tool invocations
FUSEBITS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,FUSEBITS.map -mmcu=atmega16 -o "FUSEBITS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

FUSEBITS.lss: FUSEBITS.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S FUSEBITS.elf  >"FUSEBITS.lss"
	@echo 'Finished building: $@'
	@echo ' '

FUSEBITS.hex: FUSEBITS.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex FUSEBITS.elf  "FUSEBITS.hex"
	@echo 'Finished building: $@'
	@echo ' '

FUSEBITS.eep: FUSEBITS.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex FUSEBITS.elf  "FUSEBITS.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: FUSEBITS.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 FUSEBITS.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) FUSEBITS.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
