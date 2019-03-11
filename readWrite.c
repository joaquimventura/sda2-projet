#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "fonction.h"
#include "readWrite.h"

// fonction qui lit une image au format PBM Ascii et créer une matrice de ses pixels
Matrix * Read(char * fichier)
{
    int i,j, ligne = 0, colonne = 0, compteur = 0;
    char nMagique[3];
    int color;
    FILE *file = NULL;

    file = fopen(fichier,"r");

    if(file != NULL)
    {
        // tester que c'est une image en noir et blanc
        fgets(nMagique,sizeof(nMagique),file);
        if(strcmp(nMagique,"P1")!=0)
        {
            fprintf(stderr,"Format d'image non reconnue\n");
            exit(1);
        }

        // récupérer le nombre de ligne et de colonne de la matrice à allouer
        fscanf(file,"%d %d",&colonne,&ligne);
        Matrix * m = malloc(sizeof(Matrix));
        m->est_coloriee = 0;
        m->hauteur = ligne;
        m->largeur = colonne;
        m->matrix = (couleur **)malloc(ligne*sizeof(couleur*));
        
	for(i=0;i<ligne;i++)
        {
            m->matrix[i] = malloc(colonne * sizeof(couleur));
        }

        color = fgetc(file); // pour accéder au début de la matrice et non le "\n" après les lignes colonnes en début de fichier
        for(i=0;i<ligne;i++)
        {
            for(j=0;j<colonne;j++)
            {
                color = fgetc(file); // je récupère la valeur du pixel (1 ou 0 dans ce cas)

                if(color == 10) // si on lit un "\n" on l'ignore
                {
                    color = fgetc(file);
                }

                if(color == 48) // si on lit un 0 (en ascii)
                {
                    m->matrix[i][j].red = 255; // 255 car on veut pouvoir ensuite travailler sur une image en couleur
                    m->matrix[i][j].green = 255;
                    m->matrix[i][j].blue = 255;
                }
                if(color == 49) // si on lit un 1 (en ascii)
                {
                    m->matrix[i][j].red = 0;
                    m->matrix[i][j].green = 0;
                    m->matrix[i][j].blue = 0;
                }
            }
        }

        return m;
    }
    else
    {
        fprintf(stderr,"Erreur création du fichier destination !\n");
        return NULL;
    }

    fclose(file);
}


// fonction qui renvoie la valeur max des couleurs des pixels dans la matrice
int max_couleur(Matrix * m)
{
    int i,j,resultat=0;
    resultat = m->matrix[0][0].red;
    for(i=0;i<m->hauteur;i++)
    {
        for(j=0;j<m->largeur;j++)
        {
            if((m->matrix[i][j].red) > resultat)
                resultat = m->matrix[i][j].red;
            if((m->matrix[i][j].green) > resultat)
                resultat = m->matrix[i][j].green;
            if((m->matrix[i][j].blue) > resultat)
                resultat = m->matrix[i][j].blue;
        }
    }
    return resultat;
}

// comme on ne doit pas dépasser les 70 caractères par ligne, je fai gaffe à combien de caractères j'écris
int taille_pixel(int couleur)
{
    int somme = 0;
    if((couleur >= 0) && (couleur <= 9))
        somme = 1;
    else
        somme = 1 + taille_pixel((int)(couleur / 10));

    return somme;
}
// Fonction qui renvoie le nombre de chiffre du nombre, positif ou nul, en argument.


// fonction qui écris une image au format PPM Ascii (couleur)
void Write(Matrix * test, char * fichier)
{
    int i,j,taille_vert = 0,taille_rouge = 0,taille_bleu = 0, max = 0,compteur;

    FILE* file = NULL;
    file = fopen(fichier,"w");
   
    if((file != NULL) && (test->est_coloriee)) // je vérifie que ma matrice est bien coloriée
    {
        // écriture des informations qui indiquent que c'est une image PPM

        fputs("P3\n",file);
        fprintf(file,"%d %d\n",test->largeur,test->hauteur);

        // écriture de la valeur max des pixels également (255 max dans ce projet)
        max = max_couleur(test);
        fprintf(file,"%d\n",max);

        for(i=0; i<test->hauteur; i++)
        {
            compteur=0;
            for(j=0; j<test->largeur; j++)
            {
                taille_rouge = taille_pixel(test->matrix[i][j].red);
                taille_vert = taille_pixel(test->matrix[i][j].green);
                taille_bleu = taille_pixel(test->matrix[i][j].blue);
               
                if((taille_rouge + compteur) <= 70) // si je n'ai pas encore écris 70 caractères sur ma ligne,
		// et que je peux écrire mes caractères de couleur sans dépasser les 70 caractères
                {
                    fprintf(file,"%d ",test->matrix[i][j].red);
                    compteur += taille_rouge; // j'ajoute la taille du caractère que je viens d'écrire
                    compteur += 1; // et l'espace que je laisse après
                }
                else  // sinon
                {
                    compteur = 0;
                    fputs("\n",file); // je reviens à la ligne car j'ai déjà 70 caractères, ou que je ne peux pas
		    // écrire ma couleur sans dépasser
                    fprintf(file,"%d ",test->matrix[i][j].red);
                    compteur += taille_rouge;
                    compteur += 1;
                }

                if((taille_vert + compteur) <= 70)
                {
                    fprintf(file,"%d ",test->matrix[i][j].green);
                    compteur += taille_vert;
                    compteur += 1;
                }
                else
                {
                    compteur = 0;
                    fputs("\n",file);
                    fprintf(file,"%d ",test->matrix[i][j].green);
                    compteur += taille_vert;
                    compteur += 1;
                }

                if((taille_bleu + compteur) <= 70)
                {
                    fprintf(file,"%d ",test->matrix[i][j].blue);
                    compteur += taille_bleu;
                    compteur += 1;
                }
                else
                {
                    compteur = 0;
                    fputs("\n",file);
                    fprintf(file,"%d ",test->matrix[i][j].blue);
                    compteur += taille_bleu;
                    compteur += 1;
                }

            }
            fputs("\n",file);
        }
    }
    else
    {
        fprintf(stderr,"Erreur ouverture fichier / Matrice non coloriée!\n");
	exit(1);
    }

    fclose(file);
}
