#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "Albine_function.h"
#include "../Logica_Structura/data.h"

/*
 * Functi de initializare si resetare
 */
void Initializare() {
	int i;
	printf("\nInitializare");
	fflush(stdout);
	for (i = 0; i < 20; i++) {
		Sleep(200);
		printf("~");
		fflush(stdout);
	}
}

void Initializaretimer() {
	int i;
	for (i = 1; i <= 3; i++) {
		printf("Revenire %d", i);
		printf("\r");
		fflush(stdout);
		Sleep(1000);
	}
}

void Resetare() {
	int i;
	for (i = 0; i < 50; i++) {
		printf("\n");
		fflush(stdout);
	}
}

/*
 * Functi logice de luat decizi
 */
void Raportstup(struct stup v[], char s[], int capacitate) {
	FILE *f;

	char extensie[20];
	sprintf(extensie, "%s.txt", s);
	f = fopen(extensie, "w");
	int i, j, scortotal = 0;
	float max, minim;
	fprintf(f, "\nRaport Stup\n");
	fprintf(f, "Perioada Analiza\n");
	fprintf(f, "%s --> %s\n", v[0].dataora, v[capacitate - 1].dataora);
	for (i = 0; i < 5; i++) {
		max = -99999;
		minim = 99999;
		switch (i) {
		case 0:
			fprintf(f, "\nTemperatura:\n");
			break;
		case 1:
			fprintf(f, "\nUmiditatea:\n");
			break;
		case 2:
			fprintf(f, "\nCO2:\n");
			break;
		case 3:
			fprintf(f, "\nZgomot:\n");
			break;
		case 4:
			fprintf(f, "\nPresiune:\n");
			break;
		}

		for (j = 0; j < capacitate; j++) {
			if (strcmp(v[j].idstup, s) == 0) {
				switch (i) {
				case 0:
					if (v[j].temp > max)
						max = v[j].temp;
					if (v[j].temp < minim)
						minim = v[j].temp;
					break;
				case 1:
					if (v[j].hum > max)
						max = v[j].hum;
					if (v[j].hum < minim)
						minim = v[j].hum;
					break;
				case 2:
					if (v[j].CO2 > max)
						max = v[j].CO2;
					if (v[j].CO2 < minim)
						minim = v[j].CO2;
					break;
				case 3:
					if (v[j].zgomot > max)
						max = v[j].zgomot;
					if (v[j].zgomot < minim)
						minim = v[j].zgomot;
					break;
				case 4:
					if (v[j].pres > max)
						max = v[j].pres;
					if (v[j].pres < minim)
						minim = v[j].pres;
					break;
				}
			}
		}
		fprintf(f, "Minim: %.2f\n", minim);
		fprintf(f, "Maxim: %.2f\n", max);
		fprintf(f, "Diferenta: %.2f\n", max - minim);
		scortotal += Decizie(f, max, minim, max - minim, i);
	}
	fprintf(f, "\n========================\n");
	fprintf(f, "CONCLUZIE FINALA STUP\n");
	fprintf(f, "========================\n");
	float medie = scortotal / 5.0;
	if (medie >= 2.5)
		fprintf(f, "Calificativ: EXCELENT\n");
	else if (medie >= 2.0)
		fprintf(f, "Calificativ: BUN\n");
	else if (medie >= 1.5)
		fprintf(f, "Calificativ: ACCEPTABIL\n");
	else
		fprintf(f, "Calificativ: CRITIC\n");
	fclose(f);
}

int Decizie(FILE *f, float max, float minim, float diferenta, int indice) {

	int scor = 0;

	switch (indice) {
	case 0:
		fprintf(f, "Analiza: ");

		if (max <= 36.5 && minim >= 33.5) {
			fprintf(f, "Temperatura este stabila.\n");
			scor = 3;
		} else if (minim < 32) {
			fprintf(f, "Temperatura prea mica.\n");
			scor = 1;
		} else if (max > 38) {
			fprintf(f, "Temperatura prea mare.\n");
			scor = 0;
		} else {
			fprintf(f, "Variatii moderate de temperatura.\n");
			scor = 1;
		}
		break;
	case 1:
		fprintf(f, "Analiza: ");

		if (max <= 65 && minim >= 45) {
			fprintf(f, "Umiditate normala.\n");
			scor = 3;
		} else if (max > 75) {
			fprintf(f, "Umiditate prea ridicata.\n");
			scor = 0;
		} else {
			fprintf(f, "Umiditate usor instabila.\n");
			scor = 2;
		}
		break;
	case 2:
		fprintf(f, "Analiza: ");

		if (max < 1000) {
			fprintf(f, "Nivel CO2 normal.\n");
			scor = 3;
		} else if (max < 2000 && minim > 1000) {
			fprintf(f, "Ventilatie moderata.\n");
			scor = 2;
		} else {
			fprintf(f, "Ventilatie slaba.\n");
			scor = 0;
		}
		break;
	case 3:
		fprintf(f, "Analiza: ");
		if (diferenta < 10) {
			fprintf(f, "Activitate stabila.\n");
			scor = 3;
		} else if (diferenta < 25) {
			fprintf(f, "Activitate crescuta.\n");
			scor = 2;
		} else {
			fprintf(f, "Agitatie puternica in stup.\n");
			scor = 0;
		}
		break;
	case 4:
		fprintf(f, "Analiza: ");
		if (diferenta < 3) {
			fprintf(f, "Presiune stabila.\n");
			scor = 2;
		} else {
			fprintf(f, "Variatii atmosferice semnificative.\n");
			scor = 1;
		}
		break;
	}
	return scor;
}

