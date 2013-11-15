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
	elem = AB_get_elem(arbre);
	if(AB_get_sag(arbre)!=NULL)
		printf(" ");
	printf("%d",elem);
	if(AB_get_sad(arbre)!=NULL)
		printf(" ");
}

/*
 * Crée un arbre vide
 */
AB_t AB_creer(void)
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
 * Crée un nouvel arbre à partir d'un élément et de deux sous-arbres
 */
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
void AB_parcours(AB_t arbre)
{
	if(!AB_est_vide(arbre)) {
		if(!AB_est_feuille(arbre)) {
			printf("[");
		}
		AB_parcours(AB_get_sag(arbre));
		AB_affiche_elem(arbre);
		AB_parcours(AB_get_sad(arbre));
		if(!AB_est_feuille(arbre)) {
			printf("]");
		}
	}
}

/*
 * Insère un élément dans un arbre non plein selon la structure d'un arbre de recherche :
 * Si la valeur de l'élément est inférieur à la racine, on le met à gauche, sinon on le met à droite
 * Si l'arbre est vide, alors on le crée
 */
void ABR_insere(AB_t *ptArbre, AB_ELEM_t e)
{
	AB_t arbreLocal;

	if(AB_est_plein(*ptArbre))
	{
		fprintf(stderr,"Tentative d'insertion dans un arbre plein\n");
		exit(-1);
	}
	else if(AB_est_vide(*ptArbre))
	{
		*ptArbre = AB_insere(AB_creer(),AB_creer(),e);
	}
	else if(AB_get_elem(*ptArbre)>=e)
	{
		if(AB_est_vide(AB_get_sag(*ptArbre)))
		{
			AB_set_sag(*ptArbre,AB_insere(AB_creer(),AB_creer(),e));
		} else {
			arbreLocal=AB_get_sag(*ptArbre);
			ABR_insere(&arbreLocal,e);
		}
	}
	else
	{
		if(AB_est_vide(AB_get_sad(*ptArbre)))
		{
			AB_set_sad(*ptArbre,AB_insere(AB_creer(),AB_creer(),e));
		} else {
			arbreLocal=AB_get_sad(*ptArbre);
			ABR_insere(&arbreLocal,e);
		}
	}
}

/*
 * Initialise un abr à partir d'un fichier
 */
AB_t AB_initialiserAbr(char *fileName)
{
	FILE *fileHandle;
	AB_t abr;
	AB_ELEM_t valeur;
	fileHandle=fopen(fileName,"r");
	if(fileHandle==NULL)
	{
		fprintf(stderr,"Erreur de lecture du fichier %s\n", fileName);
		exit(-1);
	}

	abr = AB_creer();
	while(fscanf(fileHandle,"%d",&valeur)!=EOF)
	{
		ABR_insere(&abr,valeur);
	}
	fclose(fileHandle);
	return abr;
}

/*
 * Retourne la hauteur d'un arbre
 * Renvoie -1 si l'arbre est vide, 1+max(hauteur-sag, hauteur-sad) sinon
 */
int AB_hauteur(AB_t arbre)
{
	if(AB_est_vide(arbre))
		return -1;
	else if(AB_hauteur(AB_get_sag(arbre))<=AB_hauteur(AB_get_sad(arbre)))
		return 1+(AB_hauteur(AB_get_sad(arbre)));
	else
		return 1+(AB_hauteur(AB_get_sag(arbre)));
}

/*
 * Renvoie 1 si x est dans l'arbre, 0 sinon
 */
int AB_est_dans_arbre(AB_t arbre, AB_ELEM_t x)
{
	if(!AB_est_vide(arbre)) {
		if(AB_get_elem(arbre)==x)
			return 1;
		else if(AB_get_elem(arbre)<x)
			return AB_est_dans_arbre(AB_get_sad(arbre),x);
		else
			return AB_est_dans_arbre(AB_get_sag(arbre),x);
	} else
		return 0;
}

