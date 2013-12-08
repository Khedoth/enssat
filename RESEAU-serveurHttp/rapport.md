**Kévin**
**Vythelingum**

<style type="text/css">html{text-align:justify;}</style>

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
Aussi, le type est `SOCK_STREAM` qui permet une connexion fiable et bidirectionnelle, nécessaire à la réception de requêtes et l'envoi de réponses.
Enfin, en mettant 0 pour le protocole, on obtient un protocole par défaut correspondant au type spécifié.

Cela donne :

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
      FATAL("socket");
    }

#### TODO 2 : associer un nom à la socket

Pour associer un nom à la socket, on utilise la fonction *bind* :

    int bind(int socket, const struct sockaddr *address, socklen_t address_len);

On teste la valeur de retour qui est négative en cas d'erreur.
Cela donne :

    test = bind(fd, (struct sockaddr *) &addr_serveur, lg_addr_serveur);
    if(test < 0)
    {
      FATAL("bind");
    }

#### TODO 3 : ouverture du service

On ouvre enfin le service pour se placer en attente de potentiels clients.
Pour cela, on utilise la fonction *listen* :

    int listen(int socket, int backlog);

Avec un backlog de 4, cela donne :

    listen(fd, 4);

### Compléments

## Conclusion

- degré d'avancement
- problèmes rencontrés
- solutions
