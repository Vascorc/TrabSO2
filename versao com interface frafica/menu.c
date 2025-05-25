// === menu.c ===
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> 

#define PIPE1 "pipe_menu_jogadores"
#define PIPE2 "pipe_jogadores_menu"

int main() {
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    int vitoriasJ1 = 0, vitoriasJ2 = 0;
    char buffer;

    int pipe_vitorias = open(PIPE2, O_RDONLY | O_NONBLOCK);
    int dummy_write = open(PIPE2, O_WRONLY | O_NONBLOCK);
    if (pipe_vitorias < 0 || dummy_write < 0) {
        perror("Erro ao abrir pipe de vitórias");
        exit(1);
    }

    while (1) {
        printf("\n=== MENU DO JOGO ===\n");
        printf("Vitórias - Jogador 1: %d | Jogador 2: %d\n", vitoriasJ1, vitoriasJ2);

        printf("1. Jogador 1\n2. Jogador 2\nOpção: ");
        int escolha;
        scanf("%d", &escolha);

        if (escolha == 1) {
            if (fork() == 0) {
                execlp("xterm", "xterm", "-e", "./jogador1", NULL);
                perror("Erro jogador1");
                exit(1);
            }
            sleep(1); // garante que jogador1 abriu antes de escrever no PIPE1

            int fd1w = open(PIPE1, O_WRONLY | O_NONBLOCK);
            if (fd1w >= 0) {
                write(fd1w, "1", 1);
                close(fd1w);
            }
        } else if (escolha == 2) {
            if (fork() == 0) {
                execlp("xterm", "xterm", "-e", "./jogador2", NULL);
                perror("Erro jogador2");
                exit(1);
            }
        } else {
            printf("Opção inválida\n");
        }

        if (read(pipe_vitorias, &buffer, 1) > 0) {
            if (buffer == '1') vitoriasJ1++;
            else if (buffer == '2') vitoriasJ2++;
        }
    }

    close(pipe_vitorias);
    close(dummy_write);
    return 0;
}
