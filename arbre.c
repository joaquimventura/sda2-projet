#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "fonction.h"
#include "readWrite.h"
#include "arbre.h"

node * makeSetA(int x,int y, Matrix * m){//initialise un noeud (allocation memoire)
	node * n = malloc(sizeof(node));
	n->rang = 0;
	n->pere = n;
	n->infoPix = &(m->matrix[x][y]);
	return n;
}


node * findSetA(int x, int y , pointeurMatrixArbre mp){//renvoit le représentant du pixel de position (x,y) = racine de l'arbre
	node * parcours = mp[x][y];

	while(parcours->pere != parcours){//boucle qui rmeonte au représentant
		parcours=parcours->pere;
	}
	return parcours;
}

node * UnionA(node * a1, node * a2){//fusionne les arbres a1 et a2
	if(a1==NULL){
		fprintf(stderr, "Union a1 == NULL\n");
		exit(1);
	}
	if(a2==NULL){
		fprintf(stderr, "Union a2 == NULL\n");
		exit(1);
	}
	while(a2 -> pere != a2){//on cherche la racine de l'arbre a2
		a2=a2->pere;
	}
	while(a1 -> pere != a1){//on cherche la racine de l'arbre a1
		a1=a1->pere;
	}
	if(a1 == a2){
		return a1;//si la racine est la meme cest que a1 et a2 appartiennent  au meme groupe
	}
	else{//sinon on attache l'abre le plus petit à la racine du plus grand
		if(a2->rang == a1->rang){
			a2->rang++;
			a1->pere=a2;
			return a2;
		}
		else{
			if(a1->rang > a2->rang){
				a2->pere = a1;
				return a1;
			}
			else{
				a1->pere = a2;
				return a2;
			}
		}
	}
}

void colorierArbre(char * image){

	Matrix * m = Read(image);

	//creation de la matrice de pointeur de noeud, elle permetra d'avoir un finset de cout constant
	pointeurMatrixArbre pm;						//creation de la matrice de pointeur;
	pm = malloc(m->hauteur*(sizeof(node **)));//et allocation mémoire 
	for (int i = 0; i < m->hauteur; i++){
		pm[i]=malloc(m->largeur*sizeof(node *));
	}

	int nombre_noeud = 0;//recherche du nombre de noeud (== nombre de case blanche)
	for(int i = 0; i < m->hauteur;i++){
		for (int j = 0; j < m->largeur; j++){
			if(estblanc(&(m->matrix[i][j])))
				nombre_noeud++;
		}
	}

	node ** tabNode = malloc(nombre_noeud*sizeof(node *));//creation du tableau de noeud qui servira a stoquer les differents arbres
	
	int k = 0;
	for(int i = 0; i < m->hauteur;i++){//allocation mémoire des éléments de tableau liste et initialisation de la matrice de pointeur
		for (int j = 0; j < m->largeur; j++){
			if(estblanc(&(m->matrix[i][j]))){
				tabNode[k] = makeSetA(i,j,m); //pixel de coordonnée [i][j]
				pm[i][j]=tabNode[k];   //représenté par le noeud pm[i][j]
				k++;
			}
		}
	}
	


	//creation des groupes
	k=0;
	for(int i = 0; i < m->hauteur;i++){ //pour chaque élément de la matrice
		for (int j = 0; j < m->largeur; j++){
			if(estblanc(&m->matrix[i][j])){//si le pixel n'est pas noir
										
										//on regarde si les voisins existe,s'il ne sont pas noir
				if(i-1>= 0 && estblanc(&m->matrix[i-1][j]) ){
					tabNode[k]= UnionA(tabNode[k],findSetA(i-1,j,pm));
					
				}
				if(i+1< m->hauteur && estblanc(&m->matrix[i+1][j]) ){
					tabNode[k]= UnionA(tabNode[k],findSetA(i+1,j,pm));
				}
				if(j+1< m->largeur && estblanc(&m->matrix[i][j+1])){
					tabNode[k]= UnionA(tabNode[k],findSetA(i,j+1,pm));
		
				}
				if(j-1 >= 0 && estblanc(&m->matrix[i][j-1])){
					tabNode[k]= UnionA(tabNode[k],findSetA(i,j-1,pm));		
				}
				k++;
			}	
		}
	}
	//On remarque que tabliste contiendra plusieurs fois le meme arbre mais ce n'est pas important étant donnée que l'on ne l'utilise pas pour colorier

	//coloriage de la marice
	
	for (int i = 0; i < nombre_noeud; i++){
		//on donne une couleur à chaque repredentant
		tabNode[i]->infoPix->blue = rand_a_b(1,255);//rand_a_b : valeur aléatoire entre 0 et 255
		tabNode[i]->infoPix->red = rand_a_b(1,255);
		tabNode[i]->infoPix->green = rand_a_b(1,255);
	}

	for (int i = 0; i < m->hauteur; i++){//on colorie chaque pixel de la couleur de son repésentant
		for (int j=0;j < m->largeur; j++){
			if(estblanc(&m->matrix[i][j])){
				node * rep=findSetA(i,j,pm);

				m->matrix[i][j].blue = rep->infoPix->blue;
				m->matrix[i][j].red= rep->infoPix->red;
				m->matrix[i][j].green = rep->infoPix->green;
			}
		}
	}

	//liberation de la mémoire

	

	//liberation de la matrice de pointeur
	for (int i = 0; i < m->hauteur; i++){
		for (int j = 0;j <m->largeur ; j++){
			if(estblanc(&m->matrix[i][j]))
				free(pm[i][j]);//on libère tous les noeuds
		}
		free(pm[i]);
	}
	free(pm);

	//liberation du tabeau d'arbre
	free(tabNode);

	
	m->est_coloriee = 1;

	char mot[50];
	strcpy(mot,image);
	if((strlen(mot) - 2) < 0)
    		fprintf(stderr, "Erreur renomage image\n");
	else
    	{
		// cette méthode permet de créer deux fichiers résultats différents pour colorier arbre
		// et colorier liste, permettant ainsi de comparer les résultats
		mot[strlen(mot) - 4] = 'a';
		mot[strlen(mot) - 3] = 'r';
		mot[strlen(mot) - 2] = 'b';
		mot[strlen(mot) - 1] = 'r';
		strcat(mot,"e.ppm");
	}

	/* else mot[strlen(mot) - 2] = 'p'; si on veut uniquement changer le nom de l'extension du fichier
	par .ppm au lieu de .pbm !

	ATTENTION : si on procède comme ceci, alors les listes ET les arbres créeront le même fichier. */

	Write(m, mot);

	return ;

	
}
