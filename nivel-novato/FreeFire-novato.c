#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10   // Capacidade máxima da mochila

// Definição da struct Item
typedef struct {
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item (ex: arma, munição, cura)
    int quantidade;    // Quantidade do item
} Item;

int main() {
    Item mochila[MAX_ITENS]; // Vetor de structs representando a mochila
    int total = 0;           // Quantidade atual de itens na mochila
    int opcao;

    do {
        printf("\n=== SISTEMA DE INVENTARIO ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Consumir o '\n' deixado pelo scanf

        switch(opcao) {
            case 1:
                inserirItem(mochila, &total);
                listarItens(mochila, total);
                break;
            case 2:
                removerItem(mochila, &total);
                listarItens(mochila, total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}

// Função para inserir item na mochila
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\nDigite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o '\n'

    printf("Digite o tipo do item: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpar o buffer

    mochila[*total] = novo; // Adiciona no vetor
    (*total)++;             // Incrementa o total

    printf("\nItem adicionado com sucesso!\n");
}

// Função para remover item da mochila
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nMochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem nao encontrado!\n");
        return;
    }

    // "Desloca" os itens para preencher a posição removida
    for (int i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--; // Atualiza quantidade
    printf("\nItem removido com sucesso!\n");
}

// Função para listar itens
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA ---\n");
    for (int i = 0; i < total; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para buscar item (busca sequencial)
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nMochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}
