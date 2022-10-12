//##############################################################################
//
//	CRS32V IOPC
//
//	Modules Name	: crs32v_iopc.c
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V IOPC ( IO Pad Controller )
//
//----------------------------------------------------------------------
//	[Revision History]
//
//
//##############################################################################


#include	<global_include.h>


/*------------------------------------------------------------------------------------------------------------------------
 * @brief	
 * @details	Case Analysis ( in same mode, no issue )
 *
 * 		Before				After (change mode)
 * 		OD H	O=0  OE=0  ( floating )	OD H	         	O=0 OE=0	( change OE first )
 *                                              OD L			O=0 OE=1
 * 						PP H			O=1 OE=1	( change O first )
 * 						PP L			O=0 OE=1	( change O first )
 * 		OD L	O=0  OE=1  ( Push L )	OD H	         	O=0 OE=0	( change OE first )
 *                                              OD L			O=0 OE=1
 * 						PP H			O=1 OE=1	
 * 						PP L			O=0 OE=1	
 * 		PP H	O=1  OE=1  ( Push H )	OD H	OE=0 		O=0 OE=0	( change OE first )
 * 						OD L			O=0 OE=1
 *						PP H			O=1 OE=1	
 *                                              PP L			O=0 OE=1	
 * 		PP L	O=0  OE=1  ( Push L )	OD H	        	O=0 OE=0	( change O -> OE for fast signal change)
 * 						OD L			O=0 OE=1
 *						PP H			O=1 OE=1	
 *                                              PP L			O=0 OE=1	
 *
 *		Before			Pre-setting	After				
 * 		OD H   	O=0 OE=0        (OE=0)		OD H	O=0  OE=0  ( floating )	
 *              OD L	O=0 OE=1        (OE=0)		                                
 * 		PP H	O=1 OE=1        OE=0						
 * 		PP L	O=0 OE=1        (OE=0)       					
 * 		OD H   	O=0 OE=0        (OE=1)		OD L	O=0  OE=1  ( Push L )	
 *              OD L	O=0 OE=1        (OE=1)		                                
 * 		PP H	O=1 OE=1        (OE=1)						
 * 		PP L	O=0 OE=1        (OE=1)						
 * 		OD H	O=0 OE=0        	 	PP H	O=1  OE=1  ( Push H )	
 * 		OD L	O=0 OE=1        						
 *		PP H	O=1 OE=1        						
 *              PP L	O=0 OE=1        		                                
 * 		OD H	O=0 OE=0        		PP L	O=0  OE=1  ( Push L )	
 * 		OD L	O=0 OE=1        						
 *		PP H	O=1 OE=1        						
 *              PP L	O=0 OE=1        		                                
 *
 * 		Before				After (change mode)
 * 		OD H	O=0  OE=0  ( floating )	OD H	         	OE=0 O=0 	( change OE first )
 *                                              OD L			OE=1 O=0 
 * 		OD L	O=0  OE=1  ( Push L )	OD H	         	OE=0 O=0 	( change OE first )
 *                                              OD L			OE=1 O=0 
 * 		PP H	O=1  OE=1  ( Push H )	OD H	 		OE=0 O=0 	( change OE first )
 * 						OD L			OE=1 O=0 
 * 		PP L	O=0  OE=1  ( Push L )	OD H	        	OE=0 O=0 	( change O -> OE for fast signal change)
 * 						OD L			OE=1 O=0 
 *
 * 		OD H	O=0  OE=0  ( floating )	PP H			O=1 OE=1	( change O first )
 * 						PP L			O=0 OE=1	( change O first )
 * 		OD L	O=0  OE=1  ( Push L )	PP H			O=1 OE=1	
 * 						PP L			O=0 OE=1	
 * 		PP H	O=1  OE=1  ( Push H )	PP H			O=1 OE=1	
 *                                              PP L			O=0 OE=1	
 * 		PP L	O=0  OE=1  ( Push L )	PP H			O=1 OE=1	
 *                                              PP L			O=0 OE=1	
 *
 *
 *
 * @param	
 * @return	
 * @remark	
 * @bug	
 * @todo	
 * @warning	
 * @see	
*///----------------------------------------------------------------------------------------------------------------------
__att_noinline__	void	set_hintn ( uint8_t wd ) {
	if ( gss.mode_hintn == MODE_HINTN_OD ) {
		sIOPC.hintn_oe = (wd&0x1)^0x1;
		sIOPC.hintn_o  = 0x0;
	} else if ( gss.mode_hintn == MODE_HINTN_PP ) {
		sIOPC.hintn_o  = wd&0x1;
		sIOPC.hintn_oe = 0x1;
	}
}


