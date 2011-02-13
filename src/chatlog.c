/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * chatlog.c
 *
 * Copyright (C) 2011 - GQQ Team
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

/* TODO: 完成存密码 */

#include <glib.h>
#include <gdbm.h> /* database */
#include "config.h"

GString *cht_dir=NULL;
GDBM_FILE cht_obj;
gboolean success=FALSE;

void
cht_chkdir ()
{
	cht_dir = g_string_new (cfg_getusrdir()->str);
	g_string_append (cht_dir, "/chatlog");
}

GString *
cht_getdir ()
{
	return cht_dir;
}

void 
cht_open (const char *to)
{
	GString
	cht_obj = gdbm_open ();
}

void 
cht_add (const chat *to,
         const char *msg)
{
	/* TODO: 考虑多人时如何写数据 */
}

void
cht_close ()
{
}
