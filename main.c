/**
 * Desafio: Construção dos Territórios
 *
 * Este programa permite o cadastro de 5 territórios usando uma estrutura de dados
 * composta (struct). Ele solicita ao usuário o nome, a cor do exército e a 
 * quantidade de tropas para cada território e, ao final, exibe todos os 
 * dados cadastrados.
 */

// 1. Bibliotecas necessárias
#include <stdio.h>  // Para funções de entrada e saída (printf, scanf)
#include <string.h> // Para manipulação de strings (embora scanf %s sirva aqui)

// 2. Definição da struct:
// Define a estrutura 'Territorio' para agrupar os dados
// relacionados a cada território.
struct Territorio {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército
    int tropas;     // Quantidade de tropas
};

int main() {
    
    // 3. Declaração de vetor de structs:
    // Cria um vetor chamado 'territorios' que pode armazenar
    // 5 elementos do tipo 'struct Territorio'.
    struct Territorio territorios[5];
    
    // Variável de controle para os laços
    int i; 

    // 4. Entrada dos dados (Cadastro):
    // Utiliza um laço 'for' para percorrer o vetor e preencher
    // os dados dos 5 territórios.
    printf("--- Cadastro de Territorios ---\n");
    printf("Por favor, insira os dados para 5 territorios.\n");
    printf("ATENCAO: Nao utilize espacos para nomes ou cores (ex: 'AmericaNorte').\n\n");

    for (i = 0; i < 5; i++) {
        // Usa 'i + 1' para exibir uma contagem amigável (1 a 5)
        printf("--- Territorio %d ---\n", i + 1);
        
        // Solicita o nome
        printf("Digite o nome: ");
        // Lê o nome. scanf("%s") lê até o primeiro espaço.
        scanf("%s", territorios[i].nome); 
        
        // Solicita a cor
        printf("Digite a cor: ");
        // Lê a cor.
        scanf("%s", territorios[i].cor);

        // Solicita as tropas
        printf("Digite a quantidade de tropas: ");
        // Lê o número de tropas. Usamos '&' para passar o endereço da variável.
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Adiciona uma linha em branco para legibilidade
    }

    // 5. Exibição dos dados:
    // Percorre o vetor novamente, após o cadastro, e exibe os dados
    // de cada território com formatação clara.
    printf("\n--- Relatorio de Territorios Cadastrados ---\n\n");

    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }

    return 0; // Indica que o programa terminou com sucesso
}
