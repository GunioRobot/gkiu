#ifndef DEBUG_H
#define DEBUG_H

// If debug
#define DEBUG

// Infomation to...
enum
{
	DBG_TERM, /* -> stdout         */
	DBG_FLOG, /* -> ~/.gkiu/applog */
	DBG_NONE  /* -> ???            */
};

// functions
void dbg_init(int to);
void dbg_print(char *dbg);
void dbg_close();

#endif