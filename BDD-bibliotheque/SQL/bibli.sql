DROP DATABASE IF EXISTS BIBLIO;

CREATE DATABASE IF NOT EXISTS BIBLIO;
USE BIBLIO;

# -----------------------------------------------------------------------------
#       TABLE : LIVRE
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS LIVRE
 (
   CODE_CATA CHAR(5) NOT NULL  ,
   TITRE VARCHAR(255) NOT NULL
   , PRIMARY KEY (CODE_CATA) 
 ) 
 ENGINE=InnoDB;

# -----------------------------------------------------------------------------
#       TABLE : EXEMPLAIRE
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS EXEMPLAIRE
 (
   CODE_BR CHAR(32) NOT NULL  ,
   CODE_CATA CHAR(5) NOT NULL  ,
   EDITEUR VARCHAR(128) NOT NULL  ,
   STATUT VARCHAR(128) NOT NULL
   , PRIMARY KEY (CODE_BR) 
 ) 
 ENGINE=InnoDB;

# -----------------------------------------------------------------------------
#       TABLE : AUTEUR
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS AUTEUR
 (
   NUM_AU CHAR(10) NOT NULL  ,
   NOM_AU VARCHAR(128) NOT NULL  ,
   PRENOM_AU VARCHAR(128) NOT NULL
   , PRIMARY KEY (NUM_AU) 
 ) 
 ENGINE=InnoDB;

# -----------------------------------------------------------------------------
#       TABLE : ABONNE
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS ABONNE
 (
   NUM_AB CHAR(10) NOT NULL  ,
   NOM_AB VARCHAR(128) NOT NULL  ,
   PRENOM_AB VARCHAR(128) NOT NULL  ,
   ADRESSE VARCHAR(255) NOT NULL  ,
   DATE_ADH DATE NOT NULL  
   , PRIMARY KEY (NUM_AB) 
 ) 
 ENGINE=InnoDB;

# -----------------------------------------------------------------------------
#       TABLE : DEMANDE
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS DEMANDE
 (
   NUM_AB CHAR(10) NOT NULL  ,
   CODE_CATA CHAR(5) NOT NULL  
   , PRIMARY KEY (NUM_AB,CODE_CATA) 
 ) 
 ENGINE=InnoDB;
 
# -----------------------------------------------------------------------------
#       TABLE : ECRITPAR
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS ECRITPAR
 (
   NUM_AU CHAR(10) NOT NULL  ,
   CODE_CATA CHAR(5) NOT NULL  
   , PRIMARY KEY (NUM_AU,CODE_CATA) 
 ) 
 ENGINE=InnoDB;
 
# -----------------------------------------------------------------------------
#       TABLE : GENRE
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS GENRE
 (
   GENRE VARCHAR(128) NOT NULL  ,
   CODE_CATA CHAR(5) NOT NULL  
   , PRIMARY KEY (GENRE,CODE_CATA) 
 ) 
 ENGINE=InnoDB;

# -----------------------------------------------------------------------------
#       TABLE : EMPRUNT
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS EMPRUNT
 (
   NUM_AB CHAR(10) NOT NULL  ,
   CODE_BR CHAR(32) NOT NULL  ,
   DATE_SORTIE DATE NOT NULL  ,
   DATE_RETOUR DATE 
   , PRIMARY KEY (NUM_AB,CODE_BR,DATE_SORTIE) 
 ) 
 ENGINE=InnoDB;


# -----------------------------------------------------------------------------
#       CREATION DES REFERENCES DE TABLE
# -----------------------------------------------------------------------------

ALTER TABLE EXEMPLAIRE 
  ADD FOREIGN KEY FK_EXEMPLAIRE_LIVRE (CODE_CATA)
      REFERENCES LIVRE (CODE_CATA) ;

ALTER TABLE DEMANDE 
  ADD FOREIGN KEY FK_DEMANDE_ABONNE (NUM_AB)
      REFERENCES ABONNE (NUM_AB) ;

ALTER TABLE DEMANDE 
  ADD FOREIGN KEY FK_DEMANDE_LIVRE (CODE_CATA)
      REFERENCES LIVRE (CODE_CATA) ;

ALTER TABLE ECRITPAR 
  ADD FOREIGN KEY FK_ECRITPAR_AUTEUR (NUM_AU)
      REFERENCES AUTEUR (NUM_AU) ;

ALTER TABLE ECRITPAR 
  ADD FOREIGN KEY FK_ECRITPAR_LIVRE (CODE_CATA)
      REFERENCES LIVRE (CODE_CATA) ;
      
ALTER TABLE GENRE 
  ADD FOREIGN KEY FK_GENRE_LIVRE (CODE_CATA)
      REFERENCES LIVRE (CODE_CATA) ;

ALTER TABLE EMPRUNT 
  ADD FOREIGN KEY FK_EMPRUNT_ABONNE (NUM_AB)
      REFERENCES ABONNE (NUM_AB) ;

ALTER TABLE EMPRUNT 
  ADD FOREIGN KEY FK_EMPRUNT_EXEMPLAIRE (CODE_BR)
      REFERENCES EXEMPLAIRE (CODE_BR) ;
