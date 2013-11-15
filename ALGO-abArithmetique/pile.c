#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

PILE_t PILE_creer(void)
{
	PILE_t pile;

	pile.sommet = NULL;
	pile.nElement = 0;
	return pile;
}

int PILE_est_vide(PILE_t *ptPile)
{
	int vide;
	if(ptPile->nElement==0)
		vide=1;
	else
		vide=0;
	return vide;
}

int PILE_est_pleine(PILE_t *ptPile)
{
	int pleine;
	if(ptPile->nElement==PILE_MAX_ELEMENT)
		pleine=1;
	else
		pleine=0;
	return pleine;
}

int PILE_nb_elem(PILE_t *ptPile)
{
	return ptPile->nElement;
}

int PILE_empiler(PILE_t *ptPile, ELEM_t e)
{
	MAILLON_t *ptMaillon;

	if(!PILE_est_pleine(ptPile))
	{
		ptMaillon = (MAILLON_t *)malloc(sizeof(MAILLON_t));
		if(ptMaillon == NULL)
		{
			fprintf(stderr,"Erreur d'allocation mémoire !\n");
			exit(-1);
		}
		ptMaillon->elem = e;
		ptMaillon->ptSuivant = ptPile->sommet;
		ptPile->sommet = ptMaillon;
		ptPile->nElement = ptPile->nElement + 1;
		return 1;
	}
	else
	{
		return 0;
	}
}

int PILE_depiler(PILE_t *ptPile, ELEM_t *ptElem)
{
	MAILLON_t *ptMaillon;

	if(!PILE_est_vide(ptPile))
	{
		ptMaillon = ptPile->sommet;
		*ptElem = ptMaillon->elem;
		ptPile->sommet = ptMaillon->ptSuivant;
		free(ptMaillon);
		ptPile->nElement = ptPile->nElement - 1;

		return 1;
	}
	else
	{
		return 0;
	}
}

