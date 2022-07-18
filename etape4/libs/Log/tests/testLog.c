#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "genericLog.h"
#include "testLog.h"

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
	
	char param[MAX_SIZE]  = "param.txt";
	//unsigned char MonMessage[MAX_SIZE] =  "49d20100000100000000000003www06google03com6d0000010001";
	logMsg_t message;
       unsigned char MonMessage[MAX_SIZE] = "003www06google03com";	
	//unsigned char MonMessage[MAX_SIZE] = {0x03,'w','w','w',0x06,'g','o','o','g','l','e',0x03,'c','o','m'};
	message.size = strlen((char*)MonMessage);
	
	memcpy(message.msg,MonMessage, message.size);
	
	test_initLog(param);
	test_addLog(&message);
	test_closeLog();

	return 0;


}
