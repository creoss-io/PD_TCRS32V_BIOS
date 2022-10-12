################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CRT0_LD_TRAP_CSR/CSR/crs32v_csr.c 

OBJS += \
./CRT0_LD_TRAP_CSR/CSR/crs32v_csr.o 

C_DEPS += \
./CRT0_LD_TRAP_CSR/CSR/crs32v_csr.d 


# Each subdirectory must supply rules for building sources it contributes
CRT0_LD_TRAP_CSR/CSR/%.o: ../CRT0_LD_TRAP_CSR/CSR/%.c CRT0_LD_TRAP_CSR/CSR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mtune=size -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\CRT0_LD_TRAP_CSR\CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\CRT0_LD_TRAP_CSR\TRAP" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\CRT0_LD_TRAP_CSR" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\UTIL" -std=gnu11 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


