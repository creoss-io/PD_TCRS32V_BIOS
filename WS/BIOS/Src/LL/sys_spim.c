//##############################################################################
//
//	CRS32V SPIM
//
//	Modules Name	: crs32v_spim.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V SPIM
//
//----------------------------------------------------------------------
//	[Revision History]
//
//
//##############################################################################


#include	<global_include.h>

#define  	smonl(a,b)		smon(a,b)
//#define  	smonl(a,b)		{ }


/* --------------------------------------------------------------------------------
 * @brief	-
 * @details	SPIM has total 16 task-scheduler. 
 * 		It is recommended to use 8 task-schedules for massive data transfer. ( = 256 * 8 = 2KB )
 * @param	-
 * @return	-
 * @remark	Because of post-setting (especially sDMAC), it is hard to make 'non-blocking mode.'
 * @bug		-
 * @todo	Make the function without internal buffer. 
 * @warning	-
 * @see		-
*///-------------------------------------------------------------------------------
void	__att_noinline__	spim_cmdgen ( uint16_t vcmd, uint32_t cmd, uint16_t wargnbyte, uint32_t warg, uint32_t wnbyte, uint8_t* wbuf, uint32_t rnbyte, uint8_t* rbuf){

	uint16_t	n;	// , m;
	uint8_t		ntask;
	uint32_t	warg_rev_byte;

	uint32_t	dmac_backup_rch_src_sel;
	uint32_t	dmac_backup_flow_ctrl;

	uint32_t	nbyte_remain;

	smonl ( st16[0], 0x0010 );
	smonl ( d32[0], (uint32_t) vcmd 		);
	smonl ( d32[1], (uint32_t) cmd	);
	smonl ( d32[2], (uint32_t) wargnbyte		);
	smonl ( d32[3], (uint32_t) warg		);
	smonl ( d32[4], (uint32_t) wnbyte		);
	smonl ( d32[5], (uint32_t) wbuf[0]		);
	smonl ( d32[6], (uint32_t) rnbyte		);
	smonl ( d32[7], (uint32_t) rbuf[0]		);

	sclr ( d32[0], 0 );

	smonl ( st16[0], 0x0020 );

	sSPIM.dma_rd_st_badr = 0;		// data pointer to send to   FLASH and read  from  SRAM
	sSPIM.dma_wr_st_badr = 0;		// data pointer to read from FLASH and write to    SRAM

	//--------------------------------------------------------------------------------
	//--	Pre-Setting
	//--------------------------------------------------------------------------------
	dmac_backup_rch_src_sel = sDMAC.rch_src_sel;
	dmac_backup_flow_ctrl   = ( sDMAC.flow_ctrl >> 8 );

	if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
		sDMAC.rch_src_sel = ( sDMAC.rch_src_sel & DMAC_RCH1_SRC_SEL_CLR ) | DMAC_RCH1_SRC_SEL_2_SPIM;

	} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
		sDMAC.rch_src_sel = ( sDMAC.rch_src_sel & DMAC_RCH2_SRC_SEL_CLR ) | DMAC_RCH2_SRC_SEL_1_SPIM;
	}


	sSPIM.ctrl_st = sSPIM.ctrl_st | ( 0x1 << 5 );		// [5] SPIM_OE
	sSPIM.ssn_sel = ( 0x1 << 0 );
	sSPIM.ssn_oe  = ( 0x1 << 0 );

	//sSPIM.clk_div     = ( 0x3 << 8 ) | ( 0x1 << 0 );
	//sSPIM.int_byte_dly = 8;	// 0x10	[15:00] BYTE_DELAY
	//sSPIM.int_pkt_dly  = 8;	// 0x11	[15:00] PKT_DELAY

	//--------------------------------------------------------------------------------
	//--	SSN = L
	//--------------------------------------------------------------------------------
	if ( 1 ) {
		ntask    = 0;
		sSPIM.task_schedule[ntask++] = ( (0x0<<4) | TID_SSN_SEL  );		
		sSPIM.task_schedule[ntask++] = ( (0x0<<4) | TID_IDLE     );
		sSPIM.ctrl_ac = SPIM_CTRL_AC_TASK_TRIG;
		macro_nop_x4 ( );
		for ( n=0 ; n<100000 ; n++ ) {
			if ( sSPIM.st == 0x01 ) {
				break;
			}
		}
	}

	smonl ( st16[1], __LINE__ );

	//------------------------------------------------------------
	//--	CMD
	//------------------------------------------------------------
	if (vcmd) {
		
		if ( (((uint32_t)(&cmd))&0xFF000000 ) == 0x40000000 ) {		// MA, CPU DATA SRAM, TCH0
			if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH1_TCH_CLR ) | DMAC_FLOW_CTRL_RCH1_TCH0_EN;
			} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH2_TCH_CLR ) | DMAC_FLOW_CTRL_RCH2_TCH0_EN;
			}

		} else if ( (((uint32_t)(&cmd))&0xFF000000 ) == 0x50000000 ) {	// MB, DMA SRAM, TCH1
			if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH1_TCH_CLR ) | DMAC_FLOW_CTRL_RCH1_TCH1_EN;
			} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH2_TCH_CLR ) | DMAC_FLOW_CTRL_RCH2_TCH1_EN;
			}
		}

		sSPIM.dma_rd_st_badr = (uint32_t) (&cmd);		// data pointer to send to   FLASH
									// [31:28] will be trimmed because of the rf size

		smonl ( d32[0] , sDMAC.flow_ctrl >> 8 ) ;
		smonl ( d32[1] , sDMAC.rch_src_sel    ) ;
		smonl ( d32[2] , sSPIM.dma_rd_st_badr ) ;
		smonl ( d32[3] , sSPIM.dma_wr_st_badr ) ;


		ntask    = 0;
		sSPIM.task_schedule[ntask++] = ( (0x0<<4) | TID_SSN_SEL    );		
		sSPIM.task_schedule[ntask++] = ( (0x0<<4) | TID_WCMD_1IO   );
		sSPIM.task_schedule[ntask++] = ( (0x0<<4) | TID_IDLE       );
		sSPIM.ctrl_ac = SPIM_CTRL_AC_TASK_TRIG;
		macro_nop_x4 ( );
		for ( n=0 ; n<100000 ; n++ ) {
			if ( sSPIM.st == 0x01 ) {
				break;
			}
		}

	}

	smonl ( st16[1], __LINE__ );

	//------------------------------------------------------------
	//--	ARGUMENT
	//------------------------------------------------------------
	if (wargnbyte!=0) {

		if (wargnbyte==4) warg_rev_byte = ((warg&0xFF)<<24) | ((warg&0xFF00)<<8) | ((warg>> 8)&0xFF00) | ((warg>>24)&0xFF);
		if (wargnbyte==3) warg_rev_byte = ((warg&0xFF)<<16) | ((warg&0xFF00)   ) | ((warg>>16)&0xFF  ) ;
		if (wargnbyte==2) warg_rev_byte = ((warg&0xFF)<< 8) | ((warg&0xFF00)>>8) ;
		if (wargnbyte==1) warg_rev_byte = ((warg&0xFF)    ) ;
		warg = warg_rev_byte;


		if ( (((uint32_t)(&warg))&0xFF000000 ) == 0x40000000 ) {		// MA, CPU DATA SRAM, TCH0
			if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH1_TCH_CLR ) | DMAC_FLOW_CTRL_RCH1_TCH0_EN;
			} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH2_TCH_CLR ) | DMAC_FLOW_CTRL_RCH2_TCH0_EN;
			}

		} else if ( (((uint32_t)(&warg))&0xFF000000 ) == 0x50000000 ) {	// MB, DMA SRAM, TCH1
			if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH1_TCH_CLR ) | DMAC_FLOW_CTRL_RCH1_TCH1_EN;
			} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH2_TCH_CLR ) | DMAC_FLOW_CTRL_RCH2_TCH1_EN;
			}
		}

		sSPIM.dma_rd_st_badr = (uint32_t) (&warg);		// data pointer to send to   FLASH

		smonl ( st16[1], __LINE__ );

		smonl ( d32[0] , sDMAC.flow_ctrl >> 8 ) ;
		smonl ( d32[1] , sDMAC.rch_src_sel    ) ;
		smonl ( d32[2] , sSPIM.dma_rd_st_badr ) ;
		smonl ( d32[3] , sSPIM.dma_wr_st_badr ) ;
		smonl ( d32[4] , wargnbyte ) ;
		smonl ( d32[5] , (uint32_t) &warg ) ;
		smonl ( d32[6] , warg ) ;
		smonl ( d32[7] , 0 ) ;



		ntask    = 0;
		sSPIM.task_schedule[ntask++] = ( ((0x0          )<<4) | TID_SSN_SEL   );		
		sSPIM.task_schedule[ntask++] = ( ((wargnbyte - 1)<<4) | TID_WDAT_1IO  );		
		sSPIM.task_schedule[ntask++] = ( ((0x0          )<<4) | TID_IDLE      );
		sSPIM.ctrl_ac = SPIM_CTRL_AC_TASK_TRIG;
		macro_nop_x4 ( );

		smonl ( st16[1], __LINE__ );

		for ( n=0 ; n<100000 ; n++ ) {
			if ( sSPIM.st == 0x01 ) {
				break;
			}
		}
	}

	smonl ( st16[1], __LINE__ );

	//------------------------------------------------------------
	//--	WRITE_DATA : if wnbyte>SPIM_NB_PER_TASK , split to multiple tasks.
	//------------------------------------------------------------
	if (wnbyte!=0) {

		if ( (((uint32_t)(wbuf))&0xFF000000 ) == 0x40000000 ) {		// MA, CPU DATA SRAM, TCH0
			if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH1_TCH_CLR ) | DMAC_FLOW_CTRL_RCH1_TCH0_EN;
			} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH2_TCH_CLR ) | DMAC_FLOW_CTRL_RCH2_TCH0_EN;
			}

		} else if ( (((uint32_t)(wbuf))&0xFF000000 ) == 0x50000000 ) {	// MB, DMA SRAM, TCH1
			if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH1_TCH_CLR ) | DMAC_FLOW_CTRL_RCH1_TCH1_EN;
			} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH2_TCH_CLR ) | DMAC_FLOW_CTRL_RCH2_TCH1_EN;
			}
		}

		sSPIM.dma_rd_st_badr   = (uint32_t) (wbuf);		// data pointer to send to   FLASH

		smonl ( d32[0] , sDMAC.flow_ctrl >> 8 ) ;
		smonl ( d32[1] , sDMAC.rch_src_sel    ) ;
		smonl ( d32[2] , sSPIM.dma_rd_st_badr ) ;
		smonl ( d32[3] , sSPIM.dma_wr_st_badr ) ;

		smonl ( st16[1], __LINE__ );

		nbyte_remain = wnbyte;

		ntask    = 0;
		sSPIM.task_schedule[ntask++] = ( (0x0<<4)   |   TID_SSN_SEL   );		

		while ( 1 ) {
			if (nbyte_remain>=SPIM_NB_PER_TASK) {
				sSPIM.task_schedule[ntask++] = (  ((SPIM_NB_PER_TASK - 1)<<4)  | TID_WDAT_1IO );
				nbyte_remain -= SPIM_NB_PER_TASK;
			} else {
				sSPIM.task_schedule[ntask++] = (  ((nbyte_remain     - 1)<<4)  | TID_WDAT_1IO );
				nbyte_remain = 0;
				break;
			}
		}
		sSPIM.task_schedule[ntask++] = ( (0x0<<4) | TID_IDLE     );
		sSPIM.ctrl_ac = SPIM_CTRL_AC_TASK_TRIG;
		macro_nop_x4 ( );
		smonl ( st16[1], __LINE__ );
		for ( n=0 ; n<100000 ; n++ ) {
			if ( sSPIM.st == 0x01 ) {
				break;
			}
		}
	}

	smonl ( st16[1], __LINE__ );

	//------------------------------------------------------------
	//--	READ_DATA
	//------------------------------------------------------------

	if (rnbyte!=0) {

		smonl ( st16[1], __LINE__ );


		if ( (((uint32_t)(rbuf))&0xFF000000 ) == 0x40000000 ) {		// MA, CPU DATA SRAM, TCH0
			if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH1_TCH_CLR ) | DMAC_FLOW_CTRL_RCH1_TCH0_EN;
			} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH2_TCH_CLR ) | DMAC_FLOW_CTRL_RCH2_TCH0_EN;
			}

		} else if ( (((uint32_t)(rbuf))&0xFF000000 ) == 0x50000000 ) {	// MB, DMA SRAM, TCH1
			if ( gss.opt_spim_n_rch==OPT_SPIM_RCH1 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH1_TCH_CLR ) | DMAC_FLOW_CTRL_RCH1_TCH1_EN;
			} else if ( gss.opt_spim_n_rch==OPT_SPIM_RCH2 ) {
				smonl ( st16[1], __LINE__ );
				sDMAC.flow_ctrl = ( sDMAC.flow_ctrl & DMAC_FLOW_CTRL_RCH2_TCH_CLR ) | DMAC_FLOW_CTRL_RCH2_TCH1_EN;
			}
		}

		sSPIM.dma_wr_st_badr = (uint32_t) (rbuf);

		smonl ( d32[0] , sDMAC.flow_ctrl >> 8 ) ;
		smonl ( d32[1] , sDMAC.rch_src_sel    ) ;
		smonl ( d32[2] , sSPIM.dma_rd_st_badr ) ;
		smonl ( d32[3] , sSPIM.dma_wr_st_badr ) ;
		smonl ( d32[4] , rnbyte ) ;
		smonl ( d32[5] , (uint32_t) rbuf ) ;
		smonl ( d32[6] , 0 ) ;
		smonl ( d32[7] , 0 ) ;

		nbyte_remain = rnbyte;
								//
		smonl ( st16[1], __LINE__ );

		ntask    = 0;
		sSPIM.task_schedule[ntask++] = ( (0x0<<4) |   TID_SSN_SEL );		

		//if    (spim_option&EN_SPIM_DREAD) { 
		//	sSPIM.task_schedule[ntask++] = ( TID_WDAT_1IO | 0         );	// dummy 8 clk in DUAL READ
		//}

		while ( 1 ) {
			if ( nbyte_remain >= SPIM_NB_PER_TASK ) {
				smonl ( st16[1], __LINE__ );
				sSPIM.task_schedule[ntask++] = ( ((SPIM_NB_PER_TASK - 1)<<4) | TID_RDAT_1IO  );
				nbyte_remain -= SPIM_NB_PER_TASK;
			} else {
				smonl ( st16[1], __LINE__ );
				sSPIM.task_schedule[ntask++] = ( ((nbyte_remain     - 1)<<4) | TID_RDAT_1IO );
				nbyte_remain = 0;
				break;
			}
		}
		sSPIM.task_schedule[ntask++] = ( TID_SSN_REL  |   (0x0<<4) );			// SSN=H, for mis-aligned read (dma_wr)
		sSPIM.task_schedule[ntask++] = ( (0x0<<4 ) | TID_IDLE      );
		sSPIM.ctrl_ac = SPIM_CTRL_AC_TASK_TRIG;
		macro_nop_x4 ( );			//
		smonl ( st16[1], __LINE__ );
		for ( n=0 ; n<100000 ; n++ ) {
			if ( sSPIM.st == 0x01 ) {
				break;
			}
		}
	}

	smonl ( st16[1], __LINE__ );

	//--------------------------------------------------------------------------------
	//--	SSN = H
	//--------------------------------------------------------------------------------
	if ( 1 ) {
		ntask    = 0;
		sSPIM.task_schedule[ntask++] = ( TID_SSN_REL  |   (0x0<<4) );		
		sSPIM.task_schedule[ntask++] = ( TID_IDLE     |   (0x0<<4) );
		sSPIM.ctrl_ac = SPIM_CTRL_AC_TASK_TRIG;
		macro_nop_x4 ( );
		for ( n=0 ; n<100000 ; n++ ) {
			if ( sSPIM.st == 0x01 ) {
				break;
			}
		}
	}
	//--------------------------------------------------------------------------------
	//--	Post-Setting
	//--------------------------------------------------------------------------------
	sDMAC.rch_src_sel  = dmac_backup_rch_src_sel ;
	sDMAC.flow_ctrl    = dmac_backup_flow_ctrl   ;

	smonl ( st16[1], __LINE__ );

	return;
}


