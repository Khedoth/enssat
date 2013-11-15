#ifndef _AB_H
#define _AB_H

#define AB_NB_MAX_NOEUD 10

/* Structure du type abstrait AB_t */

typedef char AB_ELEM_t;

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

AB_ELEM_t AB_get_elem(AB_t arbre);
int AB_set_elem(AB_t arbre, AB_ELEM_t e);
AB_t AB_get_sag(AB_t arbre);
int AB_set_sag(AB_t arbre, AB_t sag);
AB_t AB_get_sad(AB_t arbre);
int AB_set_sad(AB_t arbre, AB_t sad);

AB_t AB_insere(AB_t sag, AB_t sad, AB_ELEM_t e);
void AB_parcours(AB_t arbre);

void affiche(AB_ELEM_t elem);

AB_t AB_keyboardToAB(void);
void AB_profondeur(AB_t arbre, int cpt, int *profondeur);

#endif
