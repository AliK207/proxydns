#ifndef _LIBRESEAU_H_
#define _LIBRESEAU_H_

int initialisationSocketUDP(char *service);
int messageUDP(char *hote, char *service, unsigned char *message, int taille, unsigned char *buffer);
int boucleServeurUDP(int s, int (*traitement)(unsigned char *, int, struct sockaddr *, int));

#endif
