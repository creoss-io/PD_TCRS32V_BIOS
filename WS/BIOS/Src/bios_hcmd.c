//##############################################################################
//
//	BIOS HCMD
//
//	Modules Name	: bios_hcmd.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//
//----------------------------------------------------------------------
//	[Revision History]
//
//##############################################################################




#include	<global_include.h>


/*------------------------------------------------------------------------------------------------------------------------
 * @brief	
 * @details	
 * @param	
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///----------------------------------------------------------------------------------------------------------------------
__att_noinline__	void	BIOS_HCMD_CLEAR_INT ( ) {

	if	( harg< 0x0010)	{ gss.mode_hintn=MODE_HINTN_OD;		set_hintn(0x1);	}

	else if ( harg==0x0020)	{ 					set_hintn(0x0);	}
	else if ( harg==0x0021)	{ 					set_hintn(0x1);	}

	else if ( harg==0x0100)	{ gss.mode_hintn=MODE_HINTN_OD;		set_hintn(0x0);	}
	else if ( harg==0x0101)	{ gss.mode_hintn=MODE_HINTN_OD;		set_hintn(0x1);	}

	else if ( harg==0x0110)	{ gss.mode_hintn=MODE_HINTN_PP;		set_hintn(0x0);	}
	else if ( harg==0x0111)	{ gss.mode_hintn=MODE_HINTN_PP;		set_hintn(0x1);	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * @brief	
 * @details	
 * @param	harg	  EF Address    	FW_LD	Jump to		RUN_FW		(in old product)
 * 		0x0001 :  Auto     (SYSCFG)	O	0x00040000	O		( O )
 *		0x0002 :  			X	0x00040000	O		( O )
 *		0x0003 :  			X	WDP32[2]	O		( O )
 *		0x0010 :  WDP32[1] (SYSCFG)	O	WDP32[2]	O		( X )
 *		0x0011 :  WDP32[1] (FWINFO)	O	WDP32[2]	O		( X )
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///----------------------------------------------------------------------------------------------------------------------
__att_noinline__	void	BIOS_HCMD_RUN_CPU ( ) {

	enum	enum_res_ret		bures_fwld;

	smon ( st16[0], 0x1000 );
	smon ( d16[0],  hcmd );
	smon ( d16[1],  harg );

	if (harg==0x0001) {	bures_fwld = bu_fwld ( FW_SECT_SYSCFG_SEARCH, (128-4)*1024   );	}
	if (harg==0x0002) {	bures_fwld = RES_OK;						}
	if (harg==0x0002) {	bures_fwld = RES_OK;						}
	if (harg==0x0010) {	bures_fwld = bu_fwld ( FW_SECT_SYSCFG_USERSET, hwdp32_arg[0] );	}
	if (harg==0x0011) {	bures_fwld = bu_fwld ( FW_SECT_FWINFO_USERSET, hwdp32_arg[0] );	}

	smon ( d16[2],  bures_fwld );

	if ( bures_fwld==RES_OK ) {

	if (harg==0x0001) {	jump_to_fw ( 0x00200000 );	}
	if (harg==0x0002) {	jump_to_fw ( 0x00200000 );	}
	if (harg==0x0003) {	jump_to_fw ( hwdp32_arg[1] );	}
	if (harg==0x0010) {	jump_to_fw ( hwdp32_arg[1] );	}
	if (harg==0x0011) {	jump_to_fw ( hwdp32_arg[1] );	}

	}
}



/*------------------------------------------------------------------------------------------------------------------------
 * @brief	
 * @details	
 * @param	
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///----------------------------------------------------------------------------------------------------------------------
__att_noinline__	void	BIOS_HCMD_ACC_REG ( ) {
	uint32_t	n;	//, z;
	uint32_t	rd;

	sclr ( d16[0],  0 );

	/* W_SINGLE*/	if	(harg==0x0010) { set_mem ( hwdp32_arg[0], hwdp32_arg[1] );		}
	/* R_SINGLE*/	else if (harg==0x0011) { rd = get_mem ( hwdp32_arg[0] ); hrdp32_arg[0] = rd; 	}

	/* W_MULTI */	else if (harg==0x0020) { for ( n=0; n<hwdp32_arg[0]/4; n++ ) { set_mem ( hwdp32_arg[2*n+1], hwdp32_arg[2*n+2] );			smon(d32[2],n); smon(d32[3],hwdp32_arg[2*n+1]);             smon(d32[4],hwdp32_arg[2*n+2]);	}	}
	/* R_MULTI */	else if (harg==0x0021) { for ( n=0; n<hwdp32_arg[0]/4; n++ ) { hrdp32_arg[n] = get_mem ( hwdp32_arg[ 1 + n ] );				smon(d32[2],n); smon(d32[3],hwdp32_arg[n+1]);               smon(d32[4],hrdp32_arg[n]);	}	}

	/* W_BURST */	else if (harg==0x0030) { for ( n=0; n<hwdp32_arg[0]/4; n++ ) { set_mem ( (uint32_t) (hwdp32_arg[1] + 4*n ), hwdp32_arg[ 2 + n ] );	smon(d32[2],n); smon(d32[3],hwdp32_arg[1]+4*n);             smon(d32[4],hwdp32_arg[2+n]);	}	}
	/* R_BURST */	else if (harg==0x0031) { for ( n=0; n<hwdp32_arg[0]/4; n++ ) { hrdp32_arg[n] = get_mem ( (uint32_t) (hwdp32_arg[1] + 4*n)  );		smon(d32[2],n); smon(d32[3],(uint32_t)(hwdp32_arg[1]+4*n)); smon(d32[4],hrdp32_arg[n]);	}	}
}

