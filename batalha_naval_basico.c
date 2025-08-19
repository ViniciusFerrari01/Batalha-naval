/*
 * Batalha Naval - Nível Básico (Vetores e Matrizes)
 * Autor: Vinicius Ferrari (com auxílio do ChatGPT)
 *
 * Objetivo do exercício:
 *  - Representar um tabuleiro 10x10 usando uma matriz (array bidimensional).
 *  - Declarar DOIS vetores (arrays unidimensionais) para representar navios de tamanho 3.
 *  - Posicionar UM navio horizontalmente e UM navio verticalmente no tabuleiro.
 *  - Marcar água com 0 e partes dos navios com 3.
 *  - Validar limites do tabuleiro e impedir sobreposição.
 *  - Exibir o tabuleiro com printf (0 = água, 3 = navio).
 *
 * Simplificações:
 *  - Tamanho do tabuleiro fixo: 10x10.
 *  - Tamanho de cada navio fixo: 3.
 *  - Coordenadas definidas diretamente no código (sem input do usuário).
 *  - Não há lógica de "tiros" ou gameplay.
 *
 * Como compilar (no terminal):
 *     gcc -Wall -Wextra -O2 -std=c11 -o batalha_naval_basico batalha_naval_basico.c
 *
 * Como executar:
 *     ./batalha_naval_basico
 */

#include <stdio.h>
#include <stdlib.h>  /* exit, EXIT_FAILURE */
#include <ctype.h>   /* toupper */

#define BOARD_SIZE 10  /* Tamanho do tabuleiro: 10 linhas x 10 colunas */
#define SHIP_SIZE  3   /* Cada navio ocupa 3 posições */
#define WATER      0   /* Valor para água */
#define SHIP       3   /* Valor para parte do navio */

/* ---------- Assinaturas das funções ---------- */
void inicializar_tabuleiro(int board[BOARD_SIZE][BOARD_SIZE]);
int  dentro_limites(int linha, int coluna);
int  pode_posicionar(int board[BOARD_SIZE][BOARD_SIZE],
                     int linha_inicial, int coluna_inicial,
                     char orientacao, int tamanho);
int  posicionar_navio_do_vetor(int board[BOARD_SIZE][BOARD_SIZE],
                               int linha_inicial, int coluna_inicial,
                               char orientacao, const int navio[], int tamanho);
void exibir_tabuleiro(const int board[BOARD_SIZE][BOARD_SIZE]);

