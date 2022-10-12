//##############################################################################
//
//	CRS32V SYSC
//
//	Modules Name	: sys_sysc.h
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


#ifndef		__SYS_SYSC_H__
#define		__SYS_SYSC_H__

#include	<global_include.h>

#define		SYSC_SR_PAD1_BY_MB	(0x0<<0)
#define		SYSC_SR_PAD1_BY_PB	(0x1<<0)
#define		SYSC_SR_PAD2_BY_PC	(0x0<<1)
#define		SYSC_SR_PAD2_BY_MC	(0x1<<1)

/******************************************************************************
 * 	Type Define
 *****************************************************************************/

typedef volatile struct {

	//------------------------------------------------------------
	uint32_t		int_msk;	// 0x00
	uint32_t		int_src;        // 0x01
	uint32_t		int_mrs;        // 0x02
	uint32_t		st;		// 0x03
	uint32_t		ctrl_st;	// 0x04
	uint32_t		ctrl_ac;	// 0x05	
	uint32_t		dmy1[10];	// 

} struct_sysc;

#define sSYSC		( *((volatile struct_sysc*) BASE_BADR_IP_SYSC) )



#endif	//	__SYS_SYSC_H__
