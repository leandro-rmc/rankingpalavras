FROM gcc
WORKDIR /RankingPalavras
COPY src/* .
RUN gcc *.c -o rankingPalavras
CMD ./rankingPalavras