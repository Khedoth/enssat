/* Serveur Web - declarations.h */

#define CRLF "\r\n"
#define VERSION "0.0.7 pour Unix"

#define PORT_PAR_DEFAUT 8000
#define REPERTOIRE_PAR_DEFAUT "/tmp"
#define NB_SOUS_SERVEURS 5

#define FATAL(err) { perror((char *) err); exit(1);}

extern void servir_client (int fd_client,
                           char repertoire[]);

extern void envoyer_document (FILE *out,
                              char nom_document[],
                              char repertoire[]);

extern void document_non_trouve(FILE *out,
                                char nom_document[]);

extern void requete_invalide (FILE *out);

extern int  serveur_tcp (int numero_port);

extern int  attendre_client (int fd_serveur);