void statisticistup(struct stup v[], int capacitate, char s[]) {
	int i, nr = 0;
	float sumtemp = 0, sumhum = 0, sumco2 = 0, sumpres = 0, sumzgomot = 0;
	float maxtemp = -99999, mintemp = 99999;
	float maxhum = -99999, minhum = 99999;
	float maxco2 = -99999, minco2 = 99999;
	float maxpres = -99999, minpres = 99999;
	float maxzgomot = -99999, minzgomot = 99999;

	for (i = 0; i < capacitate; i++) {
		if (strcmp(v[i].idstup, s) == 0) {
			nr++;
			sumtemp += v[i].temp;
			sumhum += v[i].hum;
			sumco2 += v[i].CO2;
			sumpres += v[i].pres;
			sumzgomot += v[i].zgomot;
			if (v[i].temp > maxtemp)
				maxtemp = v[i].temp;
			if (v[i].temp < mintemp)
				mintemp = v[i].temp;
			if (v[i].hum > maxhum)
				maxhum = v[i].hum;
			if (v[i].hum < minhum)
				minhum = v[i].hum;
			if (v[i].CO2 > maxco2)
				maxco2 = v[i].CO2;
			if (v[i].CO2 < minco2)
				minco2 = v[i].CO2;
			if (v[i].pres > maxpres)
				maxpres = v[i].pres;
			if (v[i].pres < minpres)
				minpres = v[i].pres;
			if (v[i].zgomot > maxzgomot)
				maxzgomot = v[i].zgomot;
			if (v[i].zgomot < minzgomot)
				minzgomot = v[i].zgomot;
		}
	}

	if (nr == 0) {
		printf("Nu exista date pentru stupul: %s\n", s);
		return;
	}

	printf("\nSTATISTICI STUP: %s (%d citiri, interval de citire o ora)\n", s, nr);
	printf("Temperatura : \nmedie=%.2f C \nmin=%.2f C \nmax=%.2f C\n",sumtemp / nr, mintemp, maxtemp);
	printf("Umiditate : \nmedie=%.2f %% \nmin=%.2f %% \nmax=%.2f %%\n",sumhum / nr, minhum, maxhum);
	printf("CO2 : \nmedie=%.2f ppm \nmin=%.2f ppm \nmax=%.2f ppm\n",sumco2 / nr, minco2, maxco2);
	printf("Presiune : \nmedie=%.2f hPa \nmin=%.2f hPa \nmax=%.2f hPa \n",sumpres / nr, minpres, maxpres);
	printf("Zgomot : \nmedie=%.2f dB \nmin=%.2f dB \nmax=%.2f dB\n",sumzgomot / nr, minzgomot, maxzgomot);
	fflush(stdout);
}

