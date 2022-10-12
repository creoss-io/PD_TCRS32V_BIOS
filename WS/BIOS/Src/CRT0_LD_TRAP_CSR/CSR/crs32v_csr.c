//##############################################################################
//
//	CRS32V CSR Access
//
//	Modules Name	: crs32v_csr.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V CSR Access functions
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//		[V0.7.0]	: 2022.05.26, Steve Yun
//			- changed name : str -> crs
//
//		[V0.0.1]	: 2021.04.26, Steve Yun
//			- first draft
//
//##############################################################################



#include	<global_include.h>

//======================================================================
// Functions
//======================================================================

void	csr_check()
{
	print_str("MISA      = ");	print_hex(csr_read(misa), 8);		print_str("\n");
	print_str("MVENDORID = ");	print_hex(csr_read(mvendorid), 8);	print_str("\n");
	print_str("MARCHID   = ");	print_hex(csr_read(marchid), 8);	print_str("\n");
	print_str("MIMPID    = ");	print_hex(csr_read(mimpid), 8);		print_str("\n");
	print_str("MHARTID   = ");	print_hex(csr_read(mhartid), 8);	print_str("\n");
	print_str("MSTATUS   = ");	print_hex(csr_read(mstatus), 8);	print_str("\n");
	print_str("MIE       = ");	print_hex(csr_read(mie), 8);		print_str("\n");
	print_str("MIP       = ");	print_hex(csr_read(mip), 8);		print_str("\n");
}





//======================================================================
// interrupt related
//======================================================================

// fast interrupt
void	csr_int_init_fast_int_vector()
{
	csr_seti(0xBD9, 1);						// mfive
	//csr_seti(CSR_mfive, 1);						// mfive

	csr_write(0xBE0, (PM_START_BADR + BADR_CRT_TRAP_IRQ_00));	// mftvec_00
	csr_write(0xBE1, (PM_START_BADR + BADR_CRT_TRAP_IRQ_01));	// mftvec_01
	csr_write(0xBE2, (PM_START_BADR + BADR_CRT_TRAP_IRQ_02));	// mftvec_02
	csr_write(0xBE3, (PM_START_BADR + BADR_CRT_TRAP_IRQ_03));	// mftvec_03
	csr_write(0xBE4, (PM_START_BADR + BADR_CRT_TRAP_IRQ_04));	// mftvec_04
	csr_write(0xBE5, (PM_START_BADR + BADR_CRT_TRAP_IRQ_05));	// mftvec_05
	csr_write(0xBE6, (PM_START_BADR + BADR_CRT_TRAP_IRQ_06));	// mftvec_06
	csr_write(0xBE7, (PM_START_BADR + BADR_CRT_TRAP_IRQ_07));	// mftvec_07
	csr_write(0xBE8, (PM_START_BADR + BADR_CRT_TRAP_IRQ_08));	// mftvec_08
	csr_write(0xBE9, (PM_START_BADR + BADR_CRT_TRAP_IRQ_09));	// mftvec_09
	csr_write(0xBEA, (PM_START_BADR + BADR_CRT_TRAP_IRQ_10));	// mftvec_10
	csr_write(0xBEB, (PM_START_BADR + BADR_CRT_TRAP_IRQ_11));	// mftvec_11
	csr_write(0xBEC, (PM_START_BADR + BADR_CRT_TRAP_IRQ_12));	// mftvec_12
	csr_write(0xBED, (PM_START_BADR + BADR_CRT_TRAP_IRQ_13));	// mftvec_13
	csr_write(0xBEE, (PM_START_BADR + BADR_CRT_TRAP_IRQ_14));	// mftvec_14
	csr_write(0xBEF, (PM_START_BADR + BADR_CRT_TRAP_IRQ_15));	// mftvec_15
}





//======================================================================
// exception related
//======================================================================

// stack corruption
void	csr_exc_init_stack_check()
{
	unsigned long	csr_mstack_ctrl;

	// DM start/end address
	csr_write(0xBC3, DM_START_BADR);
	csr_write(0xBC4, DM_END_BADR);

	// stack start/end address
	csr_write(0xBC1, DM_STACK_START_BADR);
	csr_write(0xBC2, DM_STACK_END_BADR);

	// CSR.mstack_ctrl
	csr_mstack_ctrl = csr_read(0xBC0);
	csr_mstack_ctrl = csr_mstack_ctrl | 0x80;				// corruption check enable
	csr_write(0xBC0, csr_mstack_ctrl);

	#ifndef	BUILD4SIM
		print_str("CSR.mstack_ctrl = ");	print_hex(csr_read(0xBC0), 8);			print_str("\n");
		print_str("CSR.mstack_sbadr = ");	print_hex(csr_read(0xBC1), 8);			print_str("\n");
		print_str("CSR.mstack_ebadr = ");	print_hex(csr_read(0xBC2), 8);			print_str("\n");
	#endif
}
