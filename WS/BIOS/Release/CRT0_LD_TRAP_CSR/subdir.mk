################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../CRT0_LD_TRAP_CSR/crs32v_crt0.S 

OBJS += \
./CRT0_LD_TRAP_CSR/crs32v_crt0.o 

S_UPPER_DEPS += \
./CRT0_LD_TRAP_CSR/crs32v_crt0.d 


# Each subdirectory must supply rules for building sources it contributes
CRT0_LD_TRAP_CSR/%.o: ../CRT0_LD_TRAP_CSR/%.S CRT0_LD_TRAP_CSR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mtune=size -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -x assembler-with-cpp -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\UTIL" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\UTIL" -I"D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


