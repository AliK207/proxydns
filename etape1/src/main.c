#include "dns.h"
#include "dns_etape0.h"
#include "libreseau.h"
#include "args.h"
#include "log_dns.h"
#include "genericLog.h"
#include <signal.h>
#include <stdlib.h>

struct sigaction action;

int server = -1;

void hand(int sig){
	if(sig == SIGINT){

		printf("SIGINT RECU == FIN PROGRAMME\n");
		
	
		if(close_file() == 0) 
			printf("fichier ferme avec succes\n");
		
		if(close_dl() == 0)
			printf("dl fermee avec succes\n");

		exit(SIGINT);
	}
}

int traitement(unsigned char *message, int nboc, struct sockaddr *addresse, int taille) {
	
	unsigned char buffer[MAX_DNS];
	int recus = messageUDP(argument.server, argument.port, message, nboc, buffer);
       	sendto(server, buffer, recus, 0, addresse, taille);
       	return 1;

}

int main(int argc, char* argv[]) {

	action.sa_handler = hand;
	sigaction(SIGINT,&action,NULL);
	
	args(argc, argv);
	printf("Paramètres actuels : hote=%s, service=%s\n",argument.port,argument.server);

	loadStrategy(argument.strategy);
	initStrategy(argument.argstrat);
	server = initialisationSocketUDP(argument.port);
	boucleServeurUDP(server, traitement);
	
	return 0;
}


