/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * config.h
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

#ifndef CONFIG_H
#define CONFIG_H

/*
 Define config item here.
 */
#define CFG_LISTS				"Lists"
#define CFG_LISTS_USRLIST		"UsrList"

/*
 Functions
 */
void cfg_init ();
void cfg_chkdir();
void cfg_chkusrdir();
GString *cfg_getdir();
GString *cfg_getusrdir();
void cfg_chkcfg();
void cfg_save ();
void cfg_close();

/*
 Functions for GKIU
 */
void cfg_get_lists_usrlist (void (*callback)(gchar *usr));
void cfg_set_lists_usrlist (gchar **list, gsize len);
void cfg_add_user_to_list (char *usrnam);
#endif
