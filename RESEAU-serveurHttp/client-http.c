#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <resolv.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>

#define FATAL(err) { perror((char *) err); exit(1);}
#define MAXBUF  1024
#define NUMPORT 1050

int main()
{
  int fd, recu, test;
  struct sockaddr_in addr;
  size_t lg_addr = sizeof addr;
  struct hostent *host;
  char buffer[MAXBUF];

  char requete[] = "http://localhost:1050/index.txt";

  /* Recuperation de l'hote */
  host = gethostbyname("localhost");

  /* Creation de la socket */
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd < 0)
  {
    FATAL("socket");
  }

  /* Nommage de la socket */
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = ((struct in_addr *) (host->h_addr))->s_addr;
  addr.sin_port = htons(NUMPORT);

  /* Connexion au serveur */
  test = connect(fd, (struct sockaddr*)&addr, lg_addr);
  if(test != 0)
  {
    FATAL("Connect");
  }

  /* Ecriture et envoi de la requete */
  sprintf(buffer, "GET %s\n", requete);
  send(fd, buffer, strlen(buffer), 0);

  /* Affichage de la reponse */
  recu = recv(fd, buffer, sizeof(buffer), 0);
  while (recu > 0)
  {
    printf("%s", buffer);
    recu = recv(fd, buffer, sizeof(buffer), 0);
  }

  /* Fermeture de la socket */
  close(fd);

  return 0;
}
