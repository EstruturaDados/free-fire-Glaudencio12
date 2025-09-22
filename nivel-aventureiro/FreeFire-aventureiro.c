#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== DEFINIÇÕES ====================
#define MAX_ITENS 10 // Capacidade máxima do vetor

// Struct do Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct do nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==================== VARIÁVEIS GLOBAIS ====================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ==================== FUNÇÕES PARA VETOR ====================
void inserirItemVetor(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nMochila cheia (vetor)!\n");
        return;
    }

    Item novo;
    printf("\nNome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*total] = novo;
    (*total)++;
    printf("\nItem inserido no vetor!\n");
}

void removerItemVetor(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nMochila vazia (vetor)!\n");
        return;
    }

    char nome[30];
    printf("\nNome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("\nItem removido do vetor!\n");
            return;
        }
    }
    printf("\nItem nao encontrado no vetor!\n");
}

void listarItensVetor(Item mochila[], int total) {
    if (total == 0) {
        printf("\nMochila vazia (vetor)!\n");
        return;
    }
    printf("\n--- ITENS (VETOR) ---\n");
    for (int i = 0; i < total; i++) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Ordenação por Bubble Sort
void ordenarVetor(Item mochila[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\nVetor ordenado por nome!\n");
}

// Busca sequencial
void buscarSequencialVetor(Item mochila[], int total) {
    char nome[30];
    printf("\nNome do item para buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    comparacoesSequencial = 0;

    for (int i = 0; i < total; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado (Sequencial - Vetor)!\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparacoes: %d\n", comparacoesSequencial);
            return;
        }
    }
    printf("\nItem nao encontrado (Comparacoes: %d)\n", comparacoesSequencial);
}

// Busca binária
void buscarBinariaVetor(Item mochila[], int total) {
    char nome[30];
    printf("\nNome do item para buscar (binaria): ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int esq = 0, dir = total - 1;
    comparacoesBinaria = 0;

    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("\nItem encontrado (Binaria - Vetor)!\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            printf("Comparacoes: %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    printf("\nItem nao encontrado (Comparacoes: %d)\n", comparacoesBinaria);
}

// ==================== FUNÇÕES PARA LISTA ====================
void inserirItemLista(No **inicio) {
    No *novo = (No*) malloc(sizeof(No));

    printf("\nNome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *inicio;
    *inicio = novo;

    printf("\nItem inserido na lista!\n");
}

void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char nome[30];
    printf("\nNome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nItem nao encontrado na lista!\n");
        return;
    }

    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("\nItem removido da lista!\n");
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    printf("\n--- ITENS (LISTA) ---\n");
    No *temp = inicio;
    while (temp != NULL) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n",
               temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
        temp = temp->proximo;
    }
}

void buscarSequencialLista(No *inicio) {
    char nome[30];
    printf("\nNome do item para buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    comparacoesSequencial = 0;

    No *temp = inicio;
    while (temp != NULL) {
        comparacoesSequencial++;
        if (strcmp(temp->dados.nome, nome) == 0) {
            printf("\nItem encontrado (Sequencial - Lista)!\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
            printf("Comparacoes: %d\n", comparacoesSequencial);
            return;
        }
        temp = temp->proximo;
    }
    printf("\nItem nao encontrado (Comparacoes: %d)\n", comparacoesSequencial);
}

// ==================== MENU PRINCIPAL ====================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int totalVetor = 0;
    No *mochilaLista = NULL;

    int estrutura, opcao;

    do {
        printf("\n=== SISTEMA DE INVENTARIO ===\n");
        printf("1 - Usar Vetor\n");
        printf("2 - Usar Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha a estrutura: ");
        scanf("%d", &estrutura);
        getchar();

        if (estrutura == 1) { // MENU VETOR
            do {
                printf("\n--- MENU VETOR ---\n");
                printf("1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar Sequencial\n5 - Ordenar\n6 - Buscar Binaria\n0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                getchar();

                switch (opcao) {
                    case 1: inserirItemVetor(mochilaVetor, &totalVetor); break;
                    case 2: removerItemVetor(mochilaVetor, &totalVetor); break;
                    case 3: listarItensVetor(mochilaVetor, totalVetor); break;
                    case 4: buscarSequencialVetor(mochilaVetor, totalVetor); break;
                    case 5: ordenarVetor(mochilaVetor, totalVetor); break;
                    case 6: buscarBinariaVetor(mochilaVetor, totalVetor); break;
                }
            } while (opcao != 0);
        }

        else if (estrutura == 2) { // MENU LISTA
            do {
                printf("\n--- MENU LISTA ---\n");
                printf("1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar Sequencial\n0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                getchar();

                switch (opcao) {
                    case 1: inserirItemLista(&mochilaLista); break;
                    case 2: removerItemLista(&mochilaLista); break;
                    case 3: listarItensLista(mochilaLista); break;
                    case 4: buscarSequencialLista(mochilaLista); break;
                }
            } while (opcao != 0);
        }

    } while (estrutura != 0);

    printf("\nEncerrando o programa...\n");
    return 0;
}
