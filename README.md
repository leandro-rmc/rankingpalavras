# Ranking de Palavras - Estrutura de Dados

## O que é?

Trata-se de um trabalho de Estrutura de Dados I que foi passado para outras turmas do meu curso, feito apenas para ganhar mais experiência. O trabalho foi feito do zero e sem auxílio. Não está perfeito, mas não tenho prática de "espiar" o código de outras pessoas se não for para estudá-los. Foi dado um longo enunciado e uma série de funções que deveriam ser criadas do zero pelo aluno. A estrutura foi feita de acordo com o que foi pedido. O objetivo é buscar palavras dentro de um arquivo de texto e efetuar uma série de operações em memória.

## Funcionamento

O executável deve estar no mesmo diretório de um arquivo de texto (cujo nome será passado pelo usuário quando ele quiser, sem precisar reiniciar o programa) com palavras separadas por espaço ou por quebra de linha. O programa "absorverá" essas palavras e as jogará na estrutura Mapa, onde ficarão até que o usuário decida atualizar ou absorver palavras de outro arquivo. Toda manipulação é feita em cima do conteúdo dessa estrutura; o arquivo é aberto uma única vez ou manualmente sempre que o usuário quiser. Um arquivo de texto chamado "_teste.txt" contém palavras aleatórias para facilitar o uso inicial.

## Docker

Para facilitar o uso (e para eu ganhar mais experiência com essa ferramenta), o programa pode ser utilizado pelo Docker em containers Linux. Será utilizado o GCC para efetuar a compilação.

Dentro do diretório do projeto, use o seguinte comando para montar a imagem:

```powershell
docker build . -t leandromusser/ranking_palavras
```


Caso não queira fazer o clone do projeto, pode-se baixar a imagem pelo  [Docker Hub](https://hub.docker.com/r/leandromusser/ranking_palavras). usando o seguinte comando:
```powershell
docker pull leandromusser/ranking_palavras
```


Após ter a imagem em mãos, use o seguinte comando para instanciar o container:
```powershell
docker run --name ranking_palavras -it leandromusser/ranking_palavras
```
Caso queira rodar novamente, não esqueça de remover o container com **docker container rm ranking_palavras**, ou omita o parâmetro name e faça do seu jeito.


O diretório do programa é /RankingPalavras e o arquivo de texto deve ser enviado para lá. Para isso, eu utilizo o comando **docker cp**, que permite copiar arquivos da máquina hospedeira para dentro do container:
```powershell
docker cp teste.txt ranking_palavras:/RankingPalavras
```
Onde está **teste.txt**, substituir pelo caminho do seu arquivo de texto (nesse caso, ele está no diretório atual). O **ranking_palavras** é o nome do container, que eu defini no passo acima pelo parâmetro --name. O **/RankingPalavras** é o diretório do programa dentro do container.

## Interface
![Interface do programa criado](https://user-images.githubusercontent.com/36391793/82130501-4e289500-97a2-11ea-95f8-11d2b2cabd12.png)
