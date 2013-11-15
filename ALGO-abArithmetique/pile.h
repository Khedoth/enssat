#ifndef PILE_H
#define PILE_H

#include "ab.h"

#define PILE_MAX_ELEMENT 50

typedef AB_t ELEM_t;

typedef struct maillon
{
	ELEM_t elem;
	struct maillon *ptSuivant;
} MAILLON_t;

typedef struct pile
{
	int nElement;
	MAILLON_t *sommet;
} PILE_t;

PILE_t PILE_creer(void);
int PILE_est_vide(PILE_t *ptPile);
int PILE_est_pleine(PILE_t *ptPile);
int PILE_nb_elem(PILE_t *ptPile);
int PILE_empiler(PILE_t *ptPile, ELEM_t e);
int PILE_depiler(PILE_t *ptPile, ELEM_t *ptElem);

#endif
