/***************************************************************************
  *
  * keyring.c
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

#include <gnome-keyring.h>
#include <glib.h>
#include <string.h>

#include "i18n.h"
#include "keyring.h"

/**
 Save a password to default keyring.
 */
static void
save_callback (GnomeKeyringResult result,
               gpointer data)
{
	if (result != GNOME_KEYRING_RESULT_OK)
		g_warning (_("Couldn't save the password. %s"),
		           gnome_keyring_result_to_message (result));
}
void 
keyring_savepwd (const char *usr, 
                 const char *pwd)
{
	GString *des = g_string_new ("");
	g_string_sprintf (des, "GKiu_%s", usr);
	gnome_keyring_store_password (GNOME_KEYRING_NETWORK_PASSWORD,
	                              GNOME_KEYRING_DEFAULT,
	                              des->str, pwd, 
	                              &save_callback,
	                              NULL/*user data*/, NULL /*destory modify*/,
	                              /* User attributes */
	                              "user", usr,
	                              "server", "gkiu",
	                              NULL); /* End with NULL */
	g_string_free (des, TRUE);
}

/**
 Find the password of a user
 */
void
keyring_findpwd (const char *usr, 
                 char **pwd_buf)
{
	gnome_keyring_find_password_sync (GNOME_KEYRING_NETWORK_PASSWORD,
	                                  pwd_buf, 
	                                  "user", usr, 
	                                  "server", "gkiu",
	                                  NULL);
}

/**
 Delete a password from default keyring
 */
void 
keyring_delpwd (const char *usr)
{
	int ret =
	gnome_keyring_delete_password_sync (GNOME_KEYRING_NETWORK_PASSWORD,
	                                    "user", usr,
	                                    "server", "gkiu",
	                                    NULL);
	if (ret != GNOME_KEYRING_RESULT_OK)
	{
		g_warning (_("Couldn't delete the password. %s"),
		           gnome_keyring_result_to_message (ret));
	}
}