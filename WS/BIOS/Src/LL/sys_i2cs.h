//##############################################################################
//
//	CRS32V I2CS
//
//	Modules Name	: sys_i2cs.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V I2C Slave  Controller
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//##############################################################################


#ifndef		__SYS_I2CS_H__
#define		__SYS_I2CS_H__

#include	<global_include.h>

#define		I2CS_INT_START_DET			  (0x01)
#define		I2CS_INT_RESTART_DET			  (0x02)
#define		I2CS_INT_STOP_DET			  (0x04)
#define		I2CS_INT_GENERAL_CALL_DET		  (0x08)
#define		I2CS_INT_TX_DATA_EXECUTED		  (0x10)
#define		I2CS_INT_RX_DATA_EXECUTED		  (0x20)
#define		I2CS_INT_DMA_BADR_OB			  (0x40)

#define		I2CS_ST_BUSY				(0x01)
#define		I2CS_ST_DMA_WR_BUSY			(0x02)
#define		I2CS_ST_SDA_SIG_LEVEL			(0x04)
#define		I2CS_ST_SCL_SIG_LEVEL			(0x08)
#define		I2CS_ST_FSM				(0x1F0)

#define		I2CS_CTRL_ST_DEV_EN			(0x01)
#define		I2CS_CTRL_ST_SCL_STRETCH_EN		(0x02)
#define		I2CS_CTRL_ST_WAKEUP_EN			(0x04)
#define		I2CS_CTRL_ST_USE_EXT_DA_EN		(0x08)

#define		I2CS_CTRL_AC_BLK_RST			(0x01)
#define		I2CS_CTRL_TX_PHY_CLR			(0x02)

#define		I2CS_DMA_EN_RD				(0x01)
#define		I2CS_DMA_EN_WR				(0x02)

#define		I2CS_DMA_RDEN_AUTOCLR_AT_START		(0x01)
#define		I2CS_DMA_RDEN_AUTOCLR_AT_RESTART	(0x02)
#define		I2CS_DMA_RDEN_AUTOCLR_AT_STOP		(0x04)

/******************************************************************************
 * 	SYSTEM Define
 *****************************************************************************/


/******************************************************************************
 * 	Type Define
 *****************************************************************************/
typedef volatile struct {

	//--------------------------------------------------------------------------------
	uint32_t		int_msk;		// 0x00	Interrupt Mask		                        [7] RX_EXECUTED		[3] GENERAL_CALL_DET
							//				                        [6] TX_EXECUTED		[2] STOP_DET
							//				                        [5] RX_BREAK_POINT_MET	[1] RESTART_DET
							//				[8] DMA_BADR_OUT_BOUND  [4] TX_BREAK_POINT_MET	[0] START_DET
	uint32_t		int_src;        	// 0x01	Interrupt Source
	uint32_t		int_mrs;        	// 0x02	Interrupt Mirror
	uint32_t		st;			// 0x03	Status (R)		[13: 9]	I2CS_FSM		[2] PARTIAL_BYTE_ERR
							//				[8]     I2CS_SCL		[1] DMA_WR_BUSY
							//				[7]     I2CS_SDA		[0] I2CS_BUSY
							//				[ 6: 3] PARTIAL_BYTE_ERR
	uint32_t		ctrl_st;		// 0x04	Static Control (W/R)	[7] IGNORE_DEV_ADR_3_1 (24L16 emulating)	[3] GLB_CMD_EN
							//				[6] WPKT_BADR_LENGTH   (24L16 emulating)	[2] GENERAL_CALL_EN
							//			        [5] WPKT_BADR_EN				[1] SCL_STRETCH_EN
							//		                [4] USE_EXT_DA_EN				[0] I2Cs_DEV_EN
	uint32_t		ctrl_ac;		// 0x05	Auto-Clr Control	[2] RX_PHY_CLR
							//				[1] TX_PHY_CLR
							//				[0] BLK_RST
	uint32_t		dmy0[10];		// 0x06 ~ 0x0F
	//--------------------------------------------------------------------------------
	uint32_t		phy_clock_div;		// 0x10	PHY Clock Divider	[1:0] PHY_CLK_DIV
	uint32_t		phy_sync_ctrl;		// 0x11	PHY Sync Control	[2:0] PHY_SYNC_STAGE
	uint32_t		phy_scl_hold_time;	// 0x12	PHY SCL Hold time	[7:0] PHY_SCL_HOLD_TIME
	uint32_t		dev_add;		// 0x13	Device Address		[7:0] DEV_ADR		R [31:16] EXT_DEV_ADR_IN
	uint32_t		wakeup_dev_add;		// 0x14	WAKEUP Device Address	[7:0] DEV_ADR_WAKEUP
	uint32_t		dmy1[11];		// 0x15 ~ 0x1F

	//--------------------------------------------------------------------------------
	uint32_t		dma_en;			// 0x20 TRX Control		[5] DMA_ADD_WPKT_BADR
							//				[4] DMA_LE0_BE1
							//				[3] DMA_RX_EN
							//				[2] DMA_TX_EN
							//				[1] RX_BREAK_POINT_EN
							//				[0] TX_BREAK_POINT_EN
	uint32_t		dma_rd_start_badr;	// 0x21 DMA RD START BADR	W [17:0] TX_DMA_START_BADR	R [17:0] CRNT_TX_DMA_BADR
	uint32_t		dma_wr_start_badr;	// 0x22 DMA WR START BADR	W [17:0] RX_DMA_START_BADR	R [17:0] CRNT_RX_DMA_BADR
	uint32_t		dma_badr_offset;	// 0x23 DMA BADR Offset		[15:0]
	uint32_t		dma_rd_en_auto_clear;	// 0x24 DMA_RD_EN Auto Clear Source selection
	uint32_t		dma_badr_lower_limit;	// 0x25 WRITE PACKET BADR	W [17:0] DMA_BADR_LOWER_BOUND
	uint32_t		dma_badr_upper_limit;	// 0x26 WRITE PACKET BADR	W [17:0] DMA_BADR_UPPER_BOUND
	uint32_t		dmy2[9];		// ~
	//--------------------------------------------------------------------------------
	uint32_t		tx_byte_count;		// 0x30 TX_BYTE_COUNT		R [15:0] TX_BYTE_COUNT
	uint32_t		rx_byte_count;		// 0x31 RX_BYTE_COUNT		R [15:0] RX_BYTE_COUNT

} struct_i2cs;

#define sI2CS		( *((volatile struct_i2cs*) BASE_BADR_IP_I2CS) )


extern	__att_noinline__	void	int_srv_i2cs ( ) ;

#endif	//	__SYS_I2CS_H__
