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
GString *cfg_getdir();
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