#include "Mapa.h"
#include <stdlib.h>
#include <string.h>

static void reorganiza_item_diretamente (Mapa *mp, int indice){

    //Esse algoritmo coloca um item do Mapa em seu devido lugar (decrescente).
    //Exemplo A: 4, 3, 3, 2, 5, 1. O �ndice do n�mero na ordem incorreta � passado como argumento, que nesse caso � o 5.
    //O algoritmo mover� o 5 at� o seu devido lugar, para a esquerda.
    //(4, 3, 3, 2, 5, 1) => (4, 3, 3, 5, 2, 1) => (4, 3, 5, 3, 2, 1) => (4, 5, 3, 3, 2, 1) => (5, 4, 3, 3, 2, 1)
    int indiceVariavel = indice;
    while (indiceVariavel >= 1){
        if (mp->lista[indiceVariavel]->conta  > mp->lista[indiceVariavel - 1]->conta){
            Item *temp = mp->lista[indiceVariavel - 1];
            mp->lista[indiceVariavel - 1] = mp->lista[indiceVariavel];
            mp->lista[indiceVariavel] = temp;
        }
        else
            break;
        indiceVariavel--;
    }

    //Esse algoritmo coloca um item do Mapa em seu devido lugar (decrescente).
    //Exemplo B: 4, 3, 3, 2, 5, 1. O �ndice do n�mero na ordem incorreta � passado como argumento, que nesse caso � o 2.
    //O algoritmo mover� o 5 at� o seu devido lugar, para a direita.
    //(4, 2, 3, 3, 3, 1) => (4, 3, 2, 3, 3, 1) => (4, 3, 3, 2, 3, 1) => (4, 3, 3, 3, 2, 1)
    indiceVariavel = indice;
    int penultimo_item = mp->total - 2;
    while (indiceVariavel <= penultimo_item){
        if (mp->lista[indiceVariavel]->conta  < mp->lista[indiceVariavel + 1]->conta){
            Item *temp = mp->lista[indiceVariavel + 1];
            mp->lista[indiceVariavel + 1] = mp->lista[indiceVariavel];
            mp->lista[indiceVariavel] = temp;
        }
        else
            break;
        indiceVariavel++;
    }

}
static void expande_mapa_diretamente (Mapa *mp, int tamanho_grupo_itens){
    mp->blocos++;
    mp->lista = realloc (mp->lista, tamanho_grupo_itens * sizeof(Item*) * mp->blocos);
}
static void reduz_mapa_diretamente (Mapa *mp, int tamanho_grupo_itens){
    mp->blocos--;
    mp->lista = realloc (mp->lista, tamanho_grupo_itens * sizeof(Item*) * mp->blocos);
}
static void desfragmenta_mapa (Mapa *mp, int indiceNulo){
    for (int i = indiceNulo; i <= mp->total - 2; i++)
        mp->lista[i] = mp->lista[i + 1];
}
static void adiciona_item_diretamente (Mapa *mp, int indice, char *s){
    //Adiciona um item em um dado �ndice, sem qualquer tipo de verifica��o.
    mp->lista[indice] = malloc(sizeof(Item));
    mp->lista[indice]->termo = malloc(strlen(s) + 1);
    strcpy(mp->lista[indice]->termo, s);
    mp->lista[indice]->conta = 1;
    mp->total++;
}

void inicia_mapa (Mapa *mp){
    mp->blocos = 0;
    mp->lista = 0;
    mp->total = 0;
}
void insere_termo (Mapa *mp, char *s){

    //O mapa est� vazio?
    if (mp->blocos == 0){
        //Define um tamanho para o mapa e, em seguida, adiciona o primeiro item no primeiro espa�o dispon�vel (0)
        expande_mapa_diretamente(mp, TAMANHO_GRUPO_ITENS);
        adiciona_item_diretamente(mp,0,s);
        return;
    }

    //A palavra do item atual � igual a palavra que est� tentando inserir?
    //Se sim, apenas aumenta sua quantidade e reorganiza sua posi��o.
    int termo_encontrado = encontra_termo (mp, s);
    if (termo_encontrado != -1){
        mp->lista[termo_encontrado]->conta++;
        reorganiza_item_diretamente(mp,termo_encontrado);
        return;
    }

    //A partir daqui, ser� adicionado um item novo em um mapa que n�o est� vazio
    //O mapa est� completamente cheio?
    if (mp->blocos * TAMANHO_GRUPO_ITENS == mp->total)
        //Expande o tamanho do mapa para ser poss�vel adicionar mais um item
        expande_mapa_diretamente(mp, TAMANHO_GRUPO_ITENS);
    //Adiciona um item no pr�ximo espa�o vago
    adiciona_item_diretamente(mp,mp->total,s);
}

int incrementa (Mapa *mp, char *s){
    int termo_encontrado = encontra_termo(mp,s);
    if (termo_encontrado == -1) return -1;

    mp->lista[termo_encontrado]->conta++;
    reorganiza_item_diretamente(mp, termo_encontrado);
    return 1;
}
int escreve_cont (Mapa *mp, char *s, int c){
    int termo_encontrado = encontra_termo(mp,s);
    if (termo_encontrado == -1) return -1;

    mp->lista[termo_encontrado]->conta = c;
    reorganiza_item_diretamente(mp, termo_encontrado);
    return 1;
}
int le_contador (Mapa *mp, char *s){
    int termo_encontrado = encontra_termo(mp,s);
    if (termo_encontrado == -1) return -1;

    return mp->lista[termo_encontrado]->conta;
}
int remove_termo (Mapa *mp, char *s){
    int termo_encontrado = encontra_termo(mp,s);
    if (termo_encontrado == -1) return -1;

    free(mp->lista[termo_encontrado]->termo);
    free(mp->lista[termo_encontrado]);

    //Item N�O � o �ltimo da lista?
    if (termo_encontrado != mp->total - 1)
        desfragmenta_mapa(mp,termo_encontrado);
    mp->total--;

    //F�rmula para saber se h� um bloco vazio
    if ((mp->blocos - 1) * TAMANHO_GRUPO_ITENS == mp->total)
        reduz_mapa_diretamente(mp,TAMANHO_GRUPO_ITENS);
    return 1;
}
void libera_mapa (Mapa * mp){
    for (int i = 0; i <= mp->total - 1; i++){
        //Libera da mem�ria a string do Item
        free(mp->lista[i]->termo);

        //Libera da mem�ria o Item
        free(mp->lista[i]);
    }
    //Libera da mem�ria a lista do Mapa
    free(mp->lista);

    //Reinicia os valores do mapa
    inicia_mapa(mp);

    //Libera da mem�ria a estrutura, caso tenha sido alocada dinamicamente
    free(mp);
}
int tamanho_mapa (Mapa * mp){
    return mp->total;
}
int encontra_termo (Mapa * mp, char *s){
    for (int i = 0; i <= mp->total - 1; i++)
        if (strcmp(mp->lista[i]->termo, s) == 0)
            return i;
    return -1;
}
int le_termo (Mapa * mp, int i, char *t, int *c){
    //Retorna -1 em casos de �ndice inv�lido
    if (i >= mp->total)
        return -1;
    if (t != NULL)
        strcpy(t,mp->lista[i]->termo);
    *c = mp->lista[i]->conta;
    return 1;
}
