#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "shmem.h"



void add_redir(redirection *adresse, redirection* red){
        int index=0;
        while (strcmp(adresse[index].domain,"")!=0)
                index++;
        strcpy(adresse[index].domain, red->domain);
        strcpy(adresse[index].ipv4, red->ipv4);
        strcpy(adresse[index].ipv6, red->ipv6);
        strcpy(adresse[index].mail, red->mail);
        free(red);
}

void suppr_redir(redirection *adresse, redirection* red){
        int index=0;
        while (strcmp(adresse[index].domain,red->domain)!=0)
                index++;
        strcpy(adresse[index].domain,"");
        strcpy(adresse[index].ipv4,"");
        strcpy(adresse[index].ipv6,"");
        strcpy(adresse[index].mail,"");
        free(red);
}

void replace_redir(redirection *adresse, redirection* red){
        int index=0;
        while (strcmp(adresse[index].domain,red->domain)!=0)
                index++;
        strcpy(adresse[index].domain, red->domain);
        strcpy(adresse[index].ipv4, red->ipv4);
        strcpy(adresse[index].ipv6, red->ipv6);
        strcpy(adresse[index].mail, red->mail);
        free(red);
}



int main(int argc, char* argv[]){
	
	//on recupere l'acces a la memoire partagée
	void* psh=NULL;
	redirection *adresse2;
	int shid=shmget(KEY, 0, 0);
	psh=shmat(shid,0,0);
	adresse2=psh;

	//en fonction des arguments, on recup une redirection grace a la fonction args_conf
	redirection *red=args_conf(argc, argv);

	//on ecrit dans la mémoire partagée
/*	while (strcmp(adresse2[index].domain,"")!=0)
			index++;
	printf("index %d\n", index);
	strcpy(adresse2[index].domain, red->domain);
	strcpy(adresse2[index].ipv4, red->ipv4);
	strcpy(adresse2[index].ipv6, red->ipv6);
	strcpy(adresse2[index].mail, red->mail);
	free(red);
	printf("écriture du manager finie\n");*/
	printf("debut des pb\n");
	if (red->choice==0)
		suppr_redir(adresse2, red);
	if (red->choice==1)
                add_redir(adresse2, red);
	if (red->choice==2)
                replace_redir(adresse2, red);

	for(int i=0; i<10; i++){
                if (strcmp(adresse2[i].domain,"")!=0){
			printf("indice %d\n", i);
                            printf("%s\n", adresse2[i].domain);
                            printf("%s\n", adresse2[i].ipv4);
                            printf("%s\n", adresse2[i].ipv6);
                            printf("%s\n", adresse2[i].mail);
                }
        }
	printf("proxy manager fini");
//	affiche_redir(adresse2);



	return 0;
}

