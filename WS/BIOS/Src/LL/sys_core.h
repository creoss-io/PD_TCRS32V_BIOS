//##############################################################################
//
//	CRS32V CORE
//
//	Modules Name	: sys_core.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V System Core
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//		[V0.0.1]	: 2021.04.26, Steve Yun
//			- first draft
//
//##############################################################################


#ifndef		__SYS_CORE_H__
#define		__SYS_CORE_H__

#include	<global_include.h>

//--	Memory Base byte-address
#define		BASE_BADR_MA		0x40000000
#define		BASE_BADR_MB		0x50000000
#define		BASE_BADR_MC		0x60000000
#define		BASE_BADR_MD		0x70000000
#define		BASE_BADR_AHB1		0x80000000
#define		BASE_BADR_AHB2		0x81000000

//--	IP Base byte-address
#define		BASE_BADR_IP_PMU	0x80000000
#define		BASE_BADR_IP_SYSC	0x80100000
#define		BASE_BADR_IP_EFMC	0x80200000
#define		BASE_BADR_IP_GPIO	0x80300000

#define		BASE_BADR_IP_MISC	0x81000000
#define		BASE_BADR_IP_DMAC	0x81010000
#define		BASE_BADR_IP_IOPC	0x81020000
#define		BASE_BADR_IP_UART	0x81030000
#define		BASE_BADR_IP_WDTC	0x81040000
#define		BASE_BADR_IP_TMR0	0x81050000
#define		BASE_BADR_IP_TMR1	0x81060000
#define		BASE_BADR_IP_I2CM	0x81070000
#define		BASE_BADR_IP_I2CS	0x81080000
#define		BASE_BADR_IP_SPIM	0x81090000
#define		BASE_BADR_IP_SPIS	0x810A0000
#define		BASE_BADR_IP_USBFS	0x810B0000
#define		BASE_BADR_IP_OTPC	0x810C0000
#define		BASE_BADR_IP_ROM	0x810D0000
#define		BASE_BADR_IP_RSV0	0x810E0000
#define		BASE_BADR_IP_DBGMUXC	0x810F0000
#define		BASE_BADR_IP_RSV1	0x81100000
#define		BASE_BADR_IP_AFEC	0x81110000



//--------------------------------------------------------------------------------
//--	Interrupt ID
//--------------------------------------------------------------------------------
#define		INT_ID_PMU		0
#define		INT_ID_ESFM		1
#define		INT_ID_GPIO		2
#define		INT_ID_Rsvd_3		3
#define		INT_ID_MISC		4
#define		INT_ID_DMAC		5
#define		INT_ID_UART		6
#define		INT_ID_WDTC		7
#define		INT_ID_TIMER0		8
#define		INT_ID_TIMER1		9
#define		INT_ID_I2CM		10
#define		INT_ID_I2CS		11
#define		INT_ID_SPIM		12
#define		INT_ID_SPIS		13
#define		INT_ID_USBD		14
#define		INT_ID_OTPC		15


typedef void		(*FP_VOID)(void);

//--------------------------------------------------------------------------------
//--	JUMP TO FW
//--------------------------------------------------------------------------------
extern	void	__att_noinline__	jump_to_fw       ( uint32_t badd_tgt_fw    ) ;
extern	void	__att_noinline__	jump_to_app_core ( uint32_t target_address ) ;


#endif	//	__SYS_CORE_H__
