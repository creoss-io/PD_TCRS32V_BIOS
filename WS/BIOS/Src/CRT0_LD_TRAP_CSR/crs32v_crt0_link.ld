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
	prom : ORIGIN = 0x00000000, LENGTH = 0x00010000

	/* data memory : 16KB space */
	drom : ORIGIN = 0x810D0000, LENGTH = 0x00001000

	/* data memory : 16KB space */
	dram   : ORIGIN = 0x40001000, LENGTH = 0x00000800
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
	} > prom

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
	} > prom

	/*----------------------------------------------*/
	/* global constructor/destructor segement	*/
	/*----------------------------------------------*/
	.rodata	:
	{
		. = ALIGN(4);
		*(.rodata);
		*(.rodata.*)
	} > drom	/* dram_2 AT > drom 	/*drom*/		/* dram AT > drom	*/


	/* Adjust the address to the start of RAM. */
	. = ORIGIN(dram);		/* bss should be located in SRAM */
					/* for FW, remove this line to locate bss right after rodata */

	



	.bss :
	{
		. = ALIGN(4);
		_bss_start = .;
		*(.bss .bss.* .sbss .sbss.*)
		*(COMMON)
		_bss_end = .;
	} > dram

}
