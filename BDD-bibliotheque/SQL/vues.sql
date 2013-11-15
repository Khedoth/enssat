#Liste des retardataires
drop view if exists RETARD;
create view RETARD as
select EMPRUNT.NUM_AB, PRENOM_AB, NOM_AB , EMPRUNT.CODE_BR, TITRE
from EMPRUNT, LIVRE, ABONNE, EXEMPLAIRE
where DATE_RETOUR=0000-00-00
      and DATEDIFF(CURDATE(),DATE_SORTIE)>15
      and EMPRUNT.NUM_AB = ABONNE.NUM_AB
      and EMPRUNT.CODE_BR = EXEMPLAIRE.CODE_BR
      and EXEMPLAIRE.CODE_CATA = LIVRE.CODE_CATA;

#Catalogue de la bibliothèque
drop view if exists CATALOGUE;
create view CATALOGUE as
select CODE_BR,TITRE,PRENOM_AU,NOM_AU,EDITEUR,GENRE,STATUT
from EXEMPLAIRE,LIVRE,AUTEUR,GENRE,ECRITPAR
where EXEMPLAIRE.CODE_CATA=LIVRE.CODE_CATA
      and LIVRE.CODE_CATA=ECRITPAR.CODE_CATA
      and ECRITPAR.NUM_AU=AUTEUR.NUM_AU
      and LIVRE.CODE_CATA=GENRE.CODE_CATA;