int main(void) {
    /* ------------------- DECLARAÇÃO DOS DADOS -------------------
     * Matriz 10x10 representando o tabuleiro.
     *  - 0 = água
     *  - 3 = parte do navio
     */
    int tabuleiro[BOARD_SIZE][BOARD_SIZE];
    inicializar_tabuleiro(tabuleiro);

    /* Dois vetores para os navios (ambos de tamanho 3).
     * Cada posição do vetor contém o valor 3 (parte do navio).
     * A ideia é "copiar" esses valores para a matriz do tabuleiro.
     */
    const int navio_horizontal[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    const int navio_vertical[SHIP_SIZE]   = {SHIP, SHIP, SHIP};

    /* ------------------- PARÂMETROS DOS NAVIOS -------------------
     * Coordenadas iniciais e orientação definidas no código.
     * Índices de linha/coluna variam de 0 a 9 (indexação zero-based).
     *
     * - navio HORIZONTAL começa em (linha=2, coluna=1) -> ocupa (2,1) (2,2) (2,3)
     * - navio VERTICAL   começa em (linha=5, coluna=7) -> ocupa (5,7) (6,7) (7,7)
     *
     * Modifique estes valores caso deseje testar outras posições.
     */
    int  h_linha_inicial = 2;
    int  h_coluna_inicial = 1;
    char h_orientacao = 'H'; /* 'H' = horizontal */

    int  v_linha_inicial = 5;
    int  v_coluna_inicial = 7;
    char v_orientacao = 'V'; /* 'V' = vertical */

    /* ------------------- VALIDAÇÃO E POSICIONAMENTO -------------------
     * 1) Validar se cada navio cabe no tabuleiro na orientação desejada.
     * 2) Garantir que não haja sobreposição (tabuleiro deve estar com 0 nas casas).
     * 3) Posicionar (copiar) os valores do vetor para a matriz conforme a orientação.
     */

    if (!pode_posicionar(tabuleiro, h_linha_inicial, h_coluna_inicial, h_orientacao, SHIP_SIZE)) {
        fprintf(stderr, "ERRO: Navio horizontal não cabe ou sobrepõe outra peça.\n");
        exit(EXIT_FAILURE);
    }
    if (!pode_posicionar(tabuleiro, v_linha_inicial, v_coluna_inicial, v_orientacao, SHIP_SIZE)) {
        fprintf(stderr, "ERRO: Navio vertical não cabe ou sobrepõe outra peça.\n");
        exit(EXIT_FAILURE);
    }

    /* Posiciona navio horizontal */
    if (!posicionar_navio_do_vetor(tabuleiro, h_linha_inicial, h_coluna_inicial,
                                   h_orientacao, navio_horizontal, SHIP_SIZE)) {
        fprintf(stderr, "ERRO ao posicionar o navio horizontal.\n");
        exit(EXIT_FAILURE);
    }

    /* Posiciona navio vertical */
    if (!posicionar_navio_do_vetor(tabuleiro, v_linha_inicial, v_coluna_inicial,
                                   v_orientacao, navio_vertical, SHIP_SIZE)) {
        fprintf(stderr, "ERRO ao posicionar o navio vertical.\n");
        exit(EXIT_FAILURE);
    }

    /* ------------------- EXIBIÇÃO DO TABULEIRO -------------------
     * Mostra a matriz completa com 0s e 3s, organizada e com separadores.
     */
    printf("=== Batalha Naval (Matriz 10x10) ===\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}

/* Preenche todo o tabuleiro com 0 (água). */
void inicializar_tabuleiro(int board[BOARD_SIZE][BOARD_SIZE]) {
    /* Dois loops aninhados: percorrem linhas (i) e colunas (j). */
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = WATER; /* Marca água nas 100 posições. */
        }
    }
}

/* Verifica se (linha, coluna) está dentro dos limites 0..9. */
int dentro_limites(int linha, int coluna) {
    return (linha >= 0 && linha < BOARD_SIZE &&
            coluna >= 0 && coluna < BOARD_SIZE);
}

/* Checa se é possível posicionar um navio (de certo tamanho) a partir de
 * (linha_inicial, coluna_inicial) na orientação informada ('H' ou 'V').
 * Valida:
 *   - Se cabe no tabuleiro sem "transbordar".
 *   - Se não há sobreposição com partes de outros navios (células devem estar com 0).
 */
int pode_posicionar(int board[BOARD_SIZE][BOARD_SIZE],
                    int linha_inicial, int coluna_inicial,
                    char orientacao, int tamanho) {
    char o = (char)toupper((unsigned char)orientacao);

    if (o == 'H') {
        /* Verifica se a última coluna do navio está dentro do tabuleiro. */
        if (coluna_inicial + tamanho > BOARD_SIZE) {
            return 0; /* Não cabe horizontalmente. */
        }
        /* Verifica se todas as posições necessárias estão livres (== 0). */
        for (int k = 0; k < tamanho; ++k) {
            int lin = linha_inicial;
            int col = coluna_inicial + k;
            if (!dentro_limites(lin, col) || board[lin][col] != WATER) {
                return 0; /* Fora dos limites ou já ocupado. */
            }
        }
        return 1; /* Pode posicionar. */
    } else if (o == 'V') {
        /* Verifica se a última linha do navio está dentro do tabuleiro. */
        if (linha_inicial + tamanho > BOARD_SIZE) {
            return 0; /* Não cabe verticalmente. */
        }
        for (int k = 0; k < tamanho; ++k) {
            int lin = linha_inicial + k;
            int col = coluna_inicial;
            if (!dentro_limites(lin, col) || board[lin][col] != WATER) {
                return 0; /* Fora dos limites ou já ocupado. */
            }
        }
        return 1; /* Pode posicionar. */
    } else {
        /* Orientação inválida */
        return 0;
    }
}

/* Copia os valores do vetor 'navio' para o tabuleiro a partir da posição inicial,
 * respeitando a orientação 'H' (horizontal) ou 'V' (vertical).
 * Retorna 1 em caso de sucesso, 0 caso contrário.
 */
int posicionar_navio_do_vetor(int board[BOARD_SIZE][BOARD_SIZE],
                              int linha_inicial, int coluna_inicial,
                              char orientacao, const int navio[], int tamanho) {
    char o = (char)toupper((unsigned char)orientacao);

    if (!pode_posicionar(board, linha_inicial, coluna_inicial, o, tamanho)) {
        return 0; /* Falha na validação de limites/sobreposição. */
    }

    if (o == 'H') {
        for (int k = 0; k < tamanho; ++k) {
            board[linha_inicial][coluna_inicial + k] = navio[k];
        }
        return 1;
    } else if (o == 'V') {
        for (int k = 0; k < tamanho; ++k) {
            board[linha_inicial + k][coluna_inicial] = navio[k];
        }
        return 1;
    } else {
        return 0; /* Orientação inválida. */
    }
}

/* Exibe a matriz do tabuleiro com cabeçalho de colunas e índices de linha.
 * Elementos separados por espaço para facilitar a leitura.
 */
void exibir_tabuleiro(const int board[BOARD_SIZE][BOARD_SIZE]) {
    /* Cabeçalho das colunas */
    printf("    ");
    for (int c = 0; c < BOARD_SIZE; ++c) {
        printf("%d ", c);
    }
    printf("\n");

    /* Linha separadora opcional */
    printf("   ");
    for (int c = 0; c < BOARD_SIZE; ++c) {
        printf("--");
    }
    printf("\n");

    /* Conteúdo da matriz */
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%2d| ", i); /* Índice da linha + separador visual */
        for (int j = 0; j < BOARD_SIZE; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}