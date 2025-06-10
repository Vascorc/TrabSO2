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

void jogar(int jogador, int *vitoriasJ1, int *vitoriasJ2);

int main() {
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    int vitoriasJ1 = 0, vitoriasJ2 = 0;
    int jogador; 

    system("clear");
    printf("\n=== MENU DO JOGO ===\n");
    printf("Que número queres ser?\n");
    printf("1. Jogador 1\n2. Jogador 2\nOpção: ");
    scanf("%d", &jogador);
    if (jogador != 1 && jogador != 2) {
        printf("Opção inválida. Por defeito começa o Jogador 1.\n");
        jogador = 1;
    }

    while (1) {
        system("clear");
        printf("=== RESULTADOS ===\n");
        printf("Jogador 1: %d | Jogador 2: %d\n", vitoriasJ1, vitoriasJ2);
        printf("==================\n");
        printf("1. Jogar\n2. Novo jogo (pontuação a zeros)\n3. Sair\nOpção: ");
        int op;
        scanf("%d", &op);

        if (op == 1) {
            jogar(jogador, &vitoriasJ1, &vitoriasJ2);
        } else if (op == 2) {
            vitoriasJ1 = 0;
            vitoriasJ2 = 0;
            printf("Pontuação reiniciada!\n");
            sleep(1);
        } else if (op == 3) {
            printf("A sair...\n");
            break;
        } else {
            printf("Opção inválida\n");
            sleep(1);
        }
    }
    return 0;
}

void jogar(int jogador, int *vitoriasJ1, int *vitoriasJ2) {
    char buffer = 0;
    pid_t pid;
    if (jogador == 1) {
        pid = fork();
        if (pid == 0) {
            execl("./jogador1", "jogador1", NULL);
            perror("Erro jogador1");
            exit(1);
        }
        sleep(1);
        int fd1w = open(PIPE1, O_WRONLY | O_NONBLOCK);
        if (fd1w >= 0) {
            write(fd1w, "1", 1);
            close(fd1w);
        }
    } else {
        pid = fork();
        if (pid == 0) {
            execl("./jogador2", "jogador2", NULL);
            perror("Erro jogador2");
            exit(1);
        }
        sleep(1);
        int fd2w = open(PIPE1, O_WRONLY | O_NONBLOCK);
        if (fd2w >= 0) {
            write(fd2w, "2", 1);
            close(fd2w);
        }
    }

    int pipe_vitorias = open(PIPE2, O_RDONLY);
    if (pipe_vitorias < 0) {
        perror("Erro ao abrir pipe de vitórias");
    } else {
        ssize_t n;
        do {
            n = read(pipe_vitorias, &buffer, 1);
        } while (n == 0);
        if (n > 0) {
            if (buffer == '1') {
                printf("\n>> Jogador 1 venceu!\n");
                (*vitoriasJ1)++;
            } else if (buffer == '2') {
                printf("\n>> Jogador 2 venceu!\n");
                (*vitoriasJ2)++;
            } else if (buffer == 'E') {
                printf("\n>> Empate!\n");
            }
        }
        close(pipe_vitorias);
    }
    waitpid(pid, NULL, 0);

    // Limpa stdin antes de pedir ENTER
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    printf("Pressione ENTER para continuar...");
    getchar();
}
