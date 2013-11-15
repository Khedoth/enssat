# -----------------------------------------------------------------------------
#       PROCÉDURES STOCKÉES
# -----------------------------------------------------------------------------

#Retrait d un abonné
DELIMITER /
CREATE PROCEDURE retraitAB(IN abonne CHAR(10))
BEGIN
	delete from DEMANDE where NUM_AB = abonne;
	delete from EMPRUNT where NUM_AB = abonne;
	delete from ABONNE where NUM_AB = abonne;
END;
/
DELIMITER ;

#Nouvelle inscription
DELIMITER /
CREATE PROCEDURE nouvelleInscription(IN num CHAR(10), IN nom VARCHAR(128), IN prenom VARCHAR(128), IN adresse VARCHAR(255))
BEGIN
	insert into ABONNE values(num, nom, prenom, adresse, CURDATE());
END;
/
DELIMITER ;

#Gestion des livres en attente
DELIMITER /
CREATE PROCEDURE supprimerLivreAttente()
BEGIN
	delete from DEMANDE where CODE_CATA IN (select CODE_CATA from EXEMPLAIRE,EMPRUNT where EXEMPLAIRE.CODE_BR=EMPRUNT.CODE_BR and STATUT='de cote' and DATEDIFF(CURDATE(),DATE_RETOUR)>7);
	update EXEMPLAIRE set STATUT='disponible' where STATUT='de cote' and CODE_CATA not in (select CODE_CATA from DEMANDE);
END;
/
DELIMITER ;
