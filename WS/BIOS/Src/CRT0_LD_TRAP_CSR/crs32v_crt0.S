###############################################################################
#
#	CRS32V CRT0
#
#	Modules Name	: crs32v_crt0.S
#	Company		: Creoss Inc
#
#----------------------------------------------------------------------
#	[Functional Description]
#
#		- CRS32V CRT0
#
#----------------------------------------------------------------------
#	[Revistion History]
#
#		[V0.7.0]	: 2021.05.26, Steve Yun
#			- changed file name : str -> crs
#
#		[V0.6.0]	: 2021.05.11, Steve Yun
#			- removed CSR.mtra related, used CSR.mepc as return address
#			- return to crt_trap_pop_rf
#
#		[V0.6.0]	: 2021.05.10, Steve Yun
#			- moved "copying CSR.mtra to CSR.mepc"
#				- separated crt_trap_pop_rf to crt_int_pop_rf/crt_exc_pop_rf
#				- from the beginning of interrupt service to the beginning of crt_int_pop_rf
#
#		[V0.2.0]	: 2021.04.29, Steve Yun
#			- adjusting CSR.mepc for interrupt
#
#		[V0.1.1]	: 2021.04.29, Steve Yun
#			- disabled CSR.mstatus.MIE=0
#
#		[V0.0.1]	: 2020.12.22, Steve Yun
#			- first draft
#
###############################################################################






#======================================================================
# includes & definitions
#======================================================================

.equ		TRAP_STACK_SIZE, 120	# 4-byte/register, total 30 registers (except X0, X2)




#======================================================================
# reset
# 	- after reset : _start
#	- when trap : _trap_vector
#======================================================================
.section	.vectors, "ax"			# ax : Allocable, eXecutable
.option		norvc				# RISC-V option : don't use RV compresssed instructions for trap vectors

	# gobal
	.global		_start
	.global		_trap_vector_table

	.global		crt_trap_irq_00
	.global		crt_trap_irq_01
	.global		crt_trap_irq_02
	.global		crt_trap_irq_03
	.global		crt_trap_irq_04
	.global		crt_trap_irq_05
	.global		crt_trap_irq_06
	.global		crt_trap_irq_07
	.global		crt_trap_irq_08
	.global		crt_trap_irq_09
	.global		crt_trap_irq_10
	.global		crt_trap_irq_11
	.global		crt_trap_irq_12
	.global		crt_trap_irq_13
	.global		crt_trap_irq_14
	.global		crt_trap_irq_15


	#-------------------------------------------------------------
	# reset
	#-------------------------------------------------------------
	_start:
		j	_boot_init			# boot up


	
	#-------------------------------------------------------------	
	# trap vector table
	#-------------------------------------------------------------
	_trap_vector_table :

		#-------------------------------------------	
		# trap vector table : standard
		#-------------------------------------------
		_trap_vector_standard:

			# 00 : exception handler
			j	crt_trap_exc

			# 01 ~ 02 : not available
			j	crt_trap_na
			j	crt_trap_na

			# 03 : machine software interrupt
			j	crt_trap_msi

			# 04 ~ 06 : not available
			j	crt_trap_na
			j	crt_trap_na
			j	crt_trap_na

			# 07 : machine timer interrupt
			j	crt_trap_mti

			# 08 ~ 10 : not available
			j	crt_trap_na
			j	crt_trap_na
			j	crt_trap_na

			# 11 : machine external interrupt
			j	crt_trap_mei

			# 12 ~ 15 : not available
			j	crt_trap_na
			j	crt_trap_na
			j	crt_trap_na
			j	crt_trap_na


		#-------------------------------------------
		# trap vector table : custom
		#-------------------------------------------
		_trap_vector_custom :

			j	crt_trap_irq_00
			j	crt_trap_irq_01
			j	crt_trap_irq_02
			j	crt_trap_irq_03
			j	crt_trap_irq_04
			j	crt_trap_irq_05
			j	crt_trap_irq_06
			j	crt_trap_irq_07
			j	crt_trap_irq_08
			j	crt_trap_irq_09
			j	crt_trap_irq_10
			j	crt_trap_irq_11
			j	crt_trap_irq_12
			j	crt_trap_irq_13
			j	crt_trap_irq_14
			j	crt_trap_irq_15


		#-------------------------------------------
		# trap vector table : wrong addressing
		#-------------------------------------------	
		_trap_vector_wrong :
			j	crt_trap_wrong










