#ifndef LOGICASTRUCTURADATAH
#define LOGICASTRUCTURADATAH

struct stup {
    char idstup[20];
    float temp,hum,CO2,pres,zgomot;
    int varsta;
    char dataora[20];
};


int citiredate(struct stup **v);
void afisaredate(struct stup v[],int n);
void afisaredateIDSTUP(struct stup v[], int n, char s[]);
int IDStup(char z[][20], struct stup v[], int n);

#endif
