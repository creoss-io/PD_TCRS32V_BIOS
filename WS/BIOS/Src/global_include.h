//##############################################################################
//
//	Global Include
//
//	Modules Name	: global_include.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V Global Include
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//		[V0.0.1]	
//
//##############################################################################


#ifndef		__GLOBAL_INCLUDE_H__
#define		__GLOBAL_INCLUDE_H__

#include	<stdint.h>
#include	<stdbool.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>


#include	"stdarg.h"
#include	"ctype.h"


#include	<crs32v_sys_config.h>
#include	"crs32v_csr.h"
#include	"crs32v_sys_util.h"
#include	"crs32v_print.h"
#include	"printf.h"
#include	"crs32v_int.h"
#include	<crs32v_trap_handler_exc.h>

#include	<global_code.h>
#include	<global_variable.h>

#include	<sys_define.h>
#include	<bios_hcmd.h>
#include	<bios_bu.h>
#include <LL/sys_core.h>
#include <LL/sys_define.h>
#include <LL/sys_dmac.h>
#include <LL/sys_gpio.h>
#include <LL/sys_i2cs.h>
#include <LL/sys_iopc.h>
#include <LL/sys_mon.h>
#include <LL/sys_spim.h>
#include <LL/sys_sysc.h>

#include	<main_bios.h>



#endif	//	__GLOBAL_INCLUDE_H__
