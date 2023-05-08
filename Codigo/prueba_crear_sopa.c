#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PARAULES 10
#define MAX_LLETRES 8

typedef struct
{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   //Les lletres son d'una paraula que s'ha encertat
    //paraula_t par[MAX_PARAULES];    // Les paraules
    int n_par;  // Nombre de paraules
    char p[MAX_PARAULES][MAX_LLETRES];
    int n_encerts;    // Nombre de paraules encertades
} sopa_t;


int main() {

    sopa_t s;
    bool dim_correcte;


     printf("Introdueix les dimensions de la sopa de lletres\n");

     scanf("%d", &s.dim);

     dim_correcte = false;

     while (!dim_correcte) {
     if ((s.dim <= 40)&&(s.dim >= 10)) {
        dim_correcte = true;
     }

     else {
        printf("Introdueix les dimensions de la sopa de lletres\n");
        scanf("%d", &s.dim);
     }

     }

     if ((s.dim >= 10)&&(s.dim <= 15)) {
        s.n_par = 5;
     }

     else if ((s.dim > 15)&&(s.dim <= 20)) {
          s.n_par = 6;
     }

     else if ((s.dim > 20)&&(s.dim <= 25)) {
          s.n_par = 7;
     }

     else if ((s.dim > 25)&&(s.dim <= 30)) {
          s.n_par = 8;
     }

     else if ((s.dim > 30)&&(s.dim <= 35)) {
          s.n_par = 9;
     }

     else if ((s.dim > 35)&&(s.dim <= 40)) {
          s.n_par = 10;
     }


    char paraula[8];
    int i;
    int j;
    int ll;
    FILE *fit;
    fit = fopen ("palabras.txt", "r");

    if (fit == NULL)
     {
     printf("Error en obrir el fitxer\n");
     }
     else
     {
        fgets(paraula, 80, fit);

        i = 0;
        while (i < s.n_par) {

          j = 0;
          while (paraula[j] != '\0') {

               s.p[i][j] = paraula[j];

               j++;
          }

           s.p[i][j] = '\0';

          fgets(paraula, 80, fit);
          i++;

        }

       fclose(fit);

     }

    s.lletres = malloc(s.dim * s.dim * sizeof(char));   // Espai per a les lletres

    srand(time(NULL));

    int i2, j2;
    int dir;
    bool dir_correcte, dir_dreta, dir_avall, dir_esq, dir_amunt;

    for (i = 0; i < s.n_par; i++) {

    dir_correcte = false;
    while (!dir_correcte) {

    j = 0;
    i2 = rand() % s.dim;
    j2 = rand() % s.dim;
    while ((s.lletres[(i2*s.dim)+j2] != '\0')&&(s.lletres[(i2*s.dim)+j2] != s.p[i][j])) {
       i2 = rand() % s.dim;
       j2 = rand() % s.dim;
    }

    dir_dreta = true;

    j = 1;
    dir = 1;
    while ((dir_dreta)&&(s.p[i][j] != '\0')) {                 // Comprovem per la direcci� dreta

    if ((s.lletres[(i2*s.dim)+j2+dir] != '\0')&&(s.lletres[(i2*s.dim)+j2+dir] != s.p[i][j])) {
         dir_dreta = false;
    }
    j++;
    dir++;
    }

    if (dir_dreta) {

     j = 0;
     s.lletres[(i2*s.dim)+j2] = s.p[i][j];

     j = 1;
     dir = 1;
     while (s.p[i][j] != '\0') {

          if (s.lletres[(i2*s.dim)+j2+dir] == '\0') {

               s.lletres[(i2*s.dim)+j2+dir] = s.p[i][j];

          }
          j++;
          dir++;
     }

     dir_correcte = true;

    }

    else {

    dir_avall = true;

    j = 1;
    dir = 1;
    while ((dir_avall)&&(s.p[i][j] != '\0')) {                 // Comprovem per la direcci� avall

    if ((s.lletres[((i2+dir)*s.dim)+j2] != '\0')&&(s.lletres[((i2+dir)*s.dim)+j2] != s.p[i][j])) {
         dir_avall = false;
    }
    j++;
    dir++;
    }

    if (dir_avall) {

     j = 0;
     s.lletres[(i2*s.dim)+j2] = s.p[i][j];

     j = 1;
     dir = 1;
     while (s.p[i][j] != '\0') {

          if (s.lletres[((i2+dir)*s.dim)+j2] == '\0') {

               s.lletres[((i2+dir)*s.dim)+j2] = s.p[i][j];
          }
          j++;
          dir++;
     }

     dir_correcte = true;
    }

    else {

    dir_esq = true;

    j = 1;
    dir = 1;
    while ((dir_esq)&&(s.p[i][j] != '\0')) {                 // Comprovem per la direcci� esq

    if ((s.lletres[((i2)*s.dim)+j2-dir] != '\0')&&(s.lletres[(i2*s.dim)+j2-dir] != s.p[i][j])) {
         dir_esq = false;
    }
    j++;
    dir++;
    }

    if (dir_esq) {

         j = 0;
     s.lletres[(i2*s.dim)+j2] = s.p[i][j];

     j = 1;
     dir = 1;
     while (s.p[i][j] != '\0') {

          if (s.lletres[((i2)*s.dim)+j2-dir] == '\0') {

               s.lletres[((i2)*s.dim)+j2-dir] = s.p[i][j];
          }
          j++;
          dir++;
     }

     dir_correcte = true;

    }

    else {

        dir_amunt = true;

    j = 1;
    dir = 1;
    while ((dir_amunt)&&(s.p[i][j] != '\0')) {                 // Comprovem per la direcci� avall

    if ((s.lletres[((i2-dir)*s.dim)+j2] != '\0')&&(s.lletres[((i2-dir)*s.dim)+j2] != s.p[i][j])) {
         dir_amunt = false;
    }
    j++;
    dir++;
    }

    }

    }


    }


     }

    }


    for (i=0; i<s.dim; i++) {
        for (j=0; i<s.dim; j++) {
            printf("%c", s.lletres[(i*s.dim)+j]);

        }
         printf("\n");
    }



return 0;

    }





