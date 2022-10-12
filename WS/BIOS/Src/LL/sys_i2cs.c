//##############################################################################
//
//	CRS32V I2CS
//
//	Modules Name	: crs32v_i2cs.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V I2CS
//
//----------------------------------------------------------------------
//	[Revision History]
//
//
//##############################################################################


#include	<global_include.h>


/* --------------------------------------------------------------------------------
 * @brief	I2CS Interrupt Service Routine
 * @details	
 * @param	
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///-------------------------------------------------------------------------------
__att_noinline__	void	int_srv_i2cs ( ) {

	uint16_t	isr;
	uint16_t	n;

	//--------------------------------------------------------------------------------
	//--	Intro
	//--------------------------------------------------------------------------------
	isr  =  sI2CS.int_src & (~sI2CS.int_msk);

	#if	1
		sclr ( d16[ 0], 0);

		smon ( d16[ 0], sI2CS.int_msk );
		smon ( d16[ 1], sI2CS.int_src );
		smon ( d16[ 2], sI2CS.dma_en );
		smon ( d16[ 3], sI2CS.dma_rd_start_badr );
		smon ( d16[ 4], sI2CS.dma_wr_start_badr );
		smon ( d16[ 5], sI2CS.dma_badr_offset );
		smon ( d16[ 6], sI2CS.dma_rd_en_auto_clear );
		smon ( d16[ 7], sI2CS.dma_badr_lower_limit );
		smon ( d16[ 8], sI2CS.dma_badr_upper_limit );
		smon ( d16[ 9], sI2CS.tx_byte_count );
		smon ( d16[10], sI2CS.rx_byte_count );

		smon ( d16[11], 0xFFFF );
		smon ( d16[12], hwdp16[0] );
		smon ( d16[13], hwdp16[1] );
		smon ( d16[14], hwdp16[2] );
		smon ( d16[15], hwdp16[3] );
	#endif

	//--------------------------------------------------------------------------------
	//--	Body
	//--------------------------------------------------------------------------------
	smon ( st16[4], 0x1000 );
	
	hcmd = hwdp16[0];
	harg = hwdp16[1];

	//--------------------------------------------------------------------------------
	//--	Interrupt :  START + SAW + ADD_L + ADD_H + STOP ( or REPST )
	//--------------------------------------------------------------------------------
	smon ( st16[4], 0x2000 );

	if ( ( (isr&I2CS_INT_RESTART_DET) || (isr&I2CS_INT_STOP_DET) ) ) {

		smon ( st16[4], 0x2100 );


		//--	if  S + SA + D0 + D1 + P,    read address packet
		if (sI2CS.rx_byte_count==2) {

			smon ( st16[4], 0x2110 );

			set_htst ( htst );
			set_haux ( haux );

			//hrdp16[2] = htst;
			//hrdp16[3] = haux;

			//--	if hcmd==0x0010, 'read htst'
			if (hcmd==0x0010) {
				smon ( st16[4], 0x2120 );
				sI2CS.dma_rd_start_badr = POS_BADR_HRDP + 4;	// hrdp16[2], hrdp32[1]
			//--	else,
			} else {
				smon ( st16[4], 0x2130 );
				sI2CS.dma_rd_start_badr = POS_BADR_HRDP + 8;	// hrdp16[4], hrdp32[2]
			}

		//--	else,  write packet
		} else {

			smon ( st16[4], 0x2200 );

			if ( hcmd < 0x0010 ) {
				smon ( st16[4], 0x2210 );
				hcmd_trig = 0x01;
				htst = HTST_BIOS_BUSY;
			} else {
				smon ( st16[4], 0x2220 );

			}
		}
	}

	//--------------------------------------------------------------------------------
	//--	Outro
	//--------------------------------------------------------------------------------
	smon ( st16[4], 0x3000 );

	sI2CS.int_mrs = isr;
}

