#include "dns.h"
#include "dns_etape0.h"
#include "log_dns.h"
#include <resolv.h>

int initLog(void* param){
	printf("Domain names requested :\n");
	UNUSED(param);
	return 0;
}

int addLog(logMsg_t* message){
	int i = 0;
	while (message->msg[i+12] != 0){
			int j = message->msg[i+12];
			for(int k = 0; k < j; k++)
					printf("%c", message->msg[i+12+k+1]);
			
			if(message->msg[i+12+j+1] != 0)
				printf(".");
			i+=j+1;
	}
	printf("\n");
	return 0;
}

