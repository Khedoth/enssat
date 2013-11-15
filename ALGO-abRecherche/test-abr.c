#include <stdio.h>
#include "ab.h"

int main()
{
	AB_t abr, Ag, Ad;
	AB_ELEM_t e;

	abr = AB_creer();
	Ag = AB_creer();
	Ad = AB_creer();

	/* TEST 1 : affichage infixé et diverses fonctions récursives (hauteur, nb noeuds, présence d'une valeur donnée) */
	printf("\n================================ TEST 1 ================================\n");
	abr = AB_initialiserAbr("ab1.txt");
	printf("Affichage infixé en mode texte :\n");
	AB_parcours(abr);
	printf("\n");

	printf("Hauteur : %d\n", AB_hauteur(abr));
	printf("Nombre de noeuds : %d\n", AB_nb_elem(abr));

	printf("Est-ce qu'un élément est dans l'arbre ? 1 si oui, 0 sinon.\n");
	e=15;
	printf("%d est dans l'arbre ? %d\n", e, AB_est_dans_arbre(abr,e));
	e=8;
	printf("%d est dans l'arbre ? %d\n", e, AB_est_dans_arbre(abr,e));

	/* TEST 2 : coupure d'un abr par rapport à une valeur donnée */
	printf("\n================================ TEST 2 ================================\n");
	abr = AB_initialiserAbr("ab2.txt");
	e=6;
	printf("Coupure d'un arbre par rapport à %d.\n", e);
	printf("Arbre initial :\n");
	AB_parcours(abr);
	printf("\n");
	couper(e,abr,&Ag,&Ad);
	printf("Arbre Ag : ");
	AB_parcours(Ag);
	printf("\n");
	printf("Arbre Ad : ");
	AB_parcours(Ad);
	printf("\n");

	/* TEST 3 : ajout d'un élément à la racine d'un arbre par coupure */
	printf("\n================================ TEST 3 ================================\n");
	abr = AB_initialiserAbr("ab2.txt");
	e=6;
	printf("Ajout de %d à la racine de l'arbre suivant : (méthode de la coupure)\n", e);
	AB_parcours(abr);
	printf("\n");
	AB_ajoutRacine(&abr, e);
	printf("Nouvel arbre :\n");
	AB_parcours(abr);
	printf("\n");

	/* TEST 4 : rotation droite suivie d'une rotation gauche */
	printf("\n================================ TEST 4 ================================\n");
	abr = AB_initialiserAbr("ab3.txt");
	printf("Soit l'arbre de recherche suivant : \n");
	AB_parcours(abr);
	printf("\n");
	printf("Résultat d'une rotation droite :\n");
	AB_rotationDroite(&abr);
	AB_parcours(abr);
	printf("\n");
	printf("Suivi d'une rotation gauche :\n");
	AB_rotationGauche(&abr);
	AB_parcours(abr);
	printf("\n");
	printf("On retrouve bien l'arbre de recherche initial\n");

	/* TEST 5 : ajout d'un élément à la racine d'un arbre par rotation */
	printf("\n================================ TEST 5 ================================\n");
	abr = AB_initialiserAbr("ab2.txt");
	e=6;
	printf("Ajout de %d à la racine de l'arbre suivant : (méthode de la rotation)\n", e);
	AB_parcours(abr);
	printf("\n");
	AB_ajoutRacineRotation(&abr, e);
	printf("Nouvel arbre :\n");
	AB_parcours(abr);
	printf("\n");
	printf("On retrouve bien le même résultat qu'au test 3\n");

	printf("\n=============================== FIN TEST ===============================\n");

	return 0;
}
