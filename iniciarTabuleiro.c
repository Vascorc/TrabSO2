#include"iniciarTabuleiro.h"

void iniciar_tabuleiro(char tabuleiro[linhas][colunas]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}