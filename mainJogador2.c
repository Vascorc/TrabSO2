#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "iniciarTabuleiro.h"
#include "funcoesAjuda.h"

int main()
{
    int caminhoJ2 = open("pipe2to1", O_WRONLY);
    int caminhoJ1 = open("pipe1to2", O_RDONLY);

    if (caminhoJ1 < 0 || caminhoJ2 < 0)
    {
        perror("Erro ao abrir pipes");
        exit(1);
    }

    char Tabuleiro[linhas][colunas];
    char peca = 'O';
    int linha, coluna;

    while (1)
    {
        char buffer;
        int bytesRead = read(caminhoJ1, &buffer, 1);
        if (bytesRead == 0)
        {
            printf("Adversário terminou o jogo.\n");
            break;
        }
        if (bytesRead > 0 && buffer == 'V')
        {
            system("clear");
            printf("Tabuleiro final:\n");
            printJogo(Tabuleiro);
            printf("Jogador 1 (X) ganhou!\n");

            // Enviar resultado ao menu
            int fd = open("pipe_jogadores_menu", O_WRONLY);
            if (fd >= 0)
            {
                write(fd, "1", 1);
                close(fd);
            }

            close(caminhoJ1);
            close(caminhoJ2);
            exit(0);
        }
        if (bytesRead > 0 && buffer == 'E')
        {
            bytesRead = read(caminhoJ1, Tabuleiro, sizeof(Tabuleiro));
            if (bytesRead > 0)
            {
                system("clear");
                printf("Tabuleiro final:\n");
                printJogo(Tabuleiro);
            }
            printf("Empate!\n");
            int fd = open("pipe_jogadores_menu", O_WRONLY);
            if (fd >= 0)
            {
                write(fd, "E", 1);
                close(fd);
            }
            close(caminhoJ1);
            close(caminhoJ2);
            exit(0);
        }

        bytesRead = read(caminhoJ1, Tabuleiro, sizeof(Tabuleiro));
        if (bytesRead <= 0)
        {
            printf("Erro ou fim de jogo.\n");
            break;
        }

        system("clear");
        printf("Jogo do Galo\n(Você é o O)\n");
        printJogo(Tabuleiro);

        int jogada_valida = 0;
        do
        {
            printf("Jogador 2 (O), escolha a linha (1-3): ");
            scanf("%d", &linha);
            printf("Escolha a coluna (1-3): ");
            scanf("%d", &coluna);

            linha--;
            coluna--;

            if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas)
            {
                printf("Coordenadas inválidas! Tente novamente.\n");
                sleep(1);
                continue;
            }

            if (!colocar_peca(Tabuleiro, linha, coluna, peca))
            {
                printf("Posição já ocupada\n");
                sleep(1);
                continue;
            }

            jogada_valida = 1;
        } while (!jogada_valida);

        system("clear");
        printf("Jogador 2: Jogada feita na linha %d, coluna %d\n", linha, coluna);
        printJogo(Tabuleiro);

        if (verificar_vitoria(Tabuleiro, peca))
        {
            printf("Jogador 2 (O) ganhou!\n");

            // Enviar sinal de vitória
            char vitoria = 'V';
            write(caminhoJ2, &vitoria, 1);

            // Enviar tabuleiro final ao jogador 1
            write(caminhoJ2, Tabuleiro, sizeof(Tabuleiro));

            // Enviar resultado ao menu
            int fd = open("pipe_jogadores_menu", O_WRONLY);
            if (fd >= 0)
            {
                write(fd, "2", 1);
                close(fd);
            }

            close(caminhoJ1);
            close(caminhoJ2);
            exit(0);
        }
        else if (verificar_empate(Tabuleiro))
        {
            printf("Empate!\n");
            char empate = 'E';
            write(caminhoJ2, &empate, 1);
            write(caminhoJ2, Tabuleiro, sizeof(Tabuleiro));
            int fd = open("pipe_jogadores_menu", O_WRONLY);
            if (fd >= 0)
            {
                write(fd, "E", 1);
                close(fd);
            }
            sleep(1);
            close(caminhoJ1);
            close(caminhoJ2);
            exit(0);
        }
        else
        {
            char semVitoria = 'C';
            write(caminhoJ2, &semVitoria, 1);
        }

        write(caminhoJ2, Tabuleiro, sizeof(Tabuleiro));
        sleep(1);
    }

    close(caminhoJ1);
    close(caminhoJ2);

    exit(0);
}
