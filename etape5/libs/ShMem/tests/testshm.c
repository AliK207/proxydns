#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shmem.h"

redirection** red;         

void test_initShm(){
		CU_ASSERT_EQUAL(initShm(red),0);
}

void test_closeShm(){

		CU_ASSERT_EQUAL(closeShm(*red),0);
}

void test_initAdr(){
		
		//remplissage d'un tableau adresse  de type struct redirection avec les 2 redirection
		redirection adresse[] ={ {"www.google.com",
						"172.26.145.56",
						"5555",
						"5555",4},
							  {"tvantroys.plil.fr",
							  "172.26.145.55",
							  "2001:660:4401:6050:5000::5",
							  "172.26.145.55",2}};

		CU_ASSERT_EQUAL(initAdr(adresse,1),0);
}

void test_affiche_redir(){
		redirection adresse[] = { {"www.google.com",
                        "172.26.145.56",
                        "5555",
                        "5555",0},
                              {"tvantroys.plil.fr",
                              "172.26.145.55",
                              "2001:660:4401:6050:5000::5",
                              "172.26.145.55",1},{"","192.168.2.1","1111","2222",2}};

	CU_ASSERT_EQUAL(affiche_redir(adresse),0);
}


int suite_shmem_debut(){
		return 0;
}

int suite_shmem_fin(){
		return 0;}
int main(){

		CU_pSuite pSuite = NULL;
	    if (CU_initialize_registry() != CUE_SUCCESS)	
				return CU_get_error();

		pSuite = CU_add_suite("Shmem_suite",suite_shmem_debut,suite_shmem_fin);
		if(pSuite == NULL){
				
				CU_cleanup_registry();
				return CU_get_error();
		}

		if((CU_add_test(pSuite,"test_initShm",test_initShm) == NULL)){			

				CU_cleanup_registry();
				return CU_get_error();
		}

		if((CU_add_test(pSuite,"test_closeShm",test_closeShm) == NULL)){
				
				CU_cleanup_registry();
				return CU_get_error();
			
		}


		if((CU_add_test(pSuite,"test_affiche_redir",test_affiche_redir) == NULL)){
				
				CU_cleanup_registry();
				return CU_get_error();
		}


		CU_basic_set_mode(CU_BRM_VERBOSE);
		CU_basic_run_tests();
		CU_cleanup_registry();
		return CU_get_error();
}
