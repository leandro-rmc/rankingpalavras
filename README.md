# Ranking de Palavras - Estrutura de Dados I - Trabalho proposto por Dilza Schwartzman em suas aulas

Neste período de quarentena estou aproveitando para estudar e aproveitei para adiantar um dos trabalhos de Estrutura de Dados I, que encontrei no grupo. Não se sabe se esse trabalho também será passado para minha turma, pois as aulas foram interrompidas antes do trabalho ser escolhido, mas fazê-lo me proporcionará mais experiência. Possuo uma certa experiência com algoritmos, manipulação de memória, Assembly x86, entre outros. Não tenho muita experiência direta anterior em Estrutura de Dados, mas o conteúdo é facilmente absorvido por quem já tem experiência nesses assuntos mencionados anteriormente.

O trabalho foi feito do zero, sem auxílio. Não está perfeito, mas não tenho prática de "espiar" o código de outras pessoas se não for para estudá-los. O objetivo do trabalho é demonstrar o atual nível de conhecimento de quem o faz.

O funcionamento é simples: o executável deve estar no mesmo diretório do arquivo de texto. O programa "absorverá" as palavras encontradas no arquivo (separadas por espaço ou por quebra de linha) cujo nome é passado pelo usuário, e as jogará na estrutura Mapa, onde ficarão até que o usuário decida atualizar ou absorver palavras de outro arquivo. Toda manipulação é feita em cima do conteúdo dessa estrutura; o arquivo é aberto uma única vez ou manualmente sempre que o usuário quiser.

![Interface do programa criado](https://user-images.githubusercontent.com/36391793/82128752-ccca0600-9793-11ea-8edd-5b8a5e733d35.png)


## Detalhes do trabalho proposto (Texto e imagem abaixo de Dilza Schwartzman*)

1. Crie um TAD Mapa que armazenará um conjunto de palavras (strings ou cadeias de caracteres) e um contador associado a cada uma delas. Os itens do mapa deverão ser mantidos em ordem decrescente dos valores nos contadores. Abaixo são apresentadas as estruturas de dados que devem ser utilizadas e as operações que devem ser implementadas minimamente. O TAD deverá ser criado em arquivo de código separado (Mapa.c) e o arquivo de include correspondente (Mapa.h) também deverá ser disponibilizado. A alocação do vetor de ponteiros (Item** lista) deverá ser feita dinamicamente em blocos de 10 ponteiros por vez. A alocação do espaço para cada string deverá ser exatamente do seu tamanho. Faça um pequeno programa (main.c) para testar as operações implementadas.

```c
typedef struct _mapa
{
int total; // número de itens no mapa
int blocos; // número de blocos de itens alocados
Item **lista; // vetor de ponteiros para itens
} Mapa;

typedef struct _item
{
int conta; //contador
char *termo; //palavra
} Item;

void inicia_mapa (Mapa *mp); //inicia um mapa vazio

void insere_termo (Mapa *mp, char *s); // insere um item com termo s e conta=1

int incrementa (Mapa *mp, char *s) // incrementa contador do termo s, retorna 1
// se não encontrou o termo

int escreve_cont (Mapa *mp, char *s, int c) // escreve  ́'c' no contador do termo s,
// retorna 1 se não encontrou o termo

int le_contador (Mapa *mp, char *s) // retorna contador do termo s

void remove_termo (Mapa *mp, char *s); // remove o item com termo s

void libera_mapa (Mapa * mp); // libera o espaço ocupado pelo mapa

int tamanho_mapa (Mapa * mp); // retorna número de itens no mapa

void le_termo (Mapa * mp, int i, char *t, int *c); //retorna em ‘t’ o termo no índice  'i'
//e em  'c' o seu contador
```

2. Utilizando o TAD Mapa, crie um programa que exiba o ranking (contagem em ordem decrescente) das palavras de um arquivo texto especificado pelo usuário. Veja abaixo como deve ser a interface (mínima) do programa.

![Interface](https://user-images.githubusercontent.com/36391793/77501900-18b59a00-6e38-11ea-909f-c409d902b753.png)
