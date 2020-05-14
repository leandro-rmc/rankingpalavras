#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Mapa.h"
#include "Ranking.h"

Ranking *ranking;
char nome_arquivo[256+1];
ContainerPalavras *container_palavras;

void enter_para_continuar(){
    printf("\n- Aperte ENTER para continuar...");
    getchar();
    fflush(stdin);
}

void opcao_ler_arquivo(){
    printf("- Digite o nome do arquivo: ");
    scanf("%256[^\n]s", nome_arquivo);
    fflush(stdin);
    if(absorver_palavras_arquivo(ranking, nome_arquivo) == -1){
        printf("\nErro ao absorver as palavras do arquivo \"%s\"! Verifique se o arquivo existe ou se está vazio.\n", nome_arquivo);
        //exit(0);
    }
    else{
        printf("\nArquivo %s absorvido com sucesso!\n", nome_arquivo);
    }
    enter_para_continuar();
}

void opcao_exibir_palavras(){
    if (ranking->status == SemArquivo) return;
    container_palavras = obter_palavras_filtradas(ranking, ranking->rankingConfig->minimo_intervalo, ranking->rankingConfig->maximo_intervalo);
    printf("\nTotal (includindo repetidas): %i\n",container_palavras->total_repetindo);
    printf("Total (sem repetição): %i\n\n",container_palavras->total_diferente);
    int i;
    //printf("[Lista de Palavras - min. caracteres: %i]\n", ranking->rankingConfig->minimo_intervalo);
    for (i = 1; i <= container_palavras->total_diferente; i++){
        printf("%s - ", container_palavras->listaSubContainerPalavra[i-1]->palavra);
        printf("%i\n", container_palavras->listaSubContainerPalavra[i-1]->quantidade);
    }
    enter_para_continuar();
}

int main()
{
    setlocale(LC_ALL,"");
    ranking = obter_ranking();
    char comando;

    do{
        if (ranking->status == SemArquivo)
            printf("Ranking vazio. Use a opção (1) para absorver palavras de um arquivo.\n\n");
        else
            printf("Lendo de \"%s\". Para atualizar, use a opção (1) novamente.\n\n", nome_arquivo);
        printf("(1) Ler arquivo / Atualizar\n");
        if (ranking->status == ComArquivo){
            printf("(2) Exibir palavras\n");
            printf("(3) Exibir palavras entre um intervalo de Ranking\n");
            printf("(4) Buscar palavra\n");
        }
        printf("(5) Definir limite mínimo de caracteres (atualmente é %i)\n", ranking->rankingConfig->minimo_intervalo);
        printf("(6) Sair\n\n");
        printf("- Digite um comando: ");

        scanf("%c",&comando);
        fflush(stdin);
        switch(comando){
            case '1':
                opcao_ler_arquivo();
                break;
            case '2':
                opcao_exibir_palavras();
                break;
            case '3':
                if (ranking->status == SemArquivo) break;
                printf("Teste\n");
                break;
            case '4':
                if (ranking->status == SemArquivo) break;
                printf("Teste\n");
                break;
            case '5':
                printf("Teste\n");
                break;
            case '6':
                printf("Obrigado por utilizar o programa!\n");
                return 0;
        }
      printf("\n==============================================================================================================\n\n");
    } while(1);

    char temp;
    printf("ENTER para finalizar...");
    scanf("%c",&temp);
    return 0;
}