/*------------------------------------------------------------------------------------------------------------------------
 * @brief	
 * @details	
 * @param	
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///----------------------------------------------------------------------------------------------------------------------
__att_noinline__	void	BIOS_HCMD_SE        ( ) {

	uint16_t	harg_h;

//	harg_h      = harg & 0xFF00;
//
//	//------------------------------------------------------------
//	//--	SE_SL
//	//------------------------------------------------------------
	if 	(harg==0x0000) {		}
// 
//	else if (harg==0x0300) { seeprom_chip_erase    ( );										}
//	else if (harg==0x0310) { seeprom_sector_erase  ( hwdpa32[0] );	}				//	hmem32[(BOFFSET_HQARG)/4]);							}
//	else if (harg==0x0320) { seeprom_page_program  ( hwdpa32[0], hwdpa32[1], (uint8_t*) &(hwdpa32[2])); }	// hmem32[(BOFFSET_HQARG)/4], hmem16[(BOFFSET_HQARG+4)/2], &hmem8[BOFFSET_HDP_IN_HMEM] );	}
//	else if (harg==0x0330) { seeprom_read          ( hwdpa32[0], hwdpa32[1], (uint8_t*) &(hrdpa32[0]) );  }	// hmem32[(BOFFSET_HQARG)/4], hmem16[(BOFFSET_HQARG+4)/2], &hmem8[BOFFSET_HDP_IN_HMEM] );	}
//	else if (harg==0x0160) { seeprom_chk_ff        ( hwdpa32[0], hwdpa32[1], (uint8_t*) &(hrdpa32[0]) );  }	// hmem32[(BOFFSET_HQARG)/4], hmem16[(BOFFSET_HQARG+4)/2], &hmem8[BOFFSET_HDP_IN_HMEM] ); }
//
//	else if (harg==0x0200) { seeprom_rdid          ( (uint8_t*)  &(hrdpa32[0]) );		}	// &hmem8[BOFFSET_HDP_IN_HMEM] );			}
//	else if (harg==0x0210) { seeprom_rdsr          ( (uint16_t*) &(hrdpa32[0]) );		}	// &hmem8[BOFFSET_HDP_IN_HMEM] );			}
//	else if (harg==0x0220) { seeprom_wrsr          ( hwdpa32[0] );				}	//  hmem16[(BOFFSET_HQARG)/2] );		}
//	else if (harg==0x0230) { seeprom_wren          ( );					}
//	else if (harg==0x0230) { seeprom_wait_ready    ( );					}
//
//
	//------------------------------------------------------------
	//--	SE_LL
	//------------------------------------------------------------
	else if (harg==0xD000) {
		//spim_ucmd (
		//	(uint16_t) hwdp32_arg[0],	((uint8_t*) (&hwdp32_arg[2]           )),
		//	(uint16_t) hwdp32_arg[1],	((uint8_t*) (&hrdp32_arg[0]           ))
		//);
		spim_cmdgen (	0x0, 0x00,								//	uint16_t vcmd, uint16_t cmd, 
				0x0, 0x00,								//	uint16_t wargnbyte, uint32_t warg, 
				(uint16_t) hwdp32_arg[0],	((uint8_t*) (&hwdp32_arg[2] )),		//	uint32_t wnbyte, uint8_t* wbuf, 
				(uint16_t) hwdp32_arg[1],	((uint8_t*) (&hrdp32_arg[0] ))		//	uint32_t rnbyte, uint8_t* rbuf){
		);
	}

//	spim_option = 0x0000;

	//return 0;




}



/*------------------------------------------------------------------------------------------------------------------------
 * @brief	
 * @details	
 * @param	
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///----------------------------------------------------------------------------------------------------------------------
__att_noinline__	void	BIOS_HCMD_EVAL  (  ) {


	//------------------------------------------------------------
	//--	if harg< 0x8000, Enable HIF 
	//--	if harg>=0x8000, Keep   HIF disabled
	//------------------------------------------------------------
	//if (harg<0x8000) {
	//	sSPIS.tx_dma_start_badr = pos_hrdp;		// To re-set IC's internal address, dma_start address should be re-set.
	//	sSPIS.rx_dma_start_badr = pos_hwdp;
	//	sSPIS.ctrl_ac = (0x1<<1);	// 0x05	Control Auto-Clr (WR)	[1] SPIS_BUSY_CLR
	//}

	//------------------------------------------------------------
	//--	OSC_HF
	//------------------------------------------------------------
	//if ( harg==0x0001 ) {
	//	while ( harg!=0x0000 ){
	//		set_tintn ( (sTMR0.cnt1_val>>16)&0x1 );
	//	}
	//	set_tintn ( 0x1 );
	//}

	//------------------------------------------------------------
	//--	OSC_LF
	//------------------------------------------------------------
	//smon ( st1,  0x0300 );
	//if ( harg==0x0002 ) {
	//	while (harg!=0x0000){
	//		if (sWDTC.st&0x01)	{ set_tintn(0x1);	}
	//		else			{ set_tintn(0x0);	}
	//	}
	//	set_tintn ( 0x1 );
	//}

	//------------------------------------------------------------
	//--	VERSION
	//------------------------------------------------------------
	//smon ( st1,  0x0400 );
	if ( harg==0x0003 ) {
		hrdp32_arg[0x00]   = ( 'T' << 0 ) | ( 'C' << 8 ) | ( 'S' << 16 ) | ( 'R' << 24 );										// TCSR
		hrdp32_arg[0x01]   = ( '3' << 0 ) | ( '2' << 8 ) | ( 'V' << 16 ) | ( '_' << 24 );										// 32V_

		hrdp32_arg[0x02]   = ( 'B' << 0 ) | ( 'I' << 8 ) | ( 'O' << 16 ) | ( 'S' << 24 );										// 32V_
		hrdp32_arg[0x03]   = ( '.' << 0 ) | ( '.' << 8 ) | ( '.' << 16 ) | ( '.' << 24 );										// 32V_

		hrdp32_arg[0x04]   = ((__DATE__[7]          )<<0)   |   ((__DATE__[8]          )<<8)   |   ((__DATE__[9]         )<<16)   |   ((__DATE__[10]        )<<24) ;	// YYYY
		hrdp32_arg[0x05]   = ((__DEF_MONTH__/10 +'0')<<0)   |   ((__DEF_MONTH__%10 +'0')<<8)   |   ((__DEF_DAY__ /10 +'0')<<16)   |   ((__DEF_DAY__ %10 +'0')<<24) ;	// MMDD

		hrdp32_arg[0x06]   = (('_'                  )<<0)   |   (('_'                  )<<8)   |   ((__DEF_HOUR__/10 +'0')<<16)   |   ((__DEF_HOUR__%10 +'0')<<24) ;	// __HH
		hrdp32_arg[0x07]   = ((__DEF_MIN__ /10 +'0' )<<0)   |   ((__DEF_MIN__  %10 +'0')<<8)   |   ((__DEF_SEC__ /10 +'0')<<16)   |   ((__DEF_SEC__ %10 +'0')<<24) ;	// MMSS
	}

	//------------------------------------------------------------
	//--	Check_BIOS_ALIVE
	//------------------------------------------------------------
	//smon ( st1,  0x0500 );
	if ( harg==0x0100 ) {	smon (d16[2], 0x0100 );     hrdp32_arg[0x00] = 0x15141312;	}
	if ( harg==0x0101 ) {	smon (d16[2], 0x0101 );     hrdp32_arg[0x00] = 0x3E3D3C3B;	}

	//------------------------------------------------------------
	//--	delay_nop
	//------------------------------------------------------------
	//smon ( st1,  0x0600 );
	//if ( harg==0x8100 ) {	/* smon (st0, 0x8100 );	smon(den,0);	 smon(d[0], hwdpa32[0]);*/	delay_nop (hwdp32_arg[0]);						}
	//if ( harg==0x8110 ) {	/* smon (st0, 0x8110 );	smon(den,0);	*/	asm_nop_macro_x8();	__asm__ volatile ( "ewait\n\t"::: ); 	asm_nop_macro_x8();	}



}
