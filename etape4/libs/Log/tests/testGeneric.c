#include "genericLog.h"
#include "log_dns.h"
#include <stdio.h>          
#include <assert.h>
#include <unistd.h>
#include "testGeneric.h"

void test_loadStrategy(char *arg){

	printf("Test loadStrategy:=%s :",(char *)arg);
	assert(loadStrategy(arg)== 0);
	printf("Success\n");
	
}
void test_initStrategy(char *arg){

	printf("Test initStrategy =%s :",(char *)arg);
	assert(initStrategy(arg)== 0);
    	printf("Success\n");
   
}
void test_logStrategy(logMsg_t * msg){
	printf("Test logStrategy: ");
	assert(logStrategy(msg)== 0);
	printf("Success\n");
}
void test_closeStrategy(){

	printf("Test closeStrategy ");
	assert(closeLog()== 0);
        printf("Success\n");
   
}
int main(){

	char bib1[] = "libLog1.so";
	char para[] = "log.txt";
	char bib2[] = "libLog2.so";

	test_loadStrategy(bib1);
	test_initStrategy(para);
//	test_closeStrategy();
	test_loadStrategy(bib2);
	test_initStrategy(para);

	test_closeStrategy();
		
	return 0;

}
