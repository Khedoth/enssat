#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#include "infologin.h"

MYSQL *mysqlconnect;
MYSQL_RES *resultat;
MYSQL_ROW row;

/* Permet d'afficher le résultat de l'échéancier */
void afficherResultat() {
	while((row = mysql_fetch_row(resultat))) {
		printf("%s : %s %s - %s : %s\n", row[0], row[1], row[2], row[3], row[4]);
	}
}

/* Retourne 1 si le livre est dans la vue des retards, 0 sinon */
int estEnRetard(char code[10])
{
	char * requete;
	
	requete = (char *) malloc(sizeof(char)*200);
	
	sprintf(requete,"%s","select * from RETARD where CODE_BR='");
	strcat(requete, code);
	
	/* Execution de la requête */
	if(mysql_query(mysqlconnect, requete) != 0)
	{
		printf("Echec de la requete.\n");
		return -1;
	}
	else {
		resultat = mysql_store_result(mysqlconnect);
		if(resultat == NULL)
		{
			printf("Erreur de chargement des données.\n");
			return -1;
		}
		else {
			if(mysql_num_rows(resultat)==0) {
				return 0;
			}
			else {
				return 1;
			}
		}
	}
	
	free(requete);
}

/* Procédure de gestion des prêts et des demandes */
void prets_et_demandes(int choix)
{
	char requete[1000];
	char numAB[10];
	char code[10];
	
	switch(choix)
	{
		case 1: // Nouveau prêt
		printf("Numéro d'abonné :\n");
		scanf("%s", numAB);
		printf("Code barre :\n");
		scanf("%s", &(*code));
		sprintf(requete,"%s","insert into EMPRUNT values('");
		strcat(requete, strcat(numAB,"','"));
		strcat(requete, strcat(code,"', CURDATE(), 0000-00-00);"));
		break;
		
		case 2: // Nouvelle demande de réservation
		printf("Numéro d'abonné :\n");
		scanf("%s", numAB);
		printf("Code catalogue :\n");
		scanf("%s", code);
		sprintf(requete,"%s","insert into DEMANDE values('");
		strcat(requete, strcat(numAB,"','"));
		strcat(requete, strcat(code,"');"));
		break;
		
		case 3: // Enregistrement d'un retour
		printf("Code barre :\n");
		scanf("%s", code);
		sprintf(requete,"%s","update EMPRUNT set DATE_RETOUR=CURDATE() where CODE_BR='");
		strcat(requete, strcat(code,"';"));
		// Indique qu'il est nécessaire de payer une pénalité lors d'un retour tardif
		if(estEnRetard(code)==1) printf("Retard ! Il est nécessaire de payer une amende de 1 euro\n");
		break;
		
		case 4: // Enregistrement d'un renouvellement
		printf("Code barre :\n");
		scanf("%s", code);
		sprintf(requete,"%s","update EMPRUNT set DATE_SORTIE=CURDATE() where CODE_BR='");
		strcat(requete, strcat(code,"';"));
		break;
		
		default:
		printf("La valeur reçue est inconnue du système.\n");
		exit(-1);
		break;
	}
	
	/* Execution de la requête */
	if(mysql_query(mysqlconnect, requete) != 0)
		printf("Echec de la requête.\n");
	else
		printf("Requête effectuée avec succès.\n");
}

/* Procédure de mise à jour du fichier des abonnés */
void maj_fichier_abonne(int choix)
{
	char requete[1000];
	char numAB[10];
	char nomAB[20];
	char prenomAB[20];
	char adresse[100];
	
	switch(choix)
	{
		case 1: // Retrait d'un abonné
		printf("Numéro d'abonné :\n");
		scanf("%s", numAB);
		sprintf(requete,"%s","CALL retraitAB('");
		strcat(requete, strcat(numAB,"');"));
		break;
		
		case 2: // Nouvelle inscription
		printf("Numéro d'abonné :\n");
		scanf("%s", numAB);
		printf("Nom :\n");
		scanf(" %[^\n]", nomAB); // on peut insérer des espaces dans la chaîne
		printf("Prénom :\n");
		scanf(" %[^\n]", prenomAB);
		printf("Adresse :\n");
		scanf(" %[^\n]", adresse);
		sprintf(requete,"%s","CALL nouvelleInscription('");
		strcat(requete, strcat(numAB,"','"));
		strcat(requete, strcat(nomAB,"','"));
		strcat(requete, strcat(prenomAB,"','"));
		strcat(requete, strcat(adresse,"');"));
		break;
		
		case 3: // Renouvellement d'inscription
		printf("Numéro d'abonné :\n");
		scanf("%s", numAB);
		sprintf(requete,"%s","update ABONNE set DATE_ADH=CURDATE() where NUM_AB='");
		strcat(requete, strcat(numAB,"';"));
		break;
		
		default:
		printf("La valeur reçue est inconnue du système.\n");
		exit(-1);
		break;
	}
	
	/* Execution de la requête */
	if(mysql_query(mysqlconnect, requete) != 0)
		printf("Echec de la requête.\n");
	else
		printf("Requête effectuée avec succès.\n");
}

void gestion_livre_attente()
{
	char requete[1000];
	
	strcpy(requete,"call supprimerLivreAttente();");
	
	/* Execution de la requête */
	if(mysql_query(mysqlconnect, requete) != 0)
		printf("Echec de la requête.\n");
	else
		printf("Requête effectuée avec succès.\n");
}

/* Procédure d'affichage de l'échéancier */
void echeancier()
{
	char requete[1000];
	
	strcpy(requete,"select * from RETARD");
	
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
	printf("Menu administrateur.\n");
	printf("Que désirez-vous faire ?\n");
	printf("\t1- Gestion des prêts et des demandes\n");
	printf("\t2- Mise à jour du fichier des abonnés\n");
	printf("\t3- Gestion des livres en attente\n");
	printf("\t4- Echéancier\n");
	
	
	/* Récupération du choix de l'utilisateur */
	scanf("%d", &choix);
	
	/* Traitement de la demande */
	switch(choix)
	{
		case 1:
		printf("\n--------------- GESTION DES PRÊTS ET DES DEMANDES ---------------\n");
		printf("\t1- Nouveau prêt\n");
		printf("\t2- Nouvelle demande de réservation\n");
		printf("\t3- Enregistrer un retour\n");
		printf("\t4- Enregistrer un renouvellement\n");
		scanf("%d", &choix);
		prets_et_demandes(choix);
		break;
		
		case 2:
		printf("\n--------------- MISE À JOUR DU FICHIER DES ABONNÉES ---------------\n");
		printf("\t1- Retrait d'un abonné\n");
		printf("\t2- Nouvelle inscription\n");
		printf("\t3- Renouveler une inscription\n");
		scanf("%d", &choix);
		maj_fichier_abonne(choix);
		break;
		
		case 3:
		printf("\n--------------- GESTION DES LIVRES EN ATTENTE ---------------\n");
		printf("Voulez-vous rendre disponible tous les livres en attente qui ont été retournés depuis au moins une semaine ?\n");
		printf("\t1- Oui\n");
		printf("\t2- Non\n");
		scanf("%d", &choix);
		if(choix==1)
			gestion_livre_attente();
		break;
		
		case 4:
		printf("\n--------------- ECHÉANCIER ---------------\n");
		printf("Liste des retardataires pour chaque livre :\n");
		echeancier();
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
