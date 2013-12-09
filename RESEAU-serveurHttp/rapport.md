**Kévin**
**Vythelingum**

# Serveur HTTP haute disponibilité

## Introduction

Nous nous intéressons au cas d'un serveur gérant un pool de sous-serveurs HTTP ayant pour but de servir sous forme HTML des fichiers "texte" contenus dans un répertoire pré-établi.
Plus précisément, à partir d'un squelette de serveur en langage C, nous ferons l'établissement des connexions et la gestion du cycle de vie des sous-serveurs.

L'objectif du TP est de :

- décrire le cycle de vie d'une socket TCP
- forger des réponses HTTP
- interpréter des requettes HTTP

## Déroulement

### La base

Il s'agit tout d'abord de compléter le fichier *reseau.c* au niveau des trois étapes fondamentales de mise en place d'une socket, à savoir :

* la création de la socket
* l'association d'un nom à la socket
* l'ouverture du service

#### TODO 1 : création de la socket

Pour l'étape de création, on utilise la fonction `socket` dont on récupère le retour dans `fd` :

    int socket(int domain, int type, int protocol);

Cette primitive renvoie soit un descripteur de la socket créée, soit -1 en cas d'erreur.
C'est pourquoi nous testerons la valeur de `fd` afin de lancer la commande `FATAL` en cas d'erreur.
De plus, elle prend en argument le domaine, le type et le protocole utilisés.
Le choix s'est porté sur `AF_INET` pour le domaine puisque nous souhaitons communiquer par Internet en utilisant des adresses IPv4.
Aussi, le type est `SOCK_STREAM`, qui permet une connexion fiable et bidirectionnelle, nécessaire à la réception de requêtes et l'envoi de réponses.
Enfin, en mettant 0 pour le protocole, on obtient un protocole par défaut correspondant au type spécifié.

Cela donne pour le TODO 1 :

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
      FATAL("socket");
    }

#### TODO 2 : associer un nom à la socket

Pour associer un nom à la socket, on utilise la primitive `bind` :

    int bind(int socket, const struct sockaddr *address, socklen_t address_len);

Elle prend comme paramètres le descripteur de la socket concernée, ici `fd`,
une structure propre aux sockets comportant notamment le numéro du port utilisé,
ainsi que la taille de cette structure (sizeof).
Une structure `addr_serveur` de type `struct sockaddr_in` a déjà été définie, il s'agit donc la faire correspondre au type `struct addr` à l'aide d'un cast.
On indique ensuite `lg_addr_serveur` qui vaut `sizeof(addr_serveur)`, soit la taille de la structure passée en second paramètre.

Comme précédemment, on teste sa valeur de retour qui est négative en cas d'erreur.

Cela donne pour le TODO 2:

    test = bind(fd, (struct sockaddr *) &addr_serveur, lg_addr_serveur);
    if(test < 0)
    {
      FATAL("bind");
    }

#### TODO 3 : ouverture du service

On ouvre enfin le service pour se placer en attente de potentiels clients.
Pour cela, on utilise la primitive `listen` :

    int listen(int socket, int backlog);

Elle prend comme paramètres le descripteur de la socket concernée, ici `fd`,
et le nombre de clients simultannés autorisés, appelé *backlog*.

Avec un backlog de 4 comme demandé, cela donne pour le TODO3 :

    listen(fd, 4);

#### Test du serveur

Pour tester le serveur, il a d'abord fallu compiler les fichiers sources grâce au Makefile fourni, puis le lancer grâce à la commande suivante en étant placé au niveau de l'exécutable dans l'arborescence des fichiers :

    ./serveur-web -p 1050 -d "${PWD}/rep/"

Ce qui suit *-p* est le numéro du port utilisé, ici 1050, et ce qui suit *-d* est l'emplacement de la racine des fichiers qui pourront être servis.
Un '/' a été ajouté à la fin de la commande pour permettre des requêtes GET manuelles sans mettre de '/' devant l'emplacement voulu.

Ensuite, la visite de l'adresse `http://localhost:1050/rep/index.txt` avec un navigateur web a permis de valider le fonctionnement du serveur.
En effet, le contenu du fichier *index.txt* présent dans le répertoire *rep/* était affiché sur une page HTML.

### Compléments

#### Un client HTTP en C

Maintenant que nous avons testé le bon fonctionnement de notre serveur à l'aide d'un navigateur web, il s'agit de réaliser notre propre client HTTP écrit en langage C.
Pour cela, nous réalisons un programme *client-http* de fichier source *client-http.c* que nous compilerons à l'aide de la commande suivante :

    gcc -W -Wall -o client-http client-http.c

Cette commande est ajoutée dans le fichier `doIt.bash` pour faciliter la compilation de l'ensemble.

Le principe de fonctionnement du client est de mettre en place une socket connectée au serveur tout d'abord, puis d'envoyer la requête `GET index.txt HTTP/1.1` afin de demander le contenu du fichier *index.txt* au serveur.
Enfin, nous affichons le résultat de la requête à l'aide d'une boucle.

##### Mettre en place la socket du client

Pour mettre en place la socket du client, les étapes importantes sont :

* la récupération de l'hôte
* la création de la socket
* le nommage de la socket
* la connexion au serveur

La récupération de l'hôte se fait à l'aide de la primitive `gethostbyname(const char *name);` qui prend en paramètre l'adresse de l'hôte sous forme de chaîne de caractères et renvoi un `struct hostent *` qui servira au nommage de la socket.
Nous stockons le retour de cette fonction dans le pointeur `host`, c'est pourquoi nous vérifions la bonne allocation de mémoire ensuite, en envoyant une commande `FATAL` en cas d'erreur.

Cela donne :

    host = gethostbyname("localhost");
    if(host==NULL)
    {
      FATAL("gethostbyname");
    }




##### Envoyer une requête GET

##### Récupérer et afficher le résultat

## Conclusion

En somme, aucune difficulté n'a été rencontrée pour mettre en place le serveur de base.
Cependant, la réalisation du client a fait apparaître les premiers problèmes lors de l'implémentation du verbe GET.
En effet, il fallait passer comme requête `GET index.txt HTTP/1.1` et non `GET http://localhost:1050/index.txt`.

- degré d'avancement
