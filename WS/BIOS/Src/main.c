

#include	<global_include.h>



/*------------------------------------------------------------------------------------------------------------------------
 * @brief	main
 * @details	
 * @param	
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///----------------------------------------------------------------------------------------------------------------------
int	main() {

	
	//----------------------------------------------------------------------------------------------------
	//--	Very Initial Settings
	//----------------------------------------------------------------------------------------------------
	
	//--	global interrupt disable
	csr_glb_int_disable ( );

	//--	INTN Signal
	sIOPC.hintn_o  = 0x1;
	sIOPC.hintn_oe = 0x0;
	sIOPC.hintn_o  = 0x0;
	

	//----------------------------------------------------------------------------------------------------
	//--	HW, IC Init : 
	//--			CORE
	//--			TMR, WDTC, MISC
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	//--	HW, IC Init : External Interface
	//--			I2CS, SPIS, USB,
	//--			UART, SPIM
	//--			DMA
	//----------------------------------------------------------------------------------------------------

	//--	I2CS
	sSPIM.ctrl_ac = SPIM_CTRL_AC_BLK_RST;
	sSPIM.clk_div = ((12-1)<<8) | ((12/2-1)<<0);
	
	//--	I2CS
	sI2CS.ctrl_ac = I2CS_CTRL_AC_BLK_RST;
	macro_nop_x4 ( );

	sI2CS.int_msk = 0xFFFF;
	sI2CS.int_src = 0x0000;

	sI2CS.dev_add = 0xA6;

	sI2CS.dma_badr_lower_limit = 0x0000;
	sI2CS.dma_badr_upper_limit = 2*1024;

	sI2CS.dma_en = I2CS_DMA_EN_RD |	I2CS_DMA_EN_WR;

	sI2CS.dma_rd_start_badr = POS_BADR_HRDP;	// rx_dma ( DMEM0->DMA->sI2CS ), Host reads
	sI2CS.dma_wr_start_badr = POS_BADR_HWDP;	// tx_dma ( sI2CS->DMA->DMEM0 ), Host writes

	sI2CS.ctrl_st = I2CS_CTRL_ST_DEV_EN;

	sI2CS.dma_en  =   I2CS_DMA_EN_RD
			| I2CS_DMA_EN_WR ; 


	//--	DMAC
	sDMAC.ctrl_ac = DMAC_CTRL_AC_BLK_RST;
	macro_nop_x4 ( );

	sDMAC.rch_src_sel = 	  DMAC_RCH0_SRC_SEL_0_I2CS
				| DMAC_RCH1_SRC_SEL_0_SPIS
				| DMAC_RCH2_SRC_SEL_0_USBD
				| DMAC_RCH3_SRC_SEL_0_UART;

	sDMAC.flow_ctrl =	  DMAC_FLOW_CTRL_RCH0_TCH1_EN	
				| DMAC_FLOW_CTRL_RCH1_TCH1_EN	
				| DMAC_FLOW_CTRL_RCH2_TCH1_EN	
				| DMAC_FLOW_CTRL_RCH3_TCH1_EN;

	sDMAC.RCH0_MAX_TRANS_CYCLE	= 0xFFFF;
	sDMAC.RCH0_MAX_RUN_CYCLE	= 0xFFFF;
	sDMAC.RCH1_MAX_TRANS_CYCLE	= 0xFFFF;
	sDMAC.RCH1_MAX_RUN_CYCLE	= 0xFFFF;
	sDMAC.RCH2_MAX_TRANS_CYCLE	= 0xFFFF;
	sDMAC.RCH2_MAX_RUN_CYCLE	= 0xFFFF;
	sDMAC.RCH3_MAX_TRANS_CYCLE	= 0xFFFF;
	sDMAC.RCH3_MAX_RUN_CYCLE	= 0xFFFF;

	//--	GPIO
	sGPIO.int_msk          = 0xFFFFFFFF;					// turn-off all interrupts
	sGPIO.gpoe_a           = 0x0000000;					// GPOE_A = 0
	sGPIO.gpoe_b           = 0x0000000;					// GPOE_B = 0
	sGPIO.gpoe_c           = 0x0000000;					// GPOE_C = 0
	sGPIO.gpoe_d           = 0x0000000;					// GPOE_D = 0
	sGPIO.gpoe_e           = 0x0000000;					// GPOE_E = 0
	sGPIO.gpoe_f           = 0x0000000;					// GPOE_F = 0
	sGPIO.gpoe_g           = 0x0000000;					// GPOE_G = 0
	sGPIO.gpoe_h           = 0x0000000;					// GPOE_H = 0
	sGPIO.gpoe_i           = 0x0000000;					// GPOE_I = 0
	sGPIO.gpi_a_pos_wu_sel = 0x00000000;					// turn-off all wake-up
	sGPIO.gpi_b_neg_wu_sel = 0x00000000;					// turn-off all wake-up
	sGPIO.ctrl_st          = GPIO_GPI_A_SYNC_EN | GPIO_GPI_B_SYNC_EN;	// Enable GPIO A B Input

	//----------------------------------------------------------------------------------------------------
	//--	HW, IC Init : Interrupts
	//----------------------------------------------------------------------------------------------------



	// CSR init :

	// interrupt configuration
	//csr_write(mficfg, 0xffffffff);		// level interrupt, high active
	csr_write(0xBD7, 0xffffffff);		// level interrupt, high active

	// interrupt clear
	//csr_write(mcintclear, 0x1);			// clear pending interrupt
	csr_write(0xBD0, 0x1);			// clear pending interrupt

	// custom interrupt : fast interrupt vector enable
	csr_int_init_fast_int_vector();

	// interrupt enable : MFIE_00, MEIE
	csr_write(mie, (CSR_MIE_MFIE_ALL + CSR_MIE_MEIE));

	// global interrupt enable
	csr_glb_int_enable ( );


	//----------------------------------------------------------------------------------------------------
	//--	Jump to main_bios ( ) 
	//----------------------------------------------------------------------------------------------------

	main_bios ( );

	return 0;
}


