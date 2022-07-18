#ifndef _ARGS_H_
#define _ARGS_H_
#define MAX_PORT_SIZE	8
#define MAX_SERVER_SIZE 256
#define MAX_STRATEGY_SIZE 256
#define MAX_ARG_SIZE 256
#define MAX_DNS 512

#include "shmem.h"

typedef struct args_s {
	char port[MAX_PORT_SIZE];
	char server[MAX_SERVER_SIZE];
	char strategy[MAX_STRATEGY_SIZE];
	char argstrat[MAX_ARG_SIZE];
	char config[MAX_ARG_SIZE];
} args_t;
/*
typedef struct redirection{
		char domain[MAX_DNS];
		char ipv4[MAX_SERVER_SIZE];
		char ipv6[MAX_SERVER_SIZE];
		char mail[MAX_SERVER_SIZE];
		int choice;
}redirection;*/

struct param_requete{

        unsigned char requete[MAX_DNS];
        int nboctets;
        struct sockaddr* address;
        int size_addr;
};

struct param_log{

        char strategy[MAX_STRATEGY_SIZE];
        void* strat_par;
};

redirection* args_conf(int, char**);
extern args_t argument;
void help_fonction();
int args(int , char**);

#endif

