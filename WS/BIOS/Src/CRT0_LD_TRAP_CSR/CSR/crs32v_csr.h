//##############################################################################
//
//	CRS32V CSR Access
//
//	Modules Name	: crs32v_csr.h
//	Company		: Creoss Inc
//
//----------------------------------------------------------------------
//	[Functional Description]
//
//		- CRS32V CSR Access functions
//
//----------------------------------------------------------------------
//	[Revision History]
//
//		[V0.7.0]	: 2022.05.26, Steve Yun
//			- changed name : str -> crs
//
//		[V0.0.1]	: 2021.04.26, Steve Yun
//			- first draft
//
//##############################################################################

#ifndef		__CRS32V_CSR_H__
#define		__CRS32V_CSR_H__



//======================================================================
// CSR Fast Interrupt Target Address from CRS32V_CRT0.S
//======================================================================
#define	BADR_CRT_TRAP_IRQ_00  0x000000fc	// <crt_trap_irq_00>:
#define	BADR_CRT_TRAP_IRQ_01  0x00000112	// <crt_trap_irq_01>:
#define	BADR_CRT_TRAP_IRQ_02  0x00000128	// <crt_trap_irq_02>:
#define	BADR_CRT_TRAP_IRQ_03  0x0000013e	// <crt_trap_irq_03>:
#define	BADR_CRT_TRAP_IRQ_04  0x00000154	// <crt_trap_irq_04>:
#define	BADR_CRT_TRAP_IRQ_05  0x0000016a	// <crt_trap_irq_05>:
#define	BADR_CRT_TRAP_IRQ_06  0x00000180	// <crt_trap_irq_06>:
#define	BADR_CRT_TRAP_IRQ_07  0x00000196	// <crt_trap_irq_07>:
#define	BADR_CRT_TRAP_IRQ_08  0x000001ac	// <crt_trap_irq_08>:
#define	BADR_CRT_TRAP_IRQ_09  0x000001c2	// <crt_trap_irq_09>:
#define	BADR_CRT_TRAP_IRQ_10  0x000001d8	// <crt_trap_irq_10>:
#define	BADR_CRT_TRAP_IRQ_11  0x000001ee	// <crt_trap_irq_11>:
#define	BADR_CRT_TRAP_IRQ_12  0x00000204	// <crt_trap_irq_12>:
#define	BADR_CRT_TRAP_IRQ_13  0x0000021a	// <crt_trap_irq_13>:
#define	BADR_CRT_TRAP_IRQ_14  0x00000230	// <crt_trap_irq_14>:
#define	BADR_CRT_TRAP_IRQ_15  0x00000246	// <crt_trap_irq_15>:
//#define	BADR_CRT_TRAP_IRQ_00  ((uint32_t) &crt_trap_irq_00)
//#define	BADR_CRT_TRAP_IRQ_01  ((uint32_t) &crt_trap_irq_01)
//#define	BADR_CRT_TRAP_IRQ_02  ((uint32_t) &crt_trap_irq_02)
//#define	BADR_CRT_TRAP_IRQ_03  ((uint32_t) &crt_trap_irq_03)
//#define	BADR_CRT_TRAP_IRQ_04  ((uint32_t) &crt_trap_irq_04)
//#define	BADR_CRT_TRAP_IRQ_05  ((uint32_t) &crt_trap_irq_05)
//#define	BADR_CRT_TRAP_IRQ_06  ((uint32_t) &crt_trap_irq_06)
//#define	BADR_CRT_TRAP_IRQ_07  ((uint32_t) &crt_trap_irq_07)
//#define	BADR_CRT_TRAP_IRQ_08  ((uint32_t) &crt_trap_irq_08)
//#define	BADR_CRT_TRAP_IRQ_09  ((uint32_t) &crt_trap_irq_09)
//#define	BADR_CRT_TRAP_IRQ_10  ((uint32_t) &crt_trap_irq_10)
//#define	BADR_CRT_TRAP_IRQ_11  ((uint32_t) &crt_trap_irq_11)
//#define	BADR_CRT_TRAP_IRQ_12  ((uint32_t) &crt_trap_irq_12)
//#define	BADR_CRT_TRAP_IRQ_13  ((uint32_t) &crt_trap_irq_13)
//#define	BADR_CRT_TRAP_IRQ_14  ((uint32_t) &crt_trap_irq_14)
//#define	BADR_CRT_TRAP_IRQ_15  ((uint32_t) &crt_trap_irq_15)

//======================================================================
// CSR Machine Custom Address
//======================================================================

