#ifndef _ARGS_H_
#define _ARGS_H_
#define MAX_PORT_SIZE	8
#define MAX_SERVER_SIZE 256
#define MAX_STRATEGY_SIZE 256
#define MAX_ARG_SIZE 256
#define MAX_DNS 512

typedef struct args_s {
	char port[MAX_PORT_SIZE];
	char server[MAX_SERVER_SIZE];
	char strategy[MAX_STRATEGY_SIZE];
	char argstrat[MAX_ARG_SIZE];
} args_t;

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

extern args_t argument;
void help_fonction();
int args(int , char**);

#endif

