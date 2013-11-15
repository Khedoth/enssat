#include "ab.h"

#ifndef _LISTE_H
#define _LISTE_H

typedef AB_t ELEM_t;

typedef struct maillon
{
	ELEM_t elem;
	struct maillon *ptSuivant;
} MAILLON_t, *LISTE_t;

/* Initialisation */
LISTE_t LISTE_init(void);

/* get et set */
ELEM_t LISTE_get_elem(LISTE_t liste);
void LISTE_set_elem(LISTE_t liste, ELEM_t e);

LISTE_t LISTE_get_ptSuivant(LISTE_t liste);
void LISTE_set_ptSuivant(LISTE_t liste, LISTE_t ptSuivant);

/* Dénombrement */
int LISTE_nb_elem(LISTE_t liste);
int LISTE_est_vide(LISTE_t liste);
int LISTE_est_unitaire(LISTE_t liste);

/* Insertion */
void LISTE_insere_tete(LISTE_t * liste, ELEM_t e);
void LISTE_insere_tri(LISTE_t * liste, ELEM_t e);

/* Suppression */
void LISTE_supprime_tete(LISTE_t * liste);

/* Affichage */
void LISTE_afficher(LISTE_t liste);

#endif
