#
#	LSI1, Module Structures de Données
#	TP Arbre de codage de Huffman
#	ENSSAT
#

CC = gcc -g
CFLAGS = -W -Wall

all: test-huffman

test-huffman : test-huffman.o huffman.o liste.o ab.o
	$(CC) -o $@ test-huffman.o huffman.o liste.o ab.o

ab.o : ab.c ab.h
	$(CC) $(CFLAGS) -c ab.c

liste.o : liste.c liste.h ab.h
	$(CC) $(CFLAGS) -c liste.c

huffman.o : huffman.c huffman.h liste.h ab.h
	$(CC) $(CFLAGS) -c huffman.c

test-huffman.o : test-huffman.c huffman.h liste.h ab.h
	$(CC) $(CFLAGS) -c test-huffman.c

objects := $(wildcard *.o)

clean:
	rm -f ${objects} test-huffman Makefile.bak
