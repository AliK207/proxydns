#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "args.h"
#include "dns_etape0.h"
void help_fonction(){

	printf("Projet Proxy DNS\n");
	printf("Pour Choisir le Port utilisez l'option(s) -p ou --port=PORT\n");
	printf("Pour Choisir un Serveur utilisez l'option(s) -s ou --serveur=SERVEUR\n");
	printf("Pour Choisir une stratégie de logs utilisez l'option -l ou --logstrategy==STRATEGIE avec bib1 pour le stockage dans un fichier ou bib2 pour un affichage des noms de domaines\n");
	printf("Pour choisir un paramètre d'initialisation de la stratégie utilisez l'option -i ou --initlogstrategy==STRATEGIE\n\n");
}

//on passe les valeurs par défault à la structure d'arguments
args_t argument = {
	.port=PORT,
	.server=HOST,
	.strategy=STRATEGY,
	.argstrat=ARGSTRAT,
	.config="",
};


int args(int argc, char *argv[]){
	
	int opt = 0;
	
	while(1){

		static struct option long_options[] = {
			{"help",no_argument,0,'h'},
			{"port",required_argument,0,'p'},
			{"serveur",required_argument,0,'s'},
			{"logstrategy",required_argument,0,'l'},
			{"initlogstrategy",required_argument,0,'i'},
			{"configfile",required_argument,0,'c'},
			{0,0,0,0}
		};

		int option_index = 0;

		//tous ce qui prend des arguments on va mettre apres on char :
		opt = getopt_long(argc,argv,"hp:s:i:l:c:",long_options,&option_index);

		if(opt == -1)
			break;

		switch(opt){

			case 'h' :
				help_fonction();
				break;

			case 'p' : 
				if(strlen(optarg)<(MAX_PORT_SIZE-1))
					  strcpy(argument.port, optarg);
			      	else
		      		{
	      				strncpy(argument.port, optarg, MAX_PORT_SIZE-1);
					argument.port[MAX_PORT_SIZE-1] = '\0';	  
				}
			      	break;

			case 's' :
				if(strlen(optarg)<(MAX_SERVER_SIZE-1))
					strcpy(argument.server, optarg);
				else
				{
					strncpy(argument.server, optarg, MAX_SERVER_SIZE-1);
					argument.server[MAX_SERVER_SIZE-1] = '\0';	  
				}
				break;

			case 'l' :
				if(strlen(optarg)<(MAX_STRATEGY_SIZE-1))
					strcpy(argument.strategy, optarg);
				else
				{
					strncpy(argument.strategy, optarg, MAX_STRATEGY_SIZE-1);
					argument.strategy[MAX_STRATEGY_SIZE-1] = '\0';	  
				}
				break;

			case 'i' :
				if(strlen(optarg)<(MAX_ARG_SIZE-1))
					strcpy(argument.argstrat, optarg);
				else
				{
					strncpy(argument.argstrat, optarg, MAX_ARG_SIZE-1);
					argument.argstrat[MAX_ARG_SIZE-1] = '\0';	  
				}
				break;
		
			case 'c' :
				if(strlen(optarg) < (MAX_STRATEGY_SIZE -1))
						strcpy(argument.config,optarg);
				else{
						strncpy(argument.config,optarg,MAX_ARG_SIZE-1);
						argument.config[MAX_ARG_SIZE-1] =  '\0';
				}
				break;	
					
			default :
				printf("ABORTED\n");
				help_fonction();
				exit(-1);
		}
	}

	
	if(optind < argc){
		printf("non-option ARGV-elements:\n");
		while(optind < argc)
			printf("%s\n",argv[optind++]);
		
	}

	printf("\n");

	return 0;
}

redirection* args_conf(int argc, char *argv[]){

    int opt = 0;
    redirection* red=malloc(sizeof(redirection));
    while(1){

        static struct option long_options[] = {
            {"choice",required_argument,0,'c'},
            {"domain",required_argument,0,'d'},
            {"ipv4",required_argument,0,'i'},
	    {"ipv6",required_argument,0,'j'},
	    {"mail", required_argument,0,'m'},
            {0,0,0,0}
        };

        int option_index = 0;

        //tous ce qui prend des arguments on va mettre apres on char :
        //opt = getopt_long(argc,argv,"c:d:p:",long_options,&option_index);
	opt = getopt_long(argc,argv,"c:d:i:j:m:",long_options,&option_index);

        if(opt == -1)
            break;

		switch(opt){

            case 'c' :
    		    red->choice=atoi(optarg);
		    break;

            case 'd' :
                if(strlen(optarg)<(MAX_SERVER_SIZE-1))
                      strcpy(red->domain, optarg);
                else
                {
                        strncpy(red->domain, optarg, MAX_SERVER_SIZE-1);
                    	red->domain[MAX_SERVER_SIZE-1] = '\0';
		}
                break;
	    case 'i' : //4
		if(strlen(optarg)<(MAX_SERVER_SIZE-1))
                      strcpy(red->ipv4, optarg);
		else
                    {
                        strncpy(red->ipv4, optarg, MAX_SERVER_SIZE-1);
                    	red->ipv4[MAX_SERVER_SIZE-1] = '\0';
                    }
		break;
	    case 'j' :
                if(strlen(optarg)<(MAX_SERVER_SIZE-1))
                      strcpy(red->ipv6, optarg);
                else
                {
                        strncpy(red->ipv6, optarg, MAX_SERVER_SIZE-1);
                        red->ipv6[MAX_SERVER_SIZE-1] = '\0';
                }
                break;
	    case 'm' :
                if(strlen(optarg)<(MAX_SERVER_SIZE-1))
                      strcpy(red->mail, optarg);
                else
                {
	     		strncpy(red->mail, optarg, MAX_SERVER_SIZE-1);
                        red->mail[MAX_SERVER_SIZE-1] = '\0';
                }
                break;
	default :
                printf("ABORTED\n");
                help_fonction();
                exit(-1);
        }
    }


    if(optind < argc){
        printf("non-option ARGV-elements:\n");
        while(optind < argc)
            printf("%s\n",argv[optind++]);

    }

    return red;
}

