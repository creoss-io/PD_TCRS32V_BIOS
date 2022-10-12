//##############################################################################
//
//	global variable
//
//	Modules Name	: global_variable.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//
//----------------------------------------------------------------------
//	[Revision History]
//
//##############################################################################




#include	<global_include.h>



//--------------------------------------------------------------------------------
//--	DMA Mem : HDP
//--------------------------------------------------------------------------------
uint8_t  *	volatile	hwdp8;		// host write data port
uint16_t *	volatile	hwdp16;		
uint32_t *	volatile	hwdp32;		

uint8_t  *	volatile	hrdp8;		// host read data port
uint16_t *	volatile	hrdp16;		
uint32_t *	volatile	hrdp32;		

uint8_t  *	volatile	hwdp8_arg;	// host write data port, argument
uint16_t *	volatile	hwdp16_arg;		
uint32_t *	volatile	hwdp32_arg;		

uint8_t  *	volatile	hrdp8_arg;	// host read data port, argument
uint16_t *	volatile	hrdp16_arg;		
uint32_t *	volatile	hrdp32_arg;		

uint8_t  *	volatile	mem8_fwld_tgt;	// FWLD Target Address
uint16_t *	volatile	mem16_fwld_tgt;		
uint32_t *	volatile	mem32_fwld_tgt;		

//--------------------------------------------------------------------------------
//--	Host Interface Communication
//--------------------------------------------------------------------------------
uint16_t	volatile	hcmd;
uint16_t	volatile	harg;
uint8_t		volatile	hcmd_trig;

uint16_t	volatile	htst;
uint16_t	volatile	haux;

	
//--------------------------------------------------------------------------------
//--	GSS : Global System Structure
//--------------------------------------------------------------------------------
volatile	struct	struct_gss	gss;



