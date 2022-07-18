#include "shmem.h"
#include "args.h"


int index_in_mem = 0;
int shmid;

int initAdr(redirection *adr,int k){

	
	if(adr == NULL){
		printf("erreur initAdr\n");
		exit(-1);
	}
	strcpy(adr[k].domain,"");
	strcpy(adr[k].ipv4,"");
	strcpy(adr[k].ipv6,"");
	strcpy(adr[k].mail,"");
	
	return 0;
}

int initShm(redirection **adresse){

	//ouverture de shared mem
	 shmid = shmget(KEY,sizeof(redirection) * SIZE, IPC_CREAT|0666);
	if(shmid == -1){
		perror("initSh , shmget\n");
		exit(-1);
	}
	
	//shamt retourne l'@ de la shm attachee
	//a verifier sa siganture par man :)
	
	//adresse = (redirection*)
	*adresse=shmat(shmid,0,0);
/*	if (adresse == (redirection*)-1){
	       perror("initSh , shmat\n");
	       exit(-1);
	}*/
  	
	int k = 0;
	while(k < MAX_REDIR){
		initAdr(*adresse,k);
		k++;
	}
	return 0;
}

int closeShm(redirection adresse[MAX_REDIR]){

	//shmdt pour detacher les shm(s)
	if(shmdt(adresse) != -1){
	
		if(shmctl(shmid,IPC_RMID,NULL) == -1){
	       	perror("closeShm , shmdt\n");}
	       	exit(-1);
	}
	
	printf("close shmid fini\n");
	return 0;
}

/*
int free_redirections(redirection adresse[MAX_REDIR]){
		int i=0;
		while (){
				free(adresse[i]);
				i++;
		}
		return 0;
}*/

int affiche_redir(redirection adresse[]){
		for(int i=0; i<MAX_REDIR; i++){
				if (strcmp(adresse[i].domain,"")!=0){
							printf("%s\n", adresse[i].domain);
							printf("%s\n", adresse[i].ipv4);	
							printf("%s\n", adresse[i].ipv6);
							printf("%s\n", adresse[i].mail);
				}
		}

		return 0;
}

