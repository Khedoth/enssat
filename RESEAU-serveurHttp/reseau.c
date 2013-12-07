/*
  Projet serveur Web - reseau.c
  Fonctions réseau
*/

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

/* ------------------------------------------------------------
  Fonctions réseau
------------------------------------------------------------ */

int serveur_tcp (int numero_port)
{
  int fd, test;

  /* démarre un service TCP sur le port indiqué */

  struct sockaddr_in addr_serveur;
  size_t lg_addr_serveur = sizeof addr_serveur;

  //TODO 1:  création de la prise : http://pubs.opengroup.org/onlinepubs/000095399/functions/socket.html
  // récupération du descripteur dans fd et test de la bonne réalisation (FATAL)

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd < 0)
  {
    FATAL("socket");
  }

  //FIN TODO

  /* nommage de la prise */
  addr_serveur.sin_family      = AF_INET;
  addr_serveur.sin_addr.s_addr = INADDR_ANY;
  addr_serveur.sin_port        = htons(numero_port);


  // TODO 2: associer un nom à la socket : http://pubs.opengroup.org/onlinepubs/000095399/functions/bind.html
  //  et test de la bonne réallisation (FATAL)

  test = bind(fd, (struct sockaddr *) &addr_serveur, lg_addr_serveur);
  if(test < 0)
  {
    FATAL("bind");
  }

  //FIN TODO

  // TODO 3: ouverture du service http://pubs.opengroup.org/onlinepubs/000095399/functions/listen.html.
  // backlog de 4

  listen(fd, 4);

  // FIN TODO

  return (fd);
}

int attendre_client(int fd_serveur)
{
  int fd_client;
  /* A cause des signaux SIGCHLD, la fonction accept()
     peut etre interrompue quand un fils se termine.
     Dans ce cas, on relance accept().
  */
  while ( (fd_client = accept(fd_serveur, NULL, NULL)) < 0) { // http://pubs.opengroup.org/onlinepubs/000095399/functions/accept.html
    if (errno != EINTR)
      FATAL("Fin anormale de accept().");
  }
  return(fd_client);
}