// Stack Overflow/Underflow/Corruption Check
#define	mstack_ctrl		0xBC0
#define	mstack_sbadr	0xBC1
#define	mstack_ebadr	0xBC2
#define	mdm_sbadr		0xBC3
#define	mdm_ebadr		0xBC4

// Custom Interrupt Control & Status
#define	mcintclear		0xBD0
#define	mcintstatus		0xBD1
#define	mswint			0xBD2
#define	mtimectrl		0xBD3
#define	mtimepres		0xBD4
#define	mtimecmp		0xBD5
#define	mtime			0xBD6
#define	mficfg			0xBD7
#define	mtsf			0xBD8
#define	mfive			0xBD9

// Custom Fast Interrupt Vector
#define	mftvec_00		0xBE0
#define	mftvec_01		0xBE1
#define	mftvec_02		0xBE2
#define	mftvec_03		0xBE3
#define	mftvec_04		0xBE4
#define	mftvec_05		0xBE5
#define	mftvec_06		0xBE6
#define	mftvec_07		0xBE7
#define	mftvec_08		0xBE8
#define	mftvec_09		0xBE9
#define	mftvec_10		0xBEA
#define	mftvec_11		0xBEB
#define	mftvec_12		0xBEC
#define	mftvec_13		0xBED
#define	mftvec_14		0xBEE
#define	mftvec_15		0xBEF


//======================================================================
// CSR Register Bit Manipulation
//======================================================================

// MSTATUS register
#define	CSR_MSTATUS_MIE		0x8

// MIE register
#define	CSR_MIE_MSIE		0x8
#define	CSR_MIE_MTIE		0x80
#define	CSR_MIE_MEIE		0x800

#define	CSR_MIE_MFIE_00		0x00010000
#define	CSR_MIE_MFIE_01		0x00020000
#define	CSR_MIE_MFIE_02		0x00040000
#define	CSR_MIE_MFIE_03		0x00080000
#define	CSR_MIE_MFIE_04		0x00100000
#define	CSR_MIE_MFIE_05		0x00200000
#define	CSR_MIE_MFIE_06		0x00400000
#define	CSR_MIE_MFIE_07		0x00800000
#define	CSR_MIE_MFIE_08		0x01000000
#define	CSR_MIE_MFIE_09		0x02000000
#define	CSR_MIE_MFIE_10		0x04000000
#define	CSR_MIE_MFIE_11		0x08000000
#define	CSR_MIE_MFIE_12		0x10000000
#define	CSR_MIE_MFIE_13		0x20000000
#define	CSR_MIE_MFIE_14		0x40000000
#define	CSR_MIE_MFIE_15		0x80000000

#define	CSR_MIE_MFIE_ALL	0xffff0000




//======================================================================
// Function : CSR R/W
//======================================================================

#define csr_swap(csr, val)							\
({													\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrrw %0, " #csr ", %1"	\
			      : "=r" (__v) : "rK" (__v));		\
	__v;											\
})

#define csr_read(csr)								\
({													\
	register unsigned long __v;						\
	__asm__ __volatile__ ("csrr %0, " #csr			\
			      : "=r" (__v));					\
	__v;											\
})

#define csr_write(csr, val)							\
({													\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrw " #csr ", %0"		\
			      : : "rK" (__v));					\
})

#define csr_read_set(csr, val)						\
({													\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrrs %0, " #csr ", %1"	\
			      : "=r" (__v) : "rK" (__v));		\
	__v;											\
})

#define csr_set(csr, val)							\
({													\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrs " #csr ", %0"		\
			      : : "rK" (__v));					\
})

#define csr_seti(csr, val)							\
({													\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrsi " #csr ", %0"		\
			      : : "rK" (__v));					\
})

#define csr_read_clear(csr, val)					\
({													\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrrc %0, " #csr ", %1"	\
			      : "=r" (__v) : "rK" (__v));		\
	__v;											\
})

#define csr_clear(csr, val)							\
({													\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrc " #csr ", %0"		\
			      : : "rK" (__v));					\
})

#define csr_cleari(csr, val)						\
({													\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrci " #csr ", %0"		\
			      : : "rK" (__v));					\
})










//======================================================================
// Functions : Alias
//======================================================================
#define	csr_glb_int_enable()		csr_seti(mstatus, CSR_MSTATUS_MIE)
#define	csr_glb_int_disable()		csr_cleari(mstatus, CSR_MSTATUS_MIE)










//======================================================================
// Function : Routines
//======================================================================

void	csr_check();

void	csr_int_init_fast_int_vector();

void	csr_exc_init_stack_check();




#endif	//	__CRS32V_CSR_H__
