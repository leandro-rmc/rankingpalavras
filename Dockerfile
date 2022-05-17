FROM gcc
WORKDIR /RankingPalavras

COPY src/Implementacoes ./Implementacoes
COPY src/Interfaces ./Interfaces
COPY src/main.c src/bdteste.txt .

RUN gcc *.c Implementacoes/*.c Interfaces/*.h -o rankingPalavras

CMD ./rankingPalavras