<?xml version="1.0" encoding="windows-1251" ?> 
<xsl:stylesheet 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
	xmlns:sdk="http://www.standards.scientific-soft.com/xsl">
		
	<xsl:template match="*">		
		<xsl:element name="{local-name(.)}"> 
			<xsl:for-each select="@*">
				<xsl:attribute name="{name()}">
					<xsl:value-of select="."/>
			 	</xsl:attribute>  
			</xsl:for-each>		
			<xsl:apply-templates/>
		</xsl:element>
	</xsl:template>	
		
	<xsl:template match="sdk:article">
		<html>
			<head>
				<title><xsl:value-of select="/sdk:article/@title"/></title>
				<meta http-equiv="Content-Type" content="text/html; charset=windows-1251"/>
				<link href="{/sdk:article/@prefix}/styles/style.css" rel="stylesheet" type="text/css"/>
			</head>	
			<body>
				<div class="ds_doc_body">			
					<h1><xsl:value-of select="/sdk:article/@title"/></h1>
					<hr size="1"/>													
					<xsl:apply-templates/>		
				</div>
				<div class="ds_footer">
					<hr size="1"/>
				</div>					
			</body>
		</html>	
	</xsl:template>	
	
	<xsl:template match="sdk:subtitle">
		<h2><xsl:apply-templates/></h2>
	</xsl:template>	
	
	<xsl:template match="sdk:subsubtitle">
		<h3><xsl:apply-templates/></h3>
	</xsl:template>	
	
	<xsl:template match="sdk:link">
		<a href="{@link}"><xsl:apply-templates/></a>
	</xsl:template>		
	
	<xsl:template match="sdk:blink">
		<b><a href="{@link}"><xsl:apply-templates/></a></b>
	</xsl:template>	
	
	<xsl:template match="sdk:entry">
		<p><xsl:apply-templates/></p>
	</xsl:template>
	
	<xsl:template match="sdk:image">
		<img src="{@path}" alt="{@descr}"/>
	</xsl:template>	
	
	<xsl:template match="sdk:block">
		<p class="ds_ref"><xsl:value-of select="@name"/></p>		
		<blockquote>
			<xsl:apply-templates/>
		</blockquote>		
	</xsl:template>
	
	<xsl:template match="sdk:ublock">
		<blockquote>
			<xsl:apply-templates/>
		</blockquote>		
	</xsl:template>	
	
	<xsl:template match="sdk:table">
		<table class="ds_table">
			<tbody>							
				<xsl:apply-templates/>
			</tbody>
		</table>								
	</xsl:template>		
	
</xsl:stylesheet>
