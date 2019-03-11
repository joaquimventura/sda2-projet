#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "fonction.h"
#include "readWrite.c"
#include "listechaine.h"

liste * makeSet(int x, int y, Matrix * m){//initialise une liste comprenenant 1 seul élément pointant sur mat[x][y]
	element * e = malloc(sizeof(element));
	e->suivant = NULL;
	e->rep = e;
	e->infoPix = &(m->matrix[x][y]); //adresse de l'emplacement (x,y) de la matrice de pixel;

	liste * l = malloc(sizeof(liste));
	l->tete = e;
	l->queue = e;

	m->matrix[x][y].blue = rand_a_b(1,255);//On initialise la couleurs des pixels
	m->matrix[x][y].red = rand_a_b(1,255);
	m->matrix[x][y].green = rand_a_b(1,255);
	return l;
}

liste * findSet(int x, int y, pointeurMatrix pm){//retourne la liste à laquelle appartient le pixel de coordonnée(x,y)
	return pm[x][y];
}

liste * UnionL(liste * l1, liste * l2){//fait la fusion des listes l1 et l2
	if(l1==NULL){
		fprintf(stderr, "UnionL l1 == NULL\n");
		exit(1);
	}
	if(l2==NULL){
		fprintf(stderr, "UnionL l2 == NULL\n");
		exit(1);
	}

	liste * l = (liste *)malloc(sizeof(liste));
	if(l==NULL){
		fprintf(stderr, "Erreur allocation Liste dans UnionL\n" );
		exit(1);
	}

	if(l1->tete->rep == l2->tete->rep){//Si les représentants sont les memes ça signifie que l1 et l2 sont déjà dans la meme liste
		l->tete = l1->tete;
		l->queue = l1->queue;
		free(l2);
		return l;
	}
	else{
		element * parcour = l2->tete;
		while(parcour != NULL){ //tous éléments de l2 auront pour représentant l1->tete
			parcour->rep=l1->tete;
			parcour=parcour->suivant;
		}

		l->tete = l1->tete;	//sinon on attache la tete de l2 à la queue de l1
		l->queue = l2->queue;
		l1->queue->suivant=l2->tete;
		free(l1);//On supprime les anciennes liste et on renvoi la nouvelle
		free(l2);
		return l;
	}
	
}

