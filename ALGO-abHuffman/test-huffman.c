#include "huffman.h"
#include <stdio.h>
#include <string.h>

int main()
{
	AB_t arbreHuffman;
	LISTE_t liste;

	char code[8];
	char codeUtilisateur[100];

	liste = LISTE_init();
	printf("\n==================== ARBRE DE CODAGE DE HUFFMAN ====================\n\n");

	printf("Création de la liste triée :\n");
	LISTE_insere_tri(&liste, AB_creer(NULL,NULL,'C',1)); LISTE_afficher(liste); printf("\n");
	LISTE_insere_tri(&liste, AB_creer(NULL,NULL,'B',3)); LISTE_afficher(liste); printf("\n");
	LISTE_insere_tri(&liste, AB_creer(NULL,NULL,'D',1)); LISTE_afficher(liste); printf("\n");
	LISTE_insere_tri(&liste, AB_creer(NULL,NULL,'A',8)); LISTE_afficher(liste); printf("\n");
	LISTE_insere_tri(&liste, AB_creer(NULL,NULL,'E',1)); LISTE_afficher(liste); printf("\n");
	LISTE_insere_tri(&liste, AB_creer(NULL,NULL,'F',1)); LISTE_afficher(liste); printf("\n");
	LISTE_insere_tri(&liste, AB_creer(NULL,NULL,'G',1)); LISTE_afficher(liste); printf("\n");
	LISTE_insere_tri(&liste, AB_creer(NULL,NULL,'H',1)); LISTE_afficher(liste); printf("\n");
	printf("\n");

	printf("Liste triée finale : \n");
	LISTE_afficher(liste);
	printf("\n\n");

	arbreHuffman = HUFFMAN_creer(&liste);

	printf("Arbre de Huffman créé :\n");
	AB_afficher(arbreHuffman);
	printf("\n\n");

	printf("Code de l'alphabet :\n");
	strcpy(code,"");

	HUFFMAN_afficherCode(arbreHuffman,code);
	printf("\n");

	printf("Quelques exemples :\n");
	HUFFMAN_decode(arbreHuffman, "000 1 000 1");
	HUFFMAN_decode(arbreHuffman, "000 0100 000 0100");
	HUFFMAN_decode(arbreHuffman, "0010 1 0101 0101 0100");

	printf("\nA vous de jouer ! Entrez le code de votre choix : \n");
	scanf("%s", codeUtilisateur);
	HUFFMAN_decode(arbreHuffman, codeUtilisateur);

	return 0;
}
