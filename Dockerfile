FROM gcc
WORKDIR /RankingPalavras
COPY ["*.c", "*.h", "*_teste.txt", "."]
RUN ["/bin/sh", "-c", "gcc *.c"]
CMD ["./a.out"]