/*
 * couper : A x e --> Ag x Ad
 * Construit deux arbres Ag et Ad tels que :
 * - Ag contient tous les éléments de A inférieurs ou égaux à e
 * - Ad contient tous les éléments de A supérieurs à e
 */
void couper(AB_ELEM_t e, AB_t A, AB_t * Ag, AB_t * Ad)
{
	AB_t AgBis, AdBis;
	if(AB_est_vide(A)) {
		*Ag = AB_creer();
		*Ad = AB_creer();
	} else {
		if(e<AB_get_elem(A)) {
			couper(e,AB_get_sag(A),&AgBis,&AdBis);
			*Ag = AgBis;
			*Ad = A;
			AB_set_sag(*Ad,AdBis);
		} else {
			couper(e,AB_get_sad(A),&AgBis,&AdBis);
			*Ad = AdBis;
			*Ag = A;
			AB_set_sad(*Ag,AgBis);

		}
	}
}

/*
 * ajoutRacine : Abr x e --> Abr
 * Ajoute un élément à la racine d'un abr par coupure
 */
void AB_ajoutRacine(AB_t * A, AB_ELEM_t e)
{
	AB_t Ag, Ad;
	couper(e, *A, &Ag, &Ad);
	*A = AB_insere(Ag, Ad, e);
}

/*
 * Effectue une rotation droite :
          r               rg
        /   \            /  \
       rg    d   -->    gg   r
      /  \                  / \
     gg  gd                gd  d
 */
void AB_rotationDroite(AB_t * arbre)
{
	AB_t arbreTmp;
	arbreTmp = AB_get_sag(*arbre);
	AB_set_sag(*arbre,AB_get_sad(arbreTmp));
	AB_set_sad(arbreTmp,*arbre);
	*arbre = arbreTmp;
}

/*
 * Effectue une rotation gauche
 */
void AB_rotationGauche(AB_t * arbre)
{
	AB_t arbreTmp;
	arbreTmp = AB_get_sad(*arbre);
	AB_set_sad(*arbre,AB_get_sag(arbreTmp));
	AB_set_sag(arbreTmp,*arbre);
	*arbre = arbreTmp;
}

/*
 * Ajoute un élément à la racine d'un abr par rotation
 * Principe (on considère un abr A et l'élément e à insérer à sa racine) :
 * - si e est l'élément du sag de A, on effectue une rotation droite sur A
 * - si e est l'élément du sad de A, on effectue une rotation gauche sur A
 * - sinon
 *   - soit A est vide et alors on insere e comme seul élément
 *   - soit A est une feuille et donc on insere e à gauche (resp. à droite),
 *     puis on effectue une rotation droite (resp. gauche) sur A
 *   - ou alors on applique la procédure de manière récursive sur un des sous-arbre de A selon la valeur de e
 */
void AB_ajoutRacineRotation(AB_t * A, AB_ELEM_t e)
{
	AB_t abAux;

	if(AB_est_vide(*A))
	{
		*A = AB_insere(NULL,NULL,e);
	}
	else if(AB_est_feuille(*A))
	{
		if(e<=AB_get_elem(*A))
		{
			AB_set_sag(*A,AB_insere(NULL,NULL,e));
			AB_rotationDroite(A);
		}
		else
		{
			AB_set_sad(*A,AB_insere(NULL,NULL,e));
			AB_rotationGauche(A);
		}
	}
	else
	{
		if(e<AB_get_elem(*A))
		{
			abAux = AB_get_sag(*A);
			AB_ajoutRacineRotation(&abAux,e);
			AB_set_sag(*A,abAux);
			AB_rotationDroite(A);
		}
		else if(e>AB_get_elem(*A))
		{
			abAux = AB_get_sad(*A);
			AB_ajoutRacineRotation(&abAux,e);
			AB_set_sad(*A,abAux);
			AB_rotationGauche(A);
		}
	}
}
