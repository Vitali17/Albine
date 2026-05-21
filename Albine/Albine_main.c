#include <stdio.h>
#include <stdlib.h>
#include "Functi/Albine_function.h"
#include "Logica_Structura/data.h"
#include "grafic.h"

/*
 * Functi utilizator
 */
void Initializare();
void Initializaretimer();
void Resetare();
int citiredate(struct stup **v);
void afisaredate(struct stup v[], int n);
void afisaredateIDSTUP(struct stup v[], int n, char s[]);
int IDStup(char z[][20], struct stup v[], int n);
void Raportstup(struct stup v[], char id[], int capacitatea);
void statisticistup(struct stup v[], int capacitate, char s[]);
void afisarealerte(struct stup v[], int n, char s[]);

struct stup *date = NULL;
char ID[40][20];

int NR_ID = 0, i, filtru = 0;
int citiri;

int main() {

	int optiuni = 0;
	int alegere;


	printf("============================================\n");
	printf(" SISTEM INTELIGENT DE MONITORIZARE STUPURI\n");
	printf("============================================\n");

	printf("Apasati tasta:\n");
	printf("1 - Continuare\n");
	printf("0 - Abandonare\n");
	printf("Optiunea: ");
	fflush(stdout);

	while (scanf("%d", &optiuni) != 1) {
	    printf("Introdu doar cifre!\n");
	    printf("Optiunea: ");
	    fflush(stdout);
	    while (getchar() != '\n');
	}

	while (optiuni != 0 && optiuni != 1) {
	    printf("Optiune invalida! (0 sau 1)\n");
	    printf("Optiunea: ");
	    fflush(stdout);
	    while (scanf("%d", &optiuni) != 1) {
	        printf("Introdu doar cifre!\n");
	        printf("Optiunea: ");
	        fflush(stdout);
	        while (getchar() != '\n');
	    }
	}

	if (optiuni == 0) {
	    return 0;
	}

	citiri = citiredate(&date);
	NR_ID = IDStup(ID, date, citiri);
	Initializare();

	while (1) {

	    Resetare();

	    printf("Meniu:\n");
	    printf("1 - Afisare date stupi\n");
	    printf("2 - Rezumat stupi\n");
	    printf("3 - Inchidere aplicatie\n");
	    printf("Optiunea: ");
	    fflush(stdout);
	    while (scanf("%d", &optiuni) != 1) {
	        printf("Introdu doar cifre!\n");
	        printf("Optiunea: ");
	        fflush(stdout);
	        while (getchar() != '\n');
	    }

	    if (optiuni < 1 || optiuni > 3) {
	        printf("Optiune invalida!\n");
	        fflush(stdout);
	        Sleep(1000);
	        continue;
	    }

	    switch (optiuni) {

	    case 1:
	        Resetare();
	        afisaredate(date, citiri);

	        printf("\n1 - Revenire: ");
	        fflush(stdout);
	        while (scanf("%d", &alegere) != 1) {
	            printf("Introdu doar cifre!\n1 - Revenire: ");
	            fflush(stdout);
	            while (getchar() != '\n');
	        }

	        break;

	    case 2:
	        while (1) {
	            Resetare();

	            printf("ID stupurilor:\n");
	            for (i = 0; i < NR_ID; i++) {
	                printf("%d. %s\n", i + 1, ID[i]);
	            }
	            fflush(stdout);

	            printf("%d. Revenire\n", NR_ID + 1);
	            printf("Alege stupul: ");
	            fflush(stdout);
	            while (scanf("%d", &alegere) != 1) {
	                printf("Introdu doar cifre!\nAlege stupul: ");
	                fflush(stdout);
	                while (getchar() != '\n');
	            }

	            if (alegere == NR_ID + 1) break;
	            if (alegere < 1 || alegere > NR_ID + 1) {
	                printf("Stup invalid!\n");
	                fflush(stdout);
	                Sleep(1000);
	                continue;
	            }

	            do {
	                Resetare();

	                afisaredateIDSTUP(date, citiri, ID[alegere - 1]);

	                printf("\n1 - Sortare\n");
	                printf("2 - Raport\n");
	                printf("3 - Statistici\n");
	                printf("4 - Alerte\n");
	                printf("5 - Grafic\n");
	                printf("6 - Revenire\n");

	                printf("Optiunea: ");
	                fflush(stdout);
	                while (scanf("%d", &optiuni) != 1) {
	                    printf("Introdu doar cifre!\nOptiunea: ");
	                    fflush(stdout);
	                    while (getchar() != '\n');
	                }

	                if (optiuni < 1 || optiuni > 6) {
	                    printf("Optiune invalida!\n");
	                    fflush(stdout);
	                    Sleep(1000);
	                    continue;
	                }

	                Resetare();

	                switch (optiuni) {

	                case 1:
	                    sortare(date, ID[alegere - 1], citiri);
	                    printf("\n1 - Revenire: ");
	                    fflush(stdout);
	                    while (scanf("%d", &optiuni) != 1) {
	                        printf("Introdu doar cifre!\n1 - Revenire: ");
	                        fflush(stdout);
	                        while (getchar() != '\n');
	                    }
	                    break;

	                case 2:
	                    Raportstup(date, ID[alegere - 1], citiri);
	                    printf("Fisier creat!\n");
	                    fflush(stdout);
	                    Initializaretimer();
	                    break;

	                case 3:
	                    statisticistup(date, citiri, ID[alegere - 1]);
	                    printf("\n1 - Revenire: ");
	                    fflush(stdout);
	                    while (scanf("%d", &optiuni) != 1) {
	                        printf("Introdu doar cifre!\n1 - Revenire: ");
	                        fflush(stdout);
	                        while (getchar() != '\n');
	                    }
	                    break;

	                case 4:
	                    afisarealerte(date, citiri, ID[alegere - 1]);
	                    printf("\n1 - Revenire: ");
	                    fflush(stdout);
	                    while (scanf("%d", &optiuni) != 1) {
	                        printf("Introdu doar cifre!\n1 - Revenire: ");
	                        fflush(stdout);
	                        while (getchar() != '\n');
	                    }
	                    break;

	                case 5:
	                    graficTemperatura(date, citiri, ID[alegere - 1]);
	                    break;

	                case 6:
	                    break;
	                }

	            } while (optiuni != 6);
	        }
	        break;

	    case 3:
	        free(date);
	        return 0;
	    }
	}

	free(date);
	return 0;
}