#======================================================================
# trap handler & boot-up initialization
#======================================================================
.section	.text
.option		rvc				# RISC-V option : use RV compresssed instructions

	# global : trap handler
	.global		_trap_handler_exc			# exception
	.global		_trap_handler_msi			# machine software interrupt
	.global		_trap_handler_mti			# machine timer    interrupt
	.global		_trap_handler_mei			# machine external interrupt
	.global		_trap_handler_irq_00			# machine IRQ_00   interrupt
	.global		_trap_handler_irq_01			# machine IRQ_01   interrupt
	.global		_trap_handler_irq_02			# machine IRQ_02   interrupt
	.global		_trap_handler_irq_03			# machine IRQ_03   interrupt
	.global		_trap_handler_irq_04			# machine IRQ_04   interrupt
	.global		_trap_handler_irq_05			# machine IRQ_05   interrupt
	.global		_trap_handler_irq_06			# machine IRQ_06   interrupt
	.global		_trap_handler_irq_07			# machine IRQ_07   interrupt
	.global		_trap_handler_irq_08			# machine IRQ_08   interrupt
	.global		_trap_handler_irq_09			# machine IRQ_09   interrupt
	.global		_trap_handler_irq_10			# machine IRQ_10   interrupt
	.global		_trap_handler_irq_11			# machine IRQ_11   interrupt
	.global		_trap_handler_irq_12			# machine IRQ_12   interrupt
	.global		_trap_handler_irq_13			# machine IRQ_13   interrupt
	.global		_trap_handler_irq_14			# machine IRQ_14   interrupt
	.global		_trap_handler_irq_15			# machine IRQ_15   interrupt

	# global : C default
	.global		_init
	.global		_fini

	# global : boot init
	.global		_boot_init

	# global : print function
	.global		print_str

	# global : main
	.global		main



	#-------------------------------------------------------------
	# trap : not available
	#	- unlimited loop with message
	#-------------------------------------------------------------
	crt_trap_na:
		la	a0, _msg_trap_na
		jal	ra, print_str
		j	crt_trap_na

	
	
	#-------------------------------------------------------------
	# trap : wrong
	#	- this address cannot be executed
	#	- unlimited loop with message
	#-------------------------------------------------------------
	crt_trap_wrong:
		la	a0, _msg_trap_wrong
		jal	ra, print_str
		j	crt_trap_wrong



	#-------------------------------------------------------------
	# trap : exception handler
	#-------------------------------------------------------------
	crt_trap_exc :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_exc			# jump to each trap handler



	#-------------------------------------------------------------
	# trap : machine interrupt handler
	#-------------------------------------------------------------
	
	crt_trap_msi :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_msi			# jump to each trap handler
	
	crt_trap_mti :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_mti			# jump to each trap handler

	crt_trap_mei :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_mei			# jump to each trap handler



	#-------------------------------------------------------------
	# trap : custome interrupt handler
	#-------------------------------------------------------------

	crt_trap_irq_00 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_00			# jump to each trap handler

	crt_trap_irq_01 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_01			# jump to each trap handler

	crt_trap_irq_02 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_02			# jump to each trap handler

	crt_trap_irq_03 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_03			# jump to each trap handler

	crt_trap_irq_04 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_04			# jump to each trap handler

	crt_trap_irq_05 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_05			# jump to each trap handler

	crt_trap_irq_06 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_06			# jump to each trap handler

	crt_trap_irq_07 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_07			# jump to each trap handler

	crt_trap_irq_08 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_08			# jump to each trap handler

	crt_trap_irq_09 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_09			# jump to each trap handler

	crt_trap_irq_10 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_10			# jump to each trap handler

	crt_trap_irq_11 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_11			# jump to each trap handler

	crt_trap_irq_12 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_12			# jump to each trap handler

	crt_trap_irq_13 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_13			# jump to each trap handler

	crt_trap_irq_14 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_14			# jump to each trap handler

	crt_trap_irq_15 :
		addi	sp, sp, -TRAP_STACK_SIZE		# reserve stack space for trap
		sw	x1, 0*4(sp)				# push X1(=ra) first for call/ret in trap
		jal	ra, crt_trap_push_rf			# call-short push_rf
		la	ra, crt_trap_pop_rf			# save return address of each trap handler
		j	_trap_handler_irq_15			# jump to each trap handler


	
	#-------------------------------------------------------------
	# trap : push register files
	#	- X0 is tied to 0
	#	- X1 is already pushed before push_rf
	#	- X2 is stack pointer which is global variable
	#-------------------------------------------------------------	
	crt_trap_push_rf:
		sw	 x3,  1*4(sp)
		sw	 x4,  2*4(sp)
		sw	 x5,  3*4(sp)
		sw	 x6,  4*4(sp)
		sw	 x7,  5*4(sp)
		sw	 x8,  6*4(sp)
		sw	 x9,  7*4(sp)
		sw	x10,  8*4(sp)
		sw	x11,  9*4(sp)
		sw	x12, 10*4(sp)
		sw	x13, 11*4(sp)
		sw	x14, 12*4(sp)
		sw	x15, 13*4(sp)
		sw	x16, 14*4(sp)
		sw	x17, 15*4(sp)
		sw	x18, 16*4(sp)
		sw	x19, 17*4(sp)
		sw	x20, 18*4(sp)
		sw	x21, 19*4(sp)
		sw	x22, 20*4(sp)
		sw	x23, 21*4(sp)
		sw	x24, 22*4(sp)
		sw	x25, 23*4(sp)
		sw	x26, 24*4(sp)
		sw	x27, 25*4(sp)
		sw	x28, 26*4(sp)
		sw	x29, 27*4(sp)
		sw	x30, 28*4(sp)
		sw	x31, 29*4(sp)
		ret

	#-------------------------------------------------------------
	# trap : pop register files
	#	- X0 is tied to 0
	#	- X1 should be popped here
	#	- X2 is stack pointer which is global variable
	#-------------------------------------------------------------	
	crt_trap_pop_rf:
		lw	 x1,  0*4(sp)
		lw	 x3,  1*4(sp)
		lw	 x4,  2*4(sp)
		lw	 x5,  3*4(sp)
		lw	 x6,  4*4(sp)
		lw	 x7,  5*4(sp)
		lw	 x8,  6*4(sp)
		lw	 x9,  7*4(sp)
		lw	x10,  8*4(sp)
		lw	x11,  9*4(sp)
		lw	x12, 10*4(sp)
		lw	x13, 11*4(sp)
		lw	x14, 12*4(sp)
		lw	x15, 13*4(sp)
		lw	x16, 14*4(sp)
		lw	x17, 15*4(sp)
		lw	x18, 16*4(sp)
		lw	x19, 17*4(sp)
		lw	x20, 18*4(sp)
		lw	x21, 19*4(sp)
		lw	x22, 20*4(sp)
		lw	x23, 21*4(sp)
		lw	x24, 22*4(sp)
		lw	x25, 23*4(sp)
		lw	x26, 24*4(sp)
		lw	x27, 25*4(sp)
		lw	x28, 26*4(sp)
		lw	x29, 27*4(sp)
		lw	x30, 28*4(sp)
		lw	x31, 29*4(sp)
		addi	sp, sp, TRAP_STACK_SIZE			# remove stack space for trap 
		mret						# interrupt enabled automatically



	#-------------------------------------------------------------
	# C default
	#	no need to do anything because we use init_array/fini_array
	#-------------------------------------------------------------
	_init:
	_fini:
  		ret



	#-------------------------------------------------------------
	# boot initialization
	#-------------------------------------------------------------
	_boot_init:
		# disable global interrupt : CSR.mstatus.MIE=0
		csrci	mstatus, 8
	
		# set CSR.mtvec for trap vector start address
		la	x2, _trap_vector_table
		csrr	x3, mtvec
		andi	x3, x3, 1
		or	x2, x3, x2
		csrw	mtvec, x2
		
		# clear register files
		mv	 x1, zero
		mv	 x2, zero
		mv	 x3, zero
		mv	 x4, zero
		mv	 x5, zero
		mv	 x6, zero
		mv	 x7, zero
		mv	 x8, zero
		mv	 x9, zero
		mv	x10, zero
		mv	x11, zero
		mv	x12, zero
		mv	x13, zero
		mv	x14, zero
		mv	x15, zero
		mv	x16, zero
		mv	x17, zero
		mv	x18, zero
		mv	x19, zero
		mv	x20, zero
		mv	x21, zero
		mv	x22, zero
		mv	x23, zero
		mv	x24, zero
		mv	x25, zero
		mv	x26, zero
		mv	x27, zero
		mv	x28, zero
		mv	x29, zero
		mv	x30, zero
		mv	x31, zero
	
		# set stack pointer
		la	x2, _stack_start
	
		# clear BSS
	_boot_clear_bss_start:
		la	x26, _bss_start
		la	x27, _bss_end
		bge	x26, x27, _boot_libc_init
	
	_boot_clear_bss_loop:
		sw	x0, 0(x26)
		addi	x26, x26, 4
		ble	x26, x27, _boot_clear_bss_loop

		# TODO : needed? : run global initialization functions	
	_boot_libc_init:
		#call	__libc_init_array

		# enable global interrupt : CSR.mstatus.MIE=1
		#csrsi	mstatus, 8			# need to enable in main F/W
	
		# call main program : argc=0, argv=0
		mv	x10, zero
		mv	x11, zero
		jal	ra, main			# call main

		# flush instrucion cache
		# 	nothing to do for flushing instruction cache
		#  	because rtl.plc_flush_cache_o will be generated automatically after reset

		# exit
	_main_exit:
		la	a0, _msg_exit
		jal	ra, print_str
		j	_main_exit










#======================================================================
# data
#======================================================================
.section .rodata

	# trap not available
	_msg_trap_na:
		.string	"Invoked trap is not available!!!\n"

	# trap wrong
	_msg_trap_wrong:
		.string	"Wrong trap has been invoked !!!\n"

	# exit
	_msg_exit:
		.string	"Exit !!!\n"
