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

#include <time.h>

#include <glib.h>
#include <gdbm.h> /* database */
#include "i18n.h"
#include "config.h"
#include "chatlog.h"

GString *cht_dir=NULL;
GDBM_FILE cht_file;
gboolean success=FALSE;

/* TODO: 测试这些函数 */

/**
   cht_chkdir:
  
   Looking for current user's chatlog directory.
 */
void
cht_chkdir ()
{
	cht_dir = g_string_new (cfg_getusrdir()->str);
	g_string_append (cht_dir, "/chatlog");
}

/**
   cht_getdir:
   
   Get current user's chatlog directory.
   
   Return value: The directory in GString pointer.
 */
GString *
cht_getdir ()
{
	return cht_dir;
}

/**
   cht_open:
   @to: The message has sent to. It needed by filename.   
   Open the database.
   Warning: Only #cht_add() can call it. You shouldn't call it.
 */
void 
cht_open (const char *to)
{
	/* 如果还在一个处理，先暂停1秒 */
	while (cht_file)
	{
		g_usleep (1 * G_USEC_PER_SEC);
	}

	GString *filename=g_string_new ("");
	g_string_printf (filename, "%s/chat_with_%s", cht_dir->str, to);
	if ((cht_file = gdbm_open(filename->str, -1, GDBM_WRCREAT, 0777, NULL)) == NULL)
	{
		g_warning (_("Cannot open database"));
		success = FALSE;
	}

	g_string_free (filename, TRUE);
}

/**
   cht_getdbobj:
   Get database object.
   
   Return Value: A GDBM object.
*/
GDBM_FILE
cht_getdbobj ()
{
	return cht_file;
}

/**
   cht_add:
   @from: the writer of this message.
   @to: this message has sent to.
   @msg: the context of this message.
   Add a message to database.
   It'll call #cht_open() and #cht_close(), so you needn't call it by yourself.
*/
void
cht_add (char *from,
		 char *to,
         char *msg)
{
	g_return_if_fail ((cht_file != NULL) && success);

	GString *tmstr = g_string_new ("");
	datum key, context;
	time_t timeval;
	struct tm *tmbuf;
	
	time (&timeval);
	tmbuf = localtime (&timeval);

	/* format */
	g_string_printf (tmstr, "%d-%d-%d %d:%d:%d %s -> %s", 
					 tmbuf->tm_year + 1900,
					 tmbuf->tm_mon + 1,
					 tmbuf->tm_mday,
					 tmbuf->tm_hour,
					 tmbuf->tm_min,
					 tmbuf->tm_sec,
					 to, from);

	key.dptr = tmstr->str;
	key.dsize = tmstr->len;

	context.dptr = msg;
	context.dsize = strlen (msg);

	/* write data. */
	cht_open (to);
	gdbm_store (cht_file, key, context, GDBM_REPLACE); /* if this key already exist, replace it */
	cht_close (FALSE); /* just kill current action. */

	g_string_free (tmstr, TRUE);
}

/**
   cht_fetchall:
   @callback: if get any message, call it.
   Search all messages.
*/
void 
cht_fetchall(void (*callback)(gchar *info, gchar *msg))
{
	datum key, context;
	key = gdbm_firstkey (cht_file);
	while (key.dptr)
	{
		context = gdbm_fetch(cht_file, key);
		(*callback)(key.dptr, context.dptr);

		key = gdbm_nextkey (cht_file, key);
	}
}

/**
   cht_del:
   Delete a message from database.
*/
void 
cht_del()
{
	g_return_if_fail ((cht_file != NULL) && success);

	/* TODO: complete this function */
}
\
/**
   cht_close:
   @block: if set to TRUE, free all allocated memories, and close database completely, should use if app will end. if set to FALSE, only close database object.
   Close current action and free memory.
*/
void
cht_close (gboolean block)
{
	if (block)
		g_string_free (cht_dir, TRUE);
	if (cht_file)
		gdbm_close (cht_file);
	cht_file = NULL; /* 结束，置0 */
}
