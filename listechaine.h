#ifndef __LISTECHAINE_H__
#define __LISTECHAINE_H__

typedef struct element element;
struct element{
	couleur * infoPix;
	element * suivant;
	element * rep;

};

typedef struct liste liste;
struct liste
{
	element * tete;
	element * queue;
};

typedef liste*** pointeurMatrix; //matrice permettant de retrouver une liste à partir de coordonnée (x,y)
typedef element*** pointeurMatrixElt; //matrice permettant de retrouver un element à partir de coordonnée (x,y)


liste * makeSet(int x, int y, Matrix * m);//Initialise une liste avec un unique element representant le pixel(x,y)

liste * findSet(int x, int y, pointeurMatrix pm);//Retourne l'adresse de la liste contenant l'élément représentant le pixel(x,y)

liste * Union(liste * l1, liste * l2);//Crée un liste l fusion de liste l1 et l2, supprimel1 et l2

void colorierListe(char * image);//Colorie une image ppm passée en paramettre

#endif