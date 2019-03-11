#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "fonction.h"

// fonction qui renvoie un entier dans l'intervalle [a,b[
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}

// fonction qui test si un pixel est blanc dans une image PBM Ascii
int estblanc(couleur * pixel){
	if(pixel->blue != 0 && pixel->red != 0 && pixel->green !=0)
		return 1;
	else return 0;
}

