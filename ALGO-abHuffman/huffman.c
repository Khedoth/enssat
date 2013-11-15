#include "huffman.h"
#include <stdio.h>
#include <string.h>

/* Créé un arbre de Huffman à partir d'une liste triée de couples caractères-poids */
AB_t HUFFMAN_creer(LISTE_t * liste)
{
	AB_t A, Ag, Ad;

	A = AB_init();
	Ag = AB_init();
	Ad = AB_init();

	while(!LISTE_est_unitaire(*liste))
	{
		Ad = LISTE_get_elem(*liste);
		LISTE_supprime_tete(liste);
		Ag = LISTE_get_elem(*liste);
		LISTE_supprime_tete(liste);

		A = AB_creer(Ag,Ad,'#',AB_get_poids(Ag)+AB_get_poids(Ad));

		LISTE_insere_tri(liste,A);
	}

	return LISTE_get_elem(*liste);
}

/* Affiche le code associé à chaque caractère du lexique modélisé par un arbre de Huffman
 * Prend en entrée l'arbre de Huffman et une chaîne à construire (qui doit être initialisée à "") */
void HUFFMAN_afficherCode(AB_t arbreHuffman, char * code)
{
	char codeGauche[8];
	char codeDroite[8];

	if(!AB_est_vide(arbreHuffman))
	{
		strcpy(codeGauche, code);
		strcat(codeGauche, "0");

		strcpy(codeDroite, code);
		strcat(codeDroite, "1");

		if(AB_est_feuille(arbreHuffman))
		{
			printf("%c : %s\n", AB_get_elem(arbreHuffman), code);
		}

		HUFFMAN_afficherCode(AB_get_sag(arbreHuffman),codeGauche);

		HUFFMAN_afficherCode(AB_get_sad(arbreHuffman),codeDroite);
	}
}

/* Décode une chaîne de bits appelée code en une chaîne de caractères
 * à partir d'un arbre de Huffman arbreHuffman
 * Affiche à l'écran le résultat du décodage */
void HUFFMAN_decode(AB_t arbreHuffman, char * code)
{
	int i=0;
	AB_t AbAux;

	AbAux = arbreHuffman;
	printf("Le code %s donne : ", code);
	while(code[i]!='\0')
	{
		if(code[i]=='0')
		{
			AbAux = AB_get_sag(AbAux);
		}
		else if(code[i]=='1')
		{
			AbAux = AB_get_sad(AbAux);
		}

		if(AB_est_feuille(AbAux))
		{
			printf("%c", AB_get_elem(AbAux));
			AbAux = arbreHuffman;
		}

		i++;
	}

	printf("\n");
}
