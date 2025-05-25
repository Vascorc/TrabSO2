// === jogador1.c ===
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "iniciarTabuleiro.h"
#include "funcoesAjuda.h"

int main() {
    int caminhoJ2 = open("pipe2to1", O_RDONLY);
    int caminhoJ1 = open("pipe1to2", O_WRONLY);
    int estado_fd = open("pipe_menu_jogadores", O_RDONLY | O_NONBLOCK); // desbloqueia o menu
    char dummy;
    read(estado_fd, &dummy, 1);
    close(estado_fd);

    if (caminhoJ1 < 0 || caminhoJ2 < 0) {
        perror("Erro ao abrir pipes");
        exit(1);
    }

    char Tabuleiro[linhas][colunas];
    iniciar_tabuleiro(Tabuleiro);

    int linha, coluna;
    char peca = 'X';

    while (1) {
        system("clear");
        printf("Jogo do Galo\n(Você é o X)\n");
        printJogo(Tabuleiro);

        printf("Jogador 1 (X), escolha a linha (1-3): ");
        fflush(stdout);
        scanf("%d", &linha);
        linha--;

        printf("Escolha a coluna (1-3): ");
        fflush(stdout);
        scanf("%d", &coluna);
        coluna--;

        if (!colocar_peca(Tabuleiro, linha, coluna, peca)) {
            printf("Posição já ocupada\n");
            sleep(1);
            continue;
        }

        system("clear");
        printf("Jogador 1: Jogada feita na linha %d, coluna %d\n", linha, coluna);
        printJogo(Tabuleiro);

        if (verificar_vitoria(Tabuleiro, peca)) {
            printf("Jogador 1 (X) ganhou!\n");
            char vitoria = 'V';
            write(caminhoJ1, &vitoria, 1);

            int fd = open("pipe_jogadores_menu", O_WRONLY);
            write(fd, "1", 1);
            close(fd);
            break;
        } else {
            char semVitoria = 'C';
            write(caminhoJ1, &semVitoria, 1);
        }

        write(caminhoJ1, Tabuleiro, sizeof(Tabuleiro));
        printf("Jogador 1: Esperando o Jogador 2 jogar...\n");

        char buffer;
        int bytesRead = read(caminhoJ2, &buffer, 1);
        if (bytesRead > 0 && buffer == 'V') {
            printf("Jogador 2 (O) ganhou!\n");
            break;
        }

        bytesRead = read(caminhoJ2, Tabuleiro, sizeof(Tabuleiro));
        if (bytesRead <= 0) {
            printf("Erro ou fim de jogo.\n");
            break;
        }

        printf("Jogador 1: Tabuleiro atualizado recebido do Jogador 2\n");
        sleep(1);
    }

    return 0;
}
