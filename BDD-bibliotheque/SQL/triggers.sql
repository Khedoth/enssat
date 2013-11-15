# -----------------------------------------------------------------------------
#       CREATION DES TRIGGER
# -----------------------------------------------------------------------------

# Un abonné ne peut pas formuler plus de 3 demandes
DELIMITER /
Drop trigger if exists demandes3 /
Create trigger demandes3 before insert on DEMANDE
for each row 
Begin
  Declare nbDemandes int;
  select count(*) into nbDemandes from DEMANDE where NUM_AB=new.NUM_AB;
  if(nbDemandes>=3) then
  	set new.NUM_AB= NULL;
  end if;
end
/
DELIMITER ;


# Un abonné ne peut emprunter plus de 5 livres à la fois
# Un même livre ne peut pas être emprunté en même temps par plusieurs abonnés
# Un livre "de côté" ne peut être emprunté que par un abonné ayant effectué une réservation sur ce livre
DELIMITER /
Drop trigger if exists emprunts_5 /
Create trigger emprunts_5 before insert on EMPRUNT
for each row
Begin
  # Un abonné ne peut emprunter plus de 5 livres à la fois
  Declare nb_emprunts int;
  select count(*) into nb_emprunts from EMPRUNT where NUM_AB=new.NUM_AB and DATE_RETOUR = 0000-00-00;
  if(nb_emprunts>=5) then
  	set new.CODE_BR=NULL;
  end if;
  
  # Un même livre ne peut pas être emprunté en même temps par plusieurs abonnés
  if new.CODE_BR in (SELECT CODE_BR from EMPRUNT WHERE DATE_RETOUR = 0000-00-00) then
  	set new.CODE_BR=NULL;
  end if;
  
  # Un livre "de côté" ne peut être emprunté que par un abonné ayant effectué une réservation sur ce livre
  if(new.CODE_BR in (select distinct CODE_BR from DEMANDE,EXEMPLAIRE where DEMANDE.CODE_CATA=EXEMPLAIRE.CODE_CATA)) then
  	if(new.NUM_AB not in (SELECT NUM_AB from DEMANDE,EXEMPLAIRE where DEMANDE.CODE_CATA=EXEMPLAIRE.CODE_CATA and EXEMPLAIRE.CODE_BR=new.CODE_BR)) then
  		set new.CODE_BR=NULL;
  	else
  		delete from DEMANDE where NUM_AB=new.NUM_AB and CODE_CATA=(select EXEMPLAIRE.CODE_CATA from EXEMPLAIRE,LIVRE where EXEMPLAIRE.CODE_CATA=LIVRE.CODE_CATA and EXEMPLAIRE.CODE_BR=new.CODE_BR);
  	end if;
  end if;
  
  #Si aucune erreur, mettre le statut du livre emprunté à "sorti"
  update EXEMPLAIRE set STATUT='sorti' where CODE_BR=new.CODE_BR;
end;
/
DELIMITER ;

#Une demande de renouvellement peut être effectuée seulement si le livre à renouveler n est pas demandé
DELIMITER /
Drop trigger if exists renouvellement /
Create trigger renouvellement before update on EMPRUNT
FOR EACH ROW
BEGIN
	declare x char(5);
	if(new.DATE_SORTIE=CURDATE() and new.DATE_RETOUR=0000-00-00) then 
		select CODE_CATA into x from EXEMPLAIRE WHERE CODE_BR=new.CODE_BR;
		if(x in(select CODE_CATA from DEMANDE)) then
			set new.DATE_SORTIE=NULL;
		end if;
	end if;
	
	#Si la date de retour est non nulle, mettre le statut du livre non lu à "de cote" s il y a des demandes et "disponible" sinon
	if(new.DATE_RETOUR != 0000-00-00) then
		if(new.CODE_BR in (select distinct CODE_BR from DEMANDE,EXEMPLAIRE where DEMANDE.CODE_CATA=EXEMPLAIRE.CODE_CATA)) then
			update EXEMPLAIRE set STATUT='de cote' where CODE_BR=new.CODE_BR;
		else
			update EXEMPLAIRE set STATUT='disponible' where CODE_BR=new.CODE_BR;
		end if;
	end if;
end;
/
DELIMITER ;
