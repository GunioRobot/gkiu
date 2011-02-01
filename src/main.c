/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
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

#include <string.h>
#include <stdio.h>

#include <gtk/gtk.h>
#include <libintl.h>
#include <glib/gi18n.h>

#include "i18n.h"
#include "config.h"
#include "keyring.h"
#include "debug.h"
#include "uilogin.h"

/**
 * Main Function
 */
int
main (int argc, 
      char *argv[])
{
 	GtkWidget *lw_window;

	/* Config */
	cfg_init ();
	
	/* Debug */
#ifdef DEBUG
	dbg_init(DBG_TERM);
#else
	dbg_init(DBG_FLOG);
#endif
	dbg_print("DBG: Debug system is init!");
	
	/* I18n */
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
	gtk_set_locale ();
	
	/* Init GTK+ */
	gtk_init (&argc, &argv);

	/* Show login window */
	lw_window = lw_create ();
	gtk_widget_show_all (lw_window);
	gtk_main ();

	/* Clean up */
	dbg_close (); /* it will call log_close() */
	cfg_close ();
	
	return 0;
}
