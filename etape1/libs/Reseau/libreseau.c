#include "dns.h"
#include "dns_etape0.h"
#include "log_dns.h"
#include "genericLog.h"

int initialisationSocketUDP(char *service) {
  struct addrinfo precisions, *resultat, *origine;
  int statut;
  int s;

  /* Construction de la structure adresse */
  memset(&precisions, 0, sizeof precisions);
  precisions.ai_family   = AF_UNSPEC;
  precisions.ai_socktype = SOCK_DGRAM;
  precisions.ai_flags    = AI_PASSIVE;
  statut                 = getaddrinfo(NULL, service, &precisions, &origine);
  if (statut < 0) {
    perror("initialisationSocketUDP.getaddrinfo");
    exit(EXIT_FAILURE);
  }
  struct addrinfo *p;
  for (p = origine, resultat = origine; p != NULL; p = p->ai_next)
    if (p->ai_family == AF_INET6) {
      resultat = p;
      break;
    }

  /* Creation d'une socket */
  s = socket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol);
  if (s < 0) {
    perror("initialisationSocketUDP.socket");
    exit(EXIT_FAILURE);
  }

  /* Options utiles */
  int vrai = 1;
  if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &vrai, sizeof(vrai)) < 0) {
    perror("initialisationServeurUDPgenerique.setsockopt (REUSEADDR)");
    exit(-1);
  }

  /* Specification de l'adresse de la socket */
  statut = bind(s, resultat->ai_addr, resultat->ai_addrlen);
  if (statut < 0) {
    perror("initialisationServeurUDP.bind");
    exit(-1);
  }

  /* Liberation de la structure d'informations */
  freeaddrinfo(origine);

  return s;
}


int messageUDP(char *hote, char *service, unsigned char *message, int taille, unsigned char *buffer) {
  struct addrinfo precisions, *resultat, *origine;
  int statut;
  int s;

  /* Creation de l'adresse de socket */
  memset(&precisions, 0, sizeof precisions);
  precisions.ai_family   = AF_UNSPEC;
  precisions.ai_socktype = SOCK_DGRAM;
  statut                 = getaddrinfo(hote, service, &precisions, &origine);
  if (statut < 0) {
    perror("messageUDPgenerique.getaddrinfo");
    exit(EXIT_FAILURE);
  }
  struct addrinfo *p;
  for (p = origine, resultat = origine; p != NULL; p = p->ai_next)
    if (p->ai_family == AF_INET6) {
      resultat = p;
      break;
    }

  /* Creation d'une socket */
  s = socket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol);
  if (s < 0) {
    perror("messageUDPgenerique.socket");
    exit(EXIT_FAILURE);
  }

  /* Option sur la socket */
  int vrai = 1;
  if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &vrai, sizeof(vrai)) < 0) {
    perror("initialisationServeurUDPgenerique.setsockopt (BROADCAST)");
    exit(EXIT_FAILURE);
  }

  /* Envoi du message */
  int nboctets = sendto(s, message, taille, 0, resultat->ai_addr, resultat->ai_addrlen);
  if (nboctets < 0) {
    perror("messageUDPgenerique.sento");
    exit(EXIT_FAILURE);
  }

  /* Reception du message */

  int recus = recvfrom(s, buffer, MAX_DNS, 0, NULL, NULL);

  /* Liberation de la structure d'informations */
  freeaddrinfo(origine);

  /* Fermeture de la socket d'envoi */
  close(s);
  return recus;
}


int boucleServeurUDP(int s, int (*traitement)(unsigned char *, int, struct sockaddr *, int)) {
  while (1) {
    struct sockaddr_storage adresse;
    socklen_t taille = sizeof(adresse);
    unsigned char message[MAX_DNS];
    int nboctets = recvfrom(s, message, MAX_DNS, 0, (struct sockaddr *)&adresse, &taille);
    
       if (nboctets < 0)
      return -1;
    if (traitement(message, nboctets, (struct sockaddr *)&adresse, taille) < 0)
      break;
    else{
	    logMsg_t requete;
	    requete.size=nboctets;
	    memcpy(requete.msg,message, nboctets);
	    //mon ajout
	    //addLog(&requete);
		///
	    logStrategy(&requete);
    }
      }
  return 0;
}

