################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/UTIL/crs32v_print.c \
../Src/UTIL/crs32v_sys_util.c \
../Src/UTIL/printf.c 

OBJS += \
./Src/UTIL/crs32v_print.o \
./Src/UTIL/crs32v_sys_util.o \
./Src/UTIL/printf.o 

C_DEPS += \
./Src/UTIL/crs32v_print.d \
./Src/UTIL/crs32v_sys_util.d \
./Src/UTIL/printf.d 


# Each subdirectory must supply rules for building sources it contributes
Src/UTIL/%.o: ../Src/UTIL/%.c Src/UTIL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mtune=size -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\TRAP" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\UTIL" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\LL" -std=gnu11 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


