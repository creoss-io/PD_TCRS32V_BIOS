//##############################################################################
//
//	BIOS HCMD
//
//	Modules Name: bios_hcmd.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- BIOS HCMD 
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//
//##############################################################################

#ifndef		__BIOS_HCMD_H__
#define		__BIOS_HCMD_H__

#include			<global_include.h>

extern	__att_noinline__	void	BIOS_HCMD_CLEAR_INT ( ) ;
extern	__att_noinline__	void	BIOS_HCMD_RUN_CPU ( ) ;
extern	__att_noinline__	void	BIOS_HCMD_ACC_REG   ( ) ;
extern	__att_noinline__	void	BIOS_HCMD_SE        ( ) ;
extern	__att_noinline__	void	BIOS_HCMD_EVAL      ( ) ;

#endif	//	__BIOS_HCMD_H__
