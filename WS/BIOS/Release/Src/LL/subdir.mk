################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LL/sys_core.c \
../Src/LL/sys_dmac.c \
../Src/LL/sys_gpio.c \
../Src/LL/sys_i2cs.c \
../Src/LL/sys_iopc.c \
../Src/LL/sys_mon.c \
../Src/LL/sys_spim.c \
../Src/LL/sys_sysc.c 

OBJS += \
./Src/LL/sys_core.o \
./Src/LL/sys_dmac.o \
./Src/LL/sys_gpio.o \
./Src/LL/sys_i2cs.o \
./Src/LL/sys_iopc.o \
./Src/LL/sys_mon.o \
./Src/LL/sys_spim.o \
./Src/LL/sys_sysc.o 

C_DEPS += \
./Src/LL/sys_core.d \
./Src/LL/sys_dmac.d \
./Src/LL/sys_gpio.d \
./Src/LL/sys_i2cs.d \
./Src/LL/sys_iopc.d \
./Src/LL/sys_mon.d \
./Src/LL/sys_spim.d \
./Src/LL/sys_sysc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/LL/%.o: ../Src/LL/%.c Src/LL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mtune=size -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\TRAP" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\UTIL" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\LL" -std=gnu11 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


