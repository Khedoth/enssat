all : serveur-web 

serveur-web : serveur-web.o traitement-client.o reseau.o
	gcc -o serveur-web serveur-web.o traitement-client.o reseau.o -pthread
	
serveur-web.o : serveur-web.c declarations.h
	gcc -Wall -o serveur-web.o  -c serveur-web.c

traitement-client.o : traitement-client.c declarations.h
	gcc -Wall -o traitement-client.o  -c traitement-client.c

reseau.o : reseau.c declarations.h
	gcc -Wall -o reseau.o -c reseau.c
	
clean:
	rm -rf *.o
	
mrproper: clean
	rm -rf serveur-web
