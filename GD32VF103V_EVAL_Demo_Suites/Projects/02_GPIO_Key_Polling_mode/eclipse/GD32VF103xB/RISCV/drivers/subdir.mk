################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/drivers/n200_func.c 

OBJS += \
./RISCV/drivers/n200_func.o 

C_DEPS += \
./RISCV/drivers/n200_func.d 


# Each subdirectory must supply rules for building sources it contributes
RISCV/drivers/n200_func.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/drivers/n200_func.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


