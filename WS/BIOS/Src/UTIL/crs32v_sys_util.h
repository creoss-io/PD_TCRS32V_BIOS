//##############################################################################
//
//	CRS32V System Utility
//
//	Modules Name	: crs32v_sys_util.h
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


#ifndef		__CRS32V_SYS_UTIL_H__
#define		__CRS32V_SYS_UTIL_H__

#include	<global_include.h>

////======================================================================
//// Function : Alias
////======================================================================
//
//// Function : MEM R/W
//#define	set_mem(badr, wdata)	(*((volatile uint32_t*)(badr)) = (uint32_t) wdata)
//#define	get_mem(badr)			(*((volatile uint32_t*)(badr)))










//======================================================================
// Function : Routines
//======================================================================

// basic delay
void	basic_delay(unsigned long delay_time);

// LED
void	led_delay();

// UART
void	uart_init();
void	uart_tx_byte(char wdata);



#endif	//	__CRS32V_SYS_UTIL_H__
