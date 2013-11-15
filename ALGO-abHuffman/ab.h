#ifndef _AB_H
#define _AB_H

#define AB_NB_MAX_NOEUD 100

/* Structure du type abstrait AB_t */

typedef char AB_ELEM_t;

typedef struct noeud
{
	AB_ELEM_t element;
	int poids;
	struct noeud *sag;
	struct noeud *sad;

} NOEUD_t, *AB_t;

/* Prototypes */

AB_t AB_init(void);

int AB_nb_elem(AB_t arbre);
int AB_est_vide(AB_t arbre);
int AB_est_plein(AB_t arbre);
int AB_est_feuille(AB_t arbre);

AB_ELEM_t AB_get_elem(AB_t arbre);
int AB_set_elem(AB_t arbre, AB_ELEM_t e);
int AB_get_poids(AB_t arbre);
int AB_set_poids(AB_t arbre, int poids);
AB_t AB_get_sag(AB_t arbre);
int AB_set_sag(AB_t arbre, AB_t sag);
AB_t AB_get_sad(AB_t arbre);
int AB_set_sad(AB_t arbre, AB_t sad);

AB_t AB_creer(AB_t sag, AB_t sad, AB_ELEM_t e, int poids);
void AB_affiche_elem(AB_t arbre);
void AB_afficher(AB_t arbre);

#endif
