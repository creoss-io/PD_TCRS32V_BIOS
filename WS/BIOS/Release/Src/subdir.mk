################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bios_bu.c \
../Src/bios_hcmd.c \
../Src/crs32v_int.c \
../Src/global_variable.c \
../Src/main.c \
../Src/main_bios.c 

OBJS += \
./Src/bios_bu.o \
./Src/bios_hcmd.o \
./Src/crs32v_int.o \
./Src/global_variable.o \
./Src/main.o \
./Src/main_bios.o 

C_DEPS += \
./Src/bios_bu.d \
./Src/bios_hcmd.d \
./Src/crs32v_int.d \
./Src/global_variable.d \
./Src/main.d \
./Src/main_bios.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mtune=size -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\TRAP" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\UTIL" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\LL" -std=gnu11 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


