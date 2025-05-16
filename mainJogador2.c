#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "iniciarTabuleiro.h"
#include "funcoesAjuda.h"

int main()
{
    // Abrir os pipes corretamente
    int caminhoJ1 = open("pipe2to1", O_WRONLY); // Jogador 2 escreve para Jogador 1
    int caminhoJ2 = open("pipe1to2", O_RDONLY);  // Jogador 2 lê de Jogador 1

    if (caminhoJ1 < 0 || caminhoJ2 < 0)
    {
        perror("Erro ao abrir pipes");
        exit(1);
    }

    char Tabuleiro[linhas][colunas];
    iniciar_tabuleiro(Tabuleiro); // Inicia o tabuleiro vazio

    int linha, coluna;
    char peca = 'O'; // Jogador 2 é 'O'

    // O Jogador 2 deve esperar o tabuleiro do Jogador 1
    printf("Jogador 2: Aguardando o Jogador 1 jogar...\n");

    // Ler o tabuleiro do Jogador 1 (após a primeira jogada)
    int bytesRead = read(caminhoJ2, Tabuleiro, sizeof(Tabuleiro));
    if (bytesRead < 0)
    {
        perror("Erro ao ler do pipe");
        exit(1);
    }
    printf("Jogador 2: Tabuleiro recebido do Jogador 1:\n");
    printJogo(Tabuleiro); // Exibir o tabuleiro após a jogada do Jogador 1

    while (1)
    {
        system("clear"); // Limpar o terminal a cada nova jogada

        printf("\nJogo do Galo\n(Você é o O)\n");
        printJogo(Tabuleiro);  // Exibir o tabuleiro

        // Perguntar ao Jogador 2 qual a linha e a coluna onde ele quer jogar
        printf("Jogador 2 (O), escolha a linha (0-2): ");
        scanf("%d", &linha);
        printf("Escolha a coluna (0-2): ");
        scanf("%d", &coluna);

        if (!colocar_peca(Tabuleiro, linha, coluna, peca))
        {
            continue; // Se a jogada for inválida, pede para tentar novamente
        }
        system("clear"); // Limpar o terminal a cada nova jogada

        // Exibe a jogada feita
        printf("Jogador 2: Jogada feita na linha %d, coluna %d\n", linha, coluna);
        printJogo(Tabuleiro); // Exibir o tabuleiro após a jogada do Jogador 2

         if (verificar_vitoria(Tabuleiro, peca)) {
            printf("Jogador 2 (O) ganhou!\n");
            break; // Finaliza o jogo
        }

        // Enviar o tabuleiro atualizado para o Jogador 1
        write(caminhoJ1, Tabuleiro, sizeof(Tabuleiro));

        // Exibir o tabuleiro atualizado após a jogada do Jogador 2
        printf("Jogador 2: Esperando o Jogador 1 jogar...\n");

        // Esperar pelo tabuleiro atualizado do Jogador 1
        bytesRead = read(caminhoJ2, Tabuleiro, sizeof(Tabuleiro));

        // Verificar se a leitura foi bem-sucedida
        if (bytesRead < 0) {
            perror("Erro ao ler do pipe");
            exit(1);
        } else {
            printf("Jogador 2: Tabuleiro atualizado recebido do Jogador 1\n");
        }
    }

    return 0;
}
