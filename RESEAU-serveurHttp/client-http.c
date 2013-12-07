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
#include <fcntl.h>

#define FATAL(err) { perror((char *) err); exit(1);}
#define MAXBUF  1024

int main()
{
  int fd, bytes_read, test;
  struct sockaddr_in dest;
  struct hostent *host;
  char buffer[MAXBUF];

  int numero_port = 8000;
  char url[] = "http://localhost:8000/index.txt";

  /* Recuperation de l'hote */
  host = gethostbyname("localhost");

  /* Creation de la socket */
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd < 0)
  {
    FATAL("socket");
  }

  /* Nommage de la socket */
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = ((struct in_addr *) (host->h_addr))->s_addr;
  dest.sin_port = htons(numero_port);

  /* Connexion au serveur */
  test = connect(fd, (struct sockaddr*)&dest, sizeof(dest));
  if(test != 0)
  {
    FATAL("Connect");
  }

  /* Ecriture et envoi de la requete */
  sprintf(buffer, "GET %s HTTP/1.0\n\n", url);
  send(fd, buffer, strlen(buffer), 0);

  /* Affichage de la reponse */
  do
  {
    bzero(buffer, sizeof(buffer));
    bytes_read = recv(fd, buffer, sizeof(buffer), 0);
    if ( bytes_read > 0 )
    printf("%s", buffer);
  }
  while ( bytes_read > 0 );

  /* Fermeture de la socket */
  //close(fd);

  return 0;
}
