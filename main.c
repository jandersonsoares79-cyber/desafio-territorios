/**
 * Desafio: Detective Quest
 * * Este programa simula o mapa de uma mansão (Detective Quest) 
 * usando uma estrutura de dados de árvore binária.
 * O jogador começa no "Hall de entrada" (raiz da árvore) e pode 
 * navegar escolhendo caminhos para a esquerda (e) ou direita (d) 
 * até chegar a um cômodo sem saída (nó-folha) ou decidir sair (s).
 * * Conceitos aplicados:
 * - Structs: Para definir a 'Sala' (nó da árvore).
 * - Alocação Dinâmica: Uso de malloc() para criar as salas.
 * - Ponteiros: Para ligar as salas (esquerda/direita).
 * - Modularização: Funções com responsabilidades únicas.
 */

// 1. Bibliotecas necessárias
#include <stdio.h>  // Para printf() e scanf()
#include <stdlib.h> // Para malloc(), free() e exit()
#include <string.h> // Para strcpy() (copiar strings)

// 2. Definição da struct (Estrutura da Sala)
// Usamos 'typedef' para criar um tipo 'Sala' mais limpo.
// Cada Sala (nó) contém seu nome e dois ponteiros para
// as próximas salas (filhos da árvore).
typedef struct Sala {
    char nome[50];          // Nome do cômodo
    struct Sala* esquerda;  // Ponteiro para a sala à esquerda
    struct Sala* direita;   // Ponteiro para a sala à direita
} Sala;

// 3. Protótipos das funções (boa prática)
Sala* criarSala(const char* nome);
void explorarSalas(Sala* salaAtual);
void liberarMapa(Sala* sala);

/**
 * Função: main
 * Ponto de entrada do programa.
 * Responsável por:
 * 1. Montar o mapa da mansão (criar a árvore estática).
 * 2. Iniciar a exploração do jogador a partir do Hall.
 * 3. Liberar a memória alocada ao final do jogo.
 */
int main() {
    printf("--- Detective Quest: O Misterio da Mansao ---\n");
    printf("Voce esta no Hall de entrada. Explore os comodos.\n");

    // --- Montagem do Mapa (Árvore Binária) ---
    // O Hall de entrada é o nó raiz (root)
    Sala* hall = criarSala("Hall de entrada");

    // --- Ala Esquerda ---
    hall->esquerda = criarSala("Sala de estar");
    hall->esquerda->esquerda = criarSala("Cozinha"); // Nó-folha
    hall->esquerda->direita = criarSala("Jardim");   // Nó-folha

    // --- Ala Direita ---
    hall->direita = criarSala("Biblioteca");
    hall->direita->esquerda = criarSala("Escritorio"); // Nó-folha
    // (hall->direita->direita é NULL, não há sala ali)

    // --- Início da Exploração ---
    // Chama a função de navegação, começando pelo Hall
    explorarSalas(hall);

    // --- Limpeza da Memória ---
    // Libera toda a memória alocada dinamicamente antes de fechar
    liberarMapa(hall);

    return 0; // Indica que o programa terminou com sucesso
}

/**
 * Função: criarSala
 * Responsável por criar uma nova sala (alocar dinamicamente um nó).
 * Recebe o nome da sala como parâmetro.
 * Retorna um ponteiro para a sala recém-criada.
 */
Sala* criarSala(const char* nome) {
    // 1. Aloca memória do tamanho da struct Sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));

    // 2. Verifica se a alocação de memória falhou
    if (novaSala == NULL) {
        printf("ERRO CRITICO: Falha ao alocar memoria para a sala! \n");
        exit(1); // Encerra o programa se não houver memória
    }

    // 3. Inicializa os dados da sala
    strcpy(novaSala->nome, nome); // Copia o nome para a struct
    novaSala->esquerda = NULL;    // Por padrão, não há caminhos
    novaSala->direita = NULL;

    // 4. Retorna o ponteiro para a nova sala
    return novaSala;
}

/**
 * Função: explorarSalas
 * Gerencia o loop principal de exploração do jogador.
 * Recebe a sala inicial (raiz) como ponto de partida.
 * Permite a navegação interativa (e, d, s).
 * O loop termina se o jogador sair (s) ou chegar a um nó-folha.
 */
void explorarSalas(Sala* salaAtual) {
    char escolha;

    // O loop continua enquanto o jogador estiver em uma sala válida
    while (salaAtual != NULL) {
        
        // 1. Mostra a localização atual
        printf("\n----------------------------------------\n");
        printf("VoCE ESTA EM: %s\n", salaAtual->nome);
        printf("----------------------------------------\n");

        // 2. Verifica se é um nó-folha (beco sem saída)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Este e um beco sem saida. Nao ha mais caminhos.\n");
            printf("Fim da exploracao.\n");
            break; // Encerra o loop 'while'
        }

        // 3. Mostra as opções de caminho
        printf("Escolha seu caminho:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  (e) Esquerda: %s\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  (d) Direita: %s\n", salaAtual->direita->nome);
        }
        printf("  (s) Sair do jogo\n");
        printf("Sua escolha: ");

        // 4. Lê a escolha do usuário
        // O espaço antes de " %c" é crucial para ignorar
        // quebras de linha (Enter) de inputs anteriores.
        scanf(" %c", &escolha);

        // 5. Processa a escolha
        if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda; // Move o jogador para a esquerda
            } else {
                printf(">> Nao ha caminho para a esquerda.\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita; // Move o jogador para a direita
            } else {
                printf(">> Nao ha caminho para a direita.\n");
            }
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("\nVoce saiu da mansao. Ate a proxima, detetive!\n");
            break; // Encerra o loop 'while'
        } 
        else {
            printf(">> Opcao invalida. Tente 'e', 'd' ou 's'.\n");
        }
    }
}

/**
 * Função: liberarMapa
 * Libera toda a memória alocada dinamicamente para o mapa (árvore).
 * Utiliza uma travessia em pós-ordem (visita filhos antes da raiz)
 * para garantir que nenhum ponteiro seja perdido.
 */
void liberarMapa(Sala* sala) {
    // Condição de parada da recursão
    if (sala == NULL) {
        return;
    }

    // 1. Libera a sub-árvore esquerda
    liberarMapa(sala->esquerda);
    // 2. Libera a sub-árvore direita
    liberarMapa(sala->direita);
    // 3. Libera o nó atual (depois dos filhos)
    free(sala);
}
