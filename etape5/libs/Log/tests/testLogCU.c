#include "genericLog.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>


// 0 comme valeur de return si tout va bien 
int init_suite(void){	
	return 0;
}

int clean_suite(void){

	return 0;
}

//la fonction qui cree le file et ecris le message dedant


void test_libLog2(){

	char *tmp = malloc(sizeof(char) * 30);
	logMsg_t message;

	CU_ASSERT_EQUAL(loadStrategy("../../dynamic/libLog2.so"),0);
	CU_ASSERT_EQUAL(initStrategy(NULL),0); // on ne veut pas un file
	
	strcpy(tmp, "Test1 dans libLog2");
	message.size = sizeof(char) * 30;
	memcpy(message.msg,tmp,message.size);
	
	CU_ASSERT_EQUAL(logStrategy(&message),0);
	strcpy(tmp,"Test2 dans libLog2");
	CU_ASSERT_EQUAL(logStrategy(&message),0);
	free(tmp);
	CU_ASSERT_EQUAL(closeLog(),0);
}

void test_libGenericLog(void){

	CU_ASSERT_EQUAL(loadStrategy("../../dynamic/libLog1.so"),0);
	CU_ASSERT_EQUAL(initStrategy("testLogCU.txt"),0);
	CU_ASSERT_EQUAL(closeLog(),0);

	CU_ASSERT_EQUAL(loadStrategy("../../dynamic/libLog2.so"),0);
	CU_ASSERT_EQUAL(initStrategy("MonTEST.txt"),0);
	CU_ASSERT_EQUAL(closeLog(),0);
}



void test_libLog1(){

	printf("Test LOG1\n");
	char myFile[] = "testLogCU.txt";
	char *tmp = malloc(sizeof(char)*30);
	logMsg_t message;

	CU_ASSERT_EQUAL(loadStrategy("../../dynamic/libLog1"),0);
	CU_ASSERT_EQUAL(initStrategy(myFile),0);
	strcpy(tmp,"Test1 libLog1");
	
	memcpy(message.msg, tmp,message.size);
	message.size = (sizeof(char) * 30);
	CU_ASSERT_EQUAL(logStrategy(&message),0);
	strcpy(tmp,"Test2 libLog1");

	CU_ASSERT_EQUAL(logStrategy(&message),0);
	free(tmp);
	CU_ASSERT_EQUAL(closeLog(),0);

}


int main(){

	CU_pSuite pSuite = NULL;
	if(CU_initialize_registry() != CUE_SUCCESS)
		return CU_get_error();
	pSuite = CU_add_suite("log_suite", init_suite, clean_suite);

	if(pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if((CU_add_test(pSuite, "test_libGenericLog", test_libGenericLog) == NULL)){
	
		CU_cleanup_registry();
		return CU_get_error();
	}

	if((CU_add_test(pSuite, "test_libLog1", test_libLog1) == NULL)){

		CU_cleanup_registry();
		return CU_get_error();
	
	}

	if((CU_add_test(pSuite, "test_libLog2", test_libLog2)) == NULL){
		CU_cleanup_registry();
		return CU_get_error();
	
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	
	CU_basic_run_tests();
		
	CU_cleanup_registry();
	return CU_get_error();

}



