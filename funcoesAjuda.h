#ifndef FUNCOESAJUDA_H
#define FUNCOESAJUDA_H

#define linhas 3
#define colunas 3

#define RESET 0
#define BRIGHT 1
#define BLACK 0
#define RED 1
#define GREEN 2
#define WHITE 7


void printJogo(char Tabuleiro[linhas][colunas]);
int colocar_peca(char Tabuleiro[linhas][colunas], int linha, int coluna, char peca);
int verificar_vitoria(char tabuleiro[linhas][colunas], char jogador);
void textcolor (int attr, int fg, int bg);
int verificar_empate(char tabuleiro[linhas][colunas]);

#endif
