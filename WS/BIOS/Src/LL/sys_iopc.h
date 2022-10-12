//##############################################################################
//
//	CRS32V CORE
//
//	Modules Name	: sys_iopc.h
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
//##############################################################################


#ifndef		__SYS_IOPC_H__
#define		__SYS_IOPC_H__

#include	<global_include.h>


typedef	struct	{

	uint32_t	int_msk;		// 0x00	Interrupt Mask
	uint32_t	int_src;		// 0x01	Interrupt Source
	uint32_t	int_mrs;		// 0x02	Mirrored Interrupt Source
	uint32_t	st;			// 0x03	Status
	uint32_t	ctrl_st;		// 0x04 Control Static
	uint32_t	ctrl_ac;		// 0x05	Control Auto Clear
	uint32_t	dmy0[10];		// ~

	uint32_t	hintn_o;		// 0x10	HINTN O  control 
	uint32_t	hintn_oe;		// 0x11 HINTN OE control
	uint32_t	io_drv_strength;	// 0x12 Driving Strength
	uint32_t	io_mux_ctrl;		// 0x13	IO  MUX control
	uint32_t	dbg_mux_ctrl;		// 0x14	DBG MUX control
	uint32_t	dmy1[11];		// ~ 

} struct_sys_iopc;

#define		sIOPC		( * ( (volatile struct_sys_iopc *) BASE_BADR_IP_IOPC	)  )


extern	__att_noinline__	void	set_hintn ( uint8_t wd ) ;


#endif	//	__SYS_IOPC_H__
