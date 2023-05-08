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
    paraula_t par[MAX_PARAULES];    // Les paraules
    int n_par;  // Nombre de paraules
    int n_encerts;    // Nombre de paraules encertades
} sopa_t;

/* Aquesta funcio genera la sopa de lletres, a partir del fitxer i altres parametres */
/* que ja decidireu. En aquest cas només l'emplena amb una SOPA d'EXEMPLE, es a dir */
/* que haureu de fer la vostra pròpia. */
void genera_sopa(sopa_t *s)
{

    int midaSopa;
    bool midaCorrecta;

    while (!midaCorrecta)
    {
        printf("Introdueix la mida de la sopa de lletres:");
        scanf("%d",&midaSopa);

        if (midaSopa > 0 && midaSopa <= 40)
        {
            midaCorrecta = true;
        }
        else
        {
            printf("Aquesta mida no es valida. Torna a probar. (1 - 40)\n");
        }
    }

    s->dim = midaSopa;    // Mida màxima: 40 x 40
    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert

    for (int i = 0; i < s->dim * s->dim; i++)
    {
        // Generem una lletra aleatoriament
        s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
    }

    prepararSopaLletres(s);

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
        printf("\n");
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