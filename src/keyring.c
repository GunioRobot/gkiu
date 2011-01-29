/***************************************************************************
  *
  * keyring.c
  *
  * Copyright (C) 2011 - Mike Ma
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

#include "i18n.h"
#include "keyring.h"

gboolean success = FALSE;

/**
 Create a new keyring.
 */
void keyring_init ()
{
	if (gnome_keyring_create_sync (KEYRING_NAME, NULL) != GNOME_KEYRING_RESULT_OK)
	{
		g_warning (_("Could not create GNOME keyring: %s!"), KEYRING_NAME);
		return;
	}
	success = TRUE;
}

void keyring_savepwd (const char *usr, const char *pwd)
{
}