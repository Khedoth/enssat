#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/* Initialise une liste vide */
LISTE_t LISTE_init(void)
{
	return NULL;
}

/* Retourne l'élément d'un maillon */
ELEM_t LISTE_get_elem(LISTE_t liste)
{
	return liste->elem;
}

/* Modifie l'élément d'un maillon */
void LISTE_set_elem(LISTE_t liste, ELEM_t e)
{
	liste->elem = e;
}

/* Retourne un pointeur vers le maillon suivant d'une liste */
LISTE_t LISTE_get_ptSuivant(LISTE_t liste)
{
	return liste->ptSuivant;
}

/* Modifie le maillon suivant d'une liste */
void LISTE_set_ptSuivant(LISTE_t liste, LISTE_t ptSuivant)
{
	liste->ptSuivant = ptSuivant;
}

/* Renvoie le nombre d'éléments d'une liste */
int LISTE_nb_elem(LISTE_t liste)
{
	if(liste==NULL)
		return 0;
	else
		return 1+LISTE_nb_elem(LISTE_get_ptSuivant(liste));
}

/* Renvoie 1 si une liste est vide, 0 sinon */
int LISTE_est_vide(LISTE_t liste)
{
	return LISTE_nb_elem(liste)==0;
}

/* Renvoie 1 si une liste ne contient qu'un seul maillon, 0 sinon */
int LISTE_est_unitaire(LISTE_t liste)
{
	return LISTE_nb_elem(liste)==1;
}

/* Insere en tête d'une liste */
void LISTE_insere_tete(LISTE_t * liste, ELEM_t e)
{
	LISTE_t listeTete;
	listeTete = (LISTE_t) malloc(sizeof(MAILLON_t));
	if(listeTete==NULL)
	{
		fprintf(stderr,"Erreur d'allocation mémoire");
		exit(-1);
	}
	LISTE_set_elem(listeTete,e);
	LISTE_set_ptSuivant(listeTete, *liste);
	*liste = listeTete;
}

/* Insere dans une liste triée */
void LISTE_insere_tri(LISTE_t * liste, ELEM_t e)
{
	LISTE_t listeAux;
	if(LISTE_est_vide(*liste))
	{
		LISTE_insere_tete(liste, e);
	}
	else if(AB_get_poids(e)<=AB_get_poids(LISTE_get_elem(*liste)))
	{
		LISTE_insere_tete(liste, e);
	}
	else
	{
		listeAux = LISTE_get_ptSuivant(*liste);
		LISTE_insere_tri(&listeAux, e);
		LISTE_set_ptSuivant(*liste, listeAux);
	}
}

/* Supprime le maillon de tête d'une liste, ie le plus petit élément d'une liste triée */
void LISTE_supprime_tete(LISTE_t * liste)
{
	LISTE_t listeAux;
	if(!LISTE_est_vide(*liste))
	{
		listeAux = LISTE_get_ptSuivant(*liste);
		free(*liste);
		*liste = listeAux;
	}
}

/* Affiche une liste à l'écran */
void LISTE_afficher(LISTE_t liste)
{
	LISTE_t listeSuivant;
	if(!LISTE_est_vide(liste))
	{
		listeSuivant = LISTE_get_ptSuivant(liste);
		AB_affiche_elem(LISTE_get_elem(liste));
		LISTE_afficher(listeSuivant);
	}
}

