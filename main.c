#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Mapa.h"
#include "Ranking.h"
#include "ContainerPalavras.h"

#define NOME_PROGRAMA "Ranking de Palavras"
#define VERSAO_PROGRAMA "0.1"
#define CRIADOR_PROGRAMA "Leandro Rocha Musser Carneiro"
//Ranking de Palavras - v0.1 - By: Leandro Rocha Musser Carneiro

Ranking *ranking;
char nome_arquivo[256+1];

void enter_para_continuar(){
    printf("\n- Aperte ENTER para continuar...");
    getchar();
}

void exibir_palavras(int intervalo_minimo, int intervalo_maximo){
    ContainerPalavras *container_palavras;
    container_palavras = obter_palavras_filtradas(ranking, intervalo_minimo, intervalo_maximo);
    printf("\nTotal (includindo repetidas): %i\n",container_palavras->total_repetindo);
    printf("Total (sem repetição): %i\n",container_palavras->total_diferente);
    int i;
    printf("\n[Nome - Quantidade]\n\n");
    for (i = 1; i <= container_palavras->total_diferente; i++){
        printf("%s - ", container_palavras->listaSubContainerPalavra[i-1]->palavra);
        printf("%i\n", container_palavras->listaSubContainerPalavra[i-1]->quantidade);
    }
    liberar_conteudo_container_palavras(container_palavras);
}

void opcao_ler_arquivo(){
    printf("- Digite o nome do arquivo:");
    scanf("%256[^\n]s", nome_arquivo);
    getchar();
    if(absorver_palavras_arquivo(ranking, nome_arquivo) == -1){
        printf("\nErro ao absorver as palavras do arquivo \"%s\"! Verifique se o arquivo existe ou se está vazio.\n", nome_arquivo);
    }
    else{
        printf("\nArquivo %s absorvido com sucesso!\n", nome_arquivo);
    }
    enter_para_continuar();
}

void opcao_exibir_palavras(){
    if (obter_status_ranking(ranking) == SemArquivo) return;
    exibir_palavras(MINIMO_INTERVALO_PADRAO, MAXIMO_INTERVALO_PADRAO);
    enter_para_continuar();
}

void opcao_exibir_palavras_intervalo(){
    if (obter_status_ranking(ranking) == SemArquivo) return;
    int intervalo_minimo, intervalo_maximo;
    printf("- Intervalo mínimo: ");
    scanf("%i", &intervalo_minimo);
    printf("- Intervalo máximo: ");
    scanf("%i", &intervalo_maximo);
    getchar();
    exibir_palavras(intervalo_minimo, intervalo_maximo);
    enter_para_continuar();
}

void opcao_exibir_palavra_buscada(){
    if (obter_status_ranking(ranking) == SemArquivo) return;
    char *palavra = malloc(sizeof(char) * 256 + 1);
    printf("- Palavra a ser buscada: ");
    scanf("%256[^\n]s", palavra);
    getchar();
    SubContainerPalavra *sub_container_palavra;
    sub_container_palavra = buscar_palavra_filtrada(ranking, MINIMO_INTERVALO_PADRAO, MAXIMO_INTERVALO_PADRAO, palavra);
    free(palavra);
    if (sub_container_palavra->quantidade == 0){
        printf("\nPalavra não encontrada!\n");
        enter_para_continuar();
        return;
    }
    printf("\n[Nome - Quantidade]\n");
    printf("\n%s - ", sub_container_palavra->palavra);
    printf("%i\n", sub_container_palavra->quantidade);
    liberar_conteudo_sub_container_palavra(sub_container_palavra);
    enter_para_continuar();
}

void opcao_definir_limite_minimo_caracteres(){
    int minimo_caracteres;
    printf("- Número mínimo de caracteres a se considerar: ");
    scanf("%i", &minimo_caracteres);
    getchar();
    if (definir_limites_caractere_ranking(ranking, minimo_caracteres) == -1)
        printf("\nValor inválido! Tamanho mínimo deve ser 1.\n");
    else
        printf("\nModificado com sucesso!\n");
    enter_para_continuar();
}

int main()
{
    printf("["NOME_PROGRAMA " - v" VERSAO_PROGRAMA " - By: " CRIADOR_PROGRAMA "]\n");
    setlocale(LC_ALL,"");
    ranking = obter_ranking();
    char comando;

    do{
        if (obter_status_ranking(ranking) == SemArquivo)
            printf("Ranking vazio. Use a opção (1) para absorver palavras de um arquivo.\n\n");
        else
            printf("Manipulando palavras absorvidas de \"%s\". Para atualizar, use a opção (1) novamente.\n\n", nome_arquivo);
        printf("(1) Ler arquivo / Atualizar\n");
        if (obter_status_ranking(ranking) == ComArquivo){
            printf("(2) Exibir palavras\n");
            printf("(3) Exibir palavras entre um intervalo de repetição\n");
            printf("(4) Buscar palavra\n");
        }
        printf("(5) Definir limite mínimo de caracteres (atualmente é %i)\n", obter_minimo_caracteres_ranking(ranking));
        printf("(6) Sair\n\n");
        printf("- Digite um comando: ");

        scanf("%c",&comando);
		getchar();
        switch(comando){
            case '1':
                opcao_ler_arquivo();
                break;
            case '2':
                opcao_exibir_palavras();
                break;
            case '3':
                opcao_exibir_palavras_intervalo();
                break;
            case '4':
                opcao_exibir_palavra_buscada();
                break;
            case '5':
                opcao_definir_limite_minimo_caracteres();
                break;
            case '6':
                printf("\nObrigado por usar o programa!\n");
                enter_para_continuar();
                return 0;
        }
      printf("\n______________________________________________________________________________\n\n");
    } while(1);
    return 0;
}
