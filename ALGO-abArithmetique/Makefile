CC = gcc -g
CFLAGS = -W -Wall

all: test-ab

test-ab : test-ab.o ab.o pile.o
	$(CC) -o $@ $^

ab.o : ab.c ab.h pile.h
	$(CC) $(CFLAGS) -c $<
	
pile.o : pile.c pile.h ab.h
	$(CC) $(CFLAGS) -c $<

test-ab.o : test-ab.c
	$(CC) $(CFLAGS) -c test-ab.c

objects := $(wildcard *.o)

clean:
	rm -f ${objects} test-ab Makefile.bak
