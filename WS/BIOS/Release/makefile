################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/UTIL/subdir.mk
-include Src/LL/subdir.mk
-include Src/CRT0_LD_TRAP_CSR/TRAP/subdir.mk
-include Src/CRT0_LD_TRAP_CSR/CSR/subdir.mk
-include Src/CRT0_LD_TRAP_CSR/subdir.mk
-include Src/subdir.mk
-include Output_FW/subdir.mk
-include Bin_FWGEN/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BIOS
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_LIST += \
BIOS.lst \

SECONDARY_SIZE += \
BIOS.siz \


# All Target
all: main-build

# Main-build Target
main-build: BIOS.elf secondary-outputs

# Tool invocations
BIOS.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mtune=size -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "D:\42__Project__CREOSS__SW\51__Lambda\CPUFW\21__BIOS\WS\BIOS\Src\CRT0_LD_TRAP_CSR\crs32v_crt0_link.ld" -nostartfiles -nodefaultlibs -nostdlib -Xlinker --print-gc-sections -Wl,-Map,"BIOS.map" -Xlinker --cref --specs=nano.specs --specs=nosys.specs -v -o "BIOS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BIOS.lst: BIOS.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --source --all-headers --demangle --disassemble --line-numbers --syms --wide "BIOS.elf" > "BIOS.lst"
	@echo 'Finished building: $@'
	@echo ' '

BIOS.siz: BIOS.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley -x --totals "BIOS.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) BIOS.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build

-include ../makefile.targets
