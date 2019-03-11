#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "fonction.h"
#include "generate.h"
#include <time.h>

// fonction qui génère une image (matrice) de n lignes par m colonnes dans le fichier "fichier"
void Generate(int n, int m, char * fichier)
{
	int nombre_aleatoire = 0,i,j,compteur=0;
	FILE *file = NULL;
	srand(time(NULL));   // initialisation de l'aléatoire

	file = fopen(fichier,"w");   // j'ouvre le fichier destination

	if(file != NULL)
	{
		// écriture des informations qui indiquent que c'est une image PBM
		fputs("P1\n",file);   // image au format PBM Ascii
		fprintf(file,"%d %d\n",m,n);   // nombre de colonne, nombre de ligne (comme les conventions)

		for(i=1; i<=n; i++)
		{
			compteur=0;
			for(j=1; j<=m; j++)
			{
				compteur++; // comme on doit écrire pas plus de 70 caractères par ligne, on utilise
				// un compteur qu'on incrémente à chaque fois qu'on ajoute un caractère

				nombre_aleatoire = rand_a_b(0,2); // j'inialise un nombre aléatoire appartenant à [0,2[
				if(compteur > 70)
				{
					// si on est à 70 caractères pour cette ligne, j'en saute une
					fputs("\n",file);
					fprintf(file,"%d",nombre_aleatoire);
					compteur-=69;
				}
				else
				{
					fprintf(file,"%d",nombre_aleatoire);
				}
			}
			fputs("\n",file);
		}

	}
	else
	{
		fprintf(stderr,"Erreur création du fichier destination !\n");
		exit(1);
	}

	fclose(file);
}
