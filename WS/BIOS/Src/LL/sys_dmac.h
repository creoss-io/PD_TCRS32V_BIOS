//##############################################################################
//
//	CRS32V DMAC
//
//	Modules Name	: sys_dmac.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V DMA Controller
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//##############################################################################


#ifndef		__SYS_DMAC_H__
#define		__SYS_DMAC_H__

#include	<global_include.h>

#define		DMAC_INT_RCH0_EOP		0x01
#define		DMAC_INT_RCH1_EOP		0x02
#define		DMAC_INT_RCH2_EOP		0x04
#define		DMAC_INT_RCH3_EOP		0x08

#define		DMAC_ST_TCH0_BUSY		0x01
#define		DMAC_ST_TCH1_BUSY		0x02
#define		DMAC_ST_COPY_BUSY		0x04

#define		DMAC_CTRL_ST_FORCE_TCH0_EOP	0x01
#define		DMAC_CTRL_ST_FORCE_TCH1_EOP	0x02

#define		DMAC_CTRL_AC_BLK_RST		0x01

#define		DMAC_FLOW_CTRL_RCH0_TCH_CLR	(~0x11)
#define		DMAC_FLOW_CTRL_RCH1_TCH_CLR	(~0x22)
#define		DMAC_FLOW_CTRL_RCH2_TCH_CLR	(~0x44)
#define		DMAC_FLOW_CTRL_RCH3_TCH_CLR	(~0x88)

#define		DMAC_FLOW_CTRL_RCH0_TCH0_EN	0x01
#define		DMAC_FLOW_CTRL_RCH1_TCH0_EN	0x02
#define		DMAC_FLOW_CTRL_RCH2_TCH0_EN	0x04
#define		DMAC_FLOW_CTRL_RCH3_TCH0_EN	0x08
#define		DMAC_FLOW_CTRL_RCH0_TCH1_EN	0x10
#define		DMAC_FLOW_CTRL_RCH1_TCH1_EN	0x20
#define		DMAC_FLOW_CTRL_RCH2_TCH1_EN	0x40
#define		DMAC_FLOW_CTRL_RCH3_TCH1_EN	0x80

#define		DMAC_FLOW_CTRL_RCH0_TCH0_BUSY	0x01
#define		DMAC_FLOW_CTRL_RCH1_TCH0_BUSY	0x02
#define		DMAC_FLOW_CTRL_RCH2_TCH0_BUSY	0x04
#define		DMAC_FLOW_CTRL_RCH3_TCH0_BUSY	0x08
#define		DMAC_FLOW_CTRL_RCH0_TCH1_BUSY	0x10
#define		DMAC_FLOW_CTRL_RCH1_TCH1_BUSY	0x20
#define		DMAC_FLOW_CTRL_RCH2_TCH1_BUSY	0x40
#define		DMAC_FLOW_CTRL_RCH3_TCH1_BUSY	0x80

#define		DMAC_FLOW_CTRL_RCH0_TCH0_EN_RD	(0x01<<8)
#define		DMAC_FLOW_CTRL_RCH1_TCH0_EN_RD	(0x02<<8)
#define		DMAC_FLOW_CTRL_RCH2_TCH0_EN_RD	(0x04<<8)
#define		DMAC_FLOW_CTRL_RCH3_TCH0_EN_RD	(0x08<<8)
#define		DMAC_FLOW_CTRL_RCH0_TCH1_EN_RD	(0x10<<8)
#define		DMAC_FLOW_CTRL_RCH1_TCH1_EN_RD	(0x20<<8)
#define		DMAC_FLOW_CTRL_RCH2_TCH1_EN_RD	(0x40<<8)
#define		DMAC_FLOW_CTRL_RCH3_TCH1_EN_RD	(0x80<<8)

#define		DMAC_RCH0_SRC_SEL_CLR		(~(0x3 <<0))
#define		DMAC_RCH1_SRC_SEL_CLR		(~(0x3 <<2))
#define		DMAC_RCH2_SRC_SEL_CLR		(~(0x3 <<4))
#define		DMAC_RCH3_SRC_SEL_CLR		(~(0x3 <<6))

#define		DMAC_RCH0_SRC_SEL_0_I2CS		  (0x0 <<0)
#define		DMAC_RCH0_SRC_SEL_1_SPIS		  (0x1 <<0)
#define		DMAC_RCH0_SRC_SEL_2_USBD		  (0x2 <<0)
#define		DMAC_RCH0_SRC_SEL_3_UART		  (0x3 <<0)

#define		DMAC_RCH1_SRC_SEL_0_SPIS		  (0x0 <<2)
#define		DMAC_RCH1_SRC_SEL_1_I2CS		  (0x1 <<2)
#define		DMAC_RCH1_SRC_SEL_2_SPIM		  (0x2 <<2)
#define		DMAC_RCH1_SRC_SEL_3_I2CM		  (0x3 <<2)

#define		DMAC_RCH2_SRC_SEL_0_USBD		  (0x0 <<4)
#define		DMAC_RCH2_SRC_SEL_1_SPIM		  (0x1 <<4)
#define		DMAC_RCH2_SRC_SEL_2_I2CM		  (0x2 <<4)
#define		DMAC_RCH2_SRC_SEL_3_TDFE		  (0x3 <<4)

