/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 *   This file is part of the Linux kernel, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#ifndef		__PRINTF__H__
#define		__PRINTF__H__

#include	<global_include.h>


/*
 * Oh, it's a waste of space, but oh-so-yummy for debugging.  This
 * version of printf() does not include 64-bit support.  "Live with
 * it."
 *
 */

int sprintf(char *buf, const char *fmt, ...);
int crs32v_printf(const char *fmt, ...);



#endif	//	__PRINTF__H__
