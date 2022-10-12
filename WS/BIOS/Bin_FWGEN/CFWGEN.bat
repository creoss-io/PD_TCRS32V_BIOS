::====================================================================================================
::==	Clean
::====================================================================================================
if not exist "..\Output_FW\"		mkdir	..\Output_FW
if exist "..\Output_FW\*.txt"		del	..\Output_FW\*.txt
if exist "..\Output_FW\*.hex"		del	..\Output_FW\*.hex
if exist "..\Output_FW\*.hextxt32"	del	..\Output_FW\*.hextxt32
if exist "..\Output_FW\*.zip"		del	..\Output_FW\*.zip
if exist "..\Output_FW\*.7z"		del	..\Output_FW\*.7z


::====================================================================================================
::==	OBJDUMP
::==	OBJCOPY
::====================================================================================================
copy														 						..\Release\BIOS.elf	>	..\Output_FW\BIOS_02_elf.elf

C:\Users\DAN\AppData\Roaming\xPacks\xpack-riscv-none-embed-gcc-10.2.0-1.2\bin\riscv-none-embed-objdump.exe -D -t -T 						..\Release\BIOS.elf	>	..\Output_FW\BIOS_00_objdump_full.txt
C:\Users\DAN\AppData\Roaming\xPacks\xpack-riscv-none-embed-gcc-10.2.0-1.2\bin\riscv-none-embed-objdump.exe -d 							..\Release\BIOS.elf	>	..\Output_FW\BIOS_01_objdump_pm.txt


C:\Users\DAN\AppData\Roaming\xPacks\xpack-riscv-none-embed-gcc-10.2.0-1.2\bin\riscv-none-embed-objcopy.exe -O verilog						..\Release\BIOS.elf		..\Output_FW\BIOS_10_verilog_pdm.hex
C:\Users\DAN\AppData\Roaming\xPacks\xpack-riscv-none-embed-gcc-10.2.0-1.2\bin\riscv-none-embed-objcopy.exe -O verilog -j.text -j.vectors -j.text.* 		..\Release\BIOS.elf 		..\Output_FW\BIOS_11_verilog_pm.hex
C:\Users\DAN\AppData\Roaming\xPacks\xpack-riscv-none-embed-gcc-10.2.0-1.2\bin\riscv-none-embed-objcopy.exe -O verilog -j.data -j.ctor    -jdtor   -j.rodata 	..\Release\BIOS.elf 		..\Output_FW\BIOS_12_verilog_dm.hex


touch	..\Output_FW\BIOS_90_--------------------------------.hex

::====================================================================================================
::==	Source Zip
::====================================================================================================
set TIMEPAD=%TIME: =0%
7z a -r "..\Output_FW\z_src_BIOS_%DATE:~2,2%%DATE:~5,2%%DATE:~8,2%_%TIMEPAD:~0,2%%TIMEPAD:~3,2%%TIMEPAD:~6,2%_".7z   ..\src\*  ..\CRT0_LD_TRAP_CSR ..\.cproject ..\.project
::-xr!*.o



::====================================================================================================
::==	FWGEN
::====================================================================================================
CFWGEN.exe								^
									^
	-op_type		GEN_ROM					^
									^
	-in_name             	"..\Output_FW\BIOS_11_verilog_pm.hex"	^
	-in_format            	IN_FMT_OBJCOPY_O_VERILOG		^
	-in_st_badr            	0x00000000				^
	-in_full_kb         	16 					^
									^
									^
	-out_name            	"..\Output_FW\BIOS_FW_PM.hextxt32"	^
	-out_format          	HEXTXT32  				^
	-out_split_kb        	16					^
	-out_padding_min_nb  	4  					^
	-out_align_nb  		16  					^
	-out_padding_val	0x00					^
	-out_data_sel		FULL_MEM				^
									^
									^
	-log_level		LE_BASIC	 			^
	

CFWGEN.exe								^
									^
	-op_type		GEN_ROM					^
									^
	-in_name             	"..\Output_FW\BIOS_12_verilog_dm.hex"	^
	-in_format            	IN_FMT_OBJCOPY_O_VERILOG		^
	-in_st_badr            	0x810D0000				^
	-in_full_kb         	4    					^
									^
									^
	-out_name            	"..\Output_FW\BIOS_FW_DM.hextxt32"	^
	-out_format          	HEXTXT32  				^
	-out_split_kb        	4					^
	-out_padding_min_nb  	4  					^
	-out_align_nb  		16  					^
	-out_padding_val	0x00					^
	-out_data_sel		FULL_MEM				^
									^
									^
	-log_level		LE_BASIC	 			^
	


CFWGEN.exe								^
									^
	-op_type		GEN_FUNC				^
									^
	-in_name             	"..\Output_FW\BIOS_01_objdump_pm.txt"	^
	-out_name            	"..\Output_FW\BIOS_FW_10_FUNCLIST.txt"	^
									^
	-log_level		LE_BASIC	 			^
	



::	-out_padding_empty_en	PADDING_EN_ENABLE 			^
