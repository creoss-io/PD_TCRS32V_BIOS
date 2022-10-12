//##############################################################################
//
//	CRS32V SPIM
//
//	Modules Name	: sys_spim.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V SPI Master Controller
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//##############################################################################


#ifndef		__SYS_SPIM_H__
#define		__SYS_SPIM_H__

#include	<global_include.h>


/******************************************************************************
 * 	SYSTEM Define
 *****************************************************************************/


#define		EN_SPIM_DMA	0x0001
#define		EN_SPIM_DREAD	0x0010
#define		EN_SPIM_QREAD	0x0020
#define		EN_SPIM_CLKOFF	0x0100
#define		EN_SPIM_INT	0x1000

#define		TID_IDLE		(0x0 << 0)
#define		TID_SSN_SEL		(0x1 << 0)
#define		TID_SSN_REL		(0x2 << 0)
#define		TID_WCMD_1IO		(0x3 << 0)
#define		TID_WCMD_2IO		(0x4 << 0)
#define		TID_WCMD_4IO		(0x5 << 0)
#define		TID_WDAT_1IO		(0x6 << 0)
#define		TID_WDAT_2IO		(0x7 << 0)
#define		TID_WDAT_4IO		(0x8 << 0)
#define		TID_RDAT_1IO		(0x9 << 0)
#define		TID_RDAT_2IO		(0xA << 0)
#define		TID_RDAT_4IO		(0xB << 0)
#define		TID_INT_PKT_DLY		(0xC << 0)


#define		SPIM_CTRL_AC_BLK_RST	(0x1 << 0)
#define		SPIM_CTRL_AC_TASK_TRIG	(0x1 << 1)

#define		SPIM_NB_PER_TASK	(2048)


/******************************************************************************
 * 	Type Define
 *****************************************************************************/

typedef volatile struct {

	//------------------------------------------------------------
	uint32_t		int_msk;	// 0x00	[15:0]	Interrupt Mask
	uint32_t		int_src;        // 0x01	[15:0]	Interrupt Source	
	uint32_t		int_mrs;        // 0x02	[15:0]	Mirrored Interrupt Source : Writing '1' to 'nth' bit will clear 'nth' bit
	uint32_t		st;		// 0x03	[15:0]	status
	uint32_t		ctrl_st;	// 0x04	[15:0]	Control Static
						//				      [3]CD_OE  
						//		[6]3WIRE_EN           [2]LSFE        
						//		[5]SPIM_OE            [1]CLK_PHA    
						//		[4]MOSI_9BIT_EN       [0]CL_POL
	uint32_t		ctrl_ac;	// 0x05	[15:0]	Control Auto-clear
						//		[1] TASK_TRIG
						//		[0] BLK_RST		Block reset
	uint32_t		ssn_oe;		// 0x06	[7:0]	SSN OE
	uint32_t		ssn_sel_polarity;// 0x07	[7:0]	SSn Polarity 0:Low active, 1:High active
	uint32_t		clk_div;	// 0x08	[15:8]	Even divider 
						//      [ 7:0]  Odd  divider 
	uint32_t		ssn_sel;	// 0x09	[7:0]	SPI slave select
	uint32_t		dmy[6];		// 0x0A	 ~ 0x0F

	//------------------------------------------------------------
	uint32_t		int_byte_dly;	// 0x10	[15:00] BYTE_DELAY
	uint32_t		int_pkt_dly;	// 0x11	[15:00] PKT_DELAY
	uint32_t		dmy2[14];	// 

	//------------------------------------------------------------
	uint32_t		dma_rd_st_badr;	// 0x20	[17:00] DMA_RD_ST_BADR
	uint32_t		dma_wr_st_badr;	// 0x21	[17:00] DMA_WR_ST_BADR
	uint32_t		dmy3[14];	// 

	//------------------------------------------------------------
	uint32_t		task_schedule[16];	// 0x30	[11:00] { TID[3:0], REPEAT_COUNT[7:0] }

} struct_spim;

#define sSPIM		( *((volatile struct_spim*) BASE_BADR_IP_SPIM) )


extern	void	__att_noinline__	int_srv_spim ( ) ;




extern	void	__att_noinline__	spim_cmdgen( uint16_t vcmd, uint32_t cmd, uint16_t wargnbyte, uint32_t warg, uint32_t wnbyte, uint8_t* wbuf, uint32_t rnbyte, uint8_t* rbuf);


extern	void	__att_noinline__	ef_rdid          (uint8_t * rd );
extern	void	__att_noinline__	ef_rdsr          (uint16_t * rd );
extern	void	__att_noinline__	ef_wrsr          (uint16_t   wd );
extern	void	__att_noinline__	ef_wren          ( );
extern	void	__att_noinline__	ef_wait_ready    ( );

extern	void	__att_noinline__	ef_wrsr_01H_2B (uint16_t wd);
extern	void	__att_noinline__	ef_wrsr_31H    (uint16_t wd);

extern	void	__att_noinline__	ef_chip_erase    ( );
extern	void	__att_noinline__	ef_sector_erase  (uint32_t ef_add );
extern	void	__att_noinline__	ef_page_program  (uint32_t ef_add, uint32_t nbyte, uint8_t* buf8  );
extern	void	__att_noinline__	ef_read          (uint32_t ef_add, uint32_t nbyte, uint8_t* buf8  );
extern	void	__att_noinline__	ef_chk_ff        (uint32_t ef_add, uint32_t nbyte, uint8_t* buf8  );




#endif	//	__SYS_SPIM_H__
