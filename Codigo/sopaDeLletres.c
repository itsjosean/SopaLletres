#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LLETRES 8
#define MAX_PARAULES 10

/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */
typedef struct
{
    char ll[MAX_LLETRES + 1];   // Lletres de la paraula (comptem centinella)
    bool enc;   // La paraula s'ha encertat
} paraula_t;

typedef struct
{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    //paraula_t par[MAX_PARAULES];    // Les paraules
    int n_par;  // Nombre de paraules
    char p[14][12];
    int n_encerts;    // Nombre de paraules encertades
} sopa_t;

/* Aquesta funcio genera la sopa de lletres, a partir del fitxer i altres parametres */
/* que ja decidireu. En aquest cas només l'emplena amb una SOPA d'EXEMPLE, es a dir */
/* que haureu de fer la vostra pròpia. */
void genera_sopa(sopa_t *s)
{

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


    char paraula[20];
    int i;
    int j;
    FILE *fit;
    fit = fopen ("palabras.txt", "r");

    if (fit == NULL)
     {
     printf("Error en obrir el fitxer\n");
     }
     else
     {

        i = 0;
        while (i < s.n_par) {

          fgets(paraula, 80, fit);

          j = 0;
          while (paraula[j] != '\n') {

               s.p[i][j] = paraula[j];

               j++;

          }

           s.p[i][j] = '\n';
           s.p[i][j+1] = '\0';


          i++;

        }

       fclose(fit);

     }

     i = 0;
     while (i < s.n_par) {
        j = 0;
        while (s.p[i][j] != '\0') {
            j++;
        }
        i++;
     }

    s.lletres = malloc(s.dim * s.dim * sizeof(char));   // Espai per a les lletres


      for (i=0; i<s.dim; i++) {
        for (j=0; j<s.dim; j++) {
          s.lletres[i*s.dim+j] = '\0';
        }

    }


    srand(time(NULL));

    int i2, j2;
    int dir;
    int ll;
    bool dir_correcte, dir_dreta, dir_avall, dir_esq, dir_amunt;
    int direccio;

    for (i=0; i<s.n_par; i++) {

    dir_correcte = false;

    while(!dir_correcte) {

    ll = 0;
    j = 0;
    while (s.p[i][j] != '\n') {
        ll++;
        j++;
    }

    j = 0;
    i2 = rand() % s.dim;
    j2 = rand() % s.dim;
    while ((s.lletres[(i2*s.dim)+j2] != '\0')&&(s.lletres[(i2*s.dim)+j2] != s.p[i][j])) {
       i2 = rand() % s.dim;
       j2 = rand() % s.dim;
    }



    direccio = rand() % 4;

    if (direccio == 0) {

    dir_dreta = true;

    j = 1;
    dir = 1;
    while ((dir_dreta)&&(s.p[i][j] != '\n')) {                 // Comprovem per la direccio dreta

    if ((s.lletres[(i2*s.dim)+j2+dir] != '\0')&&(s.lletres[(i2*s.dim)+j2+dir] != s.p[i][j])||((j2+ll)>s.dim)) {
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
     while (s.p[i][j] != '\n') {

          if (s.lletres[(i2*s.dim)+j2+dir] == '\0') {

               s.lletres[(i2*s.dim)+j2+dir] = s.p[i][j];


          }
          j++;
          dir++;
     }



     dir_correcte = true;

    }

    }

    if (direccio == 1) {

    dir_avall = true;

    j = 1;
    dir = 1;
    while ((dir_avall)&&(s.p[i][j] != '\n')) {                 // Comprovem per la direccio avall

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
     while (s.p[i][j] != '\n') {

          if (s.lletres[((i2+dir)*s.dim)+j2] == '\0') {

               s.lletres[((i2+dir)*s.dim)+j2] = s.p[i][j];
          }
          j++;
          dir++;
     }

     dir_correcte = true;
    }

    }

    if (direccio == 2) {

    dir_esq = true;

    j = 1;
    dir = 1;
    while ((dir_esq)&&(s.p[i][j] != '\n')) {                 // Comprovem per la direccio esq

    if ((s.lletres[((i2)*s.dim)+j2-dir] != '\0')&&(s.lletres[(i2*s.dim)+j2-dir] != s.p[i][j])||(((i2*s.dim)+j2-dir)<(i2*s.dim))) {
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
     while (s.p[i][j] != '\n') {

          if (s.lletres[((i2)*s.dim)+j2-dir] == '\0') {

               s.lletres[((i2)*s.dim)+j2-dir] = s.p[i][j];
          }
          j++;
          dir++;
     }

     dir_correcte = true;

    }

    }

    if (direccio == 3) {

    dir_amunt = true;

    j = 1;
    dir = 1;
    while ((dir_amunt)&&(s.p[i][j] != '\n')) {                 // Comprovem per la direccio amunt

    if ((s.lletres[((i2-dir)*s.dim)+j2] != '\0')&&(s.lletres[((i2-dir)*s.dim)+j2] != s.p[i][j])||((i2-dir)<0)) {
         dir_amunt = false;
    }
    j++;
    dir++;
    }

    if (dir_amunt) {

         j = 0;
         s.lletres[(i2*s.dim)+j2] = s.p[i][j];

         j = 1;
         dir = 1;
         while (s.p[i][j] != '\n') {

           if (s.lletres[((i2-dir)*s.dim)+j2] == '\0') {

               s.lletres[((i2-dir)*s.dim)+j2] = s.p[i][j];
           }
           j++;
           dir++;
        }

     dir_correcte = true;

    }

    }



    }

    }


    for (i=0; i<s.dim; i++) {
        for (j=0; j<s.dim; j++) {
            printf("%c", s.lletres[(i*s.dim)+j]);

        }
         printf("\n");
    }



}

/* Mostra la sopa de lletres pel terminal */
/* En principi, NO HAURIEU DE MODIFICAR AQUEST CODI SI NO TOQUEU LES ESTRUCTURES DE DADES*/
void mostra_sopa (sopa_t *s)
{
    printf("\n~SOPA DE LLETRES~\n");
    for (int i = 0; i < s->dim ; i++)
    {
        for (int j = 0; j < s->dim; j++)
        {
            printf("|%c|", s->lletres[i * s->dim + j]);

        }
        //printf("\n");
    }
}

void guardarParaulesArxius (sopa_t *s, char paraules[], char nomArxiu[])
{

    FILE *arxiu;
    arxiu = fopen(nomArxiu, "r");

    char paraula[100];

    if (arxiu == NULL)
    {
        printf("Error al intentar obrir el arxiu.");
    }
    else
    {
        printf("\nLlista de paraules a trobar: \n");
        while(!feof(arxiu))
        {
            fgets(paraula, 100, arxiu);
            printf("%s", paraula);
        }
    }

    printf("\n");

    fclose(arxiu);
}

void jugarPartida (sopa_t *sopa)
{
    bool *partidaEnJoc = true;
    char eleccioJugador[10];
    int resultatRendicio, resultatEleccio, filaUsuari, columnaUsuari, direccioUsuari;

    mostra_sopa(sopa);

    while (&partidaEnJoc)
    {
        printf("\n's' has trobat una paraula  - 'RENDICIO' per veure la solucio\n");
        scanf("%s", &eleccioJugador);

        resultatEleccio = strcmp(eleccioJugador, "s");

        if (resultatEleccio == 0)
        {
            printf("PARAULA TROBADA...?");

            // DEMANAR FILA Y COLUMNA
            printf("\nIntrodueix les 'coordenades' de la paraula trobada:");

            printf("\nFila: ");
            scanf("%s", &filaUsuari);

            printf("\nColumna: ");
            scanf("%s", &columnaUsuari);

            printf("\nDireccio: ");
            scanf("%s", &direccioUsuari);

            // COMPROVAR LA PARAULA
            comprovacioParaula(&sopa, filaUsuari, columnaUsuari, direccioUsuari, &jugarPartida);

            printf("SOPA:\n");
            mostra_sopa(sopa);

        }
        else
        {
            resultatRendicio = strcmp(eleccioJugador, "RENDICIO");

            if (resultatRendicio == 0)
            {
                // MOSTRAR SOLUCIO
                printf("MOSTRAR SOLUCIO");
                partidaEnJoc = false;
            }
            else
            {
                // PARAULA INCORRECTA
                printf("Valor incorrecte. Torna a provar.");
            }
        }
    }
}

void comprovacioParaula (sopa_t *sopa, int filaUsuari, int columnaUsuari, int direccioUsuari, bool *estatPartida)
{
    printf("COMPROVANT PARAULA...");



    // *estatPartida = false;
}


void prepararSopaLletres (sopa_t *sopa)
{

    //int posicioFilaInical = rand() % sopa->dim;
    //int posicioColumnaInical = rand() % sopa->dim;

    char paraula[] = "JOSE";

    sopa->lletres[2] = 'J';



}

void missatgeBenvinguda ()
{

    printf("******************************************************\n");
    printf("Us donem la benvinguda al joc de la sopa de lletres!\n");
    printf("Autors: Pablo, Jose, Edgar\n");
    printf("******************************************************\n");
}

int main()
{
    char paraules[100];
    char nomArxiu[100];

    missatgeBenvinguda();

    sopa_t sopa;    // La sopa de lletres

    printf("Nom arxiu: ");
    scanf("%s", &nomArxiu);

    guardarParaulesArxius(&sopa, paraules, nomArxiu);

    genera_sopa(&sopa);     // La generem (exemple)

    jugarPartida(&sopa);

    return 0;
}