################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include RISCV/stubs/subdir.mk
-include RISCV/env_Eclipse/subdir.mk
-include RISCV/drivers/subdir.mk
-include GD32VF103_Peripherals/Source/subdir.mk
-include GD32VF103_Peripherals/subdir.mk
-include GD32VF103_EVAL/subdir.mk
-include Application/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
SECONDARY_FLASH += \
GD32VF103V_EVAL.hex \

SECONDARY_LIST += \
GD32VF103V_EVAL.lst \

SECONDARY_SIZE += \
GD32VF103V_EVAL.siz \


# All Target
all: GD32VF103V_EVAL.elf secondary-outputs

# Tool invocations
GD32VF103V_EVAL.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "E:\Google_download\GD32VF103_Demo_Suites_V1.0.0\GD32VF103_Demo_Suites_V1.0.0\GD32VF103_Firmware_Library\RISCV\env_Eclipse\GD32VF103xB.lds" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"GD32VF103V_EVAL.map" --specs=nano.specs -o "GD32VF103V_EVAL.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

GD32VF103V_EVAL.hex: GD32VF103V_EVAL.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "GD32VF103V_EVAL.elf"  "GD32VF103V_EVAL.hex"
	@echo 'Finished building: $@'
	@echo ' '

GD32VF103V_EVAL.lst: GD32VF103V_EVAL.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "GD32VF103V_EVAL.elf" > "GD32VF103V_EVAL.lst"
	@echo 'Finished building: $@'
	@echo ' '

GD32VF103V_EVAL.siz: GD32VF103V_EVAL.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "GD32VF103V_EVAL.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) GD32VF103V_EVAL.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
