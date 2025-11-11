#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ---------------------------------------------------------------
// CÓDIGO DA ILHA – NÍVEL INTERMEDIÁRIO
// Comparando Estruturas: Vetor x Lista Encadeada
// ---------------------------------------------------------------
// Este programa simula duas versões de mochila: uma baseada em vetor
// e outra em lista encadeada. O objetivo é comparar o desempenho das
// estruturas em operações de inserção, remoção, listagem e busca.
// ---------------------------------------------------------------

// ------------------------------
// Definição das estruturas
// ------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// ------------------------------
// Constantes e variáveis globais
// ------------------------------
#define MAX_ITENS 10
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ------------------------------
// Protótipos das funções
// ------------------------------
// Vetor
void inserirItemVetor(Item mochila[], int *qtd);
void removerItemVetor(Item mochila[], int *qtd);
void listarItensVetor(Item mochila[], int qtd);
int buscarSequencialVetor(Item mochila[], int qtd, char nome[]);
void ordenarVetor(Item mochila[], int qtd);
int buscarBinariaVetor(Item mochila[], int qtd, char nome[]);

// Lista encadeada
No* inserirItemLista(No *inicio);
No* removerItemLista(No *inicio);
void listarItensLista(No *inicio);
No* buscarItemLista(No *inicio, char nome[]);

// Utilitários
void limparTela();
void menuPrincipal();

// ---------------------------------------------------------------
// Função principal
// ---------------------------------------------------------------
int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtd = 0;
    No *mochilaLista = NULL;

    int opcaoEstrutura, opcaoOperacao;
    char nomeBusca[30];
    clock_t inicio, fim;
    double tempoExecucao;

    printf("=============================================\n");
    printf("     CÓDIGO DA ILHA - NÍVEL INTERMEDIÁRIO ⚙️\n");
    printf("     Comparando Vetor e Lista Encadeada\n");
    printf("=============================================\n");

    do {
        printf("\nEscolha a estrutura de dados:\n");
        printf("1 - Mochila com Vetor\n");
        printf("2 - Mochila com Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcaoEstrutura);
        getchar();

        switch(opcaoEstrutura) {
            case 1:
                do {
                    menuPrincipal();
                    scanf("%d", &opcaoOperacao);
                    getchar();

                    inicio = clock(); // mede tempo de execução
                    switch(opcaoOperacao) {
                        case 1: inserirItemVetor(mochilaVetor, &qtd); break;
                        case 2: removerItemVetor(mochilaVetor, &qtd); break;
                        case 3: listarItensVetor(mochilaVetor, qtd); break;
                        case 4:
                            printf("Digite o nome para busca sequencial: ");
                            fgets(nomeBusca, 30, stdin);
                            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                            buscarSequencialVetor(mochilaVetor, qtd, nomeBusca);
                            printf("Comparações realizadas: %d\n", comparacoesSequencial);
                            break;
                        case 5:
                            ordenarVetor(mochilaVetor, qtd);
                            printf("Itens ordenados por nome!\n");
                            printf("Digite o nome para busca binária: ");
                            fgets(nomeBusca, 30, stdin);
                            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                            buscarBinariaVetor(mochilaVetor, qtd, nomeBusca);
                            printf("Comparações realizadas: %d\n", comparacoesBinaria);
                            break;
                        case 0: printf("Voltando ao menu principal...\n"); break;
                        default: printf("Opção inválida!\n");
                    }
                    fim = clock();
                    tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    if (opcaoOperacao != 0)
                        printf("⏱️ Tempo de resposta: %.4f segundos\n", tempoExecucao);
                } while(opcaoOperacao != 0);
                break;

            case 2:
                do {
                    menuPrincipal();
                    scanf("%d", &opcaoOperacao);
                    getchar();

                    inicio = clock();
                    switch(opcaoOperacao) {
                        case 1: mochilaLista = inserirItemLista(mochilaLista); break;
                        case 2: mochilaLista = removerItemLista(mochilaLista); break;
                        case 3: listarItensLista(mochilaLista); break;
                        case 4:
                            printf("Digite o nome para buscar: ");
                            fgets(nomeBusca, 30, stdin);
                            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                            buscarItemLista(mochilaLista, nomeBusca);
                            printf("Comparações realizadas: %d\n", comparacoesSequencial);
                            break;
                        case 0: printf("Voltando ao menu principal...\n"); break;
                        default: printf("Opção inválida!\n");
                    }
                    fim = clock();
                    tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    if (opcaoOperacao != 0)
                        printf("⏱️ Tempo de resposta: %.4f segundos\n", tempoExecucao);
                } while(opcaoOperacao != 0);
                break;

            case 0:
                printf("Encerrando o sistema... 🏝️\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while(opcaoEstrutura != 0);

    return 0;
}

// ---------------------------------------------------------------
// UTILITÁRIOS
// ---------------------------------------------------------------
void menuPrincipal() {
    printf("\n=== MENU DE OPERAÇÕES ===\n");
    printf("1 - Inserir item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Buscar item (sequencial)\n");
    printf("5 - Ordenar e buscar (binária) [somente vetor]\n");
    printf("0 - Voltar\n");
    printf("Opção: ");
}

// ---------------------------------------------------------------
// FUNÇÕES – VERSÃO VETOR
// ---------------------------------------------------------------
void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo do item: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;
    printf("✅ Item adicionado!\n");
}

void removerItemVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("🗑️ Item removido!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

void listarItensVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n--- ITENS NO VETOR ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s | %s | Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int qtd, char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < qtd; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("🔎 Item encontrado: %s (%s) x%d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i;
        }
    }
    printf("❌ Item não encontrado!\n");
    return -1;
}

void ordenarVetor(Item mochila[], int qtd) {
    Item temp;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
}

int buscarBinariaVetor(Item mochila[], int qtd, char nome[]) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = qtd - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0) {
            printf("🔎 Item encontrado (busca binária): %s (%s) x%d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("❌ Item não encontrado!\n");
    return -1;
}

// ---------------------------------------------------------------
// FUNÇÕES – VERSÃO LISTA ENCADEADA
// ---------------------------------------------------------------
No* inserirItemLista(No *inicio) {
    No *novo = (No*)malloc(sizeof(No));
    printf("Nome do item: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo do item: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicio;
    printf("✅ Item adicionado à lista!\n");
    return novo;
}

No* removerItemLista(No *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia!\n");
        return inicio;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("❌ Item não encontrado!\n");
        return inicio;
    }

    if (anterior == NULL)
        inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("🗑️ Item removido da lista!\n");
    return inicio;
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    printf("\n--- ITENS NA LISTA ---\n");
    No *aux = inicio;
    int i = 1;
    while (aux != NULL) {
        printf("%d. %s | %s | Quantidade: %d\n", i, aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
        i++;
    }
}

No* buscarItemLista(No *inicio, char nome[]) {
    comparacoesSequencial = 0;
    No *aux = inicio;
    while (aux != NULL) {
        comparacoesSequencial++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("🔎 Item encontrado: %s (%s) x%d\n", aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
            return aux;
        }
        aux = aux->proximo;
    }
    printf("❌ Item não encontrado!\n");
    return NULL;
}
