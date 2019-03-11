#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct Couleur //represente la couleur d'un pixel
{
    int red;
    int green;
    int blue;
}couleur;

typedef struct matrice
{
    int hauteur;
    int largeur;
    couleur ** matrix;
    /* Chaque case de la matrice pointe sur un triplet de couleur, ce triplet
    sera (0,0,0) ou (255,255,255) dans le cas d'une image en noir et blanc (PBM), ou trois
    valeurs différentes dans le cas d'une image en couleur (PPM).
    */
    int est_coloriee;   
}Matrix;



#endif

