//##############################################################################
//
//	CRS32V MONITOR
//
//	Modules Name	: sys_mon.h
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
//		[V0.0.1]	
//
//##############################################################################


#ifndef		__SYS_MON_H__
#define		__SYS_MON_H__

#include	<global_include.h>


//----------------------------------------------------------------------------------------------------
//--	SYSMON Structure
//----------------------------------------------------------------------------------------------------
typedef volatile struct {

	uint16_t			st16[8];		// 0x00	~ 0x0F
	uint16_t			d16[16];		// 0x10 ~ 0x2F

	uint32_t			st32[8];		// 0x30 ~ 0x4F
	uint32_t			d32[16];		// 0x50 ~ 0x8F

	uint16_t			n16;			// 0x90
	uint16_t			m16;			// 0x92
	uint16_t			p16;			// 0x94
	uint16_t			q16;			// 0x96
	uint16_t			nerr16_l;		// 0x98
	uint16_t			nerr16_t;		// 0x9A
	uint16_t			dmy16_10[2];		// 0x9C ~ 0x9F	

	uint32_t			n32;			// 0xA0	
	uint32_t			m32;			// 0xA4	
	uint32_t			p32;			// 0xA8	
	uint32_t			q32;			// 0xAC	
	uint32_t			nerr32_l;		// 0xB0	
	uint32_t			nerr32_t;		// 0xB4	
	uint32_t			dmy32_10[2];		// 0xB8 ~ 0xBF

	uint8_t				func_set_cur_func0;	// 0xC0
	uint8_t				func_clear_all;		// 0xC1
	uint8_t				dmy8_20[14];		// 0xC2 ~ 0xCF

	uint8_t				dmy8_21[0x100-0xD0];	// 0xD0 ~ 0xFF

	//--	String
	char				msg[256];		// 0x100 ~ 0x1FF

	//----------------------------------------
	//--	to be re-organized
	//----------------------------------------

}	struct_sys_mon;


#define		sMON		(*((volatile struct_sys_mon*) (0x80FF0000)))
#define		sMONCLR		(*((volatile struct_sys_mon*) (0x80FE0000)))

//#define	smon(a,b)	{ sMON.a = ((uint32_t) b); }
#define		smon(a,b)	{ sMON.a    = ( (uint32_t) b); }
#define		sclr(a,b)	{ sMONCLR.a = ( (uint32_t) b); }




#endif	//	__SYS_MON_H__