void afisarealerte(struct stup v[], int n, char s[]) {
	int nralerte = 0;

	printf("============================================\n");
	printf("         ALERTE SI AVERTIZARI - %s\n", s);
	printf("============================================\n\n");

	for (int i = 0; i < n; i++) {

		if (strcmp(v[i].idstup, s) == 0) {

			/*
			 * Temperatura
			 */
			if (v[i].temp < 30.0) {
				printf("[CRITIC] %s %s - Temp foarte mica: %.2fC\n",
						v[i].idstup, v[i].dataora, v[i].temp);
				nralerte++;
			}

			if (v[i].temp >= 30.0 && v[i].temp < 34.0) {
				printf("[ATENTIE] %s %s - Temp scazuta: %.2fC\n", v[i].idstup,
						v[i].dataora, v[i].temp);
				nralerte++;
			}

			if (v[i].temp > 36.0 && v[i].temp <= 38.0) {
				printf("[ATENTIE] %s %s - Temp ridicata: %.2fC\n", v[i].idstup,
						v[i].dataora, v[i].temp);
				nralerte++;
			}

			if (v[i].temp > 38.0) {
				printf("[CRITIC] %s %s - Temp critica: %.2fC\n", v[i].idstup,
						v[i].dataora, v[i].temp);
				nralerte++;
			}

			/*
			 * Umiditate
			 */
			if (v[i].hum < 40.0) {
				printf("[CRITIC] %s %s - Umiditate mica: %.2f%%\n", v[i].idstup,
						v[i].dataora, v[i].hum);
				nralerte++;
			}

			if (v[i].hum > 75.0 && v[i].hum <= 85.0) {
				printf("[ATENTIE] %s %s - Umiditate mare: %.2f%%\n",
						v[i].idstup, v[i].dataora, v[i].hum);
				nralerte++;
			}

			if (v[i].hum > 85.0) {
				printf("[CRITIC] %s %s - Umiditate critica: %.2f%%\n",
						v[i].idstup, v[i].dataora, v[i].hum);
				nralerte++;
			}

			/*
			 * Presiune
			 */
			if (v[i].pres < 1000.0) {
				printf("[CRITIC] %s %s - Presiune mica: %.2f hPa\n",
						v[i].idstup, v[i].dataora, v[i].pres);
				nralerte++;
			}

			if (v[i].pres >= 1000.0 && v[i].pres < 1005.0) {
				printf("[ATENTIE] %s %s - Presiune scazuta: %.2f hPa\n",
						v[i].idstup, v[i].dataora, v[i].pres);
				nralerte++;
			}

			/*
			 * CO2
			 */
			if (v[i].CO2 > 5000.0) {
				printf("[CRITIC] %s %s - CO2 extrem: %.2f ppm\n", v[i].idstup,
						v[i].dataora, v[i].CO2);
				nralerte++;
			}

			if (v[i].CO2 > 3000.0 && v[i].CO2 <= 5000.0) {
				printf("[ATENTIE] %s %s - CO2 ridicat: %.2f ppm\n", v[i].idstup,
						v[i].dataora, v[i].CO2);
				nralerte++;
			}

			/*
			 * Zgomot
			 */
			if (v[i].zgomot > 80.0) {
				printf("[CRITIC] %s %s - Zgomot mare: %.2f dB\n", v[i].idstup,
						v[i].dataora, v[i].zgomot);
				nralerte++;
			}

			if (v[i].zgomot > 60.0 && v[i].zgomot <= 80.0) {
				printf("[ATENTIE] %s %s - Zgomot ridicat: %.2f dB\n",
						v[i].idstup, v[i].dataora, v[i].zgomot);
				nralerte++;
			}
		}
	}

	printf("--------------------------------------------\n");
	if (nralerte == 0) {
		printf("Nicio alerta pentru %s\n", s);
	} else {
		printf("Total alerte: %d\n", nralerte);
	}
	printf("--------------------------------------------\n");
}

/*
 * Sortare
 */

void sortare(struct stup v[], char s[], int n) {
	int i, j, k = 0, optiuni;
	struct stup copie[n];
	struct stup aux;
	for (i = 0; i < n; i++) {
		if (strcmp(v[i].idstup, s) == 0) {
			copie[k] = v[i];
			k++;
		}
	}

	printf("Sorteaza dupa:\n");
	printf("1 - Temperatura\n");
	printf("2 - Umiditate\n");
	printf("3 - CO2\n");
	printf("4 - Presiunea\n");
	printf("5 - Zgomot\n");
	fflush(stdout);
	printf("\n1 - Revenire: ");
	fflush(stdout);
	while (scanf("%d", &optiuni) != 1) {
		printf("Introdu doar cifre!\n1 - Revenire: ");
		fflush(stdout);
		while (getchar() != '\n');
	}
	for (i = 0; i < k - 1; i++) {
		for (j = 0; j < k - i - 1; j++) {
			int schimb = 0;
			switch (optiuni) {
			case 1:
				if (copie[j].temp < copie[j + 1].temp)
					schimb = 1;
				break;
			case 2:
				if (copie[j].hum < copie[j + 1].hum)
					schimb = 1;
				break;
			case 3:
				if (copie[j].CO2 < copie[j + 1].CO2)
					schimb = 1;
				break;
			case 4:
				if (copie[j].pres < copie[j + 1].pres)
					schimb = 1;
				break;
			case 5:
				if (copie[j].zgomot < copie[j + 1].zgomot)
					schimb = 1;
				break;
			}
			if (schimb) {
				aux = copie[j];
				copie[j] = copie[j + 1];
				copie[j + 1] = aux;
			}
		}
	}
	Resetare();
	switch (optiuni) {
	case 1:
		printf("\nSortare dupa Temperatura:\n");
		for (i = 0; i < k; i++) {
			printf("%s %.2f\n", copie[i].dataora, copie[i].temp);
		}
		break;
	case 2:
		printf("\nSortare dupa Umiditate:\n");
		for (i = 0; i < k; i++) {
			printf("%s %.2f\n", copie[i].dataora, copie[i].hum);
		}
		break;
	case 3:
		printf("\nSortare dupa CO2:\n");
		for (i = 0; i < k; i++) {
			printf("%s %.2f\n", copie[i].dataora, copie[i].CO2);
		}
		break;
	case 4:
		printf("\nSortare dupa Presiune:\n");
		for (i = 0; i < k; i++) {
			printf("%s %.2f\n", copie[i].dataora, copie[i].pres);
		}
		break;
	case 5:
		printf("\nSortare dupa Zgomot:\n");
		for (i = 0; i < k; i++) {
			printf("%s %.2f\n", copie[i].dataora, copie[i].zgomot);
		}
		break;
	default:
		printf("Optiune invalida!");
	}

	fflush(stdout);
}

