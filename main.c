/**
 * Desafio: Sistema de Inventário (Mochila de Loot)
 *
 * Este programa simula um inventário de jogo com capacidade para 10 itens.
 * Ele utiliza uma lista sequencial (vetor) de structs 'Item'.
 * O usuário pode interagir através de um menu para:
 * 1. Inserir um novo item (se houver espaço).
 * 2. Remover um item (buscando pelo nome).
 * 3. Listar todos os itens no inventário.
 * 4. Buscar um item específico (buscando pelo nome).
 *
 * Conceitos aplicados:
 * - Structs: Para definir o 'Item' (nome, tipo, quantidade).
 * - Vetor de Structs: Para armazenar o inventário (lista sequencial).
 * - Modularização: Funções com responsabilidades únicas.
 * - Busca Sequencial: Implementada para encontrar itens pelo nome.
 * - Manipulação de Vetor: Inserção no final e remoção com "shift-left".
 */

// 1. Bibliotecas necessárias
#include <stdio.h>  // Para printf(), scanf() (entrada/saída)
#include <stdlib.h> // Para system("clear") ou system("cls") (limpar tela)
#include <string.h> // Para strcmp() (comparar strings) e strcpy() (copiar strings)

// 2. Constantes e Definições Globais
#define MAX_ITENS 10 // Capacidade máxima da mochila

// 3. Criação da struct:
// Define a estrutura 'Item' para agrupar os dados
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// 4. Vetor de structs (Variáveis Globais):
// Cria o vetor 'mochila' (nosso inventário) e um contador
struct Item mochila[MAX_ITENS];
int totalItens = 0; // Controla a quantidade ATUAL de itens na mochila

// 5. Protótipos das funções obrigatórias
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

// Protótipo da função auxiliar de busca (boa prática)
int buscarIndicePorNome(const char* nomeBusca);
void limparTela(); // Função de utilidade (Usabilidade)

/**
 * Função: main
 * Ponto de entrada do programa.
 * Responsável por:
 * 1. Exibir o menu principal de opções.
 * 2. Ler a escolha do usuário.
 * 3. Chamar a função correspondente (modularização).
 * 4. Controlar o loop principal do programa (continua até o usuário sair).
 */
int main() {
    int opcao;

    // Loop principal do menu
    do {
        limparTela();
        printf("--- INVENTARIO DA MOCHILA (Capacidade: %d/%d) ---\n", totalItens, MAX_ITENS);
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair do Jogo\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        // Lê a opção do usuário
        scanf("%d", &opcao);

        // Estrutura switch para chamar a função correta
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
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
            // Limpa o buffer de entrada (consome o '\n' do scanf anterior)
            while (getchar() != '\n'); 
            // Espera o usuário pressionar Enter
            getchar(); 
        }

    } while (opcao != 0); // O loop continua enquanto a opção não for 0

    return 0; // Fim do programa
}

/**
 * Função: inserirItem
 * Permite o cadastro de um novo item no inventário.
 * 1. Verifica se a mochila está cheia.
 * 2. Pede ao usuário o nome, tipo e quantidade do item.
 * 3. Adiciona o item na próxima posição livre do vetor.
 * 4. Incrementa o contador 'totalItens'.
 * 5. Lista os itens (requisito funcional).
 */
void inserirItem() {
    limparTela();
    printf("--- Adicionar Novo Item ---\n");

    // 1. Verifica se a mochila está cheia
    if (totalItens >= MAX_ITENS) {
        printf("A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return; // Retorna ao menu
    }

    // 2. Pede os dados do item
    // Usa 'totalItens' como índice para o novo item
    struct Item novoItem;

    printf("Nome do item (sem espacos): ");
    scanf("%s", novoItem.nome); // Lê o nome

    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    scanf("%s", novoItem.tipo); // Lê o tipo

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade); // Lê a quantidade

    // 3. Adiciona o item na mochila
    mochila[totalItens] = novoItem;

    // 4. Incrementa o total de itens
    totalItens++;

    printf("\nItem '%s' adicionado com sucesso!\n", novoItem.nome);
    
    // 5. Lista os itens (requisito)
    listarItens();
}

/**
 * Função: removerItem
 * Permite a exclusão de um item do inventário.
 * 1. Pede o nome do item a ser removido.
 * 2. Usa a função 'buscarIndicePorNome' para encontrá-lo.
 * 3. Se não encontrar, informa o usuário.
 * 4. Se encontrar, remove o item "puxando" todos os itens seguintes
 * uma posição para a esquerda ("shift-left").
 * 5. Decrementa o contador 'totalItens'.
 * 6. Lista os itens (requisito funcional).
 */
