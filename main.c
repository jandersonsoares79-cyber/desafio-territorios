/**
 * Desafio: Tetris Stack - Fila de Peças
 *
 * Este programa simula a "fila de próximas peças" de um jogo
 * similar ao Tetris, utilizando uma estrutura de dados de 
 * Fila Circular.
 *
 * O programa inicializa a fila com 5 peças geradas 
 * automaticamente e, em seguida, permite ao usuário:
 * 1. Jogar a próxima peça (dequeue - remover do início).
 * 2. Inserir uma nova peça (enqueue - adicionar ao fim), se houver espaço.
 * 0. Sair do jogo.
 *
 * O estado da fila é exibido a cada turno.
 *
 * Conceitos aplicados:
 * - Structs: Para definir a 'Peca' (nome, id).
 * - Fila Circular: Implementada com um vetor, 'inicio', 'fim' e 'contador'.
 * Isso é eficiente, pois 'dequeue' (jogar) não exige mover
 * todos os elementos (como no desafio do inventário).
 * - Modularização: Funções com responsabilidades únicas.
 * - Geração de Dados: Peças geradas automaticamente.
 */

// 1. Bibliotecas necessárias
#include <stdio.h>  // Para printf(), scanf()
#include <stdlib.h> // Para rand(), srand() e exit()
#include <time.h>   // Para time() (semente do rand)

// 2. Constantes e Definições Globais
#define TAMANHO_FILA 5 // Tamanho fixo da fila de peças

// 3. Definição da struct (Atributos das peças)
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

// 4. Variáveis Globais para a Fila Circular
Peca filaDePecas[TAMANHO_FILA]; // O vetor que armazena a fila
int inicio = 0;    // Índice do PRIMEIRO elemento (para remover)
int fim = 0;       // Índice da PRÓXIMA POSIÇÃO VAZIA (para inserir)
int contador = 0;  // Quantidade de elementos ATUALMENTE na fila
int proximoId = 0; // Contador global para gerar IDs únicos

// 5. Protótipos das funções
void inserirPecaFila(); // Enqueue
void jogarPeca();       // Dequeue
void exibirFila();
Peca gerarPeca();       // Função helper solicitada
void limparTela();

/**
 * Função: main
 * Ponto de entrada do programa.
 * Responsável por:
 * 1. Inicializar o gerador de números aleatórios (srand).
 * 2. Preencher a fila inicial com 5 peças.
 * 3. Exibir o menu principal e controlar o loop do jogo.
 * 4. Chamar as funções corretas com base na escolha do usuário.
 */
int main() {
    // 1. Inicializa o gerador aleatório
    srand(time(NULL));

    int opcao;

    // 2. Inicializa a fila (requisito funcional)
    printf("Inicializando a fila de pecas...\n");
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirPecaFila();
    }

    // 3. Loop principal do menu
    do {
        limparTela();
        printf("--- Tetris Stack ---\n");
        
        // Exibe o estado atual da fila (requisito)
        exibirFila();

        // Exibe o menu de opções (Exemplo de saída)
        printf("\nOpcoes de acao:\n");
        printf("1. Jogar peca (dequeue)\n");
        printf("2. Inserir nova peca (enqueue)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        // 4. Processa a escolha do usuário
        switch (opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                inserirPecaFila();
                break;
            case 0:
                printf("\nSaindo do jogo... Ate mais!\n");
                break;
            default:
                printf("\nOpcao invalida! Pressione Enter para tentar novamente.\n");
        }

        // Pausa para o usuário ler a saída antes de limpar a tela
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            getchar(); // Espera o Enter
        }

    } while (opcao != 0);

    return 0;
}

/**
 * Função: inserirPecaFila (Enqueue)
 * Adiciona uma nova peça ao FINAL da fila circular.
 * 1. Verifica se a fila está cheia (usando 'contador').
 * 2. Se não estiver cheia:
 * a. Gera uma nova peça (usando 'gerarPeca').
 * b. Adiciona a peça na posição 'fim'.
 * c. Atualiza o índice 'fim' (com % para dar a volta).
 * d. Incrementa o 'contador'.
 */
void inserirPecaFila() {
    // 1. Verifica se a fila está cheia
    if (contador >= TAMANHO_FILA) {
        printf("\nAVISO: A fila de pecas esta cheia! Nao e possivel inserir.\n");
    } else {
        // 2a. Gera a peça
        Peca novaPeca = gerarPeca();
        
        // 2b. Adiciona na posição 'fim'
        filaDePecas[fim] = novaPeca;
        
        // 2c. Atualiza o 'fim' de forma circular
        // (Ex: se TAMANHO_FILA=5 e fim=4, (4+1)%5 = 0. Volta ao início)
        fim = (fim + 1) % TAMANHO_FILA;
        
        // 2d. Incrementa o contador
        contador++;

        printf("\nNova peca [%c %d] inserida no final da fila.\n", novaPeca.nome, novaPeca.id);
    }
}

/**
 * Função: jogarPeca (Dequeue)
 * Remove e "joga" a peça do INÍCIO da fila circular.
 * 1. Verifica se a fila está vazia (usando 'contador').
 * 2. Se não estiver vazia:
 * a. Pega a peça da posição 'inicio'.
 * b. Atualiza o índice 'inicio' (com % para dar a volta).
 * c. Decrementa o 'contador'.
 */
void jogarPeca() {
    // 1. Verifica se a fila está vazia
    if (contador == 0) {
        printf("\nAVISO: A fila de pecas esta vazia! Nao ha pecas para jogar.\n");
    } else {
        // 2a. Pega a peça do 'inicio'
        Peca pecaJogada = filaDePecas[inicio];
        
        // 2b. Atualiza o 'inicio' de forma circular
        inicio = (inicio + 1) % TAMANHO_FILA;
        
        // 2c. Decrementa o contador
        contador--;

        printf("\nPeca [%c %d] foi jogada (removida do inicio).\n", pecaJogada.nome, pecaJogada.id);
    }
}

/**
 * Função: exibirFila
 * Mostra o estado atual de todas as peças na fila,
 * da primeira (inicio) até a última.
 */
void exibirFila() {
    printf("Fila de pecas: ");
    
    if (contador == 0) {
        printf("[VAZIA]\n");
        return;
    }

    // Para exibir corretamente a fila circular, não podemos
    // apenas iterar de 0 a TAMANHO_FILA.
    // Devemos começar em 'inicio' e andar 'contador' passos.
    int indiceAtual = inicio;
    for (int i = 0; i < contador; i++) {
        
        Peca p = filaDePecas[indiceAtual];
        printf("[%c %d] ", p.nome, p.id);
        
        // Move o índice de forma circular
        indiceAtual = (indiceAtual + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

/**
 * Função: gerarPeca (Helper)
 * Cria e retorna uma nova peça com um tipo aleatório
 * (conforme solicitado: 'I', 'O', 'T', 'L')
 * e um 'id' sequencial único.
 */
Peca gerarPeca() {
    Peca novaPeca;
    
    // 1. Define o ID único e incrementa o contador global
    novaPeca.id = proximoId++;
    
    // 2. Gera um tipo aleatório
    char tiposPossiveis[] = {'I', 'O', 'T', 'L'}; // Conforme requisitos
    int indiceAleatorio = rand() % 4; // Gera um número de 0 a 3
    
    novaPeca.nome = tiposPossiveis[indiceAleatorio];
    
    return novaPeca;
}

/**
 * Função: limparTela (Função de Usabilidade)
 * Limpa o console para melhorar a legibilidade da interface.
 */
void limparTela() {
    // "Empurra" o conteúdo antigo para cima
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
