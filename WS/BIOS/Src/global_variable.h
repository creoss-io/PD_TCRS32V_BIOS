//##############################################################################
//
//	Global Variable
//
//	Modules Name: crs32v_int.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V Global Variable
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//
//##############################################################################

#ifndef		__GLOBAL_VARIABLE_H__
#define		__GLOBAL_VARIABLE_H__


//--------------------------------------------------------------------------------
//--	DMA Mem : HDP
//--------------------------------------------------------------------------------
#define		POS_BADR_HWDP	(0     )	// Host write, HWDP, TX_DMA : Host -> I2CS -> DMAMEM0
#define		POS_BADR_HRDP	(512-8)	// Host read , HRDP, RX_DMA : Host <- I2CS <- DMAMEM0

#define		POS_HTST_IN_HRDP16	2
#define		POS_HAUX_IN_HRDP16	3

#define		set_htst(a)	hrdp16[POS_HTST_IN_HRDP16]=a
#define		get_htst()	(hrdp16[POS_HTST_IN_HRDP16])

#define		set_haux(a)	hrdp16[POS_HAUX_IN_HRDP16]=a
#define		get_haux()	(hrdp16[POS_HAUX_IN_HRDP16])

extern	uint8_t  *	volatile	hwdp8;		// host write data port
extern	uint16_t *	volatile	hwdp16;		
extern	uint32_t *	volatile	hwdp32;		

extern	uint8_t  *	volatile	hrdp8;		// host read data port
extern	uint16_t *	volatile	hrdp16;		
extern	uint32_t *	volatile	hrdp32;		

extern	uint8_t  *	volatile	hwdp8_arg;	// host write data port, argument
extern	uint16_t *	volatile	hwdp16_arg;		
extern	uint32_t *	volatile	hwdp32_arg;		

extern	uint8_t  *	volatile	hrdp8_arg;	// host read data port, argument
extern	uint16_t *	volatile	hrdp16_arg;		
extern	uint32_t *	volatile	hrdp32_arg;		

extern	uint8_t  *	volatile	mem8_fwld_tgt;	// FWLD Target Address
extern	uint16_t *	volatile	mem16_fwld_tgt;		
extern	uint32_t *	volatile	mem32_fwld_tgt;		

//--------------------------------------------------------------------------------
//--	Host Interface Communication
//--------------------------------------------------------------------------------
extern	uint16_t	volatile	hcmd;
extern	uint16_t	volatile	harg;
extern	uint8_t		volatile	hcmd_trig;

extern	uint16_t	volatile	htst;
extern	uint16_t	volatile	haux;

//--------------------------------------------------------------------------------
//--	GSS : Global System Structure
//--------------------------------------------------------------------------------
enum	enum_mode_hintn		{ MODE_HINTN_OD = 0, MODE_HINTN_PP = 1 };
enum	enum_hintn_assert	{ MODE_HINTN_NOCHANGE_AFTER_HCMD = 0,  MODE_HINTN_ASSERT_AFTER_HCMD = 1 };

enum	enum_opt_spim_rd	{ OPT_SPIM_RD_SINGLE = 0x0, OPT_SPIM_RD_DUAL = 0x1, OPT_SPIM_RD_QUAD = 0x2 };
enum	enum_opt_spim_sclk	{ OPT_SPIM_SCLK_SYS_DIV16 = 0x0, OPT_SPIM_SCLK_SYS_DIV8 = 0x1, OPT_SPIM_SCLK_SYS_DIV4 = 0x2, OPT_SPIM_SCLK_SYS_DIV2 = 0x3 };
enum	enum_opt_spim_mode_block{ OPT_SPIM_BLOCK=0x0 };	// , OPT_SPIM_NONBLOCK=0x1 };
enum	enum_opt_spim_n_rch	{ OPT_SPIM_RCH1 =0x0, OPT_SPIM_RCH2=0x1 };


enum	enum_buopt_fwld_skip	{ BUOPT_FWLD_SKIP_OFF =0x0, BUOPT_FWLD_SKIP_ON =0x1 };
enum	enum_buopt_fw_autorun	{ BUOPT_FW_AUTORUN_OFF=0x0, BUOPT_FW_AUTORUN_ON=0x1 };

enum	enum_res_ret		{ RES_OK=0x0, RES_FAIL=0x1 };

struct	struct_gss	{

	enum	enum_mode_hintn		mode_hintn;
	enum	enum_hintn_assert	mode_hintn_assert;
	enum	enum_opt_spim_rd	opt_spim_rd;
	enum	enum_opt_spim_sclk	opt_spim_sclk;

	enum	enum_buopt_fwld_skip	buopt_fwld_skip;
	enum	enum_buopt_fw_autorun	buopt_fw_autorun;

	enum	enum_opt_spim_mode_block	opt_spim_mode_block;
	enum	enum_opt_spim_n_rch	opt_spim_n_rch;

	uint8_t				buf8[512+32];
	uint16_t *			buf16;
	uint32_t *			buf32;

	uint32_t			freq_ohf;
}	;	


extern	volatile	struct		struct_gss	gss;




#define		FW_SECT_SYSCFG_SEARCH	0x0
#define		FW_SECT_SYSCFG_USERSET	0x1
#define		FW_SECT_FWINFO_USERSET	0x2


//#define		RES_FAIL		0x0
//#define		RES_OK			0x1


#define		FAIL_NONE		0x00000000
#define		FAIL_CODE_SYSCFG_FAIL	( (0xE550 << 16) | 0x0101 )
#define		FAIL_CODE_FWINFO_FAIL	( (0xE550 << 16) | 0x0102 )
#define		FAIL_CODE_FW_FAIL	( (0xE550 << 16) | 0x0103 )

#define		NB_FW_READ		(512)

#endif	//	__GLOBAL_VARIABLE_H__
