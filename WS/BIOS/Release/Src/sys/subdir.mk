################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/sys/sys_core.c \
../Src/sys/sys_dmac.c \
../Src/sys/sys_gpio.c \
../Src/sys/sys_i2cs.c \
../Src/sys/sys_iopc.c \
../Src/sys/sys_mon.c \
../Src/sys/sys_spim.c \
../Src/sys/sys_sysc.c 

OBJS += \
./Src/sys/sys_core.o \
./Src/sys/sys_dmac.o \
./Src/sys/sys_gpio.o \
./Src/sys/sys_i2cs.o \
./Src/sys/sys_iopc.o \
./Src/sys/sys_mon.o \
./Src/sys/sys_spim.o \
./Src/sys/sys_sysc.o 

C_DEPS += \
./Src/sys/sys_core.d \
./Src/sys/sys_dmac.d \
./Src/sys/sys_gpio.d \
./Src/sys/sys_i2cs.d \
./Src/sys/sys_iopc.d \
./Src/sys/sys_mon.d \
./Src/sys/sys_spim.d \
./Src/sys/sys_sysc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sys/%.o: ../Src/sys/%.c Src/sys/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mtune=size -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\TRAP" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\UTIL" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\sys" -std=gnu11 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


