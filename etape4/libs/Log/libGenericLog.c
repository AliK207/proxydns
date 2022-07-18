#include <dlfcn.h>
#include "genericLog.h"
#include <stdio.h>
#include <stdlib.h>

void* handle;

int loadStrategy(char* bib_name){


 		handle = dlopen(bib_name, RTLD_LAZY | RTLD_NOW);

		if(!handle){
			fputs(dlerror(),stderr);
			return -1;
		}
		return 0;
}

int initStrategy(void* param){
		int (*init)(char*);
		init = dlsym(handle,"initLog"); 
		(*init)(param);
		return 0;
}

int logStrategy(logMsg_t *msg){

		int (*res)(logMsg_t*) ;
		res	= dlsym(handle,"addLog");
		(*res)(msg);
		return 0;
}


int close_logs(){
	int (*close)();
	close=dlsym(handle,"closeLog");	
	
	
	if((*close)()==-1)
		return -1;

	if(handle != NULL){
		dlclose(handle);
	}
	else 
		return -1;
	return 0;
}

