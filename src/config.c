/*
 * config.c
 *
 * Copyright (C) gqq team 2011 <gqq@freelists.org>
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
#include <glib.h>
#include <unistd.h>
#include "i18n.h"
#include "config.h"

GString *cfg_dir = NULL;
GString *cfg_file= NULL;
GKeyFile* fcfg    = NULL;

/**
 Init Config
 */
void
cfg_init ()
{
	if ((fcfg = g_key_file_new ()) == NULL)
	{
		g_error (_("Pointer is NULL!"));
		_exit (2);
	}

	cfg_chkdir ();
	cfg_chkcfg ();
	
	if (g_key_file_load_from_file (fcfg, cfg_file->str,
	                               G_KEY_FILE_NONE,
	                               NULL) == FALSE)
	{
		g_error (_("Could not read config file: %s!"), cfg_file->str);
		_exit (1);
	}
}

/**
 Does the computer have my config dir?
 If yes, it will return 0.
 */
void 
cfg_chkdir()
{
	cfg_dir = g_string_new (g_get_home_dir ());
	g_string_append(cfg_dir, "/.gkiu");
	if (cfg_dir == NULL)
	{
		g_error (_("Pointer is NULL!"));
		_exit(2);
	}
	if (g_mkdir_with_parents(cfg_dir->str, 0777)!=0 )
	{
		g_error ( _("Could not create config directory: %s!"), cfg_dir->str);
		_exit(1);
	}
}

/**
 Get config dir
 */
GString *
cfg_getdir ()
{
	return cfg_dir;
}

/**
 Check config file
 */
void
cfg_chkcfg()
{
	FILE *fp = NULL;
	cfg_file = g_string_new (cfg_dir->str);
	if(!cfg_file)
	{
		g_error (_("Pointer is NULL!"));
		_exit(2);
	}
	g_string_append (cfg_file, "/gkiu.conf");
	if (g_file_test (cfg_file->str, G_FILE_TEST_EXISTS) == FALSE)
	{
		fp = fopen (cfg_file->str, "w");
		if (fp == NULL)
		{
			g_error (_("Could not create config file: %s!"), cfg_file->str);
			_exit (1);
		}
		fclose (fp);
	}
}

/**
 Save config file
 */
void
cfg_save ()
{
	gchar *file_buf = NULL;
	
	if ((file_buf = g_key_file_to_data (fcfg,NULL,NULL)) == NULL)
	{
		g_error (_("Could not get config data!"));
		_exit (1);
	}

	if (g_file_set_contents (cfg_file->str, file_buf, -1, NULL) == FALSE)
	{
		g_error (_("Could not save config file: %s!"), cfg_file->str);
		_exit (1);
	}
}

/**
 Close config file
 */
void
cfg_close()
{
	g_key_file_free (fcfg);
}

/* --------------------------------------
            Functions for GKiu
   -------------------------------------- */

/**
 Get <Lists - UsrList>
 */
void
cfg_get_lists_usrlist (void (*callback)(gchar *usr))
{
	gchar **lst = NULL;
	gsize len = 0;
	gint i;
	lst = g_key_file_get_string_list (fcfg, CFG_LISTS, CFG_LISTS_USRLIST,
	                                  &len, NULL);
	for (i = 0; i < len; i++)
	{
		(*callback)(lst[i]);
	}
}

/**
 Set <Lists - UsrList>
 */
void
cfg_set_lists_usrlist (gchar **list,
                       gsize len)
{
	g_key_file_set_string_list (fcfg, CFG_LISTS, CFG_LISTS_USRLIST, list, len);
	cfg_save ();
}

void
cfg_add_user_to_list (char *usrnam)
{
	gchar **lst = NULL;
	gchar *tmp  = NULL;
	GString *buf = NULL;
	gsize len = 0;
	gint i;
	
	lst = g_key_file_get_string_list (fcfg, CFG_LISTS, CFG_LISTS_USRLIST,
	                                  &len, NULL);
	if (!lst)
		return;
	/* if the usrnam already exists */
	for(i=0; i<len; i++)
	{
		if (!strcmp(usrnam, lst[i]))
		{
			return;
		}
	}
	
	tmp = g_key_file_get_string (fcfg, CFG_LISTS, CFG_LISTS_USRLIST, NULL);
	buf = g_string_new (tmp);
	g_string_append (buf, usrnam);
	g_string_append (buf, ";");
	g_key_file_set_string (fcfg, CFG_LISTS, CFG_LISTS_USRLIST, buf->str);
	cfg_save ();
	/* clean up */
	g_strfreev (lst);
	g_free(tmp);
	g_string_free (buf, TRUE);
}