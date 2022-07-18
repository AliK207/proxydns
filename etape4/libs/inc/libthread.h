#ifndef _LIBTHREAD_H_
#define _LIBTHREAD_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "args.h"
#define MAX_MUTEX 10

typedef struct fnc_arg{

        void *args;
        void *(*fonction)(void*);
}fnc_arg;


extern int log_stop;
extern pthread_mutex_t tab_mutex[MAX_MUTEX];
int init_mutex();
int launchThread(void *(*)(void*),void*,size_t);
int P(int);
int V(int);

#endif
