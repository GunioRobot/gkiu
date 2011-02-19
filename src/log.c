/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * log.c
 * Copyright (C) gqq team 2011 <gqq@freelists.org>
 * 
 * gkiu is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gkiu is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h> 
#include <stdio.h>
#include <unistd.h>

#include "i18n.h"
#include "config.h"
#include "log.h"

FILE *flog = NULL;

/**
   log_open:
   Open the log file

   Return value: If opened, return FILE pointer. Or exit application.
 */
FILE *
log_open()
{
	GString *path = cfg_getdir (); /* May not be free */
	g_string_append (path, "/applog");
	fflush(stdout);
	flog = fopen (path->str, "w+");
	if(flog == NULL)
	{
		g_error( _("Could not open log file!") );
		_exit(1);
	}
	return flog;
}

/**
   log_print:
   @str: String will write.
   Write String to log file.
   Return value: See #RetureValue of #log_print_ex().
 */
int
log_print(char *str)
{
	return log_print_ex(str, flog);
}

/**
   log_print_ex:
   @str: the string will write.
   @fp: Write to.
   Write to log file (Need file pointer)
   Return value: Less than 0 means failed.
 */
int
log_print_ex(char *str, 
             FILE *fp)
{
	int ret = fprintf(fp, "%s\n", str);
	fflush(fp);
	return ret;
}

/**
   log_close:
   Close log file.
   Return Value: Less than 0 means failed.
 */
int
log_close()
{
	return fclose(flog);
}
