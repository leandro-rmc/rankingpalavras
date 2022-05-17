#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED
#define TAMANHO_GRUPO_ITENS 10

typedef struct _item
{
    int conta;
    char *termo;
} Item;

typedef struct _mapa
{
    int total;
    int blocos;
    Item **lista;
} Mapa;

void inicia_mapa(Mapa *mp);
void insere_termo (Mapa *mp, char *s);
int incrementa (Mapa *mp, char *s);
int escreve_cont (Mapa *mp, char *s, int c);
int le_contador (Mapa *mp, char *s);
int remove_termo (Mapa *mp, char *s);
void libera_mapa (Mapa * mp);
int tamanho_mapa (Mapa * mp);
int encontra_termo(Mapa * mp, char *s);
int le_termo (Mapa * mp, int i, char *t, int *c);

#endif
