#include "dns.h"
#include "dns_etape0.h"
#include "libreseau.h"
#include "args.h"
#include "log_dns.h"
#include "genericLog.h"
#include <signal.h>
#include <stdlib.h>
#include "libthread.h"
#include "memoire.h"



struct sigaction action;

static int server = -1;

void hand(int sig){
	if(sig == SIGINT){
		printf("ARRET DU PROGRAMME\n");
		freeMemory();
		if(strcmp(argument.argstrat,"")!=0)
			close_logs();
		exit(SIGINT);
	}
}


void* thread_log(){

		printf("je suis thread_log\n");	
		if(strcmp(argument.strategy,"") !=0 && strcmp(argument.argstrat,"") == 0){
			strcpy(argument.argstrat,"default_logs.txt");
		}
	//	if((*loadStrategy)(argument.strategy)){
		if(loadStrategy(argument.strategy)){
			perror("loadStrat\n");
			exit(EXIT_FAILURE);
		}


		if(initStrategy(argument.argstrat)){
			perror("initStrat\n");
			exit(EXIT_FAILURE);
		}

	while(1){
	
		uint8_t taille=0;
		pthread_mutex_lock(&plein);
		void* donnee = readMemory(&taille);

		if(taille != 0){
		
			logMsg_t m;
			
			memcpy(m.msg, donnee, taille);
			m.size = taille;
			(*logStrategy)(&m);
			
		//	free(donnee);
		}
		
		pthread_mutex_unlock(&vide);
		
	}

	return NULL;


}

void *thread_requete(void* arg){

	unsigned char rep[MAX_DNS];
	unsigned char * requete = ((struct param_requete*)arg)->requete;
	struct sockaddr* address = ((struct param_requete*)arg)->address;
	int nboc = ((struct param_requete*)arg)->nboctets;
	int size_addr = ((struct param_requete*)arg)->size_addr;

	if(strcmp(argument.strategy,"")!=0){
		pthread_mutex_lock(&vide);
		if (writeMemory((void*)requete,nboc)!=0) {
	// cas d'erreur
			perror("thread_requete fnct\n");
			exit(EXIT_FAILURE);
			}	
		pthread_mutex_unlock(&plein);
	

	}
	int recus = messageUDP(argument.server, argument.port, requete, nboc, rep);
	if(server >= 0)
		sendto(server,rep,recus,0,address,size_addr);

	return NULL;


}
/*
int traitement(unsigned char* message, int nboc, struct sockaddr* addresse, int taille){
	
	struct param_requete par;
	par.requete = message;
	par.nboctets = nboc;
	par.address = addresse;
	par.size_addr = taille;


	launchThread(thread_requete,(void*)&par, sizeof(struct param_requete));

	return 0;

} */

/*void *thread_requete(void* arg){
	//a mettre dans thread

	struct param_requete* par = (struct param_requete*)arg;
	unsigned char dns_rep[MAX_DNS];

	allocateMemory(par->nboctets);

	int recus  = messageUDP(argument.server,argument.port , par->requete, par->nboctets,dns_rep);

//	allocateMemory(par->nboctets);
	writeMemory((void*)par->requete, par->nboctets);
	int send_it = sendto(server, dns_rep, recus, 0, (struct sockaddr*)&(par->address), par->addr_size);
	if(send_it == -1){
		perror("messageUDP\n");
		exit(-1);
	}
	free(par->requete);
//	free(&(par->address));
	free(par);
	
		

	return NULL;
	
}*/


int traitement(unsigned char* message, int nboc, struct sockaddr* addresse, int taille){
	
	struct param_requete par;
	par.requete = message;
	par.nboctets = nboc;
	par.address = addresse;
	par.size_addr = taille;


	launchThread(thread_requete,(void*)&par, sizeof(struct param_requete));

	return 0;

} 

/*int traitement(unsigned char *message, int nboc, struct sockaddr *addresse, int taille) {
	:
	unsigned char buffer[MAX_DNS];
	int recus = messageUDP(argument.server, argument.port, message, nboc, buffer);
       	sendto(server, buffer, recus, 0, addresse, taille);
       	return 1;

}*/


//int traitement(unsigned char *message, int nboc, struct sockaddr *addresse, int taille){

	/*struct param_requete par;
	memcpy(par.requete, message,nboc);
	memcpy(&(par.address),addresse, taille);
	par.nboctets = nboc;
	par.addr_size = taille;
	launchThread(thread_requete, (void*)&par, sizeof(par));
	*/

/*	struct param_requete par;
	
	memcpy(par.requete, message,nboc);
	printf("trai=\n");
	memcpy(&par.address,addresse, taille);
	printf("trai=\n");
	par.nboctets = nboc;
	par.addr_size = taille;
	printf("trai=\n");

	launchThread(thread_requete,(void*)&par, sizeof(par));

	printf("trai_apres= \n");
	//en debuguant avec printf ;; je constate
	//que le probleme n'est pas dans cette fonction
	return 1;
}
*/


/*void* thread_log(void *arg){

	struct param_log* par = (struct param_log*)arg;
	uint8_t taille;
	logMsg_t req;

	if(loadStrategy(par->strategy) == -1){
	
		printf("Lib : %s n'est pas trouve\n",par->strategy);
		pthread_exit(NULL);
	}
	//init de strategy
	initStrategy(par->strat_par);

	while(1){
		memcpy(req.msg,(unsigned char*)readMemory(&taille),taille);
		logStrategy(&req);
	}
	return NULL;
	

}*/

int main(int argc, char* argv[]) {

	action.sa_handler = hand;
	sigaction(SIGINT,&action,NULL);
	
	args(argc, argv);
	printf("Paramètres actuels : hote=%s, service=%s\n",argument.port,argument.server);

	//loadStrategy(argument.strategy);
	//initStrategy(argument.argstrat);
//	launchThread(thread_log, argument.strategy, argument.argstrat);
	
	server = initialisationSocketUDP(argument.port);
	if(server < 0){
		perror("server dans le main \n");
		exit(EXIT_FAILURE);
	}
	
	if(allocateMemory(512)){
		perror("AllocateMemory Main\n");
		exit(EXIT_FAILURE);
	}
	
	init_mutex();
	if(strcmp(argument.strategy, "") != 0)
		launchThread(&thread_log, NULL, 0);

	boucleServeurUDP(server, traitement);
	
	
	
	return 0;
}


