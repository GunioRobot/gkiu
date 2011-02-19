/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
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

GString *cfg_dir = NULL;	/* ~/.gkiu				*/
GString *cfg_usrdir=NULL;   /* ~/.gkiu/users/xxxxx  */
GString *cfg_file= NULL;	/* ~/.gkiu/gkiu.conf	*/
GKeyFile* fcfg   = NULL;	/* ~/.gkiu/applog	    */

/**
   cfg_init:
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
   cfg_chkdir:
   Looking for directory this app needed. If any doesn't exist, create it.
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

	/* Check config directory */
	if (g_mkdir_with_parents(cfg_dir->str, 0777)!=0 )
	{
		g_error ( _("Could not create config directory: %s!"), cfg_dir->str);
		_exit(1);
	}
	
	/* Check users' directory */
	GString *tmp = g_string_new (cfg_dir->str);
	g_string_append (tmp, "/users");
	if (g_mkdir_with_parents(tmp->str, 0777) != 0)
	{
		g_error (_("Could not create config directory: %s!"), tmp->str);
		_exit (1);
	}
	g_string_free (tmp, TRUE);
}

/**
 Check the directory of current user
 */
void
cfg_chkusrdir (const char *user)
{
	cfg_usrdir = g_string_new (cfg_dir->str);
	g_string_append (cfg_usrdir, "/users/");
	g_string_append (cfg_usrdir, user);

	if (g_mkdir_with_parents (cfg_usrdir->str, 0777)!=0)
	{
		g_error (_("Could not create config directory: %s"), cfg_usrdir->str);
		_exit (1);
	}
}

/**
   cfg_chkcfg:
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
   cfg_getdir:
   Get config dir
   Return value: config directory in GString pointer.
 */
GString *
cfg_getdir ()
{
	return cfg_dir;
}

/**
   cfg_getusrdir:
   Get the dir of current user
 */
GString *
cfg_getusrdir ()
{
	return cfg_usrdir;
}

/**
   cfg_save:
   Save the config sets in buffer to config file.
   You should call it if modify any config.
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
   cfg_close:
   Close config file
   Should call once
 */
void
cfg_close()
{
	g_string_free (cfg_file, TRUE);
	g_string_free (cfg_dir, TRUE);
	g_string_free (cfg_usrdir, TRUE);
	g_key_file_free (fcfg);
}

/* --------------------------------------
            Functions for GKiu
   -------------------------------------- */

/**
   cfg_get_lists_usrlist:
   @callback: If found any usr, call it, cannot be NULL.
   Get config <Lists - UsrList>
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
   cfg_set_lists_usrlist:
   @list: The usr list.
   @len: How many user saved in the list.
   Set <Lists - UsrList>
 */
void
cfg_set_lists_usrlist (gchar **list,
                       gsize len)
{
	g_key_file_set_string_list (fcfg, CFG_LISTS, CFG_LISTS_USRLIST, list, len);
	cfg_save ();
}
/**
   cfg_add_user_to_list:
   @usrnam: The user name will save.
 */
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
