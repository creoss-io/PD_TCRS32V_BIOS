//##############################################################################
//
//	CRS32V Trap Handler for Exception
//
//	Modules Name	: crs32v_trap_handler_exc.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- Exception Cause : CSR.mcause[5:0]
//			6'd02 : Illegal instruction
//			6'd03 : EBREAK instruction
//			6'd11 : ECALL instruction
//			6'd24 : Stack overflow		: custom
//			6'd25 : Stack underflow		: custom
//			6'd26 : Stack corruption	: custom
//			6'd27 : divide-by-zero		: custom
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

#ifndef		__CRS32V_TRAP_HANDLER_EXC_H__
#define		__CRS32V_TRAP_HANDLER_EXC_H__


// exception cause
#define	EXC_CAUSE_INSTR_FAULT	01
#define	EXC_CAUSE_ILLEGAL_INSN	02
#define	EXC_CAUSE_BREAKPOINT	03
#define	EXC_CAUSE_LOAD_FAULT	05
#define	EXC_CAUSE_STORE_FAULT	07
#define	EXC_CAUSE_ECALL_UMODE	08
#define	EXC_CAUSE_ECALL_MMODE	11

// exception cause : custom
#define	EXC_CAUSE_SP_OV_FLOW	24	// stack overflow
#define	EXC_CAUSE_SP_UD_FLOW	25	// stack underflow
#define	EXC_CAUSE_SP_CORRUPT	26	// stack corruption
#define	EXC_CAUSE_DIV_BY_ZERO	27	// divide by zero

// functions
void	_trap_handler_exc();			// exception



#endif	//	__CRS32V_TRAP_HANDLER_EXC_H__
