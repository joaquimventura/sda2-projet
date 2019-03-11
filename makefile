all : the_coloriage

the_coloriage : arbre.h listechaine.h main.c fonction.o listechaine.o arbre.o generate.o
	gcc -o the_coloriage main.c fonction.o listechaine.o arbre.o generate.o -g

listechaine.o : struct.h listechaine.c listechaine.h fonction.h readWrite.h
	gcc -o listechaine.o -c listechaine.c -g

arbre.o : struct.h fonction.h readWrite.h arbre.h arbre.c
	gcc -o arbre.o -c arbre.c -g

fonction.o : struct.h fonction.c fonction.h
	gcc -o fonction.o -c fonction.c -g

readWrite.o : struct.h readWrite.h fonction.h readWrite.c
	gcc -o readWrite.o -c readWrite.c -g

generate.o : generate.c generate.h fonction.h
	gcc -o generate.o -c generate.c -g

clean :
	rm *.o

mrproper :
	rm the_coloriage
	rm *.ppm
	rm *.pbm
	rm *.time
