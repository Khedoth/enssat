#	
#	LSI1, Structures de données
#	TP arbres de recherche
#	ENSSAT
#

CC = gcc -g
CFLAGS = -W -Wall

all: test-abr

test-abr : test-abr.o ab.o
	$(CC) -o $@ test-abr.o ab.o

ab.o : ab.c ab.h
	$(CC) $(CFLAGS) -c ab.c

test-abr.o : test-abr.c
	$(CC) $(CFLAGS) -c test-abr.c

objects := $(wildcard *.o)

clean:
	rm -f ${objects} test-abr Makefile.bak
