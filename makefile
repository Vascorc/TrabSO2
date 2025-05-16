# Definições de variáveis
CC = gcc
CFLAGS = -Wall -g
OBJ = mainJogador1.o mainJogador2.o iniciarTabuleiro.o funcoesAjuda.o
EXE_JOGADOR1 = jogador1
EXE_JOGADOR2 = jogador2

# Definir os caminhos para os pipes
PIPE1 = pipe1to2
PIPE2 = pipe2to1

# Alvo principal (executáveis)
all: $(EXE_JOGADOR1) $(EXE_JOGADOR2) $(PIPE1) $(PIPE2)

# Compilar o Jogador 1
$(EXE_JOGADOR1): mainJogador1.o iniciarTabuleiro.o funcoesAjuda.o
	$(CC) $(CFLAGS) -o $(EXE_JOGADOR1) mainJogador1.o iniciarTabuleiro.o funcoesAjuda.o

# Compilar o Jogador 2
$(EXE_JOGADOR2): mainJogador2.o iniciarTabuleiro.o funcoesAjuda.o
	$(CC) $(CFLAGS) -o $(EXE_JOGADOR2) mainJogador2.o iniciarTabuleiro.o funcoesAjuda.o

# Compilar os arquivos .o
mainJogador1.o: mainJogador1.c iniciarTabuleiro.h funcoesAjuda.h
	$(CC) $(CFLAGS) -c mainJogador1.c

mainJogador2.o: mainJogador2.c iniciarTabuleiro.h funcoesAjuda.h
	$(CC) $(CFLAGS) -c mainJogador2.c

iniciarTabuleiro.o: iniciarTabuleiro.c iniciarTabuleiro.h
	$(CC) $(CFLAGS) -c iniciarTabuleiro.c

funcoesAjuda.o: funcoesAjuda.c funcoesAjuda.h
	$(CC) $(CFLAGS) -c funcoesAjuda.c

# Criar os pipes automaticamente
$(PIPE1) $(PIPE2):
	mkfifo $(PIPE1)
	mkfifo $(PIPE2)

# Limpeza dos arquivos gerados
clean:
	rm -f *.o $(EXE_JOGADOR1) $(EXE_JOGADOR2) $(PIPE1) $(PIPE2)
