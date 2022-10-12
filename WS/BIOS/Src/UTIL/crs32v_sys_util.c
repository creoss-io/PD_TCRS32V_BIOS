//##############################################################################
//
//	CRS32V System Utility
//
//	Modules Name	: crs32v_sys_util.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//----------------------------------------------------------------------
//	[Revision History]
//
//		[V0.7.0]	: 2022.05.26, Steve Yun
//			- changed name : str -> crs
//
//		[V0.0.1]	: 2021.04.12, Steve Yun
//			- first draft
//
//##############################################################################


#include	<global_include.h>

//=====================================================================
// Generals
//=====================================================================
void	basic_delay(unsigned long delay_time)
{
	for (int i=0; i<delay_time; i++) {asm("nop");}
}


void	led_delay()
{
	#ifdef	BUILD4SIM
		for (int i=0; i<60; i++) {asm("nop");}
	#else
		for (int i=0; i<6000000; i++) {asm("nop");}
	#endif
}










//=====================================================================
// Peripherals
//=====================================================================
//---------------------------------------
// GPIO
//---------------------------------------


//---------------------------------------
// UART
//---------------------------------------
void	uart_init()
{
	set_mem(LAMBDA_SPB_UART_INT_SRC	,	0		);		// clear INT_SRC
	set_mem(LAMBDA_SPB_UART_INT_MSK	,	0x300	);		// clear INT_MSK
	set_mem(LAMBDA_SPB_UART_FLOW	,	53		);		// div_sample
	set_mem(LAMBDA_SPB_UART_CST		, 	1		);		// tx_dma_buf_en, wakeup_en, tx_dma_en, parity_odd1_even0, parity_en=0, uart_en=1
}

void	uart_tx_byte(char wdata)
{
	unsigned int	ready=0;

	while (ready==0){
			ready = 0x1 & get_mem(LAMBDA_SPB_UART_STR);
	}

	set_mem(LAMBDA_SPB_UART_TRX_BUF0, (uint32_t)wdata);
}
