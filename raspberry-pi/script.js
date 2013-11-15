/* Variables globales */
var init = 1; //booléen qui indique si on vient de charger la page ou non
var articleCourant; //contient l'article affiché courant

/* Initialisation de l'objet XMLHttpRequest */
var xhr = new XMLHttpRequest();
xhr.onload = reqListener;

/* Callback de l'instance xhr */
function reqListener() {
	document.getElementById('article').innerHTML=this.responseText;
};

/* Permet de modifier la couleur de la bordure du bloc article en fonction de l'article à afficher */
function changerCouleurCadreArticle(oldArticle,newArticle) {
	document.getElementById('article').classList.remove(oldArticle);
	document.getElementById('article').classList.add(newArticle);
}

/* Permet de lancer l'animation de glissement lors d'un changement d'article */
function moveArticle() {
	var article = document.getElementById('article');
	/* Soit on glisse vers la droite */
	if (article.classList.contains("translate-out"))
	{
		article.classList.remove("translate-out");
		article.classList.add("translate-in");
	}
	/* Soit on glisse vers la gauche */
	else
	{
		article.classList.remove("translate-in");
		article.classList.add("translate-out");
	}
}

/* Effectue la requete qui va récupérer le nouveau contenu à afficher */
function majContenuArticle(article) {
	xhr.open("get", "articles/" + article + ".htm", true);
	xhr.send();
}

/* Fonction appelée lors d'un clic sur le menu. C'est elle qui déclenche les autres fonctions */
function afficherArticle(article) {
	/* On n'effectue pas l'animation de glissement si on vient de charger la page */
	if(init==1) {
		changerCouleurCadreArticle(articleCourant,article);
		majContenuArticle(article);
		articleCourant = article;
		init = 0;
	}
	/* Si l'article qu'on souhaite afficher est différent de l'article courant, on change d'article avec une animation */
	else if(article!=articleCourant) {
		var macro = "changerCouleurCadreArticle('"+articleCourant+"','"+article+"');majContenuArticle('"+article+"');moveArticle();";
		moveArticle();
		setTimeout(macro,1000);
		articleCourant = article;
	}
}
