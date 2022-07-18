#include "../inc/libthread.h"
#include "../inc/log_dns.h"

typedef struct fnc_arg{
  
        void *args;
  	void *(*fonction)(void*);
}fnc_arg;

void* interm_fct(void* tab){

        fnc_arg * tmp_tab = tab;
	tmp_tab->fonction(tmp_tab->args);
	free(tmp_tab->args);
	free(tab);
        return NULL;
}


void init_mutex(){
	pthread_mutex_init(&vide,NULL);
	pthread_mutex_init(&plein,NULL);
	pthread_mutex_lock(&plein);
	
}
/*
int init_mutexes(){
	for (int i=0; i<NB_VERROUS; i++){
                pthread_once(&once, init_mutex(i));
        }
        return 0;
}*/


int launchThread(void *(*fonction)(void *), void *arg, size_t argSize){
		
		void *tab_arg;
		if(argSize > 0){
		
			tab_arg = malloc(argSize);
			memcpy(tab_arg, arg, argSize);
		}
		
		fnc_arg* arg2 = malloc(sizeof(fnc_arg));
		
		arg2->args = tab_arg;
		arg2->fonction = fonction;


		pthread_t tid;
		pthread_create(&tid,NULL,interm_fct,arg2);

		pthread_detach(tid);			
		return 0;
		
}

/*
void P(int i){
        if (i>NB_VERROUS-1){
                perror("cant lock mutex");
                exit(-1);
        }
        pthread_mutex_lock(&verrous[i]);
}

void V(int i){
        if (i>NB_VERROUS-1){
                perror("cant unlock mutex");
                exit(-1);
        }               
        pthread_mutex_unlock(&verrous[i]);
}       
  */  
