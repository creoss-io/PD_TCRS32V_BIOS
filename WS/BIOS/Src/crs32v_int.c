//##############################################################################
//
//	CRS32V Interrupt
//
//	Modules Name	: crs32v_int.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V Interrupt
//
//----------------------------------------------------------------------
//	[Revision History]
//
//		[V0.7.0]	: 2022.05.26, Steve Yun
//			- changed name : str -> crs
//
//		[V0.5.0]	: 2021.05.11, Steve Yun
//			- removed mtra, mtpc
//			- added mtsf
//
//		[V0.1.1]	: 2021.05.03, Steve Yun
//			- added mtpc, mtra
//
//		[V0.0.1]	: 2021.04.26, Steve Yun
//			- first draft
//
//##############################################################################


#include	<global_include.h>


//=====================================================================
// common
//=====================================================================
// check interrupt
void	crs32v_int_check()
{
	//	print_str("\tMEPC      = ");	print_hex(csr_read(mepc), 8);		print_str("\n");
	//	print_str("\tMTSF      = ");	print_hex(csr_read(0xbd8), 8);		print_str("\n");
	//	print_str("\tMSTATUS   = ");	print_hex(csr_read(mstatus), 8);	print_str("\n");
	//	print_str("\tMIE       = ");	print_hex(csr_read(mie), 8);		print_str("\n");
	//	print_str("\tMIP       = ");	print_hex(csr_read(mip), 8);		print_str("\n");
}

// check mtsf
void	crs32v_int_check_mtsf()
{
	unsigned int	csr_mtsf;

	// read CSR.mtsf
	csr_mtsf = csr_read(0xbd8);

	// check if there is ignored exception
	if ((csr_mtsf & 0x2)==0x2){
		//	print_str("\tException is ignored due to cause = ");	print_hex((csr_mtsf>>26), 8);		print_str("\n");
	}
}




//=====================================================================
// Interrupt Service Routine
//=====================================================================

// Software interrupt
void	crs32v_trap_msi()
{
	// put user routine here
}

// Timer interrupt
void	crs32v_trap_mti()
{
	// put user routine here
}

// External interrupt
void	crs32v_trap_mei()
{
	char	t[2];

	set_mem(LAMBDA_SPB_UART_INT_MSK, 0x3f);

	//	print_str("External interrupt detected !!!\n");
	//	print_str("Received UART data = ");
	t[0] = (char)(get_mem(LAMBDA_SPB_UART_TRX_BUF0));
	t[1] = '\0';
	//	print_str(t);
	//	print_str("\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_UART_CAC, 0x8);				// RX_BUF_CLR
	set_mem(LAMBDA_SPB_UART_INT_SRC, 0);
	set_mem(LAMBDA_SPB_UART_INT_MSK, 0x3e);
}

// Fast interrupt 00
void	crs32v_trap_mfi_00()
{
	//	print_str("Fast interrupt 00 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0001);
}

// Fast interrupt 01
void	crs32v_trap_mfi_01()
{
	//	print_str("Fast interrupt 01 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0002);
}

// Fast interrupt 02
void	crs32v_trap_mfi_02()
{
	//	print_str("Fast interrupt 02 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0004);
}

// Fast interrupt 03
void	crs32v_trap_mfi_03()
{
	//	print_str("Fast interrupt 03 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0008);
}

// Fast interrupt 04
void	crs32v_trap_mfi_04()
{
	//	print_str("Fast interrupt 04 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0010);
}

// Fast interrupt 05
void	crs32v_trap_mfi_05()
{
	//	print_str("Fast interrupt 05 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0020);
}

// Fast interrupt 06
void	crs32v_trap_mfi_06()
{
	//	print_str("Fast interrupt 06 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	//set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0040);
	set_mem(LAMBDA_SPB_UART_INT_SRC, 0x0000);
}

// Fast interrupt 07
void	crs32v_trap_mfi_07()
{
	//	print_str("Fast interrupt 07 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0080);
}

// Fast interrupt 08
void	crs32v_trap_mfi_08()
{
	//	print_str("Fast interrupt 08 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0100);
}

// Fast interrupt 09
void	crs32v_trap_mfi_09()
{
	//	print_str("Fast interrupt 09 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0200);
}

// Fast interrupt 10
void	crs32v_trap_mfi_10()
{
	//	print_str("Fast interrupt 10 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0400);
}

// Fast interrupt 11
void	crs32v_trap_mfi_11()
{
	//	print_str("Fast interrupt 11 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x0800);

	int_srv_i2cs ( );
}

// Fast interrupt 12
void	crs32v_trap_mfi_12()
{
	//	print_str("Fast interrupt 12 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x1000);
}

// Fast interrupt 13
void	crs32v_trap_mfi_13()
{
	//	print_str("Fast interrupt 13 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x2000);
}

// Fast interrupt 14
void	crs32v_trap_mfi_14()
{
	//	print_str("Fast interrupt 14 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x4000);
}

// Fast interrupt 15
void	crs32v_trap_mfi_15()
{
	//	print_str("Fast interrupt 15 detected !!!\n");
	crs32v_int_check();
	crs32v_int_check_mtsf();
	set_mem(LAMBDA_SPB_EINT_INT_MRS, 0x8000);
}