void removerItem() {
    limparTela();
    printf("--- Remover Item ---\n");
    
    if (totalItens == 0) {
        printf("A mochila esta vazia. Nao ha itens para remover.\n");
        return;
    }

    // 1. Pede o nome
    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeBusca);

    // 2. Busca o índice do item
    int indice = buscarIndicePorNome(nomeBusca);

    // 3. Se não encontrar
    if (indice == -1) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
    } else {
        // 4. Se encontrar, "puxa" os elementos (shift-left)
        // Pega o nome do item antes de sobrescrevê-lo (para a msg)
        char nomeRemovido[30];
        strcpy(nomeRemovido, mochila[indice].nome);

        for (int i = indice; i < totalItens - 1; i++) {
            // Copia o item da posição [i+1] para a posição [i]
            mochila[i] = mochila[i + 1];
        }

        // 5. Decrementa o total de itens
        totalItens--;
        
        printf("\nItem '%s' removido com sucesso!\n", nomeRemovido);

        // 6. Lista os itens (requisito)
        listarItens();
    }
}

/**
 * Função: listarItens
 * Exibe todos os itens atualmente no inventário.
 * 1. Verifica se a mochila está vazia.
 * 2. Percorre o vetor 'mochila' de 0 até 'totalItens'.
 * 3. Imprime os dados de cada item formatados.
 */
void listarItens() {
    // Não limpa a tela, pois é chamada por outras funções
    printf("\n--- Itens Atuais na Mochila (%d/%d) ---\n", totalItens, MAX_ITENS);

    // 1. Verifica se está vazia
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    // 2. Percorre o vetor (lista sequencial)
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Qtd.: %d\n", mochila[i].quantidade);
        printf("-------------------\n");
    }
}

/**
 * Função: buscarItem
 * Função de busca sequencial visível ao usuário.
 * 1. Pede o nome do item a ser buscado.
 * 2. Usa a função 'buscarIndicePorNome' para encontrá-lo.
 * 3. Se encontrar, exibe os detalhes completos do item.
 * 4. Se não encontrar, informa o usuário.
 */
void buscarItem() {
    limparTela();
    printf("--- Buscar Item na Mochila ---\n");

    if (totalItens == 0) {
        printf("A mochila esta vazia. Nao ha itens para buscar.\n");
        return;
    }

    // 1. Pede o nome
    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBusca);

    // 2. Busca o índice
    int indice = buscarIndicePorNome(nomeBusca);

    // 3. Se encontrar
    if (indice != -1) {
        printf("\nItem encontrado!\n");
        printf("-------------------\n");
        printf("  Nome: %s\n", mochila[indice].nome);
        printf("  Tipo: %s\n", mochila[indice].tipo);
        printf("  Qtd.: %d\n", mochila[indice].quantidade);
        printf("-------------------\n");
    } else {
        // 4. Se não encontrar
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

/**
 * Função: buscarIndicePorNome (Função Auxiliar)
 * Realiza uma BUSCA SEQUENCIAL no vetor 'mochila'.
 * 1. Percorre o vetor de 0 até 'totalItens'.
 * 2. Compara o 'nomeBusca' com o nome de cada item na mochila.
 * 3. Se encontrar, retorna o ÍNDICE (posição no vetor) onde o item está.
 * 4. Se o loop terminar sem encontrar, retorna -1 (código de "não encontrado").
 */
int buscarIndicePorNome(const char* nomeBusca) {
    // 1. Percorre o vetor
    for (int i = 0; i < totalItens; i++) {
        // 2. Compara as strings (0 = são iguais)
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // 3. Retorna o índice
            return i;
        }
    }
    // 4. Retorna "não encontrado"
    return -1;
}

/**
 * Função: limparTela (Função de Usabilidade)
 * Limpa o console para melhorar a legibilidade da interface.
 * Usa comandos específicos do sistema operacional.
 */
void limparTela() {
    // Tenta "clear" (Linux/macOS) e "cls" (Windows)
    // O '#ifdef _WIN32' é a forma mais correta, mas
    // system() é mais simples para este nível.
    
    // system("clear || cls"); // Esta linha pode não funcionar em todos os terminais
    
    // Vamos usar uma alternativa mais simples: imprimir várias linhas
    // para "empurrar" o conteúdo antigo para cima.
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
