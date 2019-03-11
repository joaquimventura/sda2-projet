#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "struct.h"
#include "generate.h" 
#include "arbre.h" 
#include "listechaine.h"


int main(int argc, char const *argv[])
{
	Generate(4,4,"image_test.ppm");
	printf("Generate ok\n");
	
		
	colorierListe("image_test.ppm");
	
	return 0;
}

