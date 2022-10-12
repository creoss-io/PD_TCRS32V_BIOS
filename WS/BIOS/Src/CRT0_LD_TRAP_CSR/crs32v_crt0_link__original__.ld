/* CRS32V default link */

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv",
	      "elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)


/*----------------------------------------------*/
/* memory definition				*/
/*----------------------------------------------*/
MEMORY
{
	/* program rom : 64KB space */
	iram : ORIGIN = 0x00000000, LENGTH = 0x00010000

	/* data memory : 16KB space */
	dram : ORIGIN = 0x40000000, LENGTH = 0x00004000
}


/*----------------------------------------------*/
/* section definition				*/
/*	- word-aligned				*/
/*----------------------------------------------*/
SECTIONS
{
	/*----------------------------------------------*/
	/* stack start address				*/
	/*	- where stack goes down from		*/
	/*	- highest address in data RAM		*/
	/*----------------------------------------------*/
	PROVIDE(_stack_start = ORIGIN(dram) + LENGTH(dram) - 4);

	/*----------------------------------------------*/
	/* trap vectors					*/
	/*----------------------------------------------*/
	.vectors :
	{
		. = ALIGN(4);
		KEEP(*(.vectors))
	} > iram

	/*----------------------------------------------*/
	/* trap handler & boot-up initialization	*/
	/*----------------------------------------------*/
	.text : {
		. = ALIGN(4);
		_stext = .;
		*(.text)
		_etext  =  .;
		__CTOR_LIST__ = .;
		LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2)
		*(.ctors)
		LONG(0)
		__CTOR_END__ = .;
		__DTOR_LIST__ = .;
		LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2)
		*(.dtors)
		LONG(0)
		__DTOR_END__ = .;
		*(.lit)
		*(.shdata)
		_endtext = .;
	} > iram

	/*----------------------------------------------*/
	/* global constructor/destructor segement	*/
	/*----------------------------------------------*/
	.rodata	:
	{
		. = ALIGN(4);
		*(.rodata);
		*(.rodata.*)
	} > dram

	.data.string :
	{
		*(.data.string)
	} > dram

	.preinit_array :
	{
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > dram
	
	.init_array :
	{
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array ))
		PROVIDE_HIDDEN (__init_array_end = .);
	} > dram
	
	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array ))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > dram

	.shbss :
	{
		. = ALIGN(4);
		*(.shbss)
	} > dram

	.data :
	{
		. = ALIGN(4);
		sdata  =  .;
		_sdata  =  .;
		*(.data .data.* .gnu.linkonce.d.*)
		edata  =  .;
		_edata  =  .;
	} > dram

	.sdata :
	{
		sdata  =  .;
		_sdata  =  .;
		*(.sdata .sdata.* .gnu.linkonce.s.*)
		edata  =  .;
		_edata  =  .;
	} > dram

	.bss :
	{
		. = ALIGN(4);
		_bss_start = .;
		*(.bss .bss.* .sbss .sbss.*)
		*(COMMON)
		_bss_end = .;
	} > dram

	.stab  0 (NOLOAD) :
	{
		[ .stab ]
	}

	.stabstr  0 (NOLOAD) :
	{
		[ .stabstr ]
	}

	.bss :
	{
		. = ALIGN(4);
		_end = .;
	} > dram
}
