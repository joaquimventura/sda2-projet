#ifndef __READWRITE_H__
#define __READWRITE_H__

int taille_pixel(int couleur);
int max_couleur(Matrix * m);
Matrix * Read(char * fichier);
void Write(Matrix * test, char * fichier);

#endif