//########################################################################################################################
//########################################################################################################################
//##
//##	SEEPROM Command
//##
//########################################################################################################################
//########################################################################################################################

//--------------------------------------------------------------------------------------------------
// 	read ID
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_rdid(uint8_t * rd){

	spim_cmdgen (	
			1,	0x9F,		//	uint16_t vcmd,		uint16_t cmd,                     
			0,	0x0,		//	uint16_t wargnbyte,	uint32_t warg,
			0,	(uint8_t*) 0,	//	uint16_t wnbyte,	uint16_t* wbuf,
			6,	(uint8_t*) rd	//	uint16_t rnbyte,	uint16_t* rbuf);
		);

}

//--------------------------------------------------------------------------------------------------
/**
 *  @function	read status register
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_rdsr(uint16_t* rd){

	spim_cmdgen  (	
			1,	0x05,		//	uint16_t vcmd,		uint16_t cmd, 
			0,	0x0,		//	uint16_t wargnbyte,	uint32_t warg, 
			0,	(uint8_t*) 0,	//	uint16_t wnbyte,	uint16_t* wbuf,
			2,	(uint8_t*) rd	//	uint16_t rnbyte,	uint16_t* rbuf);
		);
}

//--------------------------------------------------------------------------------------------------
/**
 *  @function	write status register
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_wrsr(uint16_t wd){
	
	spim_cmdgen (	
			1,	0x01,		//	uint16_t vcmd,		uint16_t cmd,                     		
			1,	wd,		//	uint16_t wargnbyte,	uint32_t warg,		
			0,	0x0,		//	uint16_t wnbyte,	uint16_t* wbuf,		
			0,	0x0		//	uint16_t rnbyte,	uint16_t* rbuf);
		);
}

//--------------------------------------------------------------------------------------------------
/**
 *  @function	write status register
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_wrsr_01H_2B(uint16_t wd){
	
	spim_cmdgen (	
			1,	0x01,		//	uint16_t vcmd,		uint16_t cmd,                     		
			2,	wd,		//	uint16_t wargnbyte,	uint32_t warg,		
			0,	0x0,		//	uint16_t wnbyte,	uint16_t* wbuf,		
			0,	0x0		//	uint16_t rnbyte,	uint16_t* rbuf);
		);
}

//--------------------------------------------------------------------------------------------------
/**
 *  @function	write status register
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_wrsr_31H (uint16_t wd){
	
	spim_cmdgen (	
			1,	0x31,		//	uint16_t vcmd,		uint16_t cmd,                     		
			1,	wd,		//	uint16_t wargnbyte,	uint32_t warg,		
			0,	0x0,		//	uint16_t wnbyte,	uint16_t* wbuf,		
			0,	0x0		//	uint16_t rnbyte,	uint16_t* rbuf);
		);
}


//--------------------------------------------------------------------------------------------------
/**
 *  @function	write enable
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_wren(){

	spim_cmdgen (	
			1,	0x06,		//	uint16_t vcmd,		uint16_t cmd,                     		
			0,	0x0,		//	uint16_t wargnbyte,	uint32_t warg,		
			0,	0x0,		//	uint16_t wnbyte,	uint16_t* wbuf,		
			0x0,	0x0		//	uint16_t rnbyte,	uint16_t* rbuf);
		);
}


//--------------------------------------------------------------------------------------------------
/**
 *  @function	Wait Ready
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_wait_ready    ( ) {

	// spim_wait_ready ( );

}

//--------------------------------------------------------------------------------------------------
/**
 *  @function	chip erase
 *  @desc	Chip Erase : 0x60 or 0xC7	
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_chip_erase(){

	spim_cmdgen(	
			1,	0x60,		//	uint16_t vcmd,		uint16_t cmd,                     		
			0,	0x0,		//	uint16_t wargnbyte,	uint32_t warg,		
			0,	0x0,		//	uint16_t wnbyte,	uint16_t* wbuf,		
			0x0,	0x0		//	uint16_t rnbyte,	uint16_t* rbuf);
		);
}



//--------------------------------------------------------------------------------------------------
/**
 *  @function	sector erase
 *  @desc	Block Erase : 0x20
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_sector_erase(uint32_t ef_add){

	spim_cmdgen(	
			1,	0x20,		//	uint16_t vcmd,		uint16_t cmd,                     		
			3,	ef_add,	//	uint16_t wargnbyte,	uint32_t warg,		
			0,	0x0,		//	uint16_t wnbyte,	uint16_t* wbuf,		
			0x0,	0x0		//	uint16_t rnbyte,	uint16_t* rbuf);
		);
}
//--------------------------------------------------------------------------------------------------
/**
 *  @function	program page
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_page_program (uint32_t ef_add, uint32_t nbyte, uint8_t* buf8 ) {

	spim_cmdgen(	
			1,	0x02,		//	uint16_t vcmd,		uint16_t cmd,                     		
			3,	ef_add,	//	uint16_t wargnbyte,	uint32_t warg,		
			nbyte,	buf8,		//	uint16_t wnbyte,	uint16_t* wbuf,
			0x0,	0x0		//	uint16_t rnbyte,	uint16_t* rbuf);
		);

}

//--------------------------------------------------------------------------------------------------
//	void	__att_noinline__	ef_read (uint32_t ef_add, uint8_t* buf8, uint32_t nbyte){
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_read (uint32_t ef_add, uint32_t nbyte, uint8_t* buf8){

	//if (spim_option&EN_SPIM_QREAD) {
	//	// READ : 4MISO
	//	spim_cmdgen(	
	//			1,	0x6B,			//	uint16_t vcmd,		uint16_t cmd, 
	//			3,	ef_add,		//	uint16_t wargnbyte,	uint32_t warg, 
	//			0,	(uint8_t*) 0, 		//	uint32_t wnbyte,	uint8_t* wbuf,
	//			nbyte,	(uint8_t*) buf8		//	uint32_t rnbyte,	uint8_t* rbuf);
	//		);
	//

	//} else if (spim_option&EN_SPIM_DREAD) {
	//	// READ : 2MISO
	//	spim_cmdgen(	
	//			1,	0x3B,			//	uint16_t vcmd,		uint16_t cmd, 
	//			3,	ef_add,		//	uint16_t wargnbyte,	uint32_t warg, 
	//			0,	(uint8_t*) 0, 		//	uint32_t wnbyte,	uint8_t* wbuf,
	//			nbyte,	(uint8_t*) buf8		//	uint32_t rnbyte,	uint8_t* rbuf);
	//		);
	//

	//} else {
		// READ : 1MISO
		spim_cmdgen(	
				1,	0x03,			//	uint16_t vcmd,		uint16_t cmd, 
				3,	ef_add,		//	uint16_t wargnbyte,	uint32_t warg, 
				0,	(uint8_t*) 0, 		//	uint32_t wnbyte,	uint8_t* wbuf,
				nbyte,	(uint8_t*) buf8		//	uint32_t rnbyte,	uint8_t* rbuf);
			);
	//}
}



//--------------------------------------------------------------------------------------------------
/**
 *  @function	program page
 */
//--------------------------------------------------------------------------------------------------
void	__att_noinline__	ef_chk_ff (uint32_t ef_add, uint32_t nbyte, uint8_t* buf8 ) {

	uint16_t	n, nerr;
	uint32_t *	rbuf32 = (uint32_t *) buf8;

	ef_read          ( ef_add,  nbyte, buf8  );

	nerr = 0;
	for ( n=0; n<nbyte/4; n++){
		if ( rbuf32[n]!= 0xFFFFFFFF ) {
			nerr ++;
		}
	}

	rbuf32[0] = 0xCCFF;
	rbuf32[1] = nerr;

}








