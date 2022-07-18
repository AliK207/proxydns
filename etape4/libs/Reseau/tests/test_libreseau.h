#ifndef _TEST_LIBRESEAU_H_
#define _TEST_LIBRESEAU_H_


// la struct traitee dans le TP du reseau avec M.Redon
// elle sert a construire l'entete du  message udp a envoyer :)

struct dns_head{

	uint16_t id;
	uint16_t flag;
        uint16_t qdcount;
	uint16_t ancount;
 	uint16_t nscount;
	uint16_t arcount;
};

void test_initSockUDP(char* );
void test_messageUDP(char *,char *,unsigned char*,int,unsigned char*);
void test_boucleServeurUDP(int ,int (*traitement)(unsigned char*,int,void*,int));
void test_querySend(int,unsigned char*,int,struct sockaddr*,int);

#endif
