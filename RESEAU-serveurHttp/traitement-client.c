/*
  traitement-client.c

  projet serveur WEB
  Communication avec un client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "declarations.h"


void servir_client(int fdClient, char repertoire[])
{
  FILE * in, * out;
  char verbe[100], nom_document[100];
  int fd2;

  /* Ouverture de fichiers de haut niveau */
  in  = fdopen(fdClient,"r");
  /* note : si on attache out au même descripteur que in,
     la fermeture de l'un entraine la fermeture de l'autre */
  fd2 = dup(fdClient);
  out = fdopen(fd2, "w");
  
  /* lecture de la requête, du genre
     "GET quelquechose ..." */
  fscanf(in, "%100s %100s", verbe, nom_document); // il s'agit du verbe HTTP : GET, POST, PUT, DELETE
  fclose(in);

  if (strcmp(verbe, "GET") == 0)
    envoyer_document(out, nom_document, repertoire);
  else
    requete_invalide(out);
  fflush(out);      /* utile ? */
  fclose(out);
}

void envoyer_document(FILE *out, char nom_document[], char repertoire[])
{
  char nom_fichier[100];
  FILE *fichier;
  char ligne[100];

  sprintf(nom_fichier, "%s%s", repertoire, nom_document);
  
  if (strstr(nom_fichier, "/../") != NULL) {
    /* tentative d'accès hors du répertoire ! */
    document_non_trouve(out, nom_document);
    return;
  };		     
  fichier = fopen(nom_fichier, "r");
  if (fichier == NULL) {
    document_non_trouve(out, nom_document);
    return;
  };

  fprintf(out,
	  "HTTP/1.1 200 OK" CRLF
	  "Server: " VERSION CRLF
	  "Content-Type: text/html; charset=iso-8859-1" CRLF
	  CRLF);

  fprintf(out,
	  "<html><head><title>Fichier %s</title></head>" CRLF
	  "<body bgcolor=\"white\"><h1>Fichier %s</h1>" CRLF
	  "<center><table><tr><td bgcolor=\"yellow\"><listing>" CRLF, 
	  nom_document, nom_fichier);

  /* le corps du fichier */
  while( fgets(ligne,100,fichier) != NULL) {
    char *p;
    for( p=ligne; *p != '\0'; p++) {
      switch(*p) {
      case '<' : fputs("&lt;",  out); break;
      case '>' : fputs("&gt;",  out); break;
      case '&' : fputs("&amp;", out); break;
      case '\n': fputs(CRLF,    out); break;
      default :  fputc(*p,      out);
      };
    };
  };

  /* balises de fin */
  fputs("</listing></table></center></body></html>" CRLF, out);
}

void document_non_trouve (FILE *out, char nom_document[])
{
  /* envoi de la réponse : entête */
  fprintf(out,
	  "HTTP/1.1 404 Not Found" CRLF
	  "Server: MegaSoft 0.0.7 (CP/M)" CRLF
	  "Content-Type: text/html; charset=iso-8859-1" CRLF
	     CRLF);
  
  /* corps de la réponse */
  fprintf(out,
	  "<HTML><HEAD>" CRLF
	  "<TITLE>404 Not Found</TITLE>" CRLF
	  "</HEAD><BODY BGCOLOR=\"yellow\">" CRLF
	  "<H1>Pas trouvé !</H1>" CRLF
	  "Le document <font color=\"red\"><tt>%s</tt></font> "
	  "demandé<br>n'est pas disponible.<P>" CRLF
	  "<hr> Le webmaster"
	  "</BODY></HTML>" CRLF,
	  nom_document);
  fflush(out); 
}

void requete_invalide(FILE *out)
{  
  fprintf(out,
	  "<HTML><HEAD>" CRLF
	  "<TITLE>400 Bad Request</TITLE>" CRLF
	  "</HEAD><BODY BGCOLOR=\"yellow\">" CRLF
	  "<H1>Bad Request</H1>"
	  "Vous avez envoyé une requête que "
	  "ce serveur ne comprend pas." CRLF
	  "<hr> Le webmaster"
	  "</BODY></HTML>" CRLF);
  fflush(out); 
}
