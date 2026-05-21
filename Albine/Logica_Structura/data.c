#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Logica_Structura/data.h"

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BLUE  "\033[34m"

int citiredate(struct stup **v) {
    FILE *f = fopen("date.in", "r");

    if (f == NULL) {
        printf("Eroare deschidere fisier");
        return 0;
    }

    int capacitate = 4;
    int i = 0;

    *v = malloc(capacitate * sizeof(struct stup));

    if (*v == NULL) {
        fclose(f);
        return 0;
    }

    while (fscanf(f, "%19s %f %f %f %f %f %d %24s",
                  (*v)[i].idstup,
                  &(*v)[i].temp,
                  &(*v)[i].CO2,
                  &(*v)[i].hum,
                  &(*v)[i].pres,
                  &(*v)[i].zgomot,
                  &(*v)[i].varsta,
                  (*v)[i].dataora) == 8) {

        i++;

        if (i >= capacitate) {
            capacitate *= 2;

            struct stup *tmp = realloc(*v, capacitate * sizeof(struct stup));

            *v = tmp;
        }
    }

    fclose(f);
    return i;
}

void afisaredate(struct stup v[], int n) {
	printf("| %-8s | %-9s | %-9s | %-8s | %-9s | %-10s | %-8s | %-17s |\n",
			"Id_stup", "Temp(*C)", "CO2", "Hum", "Pres", "Zgomot", "Varsta",
			"Data_ora");

	printf("---------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < n; i++) {

		printf("| %-8s |", v[i].idstup);

		if (v[i].temp < 33.5 || v[i].temp > 36.5)
			printf(BLUE" %9.2f "RESET, v[i].temp);
		else
			printf(GREEN" %9.2f "RESET, v[i].temp);

		printf("| %9.2f | %8.2f | %9.2f | %10.2f | %8d | %-17s |\n", v[i].CO2,
				v[i].hum, v[i].pres, v[i].zgomot, v[i].varsta, v[i].dataora);
	}
}

void afisaredateIDSTUP(struct stup v[], int n, char s[]) {
	printf("| %-8s | %-9s | %-9s | %-8s | %-9s | %-10s | %-8s | %-17s |\n",
			"Id_stup", "Temp(*C)", "CO2", "Hum", "Pres", "Zgomot", "Varsta",
			"Data_ora");

	printf("---------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < n; i++) {

		if (strcmp(v[i].idstup, s) == 0) {

			printf("| %-8s |", v[i].idstup);

			if (v[i].temp < 33.5 || v[i].temp > 36.5)
				printf(BLUE" %9.2f "RESET, v[i].temp);
			else
				printf(GREEN" %9.2f "RESET, v[i].temp);

			printf("| %9.2f | %8.2f | %9.2f | %10.2f | %8d | %-17s |\n",
					v[i].CO2, v[i].hum, v[i].pres, v[i].zgomot, v[i].varsta,
					v[i].dataora);
		}
	}
}

int IDStup(char z[][20], struct stup v[], int n) {
	int nr = 0;
	for (int i = 0; i < n; i++) {
		int gasit = 0;
		for (int j = 0; j < nr; j++) {
			if (strcmp(z[j], v[i].idstup) == 0) {
				gasit = 1;
				break;
			}
		}
		if (!gasit) {
			strcpy(z[nr], v[i].idstup);
			nr++;
		}
	}

	return nr;
}

