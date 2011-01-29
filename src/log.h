#ifndef LOG_H
#define LOG_H

FILE *log_open();
int log_print(char *str);
int log_print_ex(char *str, FILE *fp);
int log_close();

#endif