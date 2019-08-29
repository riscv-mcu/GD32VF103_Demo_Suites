################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103V_EVAL_Demo_Suites/Projects/01_GPIO_Running_Led/main.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103V_EVAL_Demo_Suites/Projects/01_GPIO_Running_Led/systick.c 

OBJS += \
./Application/main.o \
./Application/systick.o 

C_DEPS += \
./Application/main.d \
./Application/systick.d 


# Each subdirectory must supply rules for building sources it contributes
Application/main.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103V_EVAL_Demo_Suites/Projects/01_GPIO_Running_Led/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/systick.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103V_EVAL_Demo_Suites/Projects/01_GPIO_Running_Led/systick.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


