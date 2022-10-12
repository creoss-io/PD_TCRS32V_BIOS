//##############################################################################
//
//	BIOS BOOTUPT
//
//	Modules Name	: bios_bu.c
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

//#define  	smonl(a,b)		smon(a,b)
#define  	smonl(a,b)		{ }

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
__att_noinline__	enum enum_res_ret	bu_fwld ( uint8_t  ld_opt, uint32_t ld_ef_badd ) {

	// #define		FW_SECT_SYSCFG_SEARCH	0x0
	// #define		FW_SECT_SYSCFG_USERSET	0x1
	// #define		FW_SECT_FWINFO_USERSET	0x2

	uint32_t	badd_syscfg;		uint32_t	nbyte_syscfg;		uint8_t		res_syscfg;
	uint32_t	badd_fwinfo;		uint32_t	nbyte_fwinfo;		uint8_t		res_fwinfo;
	uint32_t	badd_fw;		uint32_t	nbyte_fw;		uint8_t		res_fw;
	uint32_t	badd_fw_pm;		uint32_t	nbyte_fw_pm;		uint32_t	crc_fw_pm;
	uint32_t	badd_fw_dm;		uint32_t	nbyte_fw_dm;		uint32_t	crc_fw_dm;

	uint16_t	n_sys_write;

	uint32_t	nbyte;
	uint32_t	crc;

	uint32_t	nrpt, n, m;
	uint32_t	badd_syscfg_search;
	uint32_t	fail_code;

	uint32_t	nb_tr;		// nbye to read
	uint32_t	crc_tr;		// nbye current read
	uint32_t	nb_rm;		// nbye remained
	uint32_t	nb_cr;		// nbye current read
	uint32_t	badd_tgt;	// badd target
	uint32_t	badd_ef;	// badd EFlash


	badd_fwinfo	= ld_ef_badd;

	res_syscfg	= RES_FAIL;
	res_fwinfo	= RES_FAIL;
	res_fw		= RES_FAIL;
	fail_code	= FAIL_NONE;


	smonl ( st16[0], 0x1000 );


	if (ld_opt==FW_SECT_FWINFO_USERSET) {
		badd_fwinfo	= ld_ef_badd;
		goto	LB_READ_FWINFO;
	}

	//--------------------------------------------------------------------------------
	//--	SYSCFG : SEARCH and READ
	//--------------------------------------------------------------------------------
//LB_READ_SYSCFG:
	
	smonl ( st16[0], 0x2000 );

	//--	REPEAT Searching
	for ( nrpt=0; nrpt<10; nrpt++ ) {

		smonl ( st16[1], nrpt );

		//------------------------------------------------------------
		//--	Search
		//------------------------------------------------------------
		for ( n=0; n<3 ; n++ ) {

			smonl ( st16[2], n );

			//delay_nop(1000);

			smonl ( st16[0], 0x2210 );

			//--	Search BADD
			if ( ld_opt == FW_SECT_SYSCFG_SEARCH ) {

				smonl ( st16[0], 0x2220 );

				if	(n==0)	badd_syscfg_search = ( 128 - 4 ) * 1024;
				if	(n==1)	badd_syscfg_search = ( 256 - 4 ) * 1024;
				if	(n==2)	badd_syscfg_search = ( 512 - 4 ) * 1024;

			} else if ( ld_opt == FW_SECT_SYSCFG_USERSET ) {

				smonl ( st16[0], 0x2230 );

				badd_syscfg_search = ld_ef_badd;
			}

			smonl ( st16[0], 0x2300 );


			smonl ( d32[0], badd_syscfg_search );
			smonl ( d32[1], 32 );

			//--	Read EF
			ef_read ( badd_syscfg_search,  32, (uint8_t*) &(gss.buf8[0]) );

			smonl ( st16[0], 0x2400 );

			//--	Check Signature
			if (	  (gss.buf32[0]==0x20220101)
				| (gss.buf32[1]==0x5E1D0010) ) {

				smonl ( st16[0], 0x2410 );

			} else {
				smonl ( st16[0], 0x2420 );

				continue;
			}

			smonl ( st16[0], 0x2500 );

			//--	check nbyte valid
			nbyte = gss.buf32[4];		// nbyte of TABLE_SYSCFG, Word[0x08] ~ nbyte
			crc   = gss.buf32[5];
			
			smonl ( st16[0], 0x2510 );
			smonl ( d32[0], nbyte );
			smonl ( d32[1], crc   );

			if (nbyte>256) {
				smonl ( st16[0], 0x2520 );

				fail_code = FAIL_CODE_SYSCFG_FAIL;
				goto  LB_OUTRO;
			}

			smonl ( st16[0], 0x2600 );

			//--	Read SYSCFG  ( from ef32[8] ~ )
			badd_syscfg = badd_syscfg_search;

			smonl ( st16[0], 0x2610 );
			smonl ( d32 [0], badd_syscfg );

			ef_read ( badd_syscfg + 32, nbyte, (uint8_t*) &gss.buf8[32] );

			smonl ( st16[0], 0x2700 );
			
			//--	check CRC

			smonl ( st16[0], 0x2700 );

			//--	Get frequency 
			if (gss.buf32[8]!=0xFFFFFFFF) {
				smonl ( st16[0], 0x2710 );
				gss.freq_ohf = gss.buf32[8];
			}

				smonl ( st16[0], 0x2800 );

			//--	FW_0 ID
			if ( gss.buf32[16]==0x5E1D00F0 ) {
				smonl ( st16[0], 0x2810 );
				if ( gss.buf32[17]< 1024*1024 ) {
					smonl ( st16[0], 0x2820 );
					badd_fwinfo	= gss.buf32[17];
					goto	LB_READ_FWINFO;
				}
				smonl ( st16[0], 0x2830 );
			}
		}
	}

	smonl ( st16[0], 0x2A00 );

	if ( (nrpt==10) & (n==3) ) {
		smonl ( st16[0], 0x2A10 );
		fail_code = FAIL_CODE_SYSCFG_FAIL;
		goto	LB_OUTRO;
	}


	//--------------------------------------------------------------------------------
	//--	FWINFO : READ
	//--------------------------------------------------------------------------------
LB_READ_FWINFO:

	smonl ( st16[0], 0x3000 );

	n_sys_write = 0;

	for (nrpt=0 ; nrpt<5; nrpt ++ ) {

		smonl ( st16[1], nrpt );
		smonl ( st16[0], 0x3100 );

		//delay_nop(1000);

		//--	Read
		ef_read ( badd_fwinfo, 32, (uint8_t*) gss.buf8) ;

		smonl ( st16[0], 0x3110 );

		//--	Check Signature
		if (	  (gss.buf32[0]==0x20220101)
			| (gss.buf32[1]==0x5E1D00F0) ) {

			smonl ( st16[0], 0x3120 );
		} else {
			smonl ( st16[0], 0x3130 );
			continue;
		}

		smonl ( st16[0], 0x3200 );

		//--	Check nbyte valid
		nbyte = gss.buf32[4];		// nByte of FWINFO  Word [0x08] ~ nbyte
		crc   = gss.buf32[5];

		smonl ( st16[0], 0x3210 );

		if (nbyte>1024) {
			smonl ( st16[0], 0x3220 );
			fail_code = FAIL_CODE_FWINFO_FAIL;
			goto LB_OUTRO;
		}
	
			smonl ( st16[0], 0x3300 );

		//--	Read FWINFO ( from ef32[8] ~ )
		ef_read ( badd_fwinfo + 32, nbyte, (uint8_t*) &gss.buf8[32] );

			smonl ( st16[0], 0x3310 );

		//--	Check CRC
		
			smonl ( st16[0], 0x3400 );

		//--	BOOT_SPIM_CLKDIV, BOOT_SPIM_OPTION
		if ( (gss.buf32[0x20]==0xFFFFFFFF) ) {

		} else {
			smonl ( st16[0], 0x3420 );
			sSPIM.clk_div = gss.buf32[0x20];
		}

			smonl ( st16[0], 0x3500 );

		//--	SYS_WRITE
		if (	  ( gss.buf32[0x24] == 0xFFFFFFFF ) 
			| ( gss.buf32[0x24] >  128 )  ) {

			smonl ( st16[0], 0x3510 );

		} else {
			smonl ( st16[0], 0x3520 );

			n_sys_write = gss.buf32[0x24];

			for ( n=0 ; n< n_sys_write ; n++ ) {
				set_mem ( gss.buf32[0x26 + 2*n + 0], gss.buf32[0x26 + 2*n + 1] ); 
			}
		}

			smonl ( st16[0], 0x3600 );

		//--	PM / DM Information
		badd_fw_pm  = gss.buf32[0x10];
		nbyte_fw_pm = gss.buf32[0x11];
		crc_fw_pm   = gss.buf32[0x12];

		badd_fw_dm  = gss.buf32[0x14];
		nbyte_fw_dm = gss.buf32[0x15];
		crc_fw_dm   = gss.buf32[0x16];
	
			smonl ( st16[0], 0x3700 );

		goto	LB_READ_FW;
	}

	smonl ( st16[0], 0x3800 );

	if ( nrpt==5 ) {
		smonl ( st16[0], 0x3810 );

		fail_code = FAIL_CODE_FWINFO_FAIL;
		goto LB_OUTRO;
	}


	//--------------------------------------------------------------------------------
	//--	FW_CONTENTS : READ
	//--------------------------------------------------------------------------------
LB_READ_FW:

	smonl ( st16[0], 0x4000 );

	//--	PM / DM
	for ( nrpt=0 ; nrpt<2 ; nrpt++ ) {

		smonl ( st16[1], nrpt );
		smonl ( st16[0], 0x4000 );

		//--	Argument
		if ( nrpt==0 ) {	
			smonl ( st16[0], 0x4010 );
			badd_tgt = 0x60000000;    		// MB or PB
			badd_ef  = badd_fw_pm;  
			nb_tr    = nbyte_fw_pm;    
			nb_rm    = nbyte_fw_pm;    
			crc_tr   = crc_fw_pm;  
		} else if ( nrpt==1 ) {
			smonl ( st16[0], 0x4020 );
			badd_tgt = 0x40000000;    		// MA : DM
			badd_ef  = badd_fw_dm;  
			nb_tr    = nbyte_fw_dm;    
			nb_rm    = nbyte_fw_dm;    
			crc_tr   = crc_fw_dm;  
		}

		smonl ( st16[0], 0x4100  );
		smonl ( d32 [0], badd_tgt);
		smonl ( d32 [1], badd_ef );
		smonl ( d32 [2], nb_tr   );
		smonl ( d32 [3], nb_rm   );
		smonl ( d32 [4], crc_tr  );

		//--	CRC clear
		smonl ( st16[0], 0x4110 );
		

		//--	PM/DM pointer
		mem8_fwld_tgt	= (uint8_t  *) badd_tgt;	// host read data port, argument
		mem16_fwld_tgt	= (uint16_t *) mem8_fwld_tgt;		
		mem32_fwld_tgt	= (uint32_t *) mem8_fwld_tgt;			

		smonl ( st16[0], 0x4200 );

		//--	Pre-setting
		sSYSC.ctrl_st = SYSC_SR_PAD1_BY_MB | SYSC_SR_PAD2_BY_MC;
			
		smonl ( st16[0], 0x4210 );

		//--	nb_tr loop
		for ( n=0 ; n<1024 ; n++ ) {

			smonl ( st16[2], n );
			smonl ( st16[0], 0x4300 );

			//--	check before read
			if	( nb_rm>=NB_FW_READ )	nb_cr = NB_FW_READ;
			else				nb_cr = nb_rm;

			smonl ( st16[0], 0x4400 );
			smonl ( d32[0], n );
			smonl ( d32[1], nb_rm );
			smonl ( d32[2], nb_cr );

			//--	Read FWINFO ( from ef32[8] ~ )
			ef_read ( badd_ef + n*NB_FW_READ, nb_cr, (uint8_t*) &gss.buf8[0] );

			smonl ( st16[0], 0x4500 );

			//--	Copy Contents
			for ( m=0 ; m<nb_cr/4 ; m++ ) {
				smonl ( d32[0], (uint32_t) mem32_fwld_tgt );
				smonl ( d32[1], NB_FW_READ );
				smonl ( d32[2], n );
				smonl ( d32[3], m );
				smonl ( d32[4], n*NB_FW_READ + m);
				smonl ( d32[5], gss.buf32[m] );
				mem32_fwld_tgt[n*NB_FW_READ/4 +m] = gss.buf32[m];
			}

				smonl ( st16[0], 0x4600 );

			//--	CRC calculation
			
				smonl ( st16[0], 0x4610 );

			//--	update after read
			nb_rm = nb_rm - nb_cr;
				smonl ( st16[0], 0x4620 );

			//--	Check the end of read
			if (nb_rm==0) {
				smonl ( st16[0], 0x4630 );
				break;
			}
				smonl ( st16[0], 0x4650 );
		}

				smonl ( st16[0], 0x4700 );

		//--	Post-setting
		sSYSC.ctrl_st = SYSC_SR_PAD1_BY_MB | SYSC_SR_PAD2_BY_PC	;

				smonl ( st16[0], 0x4710 );

		//--	Check
		if (n==1024) {
			smonl ( st16[0], 0x4720 );
			fail_code = FAIL_CODE_FW_FAIL;
			goto LB_OUTRO;
		}
	}

			smonl ( st16[0], 0x4720 );

	//--------------------------------------------------------------------------------
	//--	OUTRO
	//--------------------------------------------------------------------------------
LB_OUTRO:

			smonl ( st16[0], 0x5000 );

	if ( fail_code == FAIL_NONE ) {
		smonl ( st16[0], 0x5010 );
		return	RES_OK;
	} else {
		smonl ( st16[0], 0x5020 );
		return	RES_FAIL;
	}
}
