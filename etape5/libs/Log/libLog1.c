#include "dns.h"
#include "dns_etape0.h"
#include "log_dns.h"

static FILE* f = NULL;

int initLog(void* param){
	f=fopen(param, "w");
	fprintf(f,"debut de initlog\n");
	
	fflush(f);
	return 0;
}

int addLog(logMsg_t* message){

	fprintf(f,"Requete recue :\n");
	fflush(f);

	for (int i=0; i<message->size; i++){
		fprintf(f,"%2.2x ",message->msg[i]);
		fflush(f);

	}
	fprintf(f,"\n");
	fflush(f);
	

	return 0;
}

int closeLog(){
		if (f!=NULL){
				fclose(f);
				return 0;
		}
		return -1;
}




