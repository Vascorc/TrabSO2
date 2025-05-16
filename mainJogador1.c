#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "iniciarTabuleiro.h"
#include "funcoesAjuda.h"

int main()
{
    // Abrir os pipes corretamente
    int caminhoJ2 = open("pipe2to1", O_RDONLY);  // Jogador 1 lê de Jogador 2
    int caminhoJ1 = open("pipe1to2", O_WRONLY);  // Jogador 1 escreve para Jogador 2

    if (caminhoJ1 < 0 || caminhoJ2 < 0)
    {
        perror("Erro ao abrir pipes");
        exit(1);
    }

    char Tabuleiro[linhas][colunas];
    iniciar_tabuleiro(Tabuleiro);

    int linha, coluna;
    char peca = 'X'; // Jogador 1 é 'X'

    while (1)
    {
        system("clear"); // Limpar o terminal a cada nova jogada

        printf("Jogo do Galo\n(Você é o X)\n");
        printJogo(Tabuleiro);  // Exibir o tabuleiro

        // Perguntar ao Jogador 1 qual a linha e a coluna onde ele quer jogar
        printf("Jogador 1 (X), escolha a linha (0-2): ");
        scanf("%d", &linha);
        printf("Escolha a coluna (0-2): ");
        scanf("%d", &coluna);

        if (!colocar_peca(Tabuleiro, linha, coluna, peca))
        {
            continue; // Se a jogada for inválida, pede para tentar novamente
        }

        system("clear"); // Limpar o terminal a cada nova jogada

        // Exibe a jogada feita
        printf("Jogador 1: Jogada feita na linha %d, coluna %d\n", linha, coluna);
        printJogo(Tabuleiro);

        // Enviar o tabuleiro atualizado para o Jogador 2
        write(caminhoJ1, Tabuleiro, sizeof(Tabuleiro));

        // Exibir o tabuleiro atualizado após a jogada do Jogador 1
        printf("Jogador 1: Esperando o Jogador 2 jogar...\n");

        // Esperar pelo tabuleiro atualizado do Jogador 2
        int bytesRead = read(caminhoJ2, Tabuleiro, sizeof(Tabuleiro));

        // Verificar se a leitura foi bem-sucedida
        if (bytesRead < 0) {
            perror("Erro ao ler do pipe");
            exit(1);
        } else {
            printf("Jogador 1: Tabuleiro atualizado recebido do Jogador 2\n");
        }
    }

    return 0;
}
