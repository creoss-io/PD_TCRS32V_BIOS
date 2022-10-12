//##############################################################################
//
//	Main BIOS
//
//	Modules Name	: main_bios.c
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
 * @brief	main_bios
 * @details	
 * @param	
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///----------------------------------------------------------------------------------------------------------------------
__att_noinline__	void	main_bios ( ) {

	unsigned long	i, j;
	uint32_t	n;
	enum	enum_res_ret		res_fwld;

	smon ( func_set_cur_func0, 0 );

	//----------------------------------------------------------------------------------------------------
	//--	Global variables
	//----------------------------------------------------------------------------------------------------
	hwdp8   = (uint8_t  *)	(BASE_BADR_MB + POS_BADR_HWDP);	// host write data port
	hwdp16  = (uint16_t *)  hwdp8;		
	hwdp32  = (uint32_t *)  hwdp8;		

	hrdp8   = (uint8_t  *)	(BASE_BADR_MB + POS_BADR_HRDP);	// host read  data port
	hrdp16  = (uint16_t *)  hrdp8;		
	hrdp32  = (uint32_t *)  hrdp8;		

	hwdp8_arg  = (uint8_t  *) (&hwdp8[4]);
	hwdp16_arg = (uint16_t *) (hwdp8_arg);
	hwdp32_arg = (uint32_t *) (hwdp8_arg);

	hrdp8_arg  = (uint8_t  *) (&hrdp8[8]);
	hrdp16_arg = (uint16_t *) (hrdp8_arg);
	hrdp32_arg = (uint32_t *) (hrdp8_arg);


	gss.buf16  = (uint16_t*) gss.buf8;
	gss.buf32  = (uint32_t*) gss.buf8;

	htst	= HTST_BIOS_BUSY;
	haux	= HAUX_BU_ING;

	for ( n=0 ; n<16 ; n++ ) {
	hrdp32[n] = 0x00000000;
	hwdp32[n] = 0x00000000;			// for simulation : remove x, z 
	}
	hrdp32[1] = (htst<<16) | (haux);


	gss.mode_hintn	        = MODE_HINTN_OD;
	gss.mode_hintn_assert   = MODE_HINTN_NOCHANGE_AFTER_HCMD;

	gss.opt_spim_rd         = OPT_SPIM_RD_SINGLE;
	gss.opt_spim_sclk       = OPT_SPIM_SCLK_SYS_DIV16;
	gss.opt_spim_mode_block = OPT_SPIM_BLOCK;
	gss.opt_spim_n_rch	= OPT_SPIM_RCH1;


	//----------------------------------------------------------------------------------------------------
	//--	Bootup Option
	//----------------------------------------------------------------------------------------------------
	//							       default
	if ( (sGPIO.gpi_b & 0x1) == 0x0 )	gss.buopt_fwld_skip  = BUOPT_FWLD_SKIP_OFF;		else gss.buopt_fwld_skip  = BUOPT_FWLD_SKIP_ON;
	if ( (sGPIO.gpi_b & 0x2) == 0x0 )	gss.buopt_fw_autorun = BUOPT_FW_AUTORUN_ON;		else gss.buopt_fw_autorun = BUOPT_FW_AUTORUN_OFF;

	res_fwld = RES_FAIL;

	if ( gss.buopt_fwld_skip==BUOPT_FWLD_SKIP_ON ) {
		
	} else {
		res_fwld = bu_fwld ( FW_SECT_SYSCFG_SEARCH, 0x00000000 );
	}

	if ( res_fwld == RES_OK ) {
		//jump_to_fw ( 0x00040000 );
	}

	//--	Memory Control Setting
	sSYSC.ctrl_st = SYSC_SR_PAD1_BY_MB | SYSC_SR_PAD2_BY_PC	;

	//----------------------------------------------------------------------------------------------------
	//--	HW, HIF ENBLE
	//----------------------------------------------------------------------------------------------------
	sI2CS.int_src = 0x00;
	sI2CS.int_msk = 0x00 | I2CS_INT_START_DET;


	//----------------------------------------------------------------------------------------------------
	//--	HW, HINTN = L
	//----------------------------------------------------------------------------------------------------
	sIOPC.hintn_oe = 0x1;

	htst	= HTST_BIOS;
	haux	= HAUX_NONE;
	set_htst ( htst );
	set_haux ( haux );



	// LED : counting
	i=0;
	//csr_write(mscratch, 0);

MAIN_BIOS_LOOP:

	smon ( d16[0], i );

	//------------------------------------------------------------
	//--	HCMD
	//------------------------------------------------------------
	if ( hcmd_trig == 0x1 ) {

		//----------------------------------------
		//--	Intro
		//----------------------------------------
		htst = HTST_BIOS_BUSY;
		haux = HTST_BIOS_BUSY;

		set_htst ( htst );	//hrdp16[2] = htst;
		set_haux ( haux );	//hrdp16[3] = haux;

		//----------------------------------------
		//--	HCMD Parsing
		//----------------------------------------
		sclr ( d16[0], 0 );
		smon ( d16[1], 0x0100 );
		smon ( d16[2], hcmd   );
		smon ( d16[3], harg   );

		if	(hcmd==0x0000)	{	                        	}
		else if	(hcmd==0x0002)	{	BIOS_HCMD_CLEAR_INT ( );	}
		else if	(hcmd==0x0004)	{	BIOS_HCMD_RUN_CPU   ( );	}
		else if	(hcmd==0x0006)	{	BIOS_HCMD_ACC_REG   ( );	}
		else if	(hcmd==0x0008)	{	BIOS_HCMD_SE        ( );	}
		else if	(hcmd==0x000E)	{	BIOS_HCMD_EVAL      ( );	}

		//----------------------------------------
		//--	After HCMD Service
		//----------------------------------------
		htst = HTST_BIOS;
		haux = HAUX_NONE;

		hrdp16[2] = htst;
		hrdp16[3] = haux;

		hcmd_trig = 0x0000;

	}


	//jump_to_app_core ( 0x00200000 );

	//j=csr_read(mscratch);
	//j++;
	//csr_write(mscratch, j);

	//// test exception
	//if (i==0x3f) asm("ebreak");
	//if (i==0x7f) asm("ecall");
	//if (i==0xff) {
	//	// custom exception : stack corruption
	//	csr_exc_init_stack_check();

	//	basic_delay(60);

	//	// invoking stack corruption
	//	set_mem(DM_STACK_START_BADR, 0x12345678);		// stack corruption
	//}

	i++;

	goto	MAIN_BIOS_LOOP;
}



