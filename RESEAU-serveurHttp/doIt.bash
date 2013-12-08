
 make

 make clean

 gcc -W -Wall -o client-http client-http.c

# Lancement du serveur web sur le port 1050,
# répertoire de fichier : ./rep
 ./serveur-web -p 1050 -d "${PWD}/rep/"

