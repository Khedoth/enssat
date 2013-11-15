# -----------------------------------------------------------------------------
#		SUPPRESSION DES DONNEES DE LA BIBLIOTHEQUE
# -----------------------------------------------------------------------------
delete from EMPRUNT;
delete from ECRITPAR;
delete from DEMANDE;
delete from EXEMPLAIRE;
delete from GENRE;
delete from AUTEUR;
delete from ABONNE;
delete from LIVRE;

# -----------------------------------------------------------------------------
#       INSERTION DES DONNEES DE LA BIBLIOTHEQUE
# -----------------------------------------------------------------------------

load data local infile '../Donnees/Abonne.txt' into table ABONNE;
load data local infile '../Donnees/Livres.txt' into table LIVRE;
load data local infile '../Donnees/Exemplaire.txt' into table EXEMPLAIRE;
load data local infile '../Donnees/Auteur.txt' into table AUTEUR;
load data local infile '../Donnees/Genre.txt' into table GENRE;
load data local infile '../Donnees/Emprunt.txt' into table EMPRUNT;
load data local infile '../Donnees/Ecrit par.txt' into table ECRITPAR;
load data local infile '../Donnees/Demande.txt' into table DEMANDE;
