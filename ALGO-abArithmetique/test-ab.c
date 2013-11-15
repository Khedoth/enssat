#include <stdio.h>
#include "ab.h"

int main()
{
	AB_t abr;
	int profondeur=0;
	abr = AB_creer();

	abr = AB_keyboardToAB();

	AB_parcours(abr);
	printf("\n");

	AB_profondeur(abr,0,&profondeur);
	printf("La profondeur de l'arbre vaut : %d\n",profondeur);

	return 0;
}
