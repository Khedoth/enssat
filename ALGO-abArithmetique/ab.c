#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include "pile.h"

void affiche(AB_ELEM_t elem)
{
	printf("%c",elem);
}

AB_t AB_creer(void)
{
	return NULL;
}

int AB_nb_elem(AB_t arbre)
{
	if(arbre==NULL)
		return 0;
	else
		return 1+AB_nb_elem(arbre->sag)+AB_nb_elem(arbre->sad) ;
}

int AB_est_vide(AB_t arbre)
{
	return AB_nb_elem(arbre)==0;
}

int AB_est_plein(AB_t arbre)
{
	return AB_nb_elem(arbre)==AB_NB_MAX_NOEUD;
}

AB_ELEM_t AB_get_elem(AB_t arbre)
{
	if(!AB_est_vide(arbre))
		return arbre->element;
	else
		return (AB_ELEM_t) 0;
}

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

AB_t AB_get_sag(AB_t arbre)
{
	if(!AB_est_vide(arbre))
		return arbre->sag;
	else
		return NULL;
}

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

AB_t AB_get_sad(AB_t arbre)
{
	if(!AB_est_vide(arbre))
		return arbre->sad;
	else
		return NULL;
}

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

AB_t AB_insere(AB_t sag, AB_t sad, AB_ELEM_t e)
{
	AB_t arbre;

	arbre = (AB_t)malloc(sizeof(NOEUD_t));
	if(arbre==NULL)
	{
		fprintf(stderr,"Erreur d'allocation mémoire !\n");
		exit(-1);
	}
	arbre->element = e;
	arbre->sag = sag;
	arbre->sad = sad;

    	return arbre;
}

int est_operateur(char c) {
	return (c=='+' || c=='-' || c=='*' || c=='/');
}

void AB_parcours(AB_t arbre)
{
	if(!AB_est_vide(arbre)) {
		if(est_operateur(AB_get_elem(arbre))) {
			affiche('(');
		}
		AB_parcours(AB_get_sag(arbre));
		affiche(AB_get_elem(arbre));
		AB_parcours(AB_get_sad(arbre));
		if(est_operateur(AB_get_elem(arbre))) {
			affiche(')');
		}
	}
}

AB_t AB_keyboardToAB(void)
{
	AB_t ab;
	PILE_t pile=PILE_creer();
	ELEM_t a1,a2;
	char c;

	printf("Entrez votre expression arithmétique en notation polonaise inversée et terminez par '.' :\n");
	scanf("%c",&c);
	while(c!='.')
	{
		if(!est_operateur(c))
		{
			ab = AB_creer();
			ab = AB_insere(NULL,NULL,c);
			PILE_empiler(&pile,ab);
		}
		else
		{
			ab = AB_creer();
			PILE_depiler(&pile,&a2);
			PILE_depiler(&pile,&a1);
			ab = AB_insere(a1,a2,c);
			PILE_empiler(&pile,ab);
		}
		scanf("%c",&c);
	}

	return ab;
}

void AB_profondeur(AB_t arbre, int cpt, int *profondeur)
{
	if(!AB_est_vide(arbre)) {
		if(!est_operateur(AB_get_elem(arbre)) && cpt>*profondeur)
			*profondeur=cpt;
		cpt++;
		AB_profondeur(AB_get_sag(arbre),cpt,profondeur);
		AB_profondeur(AB_get_sad(arbre),cpt,profondeur);
	}
}