void colorierListe(char * image){


	Matrix * m = Read(image);
		
	pointeurMatrixElt pe;							//Matrice d'élément permetant de colorier et d'avoir toujours un accès aux elements
	pe = malloc(m->hauteur*(sizeof(element **)));	
	for (int i = 0; i < m->hauteur; i++){
		pe[i]=malloc(m->largeur*sizeof(element *));
	}

	pointeurMatrix pm;							//Matrice des liste;
	pm = malloc(m->hauteur*(sizeof(liste **)));
	for (int i = 0; i < m->hauteur; i++){		//permet de retrouver la liste à laquelle appartient le pixel (x,y) et de stoquer toutes les listes
		pm[i]=malloc(m->largeur*sizeof(liste *));
	}

	for(int i = 0; i < m->hauteur;i++){//allocation mémoire des éléments et des listes
		for (int j = 0; j < m->largeur; j++){
			if(estblanc(&m->matrix[i][j])){
				pm[i][j]=makeSet(i,j,m); //pixel de coordonnée [i][j] representé par la liste pointée par pm[i][j]
				pe[i][j]=pm[i][j]->tete->rep;//pixel [i][j] = element de couleur[i][j]
			}
			else{
				pm[i][j]=NULL;
				pe[i][j]=NULL;
			}
		}
	}
	
	//creation des groupes
	
	//Nous avions au début réalisé un algorithme plus optimisé mais celui si continuait de segfault malgrès tous nos effort.
	//Celui ci est beaucoup plus complexe (voir trop complexe) mais fonctionnel
	
	liste * fusion;
	
	for(int i = 0; i < m->hauteur;i++){ //pour chaque élément de la matrice
		for (int j = 0; j < m->largeur; j++){
			if(estblanc(&m->matrix[i][j])){//si le pixel n'est pas noir						
													
				if(i-1>= 0 && estblanc(&m->matrix[i-1][j])){//on regarde si les voisins existe,s'il ne sont pas noir
					liste * l1 = findSet(i,j,pm);
					liste * l2 = findSet(i-1,j,pm);
					fusion=UnionL(l1,l2);					//On fusionne le voisin 

					for(int l = 0 ; l < m->hauteur; l++){	//on met à jour pm : on supprime toutes les listes ayant le meme representant qu'un des éléments fusionné
						for(int n=0 ; n < m->largeur ; n++){//et on fait pointer la matrice sur fusion
							if(estblanc(&m->matrix[i][j])){	
								if(pm[l][n] == l1 || pm[l][n]==l2){
									pm[l][n]=fusion;
								}
							}
						}
					}
				}
				if(i+1< m->hauteur && estblanc(&m->matrix[i+1][j])){
					liste * l1 = findSet(i,j,pm);
					liste * l2 = findSet(i+1,j,pm);
					fusion=UnionL(l1,l2);//On fusionne les deux liste
					for(int l = 0 ; l < m->hauteur; l++){
						for(int n=0 ; n < m->largeur ; n++){
							if(estblanc(&m->matrix[i][j])){
								if(pm[l][n] == l1 || pm[l][n]==l2){
									pm[l][n]=fusion;
								}
							}
						}
					}
				}
				if(j+1< m->largeur && estblanc(&m->matrix[i][j+1])){
					liste * l1 = findSet(i,j,pm);
					liste * l2 = findSet(i,j+1,pm);
					fusion=UnionL(l1,l2);//On fusionne les deux liste
					for(int l = 0 ; l < m->hauteur; l++){
						for(int n=0 ; n < m->largeur ; n++){
							if(estblanc(&m->matrix[i][j])){
								if(pm[l][n] == l1 || pm[l][n]==l2){
									pm[l][n]=fusion;
								}
							}
						}
					}
				}
				if(j-1 >= 0 && estblanc(&m->matrix[i][j-1])){
					liste * l1 = findSet(i,j,pm);
					liste * l2 = findSet(i,j-1,pm);
					fusion=UnionL(l1,l2);//On fusionne les deux liste
					for(int l = 0 ; l < m->hauteur; l++){
						for(int n=0 ; n < m->largeur ; n++){
							if(estblanc(&m->matrix[i][j])){
								if(pm[l][n] == l1 || pm[l][n]==l2){
									pm[l][n]=fusion;
								}
							}
						}
					}
				}
			}	
		}
	}

	//coloriage

	for(int i = 0; i < m->hauteur; i++){//On colorie chaque pixel en fonction de son représentant
		for (int j = 0; j < m->largeur; j++){
			if(estblanc(&m->matrix[i][j])){
				m->matrix[i][j].blue=pe[i][j]->rep->infoPix->blue;
				m->matrix[i][j].red=pe[i][j]->rep->infoPix->red;
				m->matrix[i][j].green=pe[i][j]->rep->infoPix->green;
			}
		}
	}
	m->est_coloriee = 1;
	
	//liberation de la mémoire

	
	//liberation de tous les noeuds et de toutes les istes
	for(int i = 0; i < m->hauteur;i++){
		for (int j = 0; j < m->largeur; j++){
			if(estblanc(&m->matrix[i][j])){
				if(pm[i][j]!=NULL){
					//free(pm[i][j]);//segfault car : "invalid free" ce qui ne devrais pas arriver etant donnée la précondition
				}
				free(pe[i][j]);

			}
		}
		free(pm[i]);
		free(pe[i]);
	}
	free(pe);
	free(pm);
	

	char mot[50];
	strcpy(mot,image);
	if((strlen(mot) - 2) < 0)
    		fprintf(stderr, "Erreur renomage image\n");
	else
    	{
		// cette méthode permet de créer deux fichiers résultats différents pour colorier arbre
		// et colorier liste, permettant ainsi de comparer les résultats
		mot[strlen(mot) - 4] = 'l';
		mot[strlen(mot) - 3] = 'i';
		mot[strlen(mot) - 2] = 's';
		mot[strlen(mot) - 1] = 't';
		strcat(mot,"e.ppm");
	}
	
	/* else mot[strlen(mot) - 2] = 'p'; si on veut uniquement changer le nom de l'extension du fichier
	par .ppm au lieu de .pbm !

	ATTENTION : si on procède comme ceci, alors les listes ET les arbres créeront le même fichier. */
	
	Write(m, mot);

	return;

}
