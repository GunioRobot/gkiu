/*
 * debug.c
 *
 * Copyright (C) 2011 - GQQ Team <gqq@freelists.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "log.h"
#include "debug.h"

int infoto;

/**
 Init debug system.
 */
void
dbg_init(int to)
{
	infoto = to;
	if(infoto == DBG_FLOG)
	{
		log_open ();
	}
}

/**
 Print debug info.
 */
void
dbg_print(char *str)
{
	switch(infoto)
	{
		case DBG_TERM:
			log_print_ex(str, stdout);
			break;
		case DBG_FLOG:
			log_print(str);
			break;
		default:
			break;
	}
}

void
dbg_close()
{
	if(infoto == DBG_FLOG)
		log_close();
}