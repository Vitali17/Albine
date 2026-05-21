#ifndef ALBINEFUNCTIONH
#define ALBINEFUNCTIONHS

#include "../Logica_Structura/data.h"

void Initializare();
void Initializaretimer();
void Resetare();
void Raportstup(struct stup v[], char s[], int capacitate);
int Decizie(FILE *f, float max, float minim, float diferenta, int indice);
void statisticistup(struct stup v[], int capacitate, char s[]);
void afisarealerte(struct stup v[], int n, char s[]);
void sortare(struct stup v[], char s[] , int n);


#endif
