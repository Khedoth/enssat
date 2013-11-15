#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ab.h"

/*
 * Affiche à l'écran l'élément d'un arbre
 * Ajoute un espace avant (resp. après) si le l'arbre comporte un sag (resp. sad)
 */
void AB_affiche_elem(AB_t arbre)
{
	AB_ELEM_t elem;
	int poids;
	elem = AB_get_elem(arbre);
	poids = AB_get_poids(arbre);
	if(AB_get_sag(arbre)!=NULL)
		printf(" ");
	printf("(%c %d)",elem, poids);
	if(AB_get_sad(arbre)!=NULL)
		printf(" ");
}

/*
 * Crée un arbre vide
 */
AB_t AB_init(void)
{
	return NULL;
}

/*
 * Retourne le nombre d'éléments d'un arbre
 */
int AB_nb_elem(AB_t arbre)
{
	if(arbre==NULL)
		return 0;
	else
		return 1+AB_nb_elem(arbre->sag)+AB_nb_elem(arbre->sad) ;
}

/*
 * Teste si un arbre est vide
 * Renvoie 1 si l'arbre est vide, 0 sinon
 */
int AB_est_vide(AB_t arbre)
{
	return AB_nb_elem(arbre)==0;
}

/*
 * Teste si un arbre est plein
 * Renvoie 1 si l'arbre est plein, 0 sinon
 */
int AB_est_plein(AB_t arbre)
{
	return AB_nb_elem(arbre)==AB_NB_MAX_NOEUD;
}

/*
 * Teste si l'arbre est une feuille
 * Renvoie 1 si l'arbre est une feuille, 0 sinon
 */
int AB_est_feuille(AB_t arbre)
{
	return AB_get_sag(arbre)==NULL && AB_get_sad(arbre)==NULL;
}

/*
 * Retourne la valeur de l'élément d'un arbre non vide
 */
AB_ELEM_t AB_get_elem(AB_t arbre)
{
	assert(!AB_est_vide(arbre));
	return arbre->element;
}

/*
 * Modifie la valeur de l'élément d'un arbre non vide
 * Renvoie 1 si l'arbre est effectivement non vide, 0 sinon (echec)
 */
int AB_set_elem(AB_t arbre, AB_ELEM_t e)
{
	if(!AB_est_vide(arbre))
	{
		arbre->element = e;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * Retourne le poids de l'élément d'un arbre non vide
 */
int AB_get_poids(AB_t arbre)
{
	assert(!AB_est_vide(arbre));
	return arbre->poids;

}

/*
 * Modifie le poids de l'élément d'un arbre non vide
 * Renvoie 1 si l'arbre est effectivement non vide, 0 sinon (echec)
 */
int AB_set_poids(AB_t arbre, int poids)
{
	if(!AB_est_vide(arbre))
	{
		arbre->poids = poids;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * Retourne le sag d'un arbre non vide
 * Renvoie NULL si l'arbre d'entrée est vide
 */
AB_t AB_get_sag(AB_t arbre)
{
	if(!AB_est_vide(arbre))
		return arbre->sag;
	else
		return NULL;
}

/*
 * Modifie le sag d'un arbre non vide
 * Renvoie 1 si l'arbre est effectivement non vide, 0 sinon (echec)
 */
int AB_set_sag(AB_t arbre, AB_t sag)
{
	if(!AB_est_vide(arbre))
	{
		arbre->sag = sag;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * Retourne le sad d'un arbre non vide
 * Renvoie NULL si l'arbre d'entrée est vide
 */
AB_t AB_get_sad(AB_t arbre)
{
	if(!AB_est_vide(arbre))
		return arbre->sad;
	else
		return NULL;
}

/*
 * Modifie le sad de l'élément d'un arbre non vide
 * Renvoie 1 si l'arbre est effectivement non vide, 0 sinon (echec)
 */
int AB_set_sad(AB_t arbre, AB_t sad)
{
	if(!AB_est_vide(arbre))
	{
		arbre->sad = sad;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * Crée un nouvel arbre à partir d'un élément et de son poids et de deux sous-arbres
 */
AB_t AB_creer(AB_t sag, AB_t sad, AB_ELEM_t e, int poids)
{
	AB_t arbre;

	arbre = (AB_t)malloc(sizeof(NOEUD_t));
	if(arbre==NULL)
	{
		fprintf(stderr,"Erreur d'allocation mémoire !\n");
		exit(-1);
	}
	AB_set_elem(arbre, e);
	AB_set_poids(arbre, poids);
	AB_set_sag(arbre, sag);
	AB_set_sad(arbre, sad);

	return arbre;
}

/*
 * Affiche à l'écran un arbre en parcours infixé
 * Les éléments de l'arbre sont encadrés par [ ] de manière à distinguer racine, sag et sad
 * Ainsi, l'arbre suivant :
	           9
	         /   \
	        6     45
	       / \   /
	      3   8 21
 * sera affiché [[3 6 8] 9 [21 45]]
 */
void AB_afficher(AB_t arbre)
{
	if(!AB_est_vide(arbre)) {
		if(!AB_est_feuille(arbre)) {
			printf("[");
		}
		AB_afficher(AB_get_sag(arbre));
		AB_affiche_elem(arbre);
		AB_afficher(AB_get_sad(arbre));
		if(!AB_est_feuille(arbre)) {
			printf("]");
		}
	}
}
