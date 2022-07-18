#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "genericLog.h"
#include "testLog.h"

#define MAX_SIZE	100

void test_initLog(void* param){


	printf("Test initLog : ");
	assert(initLog(param) == 0);
	printf("SUCCESS\n");
}

void test_addLog(logMsg_t* message){

	printf("Test addLog : ");
	assert(addLog(message) == 0);
	printf("Success\n");
}

void test_closeLog(){

	printf("Test Close Log : ");
	assert(closeLog() == 0);
	printf("succes\n");
}

int main(){
	
	 char* MonMessage = "03www06google03com";
	
	logMsg_t m;// = {MAX_SIZE,MonMessage};
	char *para = "log2.txt";
	m.size = strlen((char*)MonMessage);
	memcpy(m.msg,MonMessage,m.size);

	test_initLog(para);
	test_addLog(&m);
	test_closeLog();

	return 0;
}

