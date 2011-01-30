#ifndef DEBUG_H
#define DEBUG_H

// If debug
//#define DEBUG

// Infomation to...
enum
{
	DBG_TERM,
	DBG_FLOG,
	DBG_NONE,
};

// functions
void dbg_init(int to);
void dbg_print(char *dbg);
void dbg_close();

#endif