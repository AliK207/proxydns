#include <stdio.h>
#include <assert.h>

#include "testMemory.h"
#include "memoire.h"

void test_allocateMemory(size_t size){

	printf("Test allocateMemory, size=%d : ",(int)size);
	assert(allocateMemory(size) == 0);
	printf("success\n");
}

void test_writeMemory(void* data, uint8_t size){

	printf("Test writeMemory, data = %s : ",(char*)data);
	assert(writeMemory(data,size) == 0);
	printf("Writing succes\n");
	
}

/*void test_readMemory(uint8_t size){

	char* lu = NULL;
	printf("Test readMemory, ");
	
	assert((lu=readMemory(&size)) != NULL);
	printf("size=%d\nReading success\n",(int)size);
	
	printf("j'ai lu le mot suivant : ");

	for(int i = 0; i <size ; i++)
		printf("%c",lu[i]);
	printf("\n");
}*/

void test_readMemory(uint8_t* size){

	printf("Test readMemory\n");
	unsigned char* message = (unsigned char *)readMemory(size);
	printf("message récupéré : %s \n taille du message : %d\n\n", message, (int)*size);
}

int main(void){
	
/*	char *data = "j'ai ecrit dans la memoire en dépassant la taille du buffer";
	uint8_t taille = -1;
	char *data2 = "test buffer tour complet test buffer tour complet test buffer tour complet";
	uint8_t taille2 = -1;
	char *data3 = "00001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111";
	uint8_t taille3 = -1;
	*/

	test_allocateMemory(256);
	test_allocateMemory(354);
	test_allocateMemory(0);
	test_allocateMemory(1500);
	
	uint8_t taille;
	
	unsigned char data[] = "Hello world !!!";
	test_writeMemory((void*)data,(uint8_t)sizeof(data));
	test_readMemory(&taille);
	
	unsigned char data2[] = "data exemple 2 est la!!";
	test_writeMemory((void*)data2,(uint8_t)sizeof(data2));
	test_readMemory(&taille);


	unsigned char data3[] = "data exemple 3 est la!! voici un exemple....";
	test_writeMemory((void*)data3,(uint8_t)sizeof(data3));
	test_readMemory(&taille);

	freeMemory();	
	return 0;
}

