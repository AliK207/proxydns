#include <stdio.h>
#include <assert.h>
#include "../../inc/libreseau.h"
#include "test_libreseau.h"

int s;
void test_initSockUDP(char* service){

	printf("Test initSockUDP : %s",service);
//	assert((s=initialisationSocketUDP(service))!= -1);
	s = initialisationSocketUDP(service); 
	printf("Nice sockUDP init\n");
}

void test_messageUDP(char *hote, char *ser, unsigned char* message, int taille, unsigned char *rep){
	int x;
	printf("Test messageUDP : ");
	assert((x = messageUDP(hote,ser,message,taille,rep)) > 0);
	printf("Nice\n");

}

void test_boucleServeurUDP(int s,int (*traitement)(unsigned char*,int,void*,int)){

	printf("Test Boucle server UDP\n");
	assert(boucleServeurUDP(s,traitement) == 0);
	printf("NICE BOUCLE SERVER UDP. . . : socket = %d\n",s);
}


void test_querySend(int server,unsigned char* rep,int recus,struct sockaddr* address,int size_addr){

	printf("TEST QUERYSEND\n");
	assert(querySend(server,rep,recus,address,size_addr));
	printf("NICE QUERY SEND\n");
}

int interm_test_fct(unsigned char* var1,int var2,void* var3,int var4){

	printf("INTERM FCT\n");
	
	if(var1 || var2 || var4 || var3)
		printf("OKKK\n");
	printf("apres le if de interms fct\n");
	return 0;
}

//void test_initsock()

struct dns_head tete;
int  main(){

	unsigned char* response = malloc(MAX_DNS);
	char* ser1 = "53";
	//char* ser2 = "12";

	uint8_t web[] = {0x03,'w','w','w',0x06,'g','o','o','g','l','e',0x02,'c','o','m'};

	//voir la struct dans le .h ...
	tete.id = 0 ;
	tete.flag    = 0x0001;
	tete.qdcount = 0x0100;
	tete.ancount = 0x0000;
	tete.nscount = 0x0000;
	tete.arcount = 0x0000;

	uint16_t qtype = 0x0100;
	uint16_t qclass = 0x0100;

	//allocation comme vu dans le tp
	unsigned char* data1 = malloc(sizeof(tete)+sizeof(web)+ (2*sizeof(uint16_t)));
	
	memcpy(data1,(uint16_t*)&tete,sizeof(tete));
	memcpy(&data1[sizeof(tete)],(uint8_t*)web,sizeof(web));
	memcpy(&data1[sizeof(tete)+sizeof(web)],(uint16_t*)&qtype,sizeof(uint16_t));
	memcpy(&data1[sizeof(tete)+sizeof(web)+sizeof(uint16_t)],(uint16_t*)&qclass,sizeof(uint16_t));


	test_initSockUDP(ser1);
	//test_initSockUDP(ser2);
	test_boucleServeurUDP(s,interm_test_fct);
	
	// agere le typage pour ces parametres +++++
	test_messageUDP(ser1,"127.0.0.53",data1,sizeof(data1),response);
	return 0;

}
