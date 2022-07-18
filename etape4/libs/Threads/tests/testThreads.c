#include "libthread.h"
#include "testThreads.h"
#include <assert.h>

void test_initMutex(int param){

        printf("Test initMutex : ");
        assert(init_mutex(param)== 0);
        printf("SUCCESS\n");
}

void test_P(int param){

        printf("Test P(%d) : ", param);
        assert(P(param) == 0);
        printf("SUCCESS\n");
}

void test_V(int param){

        printf("Test V(%d) : ", param);
        assert(V(param) == 0);
        printf("SUCCESS\n");
}

void test_launchThread(void *(*fonction)(void *), void *arg, size_t argSize){
	printf("Test launchThread : ");
	assert(launchThread(fonction, arg, argSize) == 0);
	printf("SUCCES");
}

int main(){
	test_initMutex(3);
	test_P(0);
	test_V(0);
	test_V(1);
	test_P(1);
	test_V(1);
	test_V(2);
	test_P(2);
	test_V(2);
	return 0;
}
