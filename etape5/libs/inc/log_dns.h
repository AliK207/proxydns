#ifndef _LOG_DNS_H_
#define _LOG_DNS_H_

#define UNUSED(x) (void)(x)
#include <fcntl.h>

typedef struct logMsg_s {
	int size;
	unsigned char msg[1];
}logMsg_t;



int initLog(void *);
int addLog(logMsg_t *);
int closeLog();
#endif
