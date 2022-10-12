//##############################################################################
//
//	CRS32V Trap Handler for Exception
//
//	Modules Name	: crs32v_trap_handler_exc.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- Exception Cause : CSR.mcause[5:0]
//		- before using ECALL/EBREAK, CSR.mepc should be pushed by user
//		- after return, pushed CSR.mepc should be popped by user
//
//----------------------------------------------------------------------
//	[Revision History]
//
//		[V0.7.0]	: 2022.05.26, Steve Yun
//			- changed name : str -> crs
//
//		[V0.0.1]	: 2021.04.30, Steve Yun
//			- first draft
//
//##############################################################################



#include	<global_include.h>

// exception handler
void	_trap_handler_exc()
{
	unsigned char	led_dir;
	unsigned int	led_data;
	unsigned int	exc_mepc_buf;
	unsigned int	exc_mcause_buf;
	unsigned int	exc_mtsf_buf;
	unsigned int	unlimited_loop = 0;

	// push CSR.mepc
	exc_mepc_buf = csr_read(mepc);		// push for nested exception

	// read CSR.mcause
	exc_mcause_buf = csr_read(mcause);

	// read CSR.mtsf
	exc_mtsf_buf = csr_read(0xbd8);

	// parsing
	if (exc_mcause_buf==EXC_CAUSE_ILLEGAL_INSN) {
		print_str("Illegal instruction detected!!!\n");
		print_str("\tINSTRUCTION = ");	print_hex(csr_read(mtval), 8);	print_str("\n");	// instruction value
		unlimited_loop = 1;
	}
	else if (exc_mcause_buf==EXC_CAUSE_BREAKPOINT) {
		print_str("EBREAK instruction detected!!!\n");
		print_str("\tUser should program crs32v_trap_handler_exc.c!!!\n");
		print_str("\tbefore using ECALL/EBREAK, CSR.mepc should be pushed by user!!!\n");
		print_str("\tafter return, pushed CSR.mepc should be popped by user!!!\n");

		unlimited_loop = 0;
	}
	else if (exc_mcause_buf==EXC_CAUSE_ECALL_MMODE) {
		print_str("ECALL instruction detected!!!\n");
		print_str("\tUser should program crs32v_trap_handler_exc.c!!!\n");
		print_str("\tbefore using ECALL/EBREAK, CSR.mepc should be pushed by user!!!\n");
		print_str("\tafter return, pushed CSR.mepc should be popped by user!!!\n");

		unlimited_loop = 0;
	}
	else if (exc_mcause_buf==EXC_CAUSE_SP_OV_FLOW) {
		print_str("Stack overflowed!!!\n");
		// TODO : need to print the accessed address
		unlimited_loop = 1;
	}
	else if (exc_mcause_buf==EXC_CAUSE_SP_UD_FLOW) {
		print_str("Stack underflowed!!!\n");
		// TODO : need to print the accessed address
		unlimited_loop = 1;
	}
	else if (exc_mcause_buf==EXC_CAUSE_SP_CORRUPT) {
		print_str("Stack corrupted!!!\n");
		// TODO : need to print the accessed address
		unlimited_loop = 1;
	}
	else if (exc_mcause_buf==EXC_CAUSE_DIV_BY_ZERO) {
		print_str("DIVIDE_BY_ZERO detected!!!\n");
		unlimited_loop = 1;
	}

	// exception information display
	print_str("\tMEPC      = ");	print_hex(exc_mepc_buf, 8);		print_str("\n");
	print_str("\tMTSF      = ");	print_hex(exc_mtsf_buf, 8);		print_str("\n");

	// unlimited loop
	led_dir = 1;
	led_data = 0x0001;

	if (unlimited_loop){
		print_str("\tMSCARTCH  = ");	print_hex(csr_read(mscratch), 8);		print_str("\n");
		print_str("CPU shall stop here!!!\n");
	}

	while(unlimited_loop)
	{
		if (led_dir==1){
			led_data = led_data << 1;
		}
		else {
			led_data = led_data >> 1;
		}

		if (led_data==0x0001){
			led_dir = 1;
		}
		else if (led_data==0x8000){
			led_data = 0xffff8000;
			led_dir = 0;
		}

		set_mem(LAMBDA_SPB_GPIO_GPO_A, ~led_data);
		basic_delay(600000);
	}

	// pop CSR.mepc
	csr_write(mepc, exc_mepc_buf);
}
