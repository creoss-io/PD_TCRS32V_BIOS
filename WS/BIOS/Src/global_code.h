//##############################################################################
//
//	Global Code
//
//	Modules Name: crs32v_code.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V Global Code
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//
//##############################################################################

#ifndef		__GLOBAL_CODE_H__
#define		__GLOBAL_CODE_H__


//--------------------------------------------------------------------------------
//--	HTST, HAUX
//--------------------------------------------------------------------------------
#define		HTST_NONE		( 0x0000 )
#define		HTST_BIOS		( 0x4000 )
#define		HTST_BIOS_AUX		( 0x4000 | 0x1000)
#define		HTST_BIOS_BUSY		( 0x4000 | 0x8000)

#define		HAUX_NONE		( 0xB000 )
#define		HAUX_BU_ING		( 0xB010 )
#define		HAUX_BU_OK		( 0xB011 )
#define		HAUX_BU_FORCE_BIOS	( 0xB012 )
#define		HAUX_FWLD_SKIP		( 0xB020 )
#define		HAUX_FWLD_OK		( 0xB021 )
#define		HAUX_FWLD_FAIL		( 0xB022 )
#define		HAUX_HCMD_SERVICE	( 0xB030 )





#endif	//	__GLOBAL_CODE_H__
