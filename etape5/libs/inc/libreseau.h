#ifndef _LIBRESEAU_H_
#define _LIBRESEAU_H_
#include "libthread.h"
#include "memoire.h" 

int initialisationSocketUDP(char *service);
int messageUDP(char *hote, char *service, unsigned char *message, int taille, unsigned char *buffer);
int boucleServeurUDP(int s, int (*traitement)(unsigned char *, int, void *, int));
int querySend(int, unsigned char* , int , struct sockaddr*, int );
#endif
