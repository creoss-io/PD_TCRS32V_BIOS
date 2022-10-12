//##############################################################################
//
//	CRS32V System Configuration
//
//	Modules Name	: crs32v_sys_config.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V System Configuration
//
//----------------------------------------------------------------------
//	[Revision History]
//
//		[V0.7.0]	: 2022.05.26, Steve Yun
//			- changed name : str -> crs
//
//		[V0.1.0]	: 2021.04.29, Steve Yun
//			- added custom address for CSR
//
//		[V0.0.1]	: 2020.12.22, Steve Yun
//			- first draft
//
//##############################################################################



#include	<global_include.h>

//#define	BUILD4SIM



//======================================================================
// PM/DM address
//======================================================================
#define	PM_START_BADR					0x00000000
#define	DM_START_BADR					0x40000000
#define	DM_END_BADR						0x40003fff
#define	DM_STACK_START_BADR				0x40003000
#define	DM_STACK_END_BADR				0x40003ffc

//======================================================================
// Peripheral address
//======================================================================
#define OUTPORT							0xF0000000

#define	LAMBDA_SPB_GPIO_BASE			0x80300000
	#define	LAMBDA_SPB_GPIO_GPO_A		LAMBDA_SPB_GPIO_BASE + 4 * (0x20 + 0)
	#define	LAMBDA_SPB_GPIO_GPOE_A		LAMBDA_SPB_GPIO_BASE + 4 * (0x30 + 0)

#define LAMBDA_SPB_UART_BASE			0x81030000
	#define	LAMBDA_SPB_UART_INT_MSK		LAMBDA_SPB_UART_BASE + 4 * (0x00 + 0)
	#define	LAMBDA_SPB_UART_INT_SRC		LAMBDA_SPB_UART_BASE + 4 * (0x00 + 1)
	#define	LAMBDA_SPB_UART_INT_MRS		LAMBDA_SPB_UART_BASE + 4 * (0x00 + 2)
	#define	LAMBDA_SPB_UART_STR		LAMBDA_SPB_UART_BASE + 4 * (0x00 + 3)
	#define	LAMBDA_SPB_UART_CST		LAMBDA_SPB_UART_BASE + 4 * (0x00 + 4)
	#define	LAMBDA_SPB_UART_CAC		LAMBDA_SPB_UART_BASE + 4 * (0x00 + 5)
	#define	LAMBDA_SPB_UART_FLOW		LAMBDA_SPB_UART_BASE + 4 * (0x00 + 6)

	#define	LAMBDA_SPB_UART_TRX_BUF0	LAMBDA_SPB_UART_BASE + 4 * (0x20 + 0)
	#define	LAMBDA_SPB_UART_TRX_BUF1	LAMBDA_SPB_UART_BASE + 4 * (0x20 + 1)
	#define	LAMBDA_SPB_UART_TRX_BUF2	LAMBDA_SPB_UART_BASE + 4 * (0x20 + 2)
	#define	LAMBDA_SPB_UART_TRX_BUF3	LAMBDA_SPB_UART_BASE + 4 * (0x20 + 3)

#define LAMBDA_SPB_EINT_BASE			0x810D2000
	#define LAMBDA_SPB_EINT_BASE		0x810D2000
	#define	LAMBDA_SPB_EINT_INT_MSK		0x810D2000
	#define	LAMBDA_SPB_EINT_INT_SRC		0x810D2004
	#define	LAMBDA_SPB_EINT_INT_MRS		0x810D2008
	#define	LAMBDA_SPB_EINT_STR		0x810D200C
	#define	LAMBDA_SPB_EINT_CST		0x810D2010
	#define	LAMBDA_SPB_EINT_CAC		0x810D2014





