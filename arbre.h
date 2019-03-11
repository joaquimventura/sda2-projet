#ifndef __ARBRE_H__
#define __ARBRE_H__


typedef struct node node;
struct node
{
	int rang;
	node * pere;
	couleur * infoPix;
};


typedef node*** pointeurMatrixArbre;//matrice permettant de retrouver un noeud à partir de coordonnée x,y

node * makeSetA(int x,int y, Matrix * m);//Initialise un noeud

node * findSetA(int x, int y , pointeurMatrixArbre mp);//renvoit l'adresse du représentant du pixel(x,y)

node * UnionA(node * a1, node * a2);//renvoit la fusion de a1 et a2 (ne creer pas de nouveau noeud)

void colorierArbre(char * image);//Colorie une image pbm passée en parametre

#endif