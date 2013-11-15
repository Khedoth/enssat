#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#include "infologin.h"

MYSQL *mysqlconnect;
MYSQL_RES *resultat;
MYSQL_ROW row;

/* Permet d'afficher le résultat d'une requête sous forme de liste */
void afficherResultat() {
	int i;
	printf("---------------------------------------------------------\n");
	printf("REF  -  TITRE  -  AUTEUR  -  EDITEUR  -  GENRE  -  STATUT\n");
	printf("---------------------------------------------------------\n");
	while((row = mysql_fetch_row(resultat))) {
		for(i=0 ; i < mysql_num_fields(resultat) ; i++)
			printf("%s\t", row[i]);
		printf("\n");
	}
}

void recherche(int choix, char motCle[])
{		
	char requete[100];
	
	switch(choix)
	{
		case 1:
		sprintf(requete,"%s","select * from CATALOGUE where TITRE='");
		strcat(requete, strcat(motCle,"'"));
		break;
		
		case 2:
		sprintf(requete,"%s","select * from CATALOGUE where NOM_AU='");
		strcat(requete, strcat(motCle,"'"));
		break;
	
		case 3:
		sprintf(requete,"%s","select * from CATALOGUE where EDITEUR='");
		strcat(requete, strcat(motCle,"'"));
		break;
		
		case 4:
		sprintf(requete,"%s","select * from CATALOGUE where GENRE='");
		strcat(requete, strcat(motCle,"'"));
		break;
		
		default:
		printf("La valeur reçue est inconnue du système.\n");
		exit(-1);
		break;
	}
	
	/* Execution de la requête */
	if(mysql_query(mysqlconnect, requete) != 0)
		printf("Echec de la requete.\n");
	else {
		resultat = mysql_store_result(mysqlconnect);
		if(resultat == NULL)
			printf("Erreur de chargement des données.\n");
		else {
			if(mysql_num_rows(resultat)==0) {
				printf("Aucun résultat ne correspond à votre requête\n");
			}
			else {
				afficherResultat();
			}
		}
	}
}

int main()
{
	int choix;
	char motCle[30];
	
	/* initialisation de la connexion */
	mysqlconnect = mysql_init(NULL);
	mysql_options(mysqlconnect,MYSQL_READ_DEFAULT_GROUP,"toto");

	if (mysqlconnect == NULL)
	{
		printf("Echec de l'initialisation...\n");
		exit (-1);
	}
	/* se connecter au serveur MySQL à l’aide des informations de connexion fournies */
	if (mysql_real_connect(mysqlconnect, HOSTNAME, USERNAME, PASSWD, DATABASE, PORT, SOCKET, FLAGS) == NULL)
	{
		printf("Echec de la connexion. Message retournée (%s)\n", mysql_error(mysqlconnect));
	}
		
	/* Message d'accueil de l'utilisateur - affichage du menu */
	printf("Bonjour et bienvenue sur notre outil de recherche.\n");
	printf("Que désirez-vous faire ?\n");
	printf("\t1- Recherche par nom d'ouvrage\n");
	printf("\t2- Recherche par nom d'auteur\n");
	printf("\t3- Recherche par nom d'éditeur\n");
	printf("\t4- Recherche par genre\n");
	
	/* Récupération du choix de l'utilisateur */
	scanf("%d", &choix);
	
	/* Traitement de la demande */
	switch(choix)
	{
		case 1:
		printf("\n--------------- RECHERCHE PAR NOM D'OUVRAGE ---------------\n");
		printf("Entrez le nom de l'ouvrage recherché :\n");
		scanf(" %[^\n]",motCle); // scanf "spécial" pour prendre en compte les espaces dans les noms d'ouvrages
		recherche(choix, motCle);
		break;
		
		case 2:
		printf("\n--------------- RECHERCHE PAR NOM D'AUTEUR ---------------\n");
		printf("Entrez le nom de l'auteur recherché :\n");
		scanf("%s",motCle);
		recherche(choix, motCle);
		break;
		
		case 3:
		printf("\n--------------- RECHERCHE PAR NOM D'EDITEUR ---------------\n");
		printf("Entrez le nom de l'éditeur recherché :\n");
		scanf("%s",motCle);
		recherche(choix, motCle);
		break;
		
		case 4:
		printf("\n--------------- RECHERCHE PAR GENRE ---------------\n");
		printf("Entrez le genre recherché :\n");
		scanf("%s",motCle);
		recherche(choix, motCle);
		break;
		
		default:
		printf("La valeur reçue est inconnue du système.\n");
		exit(-1);
		break;
	}		

	/*fermer la connexion au serveur */
	mysql_close(mysqlconnect);
	
	return 0;
}
