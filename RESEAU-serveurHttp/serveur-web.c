/* serveur-web.c */

/* ------------------------------------------------
   Serveur TCP

   serveur web, qui renvoie les fichiers (textes)
   d'un répertoire sous forme de pages HTML

  usage :  serveur-web [-p port] [-d repertoire]
  exemple: serveur-web -p 8000 -d /usr/doc/exemples

  Version basée sur les threads. Au lieu de créer
  un processus par connexion, on gère un pool de tâches
  (sous-serveurs).
  - au démarrage du serveur les sous-serveurs sont créés,
  et bloqués par un verrou
  - quand un client se connecte, la connexion est
  confiée à un sous-serveur inactif, qui est débloqué
  pour l'occasion.
--------------------------------------------------*/

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

void arreter_serveur(int numero_signal);

struct donnees_sous_serveur {
     pthread_t       id;		/* identificateur de thread  */
     pthread_mutex_t verrou;
     int             actif;  		/* 1 => sous-serveur occupé */
     int             fd;		/* socket du client          */
     char            *repertoire;
};

struct donnees_sous_serveur pool[NB_SOUS_SERVEURS];
int fd_serveur;			/* variable globale, pour partager
				   avec traitement signal fin_serveur */

/* -------------------------------------------------------
   sous_serveur
   ------------------------------------------------------- */
void *executer_sous_serveur(void *data)
{
     struct donnees_sous_serveur *d = data;
     while (1) {
          pthread_mutex_lock(&d->verrou);
          servir_client(d->fd, d->repertoire); //cf traitement-client.c
          close(d->fd);
          d->actif = 0;
     }
     return NULL; /* jamais exécuté */
}

/* ------------------------------------------------------- */
void creer_sous_serveurs(char repertoire[])
{
     int k;

     for (k = 0; k < NB_SOUS_SERVEURS; k++) {
          struct donnees_sous_serveur *d = pool + k;
          d->actif = 0;
          d->repertoire = repertoire;
          pthread_mutex_init(&d->verrou, NULL);
          pthread_mutex_lock(&d->verrou);
          pthread_create(&d->id, NULL, 
			 executer_sous_serveur, (void *) d);
     }
}

/* -----------------------------------------------------
   demarrer_serveur: crée le socket serveur
   et lance des processus pour chaque client
   ----------------------------------------------------- */

int demarrer_serveur(int numero_port, char repertoire[])
{
     int numero_client = 0;
     int fd_client;
     struct sigaction action_fin;

     printf("> Serveur " VERSION "+threads "
            "(port=%d, répertoire de documents=\"%s\")\n",
            numero_port, repertoire);

     /* signal SIGINT -> arrêt du serveur */

     action_fin.sa_handler = arreter_serveur;
     sigemptyset(&action_fin.sa_mask);
     action_fin.sa_flags = 0;
     sigaction(SIGINT, &action_fin, NULL);

     /* création du socket serveur et du pool de sous-serveurs */
     fd_serveur = serveur_tcp(numero_port); //cf reseau.c : 
     creer_sous_serveurs(repertoire);

     /* boucle du serveur */
     while (1) {
          struct sockaddr_in a;
          size_t l = sizeof a;
          int k;

          fd_client = attendre_client(fd_serveur); //cf reseau.c : attente active d'une connexion
          
          //TODO : Faire ici un appel à getsockname  de <sys/socket.h> : http://pubs.opengroup.org/onlinepubs/009695399/functions/getsockname.html
          //
          
          //FIN TODO
          
          numero_client++;

          /* recherche d'un sous-serveur inoccupé */
          for (k = 0; k < NB_SOUS_SERVEURS; k++)
               if (pool[k].actif == 0)
                    break;
          if (k == NB_SOUS_SERVEURS) {	/* pas de sous-serveur libre ? */
               printf("> client %d [%s] rejeté (surcharge)\n",
                      numero_client, inet_ntoa(a.sin_addr)); // http://pubs.opengroup.org/onlinepubs/000095399/functions/inet_addr.html
               close(fd_client);
          } else {
               /* affectation du travail et déblocage du sous-serveur */
               printf("> client %d [%s] traité par sous-serveur %d\n",
                      numero_client, inet_ntoa(a.sin_addr), k);
               pool[k].fd = fd_client;
               pool[k].actif = 1;
               pthread_mutex_unlock(&pool[k].verrou);
          }
     }
}

/* -------------------------------------------------------------
 Traitement des signaux
--------------------------------------------------------------- */

void arreter_serveur(int numero_signal)
{
     printf("=> fin du serveur\n");
     shutdown(fd_serveur, 2);	/* utile ? */
     close(fd_serveur);
     exit(EXIT_SUCCESS);
}


/* -------------------------------------------------------------*/
void usage(char prog[])
{
     printf("Usage : %s [options\n\n", prog);
     printf("Options :"
            "-h\tcemessage\n"
            "-p port\tport du serveur          [%d]\n"
            "-d dir \trépertoire des documents [%s]\n",
            PORT_PAR_DEFAUT, REPERTOIRE_PAR_DEFAUT);
}

/* -------------------------------------------------------------*/
int main(int argc, char *argv[])
{
     int   port =       PORT_PAR_DEFAUT;
     char *repertoire = REPERTOIRE_PAR_DEFAUT;	/* la racine
						   des documents */
     char c;

     while ((c = getopt(argc, argv, "hp:d:")) != -1)
          switch (c) {
          case 'h':
               usage(argv[0]);
               exit(EXIT_SUCCESS);
               break;
          case 'p':
               port = atoi(optarg);
               break;
          case 'd':
               repertoire = optarg;
               break;
          case '?':
               fprintf(stderr,
                       "Option inconnue -%c. -h pour aide.\n", optopt);
               break;
          }
     demarrer_serveur(port, repertoire);
     exit(EXIT_SUCCESS);
}
