#ifndef _AB_H
#define _AB_H

#define AB_NB_MAX_NOEUD 50

/* Structure du type abstrait AB_t */

typedef int AB_ELEM_t;

typedef struct noeud
{
	AB_ELEM_t element;
	struct noeud *sag;
	struct noeud *sad;

} NOEUD_t;

typedef NOEUD_t * AB_t;

typedef AB_t ABR_t;

/* Prototypes */

AB_t AB_creer(void);

int AB_nb_elem(AB_t arbre);
int AB_est_vide(AB_t arbre);
int AB_est_plein(AB_t arbre);
int AB_est_feuille(AB_t arbre);

AB_ELEM_t AB_get_elem(AB_t arbre);
int AB_set_elem(AB_t arbre, AB_ELEM_t e);
AB_t AB_get_sag(AB_t arbre);
int AB_set_sag(AB_t arbre, AB_t sag);
AB_t AB_get_sad(AB_t arbre);
int AB_set_sad(AB_t arbre, AB_t sad);

AB_t AB_insere(AB_t sag, AB_t sad, AB_ELEM_t e);
void AB_parcours(AB_t arbre);

void ABR_insere(AB_t *ptArbre, AB_ELEM_t e);

AB_t AB_initialiserAbr(char *fileName);

int AB_hauteur(AB_t arbre);
int AB_est_dans_arbre(AB_t arbre, AB_ELEM_t x);

void couper(AB_ELEM_t e, AB_t A, AB_t * Ag, AB_t * Ad);
void AB_ajoutRacine(AB_t * A, AB_ELEM_t e);

void AB_rotationDroite(AB_t * arbre);
void AB_rotationGauche(AB_t * arbre);
void AB_ajoutRacineRotation(AB_t * A, AB_ELEM_t e);

#endif
