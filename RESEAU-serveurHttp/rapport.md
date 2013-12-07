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

#### TODO 1 : création de la prise

Pour l'étape de création, on utilise la fonction *socket* dont on récupère le retour dans *fd* :

    int socket(int domain, int type, int protocol);

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
