<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" encoding="utf-8" indent="yes"/>
<xsl:template match="/">
<biblio>
	<livres>
		<!-- pour chaque item, recuperer les infos et les ecrire en respectant la structure de la dtd -->
		<xsl:for-each select="BookList/Books/Item">
		<xsl:element name="livre">
			<xsl:attribute name="cat"><xsl:value-of select='@cat'/></xsl:attribute>
			<xsl:attribute name="lieu">biblio2</xsl:attribute>
			<titre><xsl:value-of select='Title'/></titre>
			<auteur><xsl:value-of select='Author'/></auteur>
			<editeur><xsl:value-of select='Publisher'/></editeur>
			<ref><xsl:value-of select='@ISBN'/></ref>
		</xsl:element>
		</xsl:for-each>
  	</livres>
  	<categories>
  		<!-- pour chaque categorie, recuperer les infos et les ecrire en respectant la structure de la dtd -->
  		<xsl:for-each select="BookList/Categories/Category">
  			<xsl:element name="categorie">
				<xsl:attribute name="code">
					<xsl:value-of select='@code'/>
				</xsl:attribute>
				<xsl:attribute name="desc">
					<xsl:value-of select='@desc'/>
				</xsl:attribute>
			</xsl:element>
		</xsl:for-each>
	</categories>
	<emprunts/> <!-- la biblio2 ne possede pas d'infos sur les emprunts mais la balise est necessaire a la validation -->
</biblio>
</xsl:template>
</xsl:stylesheet>


