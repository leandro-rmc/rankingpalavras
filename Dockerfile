FROM gcc
WORKDIR /RankingPalavras
COPY ["*.c", "*.h", "*file.txt", "."]
RUN ["/bin/sh", "-c", "gcc *.c"]
CMD ["./a.out"]