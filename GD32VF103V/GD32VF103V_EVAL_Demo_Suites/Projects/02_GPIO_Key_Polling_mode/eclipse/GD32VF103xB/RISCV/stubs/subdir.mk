################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/_exit.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/close.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/fstat.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/isatty.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/lseek.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/read.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/sbrk.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/write.c \
E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/write_hex.c 

OBJS += \
./RISCV/stubs/_exit.o \
./RISCV/stubs/close.o \
./RISCV/stubs/fstat.o \
./RISCV/stubs/isatty.o \
./RISCV/stubs/lseek.o \
./RISCV/stubs/read.o \
./RISCV/stubs/sbrk.o \
./RISCV/stubs/write.o \
./RISCV/stubs/write_hex.o 

C_DEPS += \
./RISCV/stubs/_exit.d \
./RISCV/stubs/close.d \
./RISCV/stubs/fstat.d \
./RISCV/stubs/isatty.d \
./RISCV/stubs/lseek.d \
./RISCV/stubs/read.d \
./RISCV/stubs/sbrk.d \
./RISCV/stubs/write.d \
./RISCV/stubs/write_hex.d 


# Each subdirectory must supply rules for building sources it contributes
RISCV/stubs/_exit.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/_exit.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/stubs/close.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/close.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/stubs/fstat.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/fstat.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/stubs/isatty.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/isatty.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/stubs/lseek.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/lseek.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/stubs/read.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/read.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/stubs/sbrk.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/sbrk.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/stubs/write.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/write.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/stubs/write_hex.o: E:/Google_download/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Demo_Suites_V1.0.0/GD32VF103_Firmware_Library/RISCV/stubs/write_hex.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_STDPERIPH_DRIVER -DGD32VF103V_EVAL -I../../../../Utilities -I../../ -I../../../../../GD32VF103_Firmware_Library/RISCV/env_Eclipse -I../../../../../GD32VF103_Firmware_Library/RISCV/drivers -I../../../../../GD32VF103_Firmware_Library/RISCV/stubs -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral/Include -I../../../../../GD32VF103_Firmware_Library/GD32VF103_standard_peripheral -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


