//##############################################################################
//
//	CRS32V Interrupt
//
//	Modules Name	: crs32v_int.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V Interrupt
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//		[V0.0.1]	: 2021.04.26, Steve Yun
//			- first draft
//
//##############################################################################

#ifndef		__CRS32V_IN_H__
#define		__CRS32V_IN_H__

// common
void	crs32v_int_check();
void	crs32v_int_check_mtsf();

// interrupt service routine
void	crs32v_trap_msi();
void	crs32v_trap_mti();
void	crs32v_trap_mei();
void	crs32v_trap_mfi_00();
void	crs32v_trap_mfi_01();
void	crs32v_trap_mfi_02();
void	crs32v_trap_mfi_03();
void	crs32v_trap_mfi_04();
void	crs32v_trap_mfi_05();
void	crs32v_trap_mfi_06();
void	crs32v_trap_mfi_07();
void	crs32v_trap_mfi_08();
void	crs32v_trap_mfi_09();
void	crs32v_trap_mfi_10();
void	crs32v_trap_mfi_11();
void	crs32v_trap_mfi_12();
void	crs32v_trap_mfi_13();
void	crs32v_trap_mfi_14();
void	crs32v_trap_mfi_15();


#endif	//	__CRS32V_IN_H__
