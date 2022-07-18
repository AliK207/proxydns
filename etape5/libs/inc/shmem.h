#ifndef _SHMEM_H_
#define _SHMEM_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>
#include "dns_etape0.h"
#define FILE_NAME	"../../src/config.txt"
#define KEY	(key_t)1000
#define SIZE	1000
#define MAX_SERVER_SIZE 256
#define MAX_REDIR 100

typedef struct redirection{
		char domain[MAX_DNS];
		char ipv4[MAX_SERVER_SIZE];
		char ipv6[MAX_SERVER_SIZE];
		char mail[MAX_SERVER_SIZE];
		int choice;
}redirection;


int initAdr(redirection *,int);
int initShm(redirection **);
int closeShm(redirection[MAX_REDIR]);
int free_redirections(redirection[]);
int affiche_redir(redirection[]);

#endif
