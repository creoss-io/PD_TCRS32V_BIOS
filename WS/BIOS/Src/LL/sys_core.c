//##############################################################################
//
//	CRS32V Core
//
//	Modules Name	: crs32v_core.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V Core
//
//----------------------------------------------------------------------
//	[Revision History]
//
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
void	__att_noinline__	jump_to_fw ( uint32_t badd_tgt_fw ) {

	jump_to_app_core ( badd_tgt_fw );

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
void	__att_noinline__	jump_to_app_core ( uint32_t target_address ) {

	//sMON.run_fw = target_address;	// FW Quick Loading in Simulation

	//------------------------------------------------------------
	// from sys_core.h
	//	typedef void (*FP_VOID)(void);
	//------------------------------------------------------------

	uint32_t	JumpAddress;
  	FP_VOID		_main_app;

	JumpAddress   = target_address;	
	_main_app     = (void *) JumpAddress;


	smon ( func_clear_all, 0 );

	_main_app ( );
}

