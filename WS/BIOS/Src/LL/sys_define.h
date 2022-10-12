//##############################################################################
//
//	CRS32V CORE
//
//	Modules Name	: sys_define.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V System Define
//
//----------------------------------------------------------------------
//	[Revistion History]
//
//		[V0.0.1]	
//
//##############################################################################


#ifndef		__SYS_DEFINE_H__
#define		__SYS_DEFINE_H__

#include	<global_include.h>

//======================================================================
// Function : Alias
//======================================================================

// Function : MEM R/W
#define		set_mem(badr, wdata)	(*((volatile uint32_t*)(badr)) = (uint32_t) wdata)
#define		get_mem(badr)		(*((volatile uint32_t*)(badr)))

//--------------------------------------------------------------------------------
//--	Compile Supporting
//--------------------------------------------------------------------------------
#define  	__att_noinline__	__attribute__ ((noinline))
#define  	__att_unused__		__attribute__ ((unused))
#define  	__att_inline__		__attribute__ ((inline))

//#define  	__att_noinline__	//__attribute__ ((noinline))
//#define  	__att_inline__		//__attribute__ ((inline))

//------------------------------------------------------------
//--	Function Pointer (void, no argument)
//------------------------------------------------------------
typedef void		(*FP_VOID)(void);
typedef void		(*FP_1ARG)(uint32_t arg0);
typedef void		(*FP_2ARG)(uint32_t arg0, uint32_t arg1 );
typedef void		(*FP_3ARG)(uint32_t arg0, uint32_t arg1, uint32_t arg2 );
typedef void		(*FP_4ARG)(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3 );

//------------------------------------------------------------
//--	NOP
//--	http://wiki.kldp.org/KoreanDoc/html/EmbeddedKernel-KLDP/app3.basic.html
//------------------------------------------------------------
#define		macro_nop_x1()		{ __asm__ volatile ( "nop\n\t" ::: ) ; }
#define		macro_nop_x2()		{ macro_nop_x1()   ;    macro_nop_x1()   ; }
#define		macro_nop_x4()		{ macro_nop_x2()   ;    macro_nop_x2()   ; }
#define		macro_nop_x8()		{ macro_nop_x4()   ;    macro_nop_x4()   ; }
#define		macro_nop_x16()		{ macro_nop_x8()   ;    macro_nop_x8()   ; }
#define		macro_nop_x32()		{ macro_nop_x16()  ;    macro_nop_x16()  ; }
#define		macro_nop_x64()		{ macro_nop_x32()  ;    macro_nop_x32()  ; }
#define		macro_nop_x128()	{ macro_nop_x64()  ;    macro_nop_x64()  ; }
#define		macro_nop_x256()	{ macro_nop_x128() ;    macro_nop_x128() ; }
#define		macro_nop_x512()	{ macro_nop_x256() ;    macro_nop_x256() ; }
#define		macro_nop_x1024()	{ macro_nop_x512() ;    macro_nop_x512() ; }
#define		macro_nop_x2048()	{ macro_nop_x1024();    macro_nop_x1024(); }
         
//------------------------------------------------------------
//--	Diff 32bit integer
//--	http://wiki.kldp.org/KoreanDoc/html/EmbeddedKernel-KLDP/app3.basic.html
//------------------------------------------------------------
#define		get_diff_3101_31b(x,y)	( ( ((0x80000000| (x>>1)       )-( (y>>1)       &(~0x80000000))) & 0x7FFFFFFF ) << 1 )
#define		get_diff_3000_31b(x,y)	  ( ((0x80000000| x            )-( y            &(~0x80000000))) & 0x7FFFFFFF )
#define		get_diff_3016_15b(x,y)	  ( ((0x80000000|(x&0xFFFF0000))-((y&0xFFFF0000)&(~0x80000000))) & 0x7FFFFFFF )


//----------------------------------------------------------------------------------------------------
//--	Define for DATA and TIME
//----------------------------------------------------------------------------------------------------
#define		__DEF_YEAR__		(	((__DATE__[ 7]-'0')*1000) +		\
						((__DATE__[ 8]-'0')* 100) +		\
						((__DATE__[ 9]-'0')*  10) +		\
						((__DATE__[10]-'0')*   1) 		\
					)

#define		__DEF_MONTH__		(	( (__DATE__[0]=='J')&&(__DATE__[1]=='a')&&(__DATE__[2]=='n') )	?	1	:		\
						( (__DATE__[0]=='F')&&(__DATE__[1]=='e')&&(__DATE__[2]=='b') )	?	2	:		\
						( (__DATE__[0]=='M')&&(__DATE__[1]=='a')&&(__DATE__[2]=='r') )	?	3	:		\
																		\
						( (__DATE__[0]=='A')&&(__DATE__[1]=='p')&&(__DATE__[2]=='r') )	?	4	:		\
						( (__DATE__[0]=='M')&&(__DATE__[1]=='a')&&(__DATE__[2]=='y') )	?	5	:		\
						( (__DATE__[0]=='J')&&(__DATE__[1]=='u')&&(__DATE__[2]=='n') )	?	6	:		\
																		\
						( (__DATE__[0]=='J')&&(__DATE__[1]=='u')&&(__DATE__[2]=='l') )	?	7	:		\
						( (__DATE__[0]=='A')&&(__DATE__[1]=='u')&&(__DATE__[2]=='g') )	?	8	:		\
						( (__DATE__[0]=='S')&&(__DATE__[1]=='e')&&(__DATE__[2]=='p') )	?	9	:		\
																		\
						( (__DATE__[0]=='O')&&(__DATE__[1]=='c')&&(__DATE__[2]=='t') )	?	10	:		\
						( (__DATE__[0]=='N')&&(__DATE__[1]=='o')&&(__DATE__[2]=='v') )	?	11	:		\
						( (__DATE__[0]=='D')&&(__DATE__[1]=='e')&&(__DATE__[2]=='c') )	?	12	:		\
															13			\
					)

#define		__DEF_DAY__		(	((__DATE__[ 4]==' ')) 					\
							?	((__DATE__[ 5]-'0')* 1) 		\
							:	((__DATE__[ 4]-'0')*10) +		\
								((__DATE__[ 5]-'0')* 1) 		\
					)

 
#define		__DEF_HOUR__		(	((__TIME__[ 0]-'0')*10) +		\
						((__TIME__[ 1]-'0')* 1) 		\
					)

#define		__DEF_MIN__		(	((__TIME__[ 3]-'0')*10) +		\
						((__TIME__[ 4]-'0')* 1) 		\
					)

#define		__DEF_SEC__		(	((__TIME__[ 6]-'0')*10) +		\
						((__TIME__[ 7]-'0')* 1) 		\
					)



#endif	//	__SYS_DEFINE_H__
