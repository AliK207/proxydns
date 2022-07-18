#include "dns.h"
#include "dns_etape0.h"
#include "libreseau.h"
#include "args.h"
#include "shmem.h"
#include "log_dns.h"
#include "genericLog.h"
#include <signal.h>
#include <stdlib.h>



struct sigaction action;

static int server = -1;
redirection *adresse = NULL;

void hand(int sig){
	if(sig == SIGINT){
		printf("ARRET DU PROGRAMME\n");
		if (strcmp(argument.argstrat,"")!=0){
			log_stop=1;
			printf("on libere le verrou pour leave while\n");
			V(1); //on libere le verrou pour terminer la boucle while 			
			P(2);
			printf("on a reussi a recup le verrou de fin\n");
		}
		
		freeMemory();
		if (strcmp(argument.config,"")!=0){
				closeShm(adresse);
		}
		printf("on free la mem\n");
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
		P(1);
		if(log_stop!=0){
			break;
		}
		P(0);
		//pthread_mutex_lock(&plein);

		void* donnee = readMemory(&taille);

		if(taille != 0){
		
			logMsg_t m;
			
			memcpy(m.msg, donnee, taille);
			m.size = taille;
			(*logStrategy)(&m);
			
		}
		V(0);
		//pthread_mutex_unlock(&vide);
		
	}
	printf("normalement le while s'arrete\n");
	close_logs();
	printf("logs closed\n");
	V(2); //on libere le verrou de fin pour permettre l'execution des instructions de SIGINT
	//pthread_detach(pthread_self());
	printf("verrou de fin libéré et fin du thread\n");
	return NULL;
}

void *thread_requete(void* arg){

	unsigned char rep[MAX_DNS];
	unsigned char * requete = ((struct param_requete*)arg)->requete;
	struct sockaddr* address = ((struct param_requete*)arg)->address;
	int nboc = ((struct param_requete*)arg)->nboctets;
	int size_addr = ((struct param_requete*)arg)->size_addr;

	if(strcmp(argument.strategy,"")!=0){
		P(0);
		//pthread_mutex_lock(&vide);
		if (writeMemory((void*)requete,nboc)!=0) {
	// cas d'erreur
			perror("thread_requete fnct\n");
			exit(EXIT_FAILURE);
		}	
		V(0);
		//pthread_mutex_unlock(&plein);
		V(1);
	

	}
	int recus = messageUDP(argument.server, argument.port, requete, nboc, rep);
	if(server >= 0){
		querySend(server,rep,recus,address,size_addr);
	}
	
	return NULL;


}

int traitement(unsigned char* message, int nboc, void* addresse, int taille){
	
	struct param_requete par;
	memcpy(par.requete,message,nboc);
	par.nboctets = nboc;
	par.address = addresse;
	par.size_addr = taille;


	launchThread(thread_requete,(void*)&par, sizeof(struct param_requete));

	return 0;

}


void read_conf(char* file){
	FILE *f;
	f=fopen(file, "r");
	int index=0;
	char ligne[300];
	const char* sep=",=";
	while (fgets(ligne, 300, f)!=NULL)
	{
		redirection red;
		char* token=strtok(ligne,sep);
      		if (token!=NULL)
		strcpy(red.domain,token);

		token=strtok(NULL,sep);
                if (token!=NULL)
                strcpy(red.ipv4,token);

		token=strtok(NULL,sep);
                if (token!=NULL)
                strcpy(red.ipv6,token);

		token=strtok(NULL,sep);
                if (token!=NULL)
                strcpy(red.mail,token);
		
	//	adresse[index]=red;		
		memcpy(&adresse[index],&red,sizeof(redirection));
		index++;
		
	}
	affiche_redir(adresse);

	fclose(f);

}




int main(int argc, char* argv[]) {

	action.sa_handler = hand;
	sigaction(SIGINT,&action,NULL);
	
	args(argc, argv);
	printf("Paramètres actuels : hote=%s, service=%s\n",argument.port,argument.server);
	
	server = initialisationSocketUDP(argument.port);
	if(server < 0){
		perror("server dans le main \n");
		exit(EXIT_FAILURE);
	}
	
	if(allocateMemory(512)){
		perror("AllocateMemory Main\n");
		exit(EXIT_FAILURE);
	}
	
	init_mutex(10);
	if(strcmp(argument.strategy, "") != 0)
		launchThread(&thread_log, NULL, 0);
	if(strcmp(argument.config, "") != 0){
		
		initShm(&adresse);
		read_conf(argument.config);
	}
		


	boucleServeurUDP(server, traitement);
	
	
	
	return 0;
}

