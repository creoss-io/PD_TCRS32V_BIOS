// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.



#include	<global_include.h>


void print_str(const char *p)
{
	while (*p != '\0') {
		if (*p == '\n') {
			uart_tx_byte('\r');
			uart_tx_byte(*(p++));
		}
		else if (*p == '\t') {
			uart_tx_byte(' ');
			uart_tx_byte(' ');
			uart_tx_byte(' ');
			uart_tx_byte(' ');
			uart_tx_byte(' ');
			uart_tx_byte(' ');
			p++;
		}
		else {
			uart_tx_byte(*(p++));
		}
	}
}

void print_hex(unsigned int val, int digits)
{
	for (int i = (4*digits)-4; i >= 0; i -= 4)
		uart_tx_byte("0123456789ABCDEF"[(val >> i) % 16]);
}
