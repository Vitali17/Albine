#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "Logica_Structura/data.h"
#include "Functi/Albine_function.h"

float temp[100];
int nr = 0;

void display() {

	int i,j;
	char text[20];
	float min = temp[0], max = temp[0], x, y;
	for (i = 1; i < nr; i++) {
		if (temp[i] < min)
			min = temp[i];
		if (temp[i] > max)
			max = temp[i];
	}

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	/*
	 * Linile de axa
	 */
	glVertex2f(-0.9f, -0.8f);
	glVertex2f(0.9f, -0.8f);
	glVertex2f(-0.9f, -0.8f);
	glVertex2f(-0.9f, 0.8f);

	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);

	/*
	 * Linile de variatie a temperaturi
	 */
	for (i = 0; i < nr; i++) {
		x = -0.8f + i * 1.6f / (nr - 1);
		y = -0.8f + ((temp[i] - min) / (max - min)) * 1.6f;
		glVertex2f(x, y);
	}

	glEnd();

	/*
	 * Adaugam scrisul
	 */
	for (i = 0; i < nr; i++) {
		x = -0.8f + i * 1.6f / (nr - 1);
		y = -0.8f + ((temp[i] - min) / (max - min)) * 1.6f;
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		sprintf(text, "%.2f", temp[i]);
		glRasterPos2f(x - 0.03f, y + 0.05f);
		for (j = 0; j < strlen(text); j++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[j]);
		}
	}
	glFlush();
}

void graficTemperatura(struct stup v[], int n, char id[]) {
	int i,optiune;
	nr = 0;
	Resetare();
	printf("1 - Temperatura\n");
	printf("2 - Umiditate\n");
	printf("Optiunea: ");
	fflush(stdout);

	while (scanf("%d", &optiune) != 1 || (optiune != 1 && optiune != 2)) {

		printf("Optiune invalida! Incearca din nou:\n");
		printf("1 - Temperatura\n");
		printf("2 - Umiditate\n");
		printf("Optiunea: ");
		fflush(stdout);
		Sleep(1);

		while (getchar() != '\n');
	}
	switch(optiune){
	case 1:
		for (i = 0; i < n; i++) {
				if (strcmp(v[i].idstup, id) == 0) {
					temp[nr] = v[i].temp;
					nr++;
				}
			}
		break;
	case 2:
		for (i = 0; i < n; i++) {
				if (strcmp(v[i].idstup, id) == 0) {
					temp[nr] = v[i].hum;
					nr++;
				}
			}
		break;
	}

	if (nr == 0) {
		printf("Nu exista date!\n");
		return;
	}

	int argc = 1;
	char *argv[] = { "App" };
	glutInit(&argc, argv);
	glutInitWindowSize(800, 400);
	switch(optiune){
	case 1:
		glutCreateWindow("Grafic temperatura");
		break;
	case 2:
		glutCreateWindow("Grafic umiditate");
		break;
	}
	glutDisplayFunc(display);
	glutMainLoop();
}
