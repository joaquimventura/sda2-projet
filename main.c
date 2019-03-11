#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "struct.h"
#include "generate.h" 
#include "arbre.h" 
#include "listechaine.h"

double calculTempsExec(clock_t start_t, clock_t end_t){
	return ((double)(end_t-start_t))/(double)CLOCKS_PER_SEC;
}


int main(int argc, char const *argv[]){

	int n = 10;
	double total_t1;
	double total_t2;
	clock_t start_t1,end_t1;
	clock_t start_t2,end_t2;
	time_t t;
	srand((unsigned) time(&t)); //initializes random number generator
	
	FILE * f1=NULL;
	f1=fopen("valeurListe.time","w");

	FILE * f2=NULL;
	f2=fopen("valeurArbre.time","w");


	while(n <= 5120){//pour n de 10 à 10240 (limité à une image de 10240px sur 10240px sinon la mémoire est saturée)

		fprintf(stdout, "processing for size %d * %d\n",n,n);

		Generate(n,n,"image_test.pbm");

		total_t1 = 0;
		total_t2 = 0;

		if(n <= 160){//limité a 640 car l'algorithme est trop complexe  et prends un temps fous à l'execution (~17 minutes)
			start_t1=clock();		
			colorierListe("image_test.pbm");
			end_t1=clock();
		}

		start_t2=clock();
		colorierArbre("image_test.pbm");
		end_t2=clock();

		total_t1 = calculTempsExec(start_t1,end_t1);
		total_t2 = calculTempsExec(start_t2,end_t2);

		fprintf(f1,"%d %f\n",n,total_t1);
		fprintf(f2,"%d %f\n",n,total_t2);

		n*=2;
	}


	fclose(f1);
	fclose(f2);
	

	return 0;
}
