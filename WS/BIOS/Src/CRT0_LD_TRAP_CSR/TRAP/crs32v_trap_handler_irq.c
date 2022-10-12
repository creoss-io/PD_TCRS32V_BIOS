// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.




#include	<global_include.h>

void	_trap_handler_msi()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_msi();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_mti()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mti();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_mei()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mei();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_00()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_00();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_01()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_01();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_02()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_02();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_03()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_03();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_04()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_04();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_05()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_05();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_06()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_06();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_07()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_07();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_08()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_08();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_09()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_09();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_10()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_10();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_11()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_11();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_12()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_12();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_13()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_13();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_14()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_14();
	csr_write(mepc, _trap_mepc_keep_buf);
}

void	_trap_handler_irq_15()	{
	unsigned int	_trap_mepc_keep_buf = csr_read(mepc);	// push for nested exception
	crs32v_trap_mfi_15();
	csr_write(mepc, _trap_mepc_keep_buf);
}
