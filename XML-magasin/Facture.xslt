<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
 <html>
  <head>
  	<meta charset="UTF-8"/>
  </head>
  <body>
 	 <h1>Facture n°<xsl:value-of select="Facture/@idFact"/> commande n°<xsl:value-of select="Facture/@idCom"/></h1>
 	 
 	 <h2>Client</h2>
 	 <p>
 	 	Num : <xsl:value-of select="Facture/Client/Num"/><br/>
 	 	Nom : <xsl:value-of select="Facture/Client/Nom"/><br/>
 	 	Prenom : <xsl:value-of select="Facture/Client/Prenom"/><br/>
 	 	Adresse : <xsl:value-of select="Facture/Client/Adresse"/><br/>
 	 </p>
 	 
  	 <h2>Produits</h2>
  	 <table border="1">
  	 	<tr>
  	 		<th>Nom</th>
  	 		<th>Catégorie</th>
  	 		<th>Prix unitaire (en euros)</th>
  	 		<th>Quantité</th>
  	 		<th>Prix produit (en euros)</th>
  	 	</tr>
  	 	<xsl:for-each select="Facture/ListProduit/produit">
  	 	<tr>
  			<td><xsl:value-of select="Nom"/></td>
  			<td><xsl:value-of select="categorie"/></td>
  			<td><xsl:value-of select="prixUnit"/></td>
  			<td><xsl:value-of select="quantite"/></td>
  			<td><xsl:value-of select="prixProd"/></td>
  		</tr>
  	 	</xsl:for-each>
  	 </table>
  	 <h2>Total TTC</h2>
  	 <p>
  	 	<strong><xsl:value-of select="Facture/TotalTTC"/><xsl:value-of select="Facture/TotalTTC/@curr"/></strong><br/>
  	 	dont TVA à<xsl:value-of select="Facture/TVA"/>:
  	 	<xsl:value-of select="Facture/TotalTVA"/><xsl:value-of select="Facture/TotalTVA/@curr"/>
  	 </p>
  </body>
 </html>
</xsl:template>
</xsl:stylesheet>


