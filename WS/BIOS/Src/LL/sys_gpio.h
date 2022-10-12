//##############################################################################
//
//	CRS32V CORE
//
//	Modules Name	: sys_gpio.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V System GPIO
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//##############################################################################


#ifndef		__SYS_GPIO_H__
#define		__SYS_GPIO_H__

#include	<global_include.h>


#define		GPIO_GPI_A_SYNC_EN	( (0x1) << 0 )
#define		GPIO_GPI_B_SYNC_EN	( (0x1) << 1 )

typedef	struct	{

	//------------------------------------------------------------
	uint32_t	int_msk;		// 0x00	
	uint32_t	int_src;		// 0x01	
	uint32_t	int_mrs;		// 0x02	
	uint32_t	st;			// 0x03	
	uint32_t	ctrl_st;		// 0x04 
	uint32_t	ctrl_ac;		// 0x05 

	uint32_t	gpi_a_pos_wu_sel;	// 0x06
	uint32_t	gpi_b_neg_wu_sel;	// 0x07
	uint32_t	ro_wakeup_cause;	// 0x08
	uint32_t	dmy0[7];		// ~

	//------------------------------------------------------------
	uint32_t	gpi_a;			// 0x10 [7:0]  PAD_GPI_A
	uint32_t	gpi_b;			// 0x11 [15:0] PAD_GPI_B
	uint32_t	gpi_c;			// 0x12 [15:0] GPI_C
	uint32_t	gpi_d;			// 0x13 [15:0] GPI_D
	uint32_t	gpi_e;			// 0x14 [15:0] GPI_E
	uint32_t	gpi_f;			// 0x15 [15:0] GPI_F
	uint32_t	gpi_g;			// 0x16 [15:0] GPI_G
	uint32_t	gpi_h;			// 0x17 [15:0] GPI_H
	uint32_t	gpi_i;			// 0x18 [15:0] GPI_I
	uint32_t	dmy1[7];		// ~ 

	//------------------------------------------------------------
	uint32_t	gpo_a;			// 0x20 [7:0]  PAD_GPO_A
	uint32_t	gpo_b;			// 0x21 [15:0] GPO_B
	uint32_t	gpo_c;			// 0x22 [15:0] GPO_C
	uint32_t	gpo_d;			// 0x23 [15:0] GPO_D
	uint32_t	gpo_e;			// 0x24 [15:0] GPO_E
	uint32_t	gpo_f;			// 0x25 [15:0] GPO_F
	uint32_t	gpo_g;			// 0x26 [15:0] GPO_G
	uint32_t	gpo_h;			// 0x27 [15:0] GPO_H
	uint32_t	gpo_i;			// 0x28 [15:0] GPO_I
	uint32_t	dmy2[7];		// ~

	//------------------------------------------------------------
	uint32_t	gpoe_a;			// 0x30 [7:0]  PAD_GPOE_A
	uint32_t	gpoe_b;			// 0x31 [15:0] GPOE_B
	uint32_t	gpoe_c;			// 0x32 [15:0] GPOE_C
	uint32_t	gpoe_d;			// 0x33 [15:0] GPOE_D
	uint32_t	gpoe_e;			// 0x34 [15:0] GPOE_E
	uint32_t	gpoe_f;			// 0x35 [15:0] GPOE_F
	uint32_t	gpoe_g;			// 0x36 [15:0] GPOE_G
	uint32_t	gpoe_h;			// 0x37 [15:0] GPOE_H
	uint32_t	gpoe_i;			// 0x38 [15:0] GPOE_I
	uint32_t	dmy3[7];		// ~

	//------------------------------------------------------------
	uint32_t	gpo_a_setbit;		// 0x40
	uint32_t	gpo_b_setbit;		// 0x41
	uint32_t	gpo_c_setbit;		// 0x42
	uint32_t	gpo_d_setbit;		// 0x43
	uint32_t	gpo_e_setbit;		// 0x44
	uint32_t	gpo_f_setbit;		// 0x45
	uint32_t	gpo_g_setbit;		// 0x46
	uint32_t	gpo_h_setbit;		// 0x47
	uint32_t	gpo_i_setbit;		// 0x48
	uint32_t	dmy4[7];		// ~

	//------------------------------------------------------------
	uint32_t	gpo_a_clrbit;		// 0x50
	uint32_t	gpo_b_clrbit;		// 0x51
	uint32_t	gpo_c_clrbit;		// 0x52
	uint32_t	gpo_d_clrbit;		// 0x53
	uint32_t	gpo_e_clrbit;		// 0x54
	uint32_t	gpo_f_clrbit;		// 0x55
	uint32_t	gpo_g_clrbit;		// 0x56
	uint32_t	gpo_h_clrbit;		// 0x57
	uint32_t	gpo_i_clrbit;		// 0x58
	uint32_t	dmy5[7];		// ~

} struct_sys_gpio;

#define		sGPIO		( * ( (volatile struct_sys_gpio *) BASE_BADR_IP_GPIO	)  )


extern	__att_noinline__	void	set_hintn ( uint8_t wd ) ;


#endif	//	__SYS_IOPC_H__
