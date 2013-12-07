
# make

# make clean

# Lancement du serveur web sur le port 1050,
# répertoire de fichier : ./rep
./serveur-web -p 1050 -d "${PWD}/rep"

# La commande wget envoir une requête http sur le port 1050
# et envoie le contenu sur sortie standard
# wget -q -O -  http://localhost:1050/index.txt
