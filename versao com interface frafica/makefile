# Definições de variáveis
CC = gcc
CFLAGS = -Wall -g
OBJ = mainJogador1.o mainJogador2.o iniciarTabuleiro.o funcoesAjuda.o menu.o
EXE_JOGADOR1 = jogador1
EXE_JOGADOR2 = jogador2
EXE_MENU = menu

# Definir os caminhos para os pipes
PIPE1 = pipe1to2
PIPE2 = pipe2to1
PIPE_MENU1 = pipe_menu_jogadores
PIPE_MENU2 = pipe_jogadores_menu


# Alvo principal (executáveis)
all: $(EXE_JOGADOR1) $(EXE_JOGADOR2) $(EXE_MENU) pipes

# Compilar o Jogador 1
$(EXE_JOGADOR1): mainJogador1.o iniciarTabuleiro.o funcoesAjuda.o
	$(CC) $(CFLAGS) -o $(EXE_JOGADOR1) mainJogador1.o iniciarTabuleiro.o funcoesAjuda.o

# Compilar o Jogador 2
$(EXE_JOGADOR2): mainJogador2.o iniciarTabuleiro.o funcoesAjuda.o
	$(CC) $(CFLAGS) -o $(EXE_JOGADOR2) mainJogador2.o iniciarTabuleiro.o funcoesAjuda.o

# Compilar o Menu
$(EXE_MENU): menu.o
	$(CC) $(CFLAGS) -o $(EXE_MENU) menu.o

# Compilar os arquivos .o
mainJogador1.o: mainJogador1.c iniciarTabuleiro.h funcoesAjuda.h
	$(CC) $(CFLAGS) -c mainJogador1.c

mainJogador2.o: mainJogador2.c iniciarTabuleiro.h funcoesAjuda.h
	$(CC) $(CFLAGS) -c mainJogador2.c

iniciarTabuleiro.o: iniciarTabuleiro.c iniciarTabuleiro.h
	$(CC) $(CFLAGS) -c iniciarTabuleiro.c

funcoesAjuda.o: funcoesAjuda.c funcoesAjuda.h
	$(CC) $(CFLAGS) -c funcoesAjuda.c

menu.o: menu.c
	$(CC) $(CFLAGS) -c menu.c


pipes:
	@if [ ! -p $(PIPE1) ]; then mkfifo $(PIPE1); fi
	@if [ ! -p $(PIPE2) ]; then mkfifo $(PIPE2); fi
	@if [ ! -p $(PIPE_MENU1) ]; then mkfifo $(PIPE_MENU1); fi
	@if [ ! -p $(PIPE_MENU2) ]; then mkfifo $(PIPE_MENU2); fi

# Limpeza dos arquivos gerados
clean:
	rm -f *.o $(EXE_JOGADOR1) $(EXE_JOGADOR2) $(EXE_MENU) $(PIPE1) $(PIPE2) $(PIPE_MENU1) $(PIPE_MENU2)
