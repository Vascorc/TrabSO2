#include"funcoesAjuda.h"
#include <stdio.h>

void printJogo(char Tabuleiro[linhas][colunas]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            char c = Tabuleiro[i][j];
            if (c == 'X') {
                textcolor(BRIGHT, RED, -1);
                printf(" %c ", c);
                textcolor(RESET, WHITE, -1);
            } else if (c == 'O') {
                textcolor(BRIGHT, GREEN, -1);
                printf(" %c ", c);
                textcolor(RESET, WHITE, -1);
            } else {
                printf("   ");
            }

            if (j < colunas - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < linhas - 1) {
            printf("---+---+---\n");
        }
    }
}



int colocar_peca(char Tabuleiro[linhas][colunas], int linha, int coluna, char peca) {
    if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
        printf("Coordenadas inválidas! Tente novamente.\n");
        return 0;
    }

    if (Tabuleiro[linha][coluna] != ' ') {
        printf("A célula já está ocupada! Tente novamente.\n");
        return 0;
    }

    Tabuleiro[linha][coluna] = peca;
    return 1;
}


int verificar_vitoria(char tabuleiro[linhas][colunas], char jogador)
{
    // Verifica as linhas
    for (int i = 0; i < linhas; i++) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) {
            return 1; 
        }
    }

    // Verifica as colunas
    for (int i = 0; i < colunas; i++) {
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador) {
            return 1; 
        }
    }

    // Verifica as diagonais
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) {
        return 1;
    }
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) {
        return 1; 
    }

    return 0;
}


void textcolor(int attr, int fg, int bg)
{
    char command[20];
    if (bg == -1) {
        // Fundo padrão do terminal (transparente)
        sprintf(command, "%c[%d;%dm", 0x1B, attr, fg + 30);
    } else {
        sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    }
    printf("%s", command);
}
