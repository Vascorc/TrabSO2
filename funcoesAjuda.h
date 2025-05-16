#ifndef FUNCOESAJUDA_H
#define FUNCOESAJUDA_H

#define linhas 3
#define colunas 3

void printJogo(char Tabuleiro[linhas][colunas]);
int colocar_peca(char Tabuleiro[linhas][colunas], int linha, int coluna, char peca);
int verificar_vitoria(char tabuleiro[linhas][colunas], char jogador);

#endif
