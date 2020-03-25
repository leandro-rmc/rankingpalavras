# Ranking de Palavras - Estrutura de Dados I
## Trabalho proposto por Dilza Schwartzman em suas aulas

Neste período de quarentena, estou aproveitando e adiantando um dos trabalhos de Estrutura de Dados I, que encontrei no grupo. Não se sabe se esse trabalho também será passado para minha turma, pois as aulas foram interrompidas antes do trabalho ser escolhido, mas fazê-lo me proporcionará mais experiência. Possuo uma certa experiência com algorítmos, manipulação de memória, Assembly x86, entre outros. Não tenho muita experiência direta em Estrutura de Dados, mas o conteúdo é facilmente absorvido por quem já tem experiência nesses assuntos mencionados anteriormente.

No momento, apenas a primeira metade do trabalho está pronta (todas as funções do TAD Mapa), mas assim que possível vou terminar a outra parte, que é usar o TAD para criar um Ranking de Palavras. Também pretendo refatorar o TAD futuramente com o intuito de melhorar a legibilidade.

Algumas assinaturas das funções do trabalho da Dilza foram alteradas por mim, como tipos de retorno "void" sendo alterados para "int" para retornarem códigos de erro, caso a operação falhe (não encontre uma palavra, por exemplo). Uma função de verificar a existência de uma determinada palavra também foi criada.


## Detalhes do trabalho proposto
### Texto de Dilza Schwartzman*

Crie um TAD Mapa que armazenará um conjunto de palavras (strings ou cadeias de caracteres) e um contador associado a cada uma delas. Os itens do mapa deverão ser mantidos em ordem decrescente dos valores nos contadores. Abaixo são apresentadas as estruturas de dados que devem ser utilizadas e as operações que devem ser implementadas minimamente. O TAD deverá ser criado em arquivo de código separado (Mapa.c) e o arquivo de include correspondente (Mapa.h) também deverá ser disponibilizado. A alocação do vetor de ponteiros (Item** lista) deverá ser feita dinamicamente em blocos de 10 ponteiros por vez. A alocação do espaço para cada string deverá ser exatamente do seu tamanho. Faça um pequeno programa (main.c) para testar as operações implementadas.

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
//e em  'c' o seu contador```

2. Utilizando o TAD Mapa, crie um programa que exiba o ranking (contagem em ordem decrescente) das palavras de um arquivo texto especificado pelo usuário. Veja abaixo como deve ser a interface (mínima) do programa.

![Interface](https://i.imgur.com/EXxeGgB.png)