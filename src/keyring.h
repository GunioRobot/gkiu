#ifndef KEYRING_H
#define KEYRING_H

#define KEYRING_NAME "GKiu_Password"

void keyring_savepwd (const char *usr, const char *pwd);
void keyring_findpwd (const char *usr, char *pwd_buf);
void keyring_delpwd (const char *usr);

#endif