#define		DMAC_RCH3_SRC_SEL_0_UART		  (0x0 <<6)
#define		DMAC_RCH3_SRC_SEL_1_MISC		  (0x1 <<6)
#define		DMAC_RCH3_SRC_SEL_0_MEMCP		  (0x0 <<6)

#define		DMAC_CNT_EN_TCH0_TCNT_EN		  (0x1)
#define		DMAC_CNT_EN_TCH0_RCNT_EN		  (0x2)
#define		DMAC_CNT_EN_TCH1_TCNT_EN		  (0x4)
#define		DMAC_CNT_EN_TCH1_RCNT_EN		  (0x8)

#define		DMAC_COPY_CTRL_R0_W1_TRIG		  (0x1)
#define		DMAC_COPY_CTRL_R1_W0_TRIG		  (0x2)
#define		DMAC_COPY_CTRL_R0_W0_TRIG		  (0x4)
#define		DMAC_COPY_CTRL_R1_W1_TRIG		  (0x8)


//	DMA Source Table
//
//				SRC0		SRC1		SRC2		SRC3
//	RCH0			I2CS		SPIS		USBD		UART
//	RCH1			SPIS		I2CS		SPIM		I2CM
//	RCH2			USBD		SPIM		I2CM		TDFE
//	RCH3-1 (External)	UART		MISC		RESERVED	RESERVED
//	RCH3-0 (Internal)	DMAC_MEMCP	PROHIBITED	-		-


typedef	struct	{
	uint32_t	int_msk;		// 0x00	[15:0]	Interrupt Mask
	uint32_t	int_src;		// 0x01	[15:0]	Interrupt Source
	uint32_t	int_mrs;		// 0x02	[15:0]	Mirrored Interrupt Source : Writing '1' to 'nth' bit will clear 'nth' bit
	uint32_t	st;			// 0x03	control & status
	uint32_t	ctrl_st;		// 0x04	static control
	uint32_t	ctrl_ac;		// 0x05	dynamic control
	uint32_t	flow_ctrl;		// 0x06 [3:0] RCHx_TCH0_EN,  [7:4] RCHx_TCH1_EN
	uint32_t	rch_src_sel;		// 0x07 [1:0]  RCH0 source selection [3:2]RCH1   [5:4]RCH2
	uint32_t	cnt_en;			// 0x08 [3:0]  [0]TCH0 TCYC, [1]TCH0 RCYC, [2]TCH1 TCYC, [3]TCH1 RCYC
	uint32_t	cp_ctrl;		// 0x09 [1:0]  [0]copy trig, from TCH0 to TCH1, AC
						//             [1]copy trig, from TCH1 to TCH0, AC
	uint32_t	cp_word_cnt;		// 0x0A [15:0]	copy word count    0: 1word
	uint32_t	TCH0_CP_ST_ADD;		// 0x0B [15:0]	TCH0 copy start address
	uint32_t	TCH1_CP_ST_ADD;		// 0x0C [15:0]	TCH1 copy start address
	uint32_t	dmy[3];			// 0x0D ~ 0x0F 

	uint32_t	RCH0_MAX_TRANS_CYCLE;	// 0x10 [15:0]	max transaction cycle after RCH0 DREQ
	uint32_t	RCH0_MAX_RUN_CYCLE;	// 0x11 [15:0]	max run         cycle after RCH0 DREQ
	uint32_t	RCH1_MAX_TRANS_CYCLE;	// 0x12 [15:0]	max transaction cycle after RCH1 DREQ
	uint32_t	RCH1_MAX_RUN_CYCLE;	// 0x13 [15:0]	max run         cycle after RCH1 DREQ
	uint32_t	RCH2_MAX_TRANS_CYCLE;	// 0x14 [15:0]	max transaction cycle after RCH2 DREQ
	uint32_t	RCH2_MAX_RUN_CYCLE;	// 0x15 [15:0]	max run         cycle after RCH2 DREQ
	uint32_t	RCH3_MAX_TRANS_CYCLE;	// 0x16 [15:0]	max transaction cycle after RCH3 DREQ
	uint32_t	RCH3_MAX_RUN_CYCLE;	// 0x17 [15:0]	max run         cycle after RCH3 DREQ
	uint32_t	dmy2[8];		// 0x18 ~ 0x1F

	uint32_t	cur_tch0_tcnt;		// 0x20	[15:0]	Current TCH0 TRANS counter value
	uint32_t	cur_tch0_rcnt;		// 0x21	[15:0]	Current TCH0 RUN   counter value
	uint32_t	cur_tch1_tcnt;		// 0x22	[15:0]	Current TCH1 TRANS counter value
	uint32_t	cur_tch1_rcnt;		// 0x23	[15:0]	Current TCH1 RUN   counter value

} struct_dmac;


#define sDMAC		( *((volatile struct_dmac*) BASE_BADR_IP_DMAC) )



#endif	//	__SYS_DMAC_H__
