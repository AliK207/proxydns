#include "../inc/libthread.h"
#include "../inc/log_dns.h"

pthread_mutex_t tab_mutex[MAX_MUTEX];
int log_stop=0;

int init_mutex(int nb_mutex){
	for(int i=0; i<nb_mutex; i++){
		if(pthread_mutex_init(&tab_mutex[i],NULL)!=0){
			perror("erreur à l'initialisation du tableau de mutexs\n");
			return -1;
		}
	}
	if ((pthread_mutex_lock(&tab_mutex[1])!=0) || (pthread_mutex_lock(&tab_mutex[2])!=0)){
		perror("erreur au verouillage des mutexs à l'initialisation\n");
		return -1;
	}
	return 0;
}

int P(int indice_mutex){
	if (pthread_mutex_lock(tab_mutex+indice_mutex)!=0){
		perror("erreur fonction P\n");
		return -1;
	}
	return 0;
}

int V(int indice_mutex){
	if (pthread_mutex_unlock(tab_mutex+indice_mutex)!=0){
		perror("erreur fonction V\n");
		return -1;
	}
	return 0;
}


void* interm_fct(void* tab){

        fnc_arg * tmp_tab = tab;
	tmp_tab->fonction(tmp_tab->args);
	if(tmp_tab->args!=NULL)
		free(tmp_tab->args);
	free(tab);
        return NULL;
}


int launchThread(void *(*fonction)(void *), void *arg, size_t argSize){
		
		void *tab_arg=NULL;
		if(argSize > 0){
		
			tab_arg = malloc(argSize);
			memcpy(tab_arg, arg, argSize);
		}
		
		fnc_arg* arg2 = malloc(sizeof(fnc_arg));
		
		arg2->args = tab_arg;
		arg2->fonction = fonction;


		pthread_t tid;
		if(pthread_create(&tid,NULL,interm_fct,arg2)!=0){
			perror("erreur de pthread_create dans launchThread\n");
			return -1;
		}

		pthread_detach(tid);			
		return 0;
		
}

