#include "ab.h"
#include "liste.h"

#ifndef HUFFMAN_H
#define HUFFMAN_H

AB_t HUFFMAN_creer(LISTE_t * liste);
void HUFFMAN_afficherCode(AB_t arbreHuffman, char * code);
void HUFFMAN_decode(AB_t arbreHuffman, char * code);

#endif
