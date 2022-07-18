#ifndef _LIBTHREAD_H_
#define _LIBTHREAD_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../inc/args.h"
#define NB_VERROUS 255

struct param_requete{
	
	//unsigned char requete[MAX_DNS];
    	unsigned char * requete;
	int nboctets; 
	struct sockaddr* address;
	int size_addr;
};	
	
struct param_log{

	char strategy[MAX_STRATEGY_SIZE];
	void* strat_par;
};

pthread_t *ptid;

pthread_mutex_t vide, plein;
void init_mutex();
int launchThread(void *(*)(void*),void*,size_t);
#endif
