<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:key name="category" match="Produit" use="Categorie" />

<xsl:template match="Magasin">

 <html>
  <head>
  	<meta charset="UTF-8"/>
  </head>
  <body>
 	 <h2>Produits par catégories</h2>
 	 
 	 <xsl:for-each select="Produit[count(. | key('category', Categorie)[1]) = 1]">
 	 
 	 	<xsl:sort select="Categorie" />
		<h3><xsl:value-of select="Categorie" /></h3>
		
  	 	<xsl:for-each select="key('category', Categorie)">
  			<xsl:sort select="Prix" data-type="number"/>
  			<xsl:value-of select="Nom"/>
  			<xsl:value-of select="Prix"/>
  			<br/>
  	 	</xsl:for-each>
  	 </xsl:for-each>
  </body>
 </html>
</xsl:template>
</xsl:stylesheet>


