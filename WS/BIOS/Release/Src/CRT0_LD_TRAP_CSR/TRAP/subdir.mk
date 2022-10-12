################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/CRT0_LD_TRAP_CSR/TRAP/crs32v_trap_handler_exc.c \
../Src/CRT0_LD_TRAP_CSR/TRAP/crs32v_trap_handler_irq.c 

OBJS += \
./Src/CRT0_LD_TRAP_CSR/TRAP/crs32v_trap_handler_exc.o \
./Src/CRT0_LD_TRAP_CSR/TRAP/crs32v_trap_handler_irq.o 

C_DEPS += \
./Src/CRT0_LD_TRAP_CSR/TRAP/crs32v_trap_handler_exc.d \
./Src/CRT0_LD_TRAP_CSR/TRAP/crs32v_trap_handler_irq.d 


# Each subdirectory must supply rules for building sources it contributes
Src/CRT0_LD_TRAP_CSR/TRAP/%.o: ../Src/CRT0_LD_TRAP_CSR/TRAP/%.c Src/CRT0_LD_TRAP_CSR/TRAP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mtune=size -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\TRAP" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\UTIL" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\LL" -std=gnu11 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


