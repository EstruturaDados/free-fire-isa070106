/*
  PLANO DE FUGA - CÓDIGO DA ILHA (NÍVEL MESTRE)
  ---------------------------------------------------------
  - Ordenação: Bubble (nome), Insertion (tipo), Selection (prioridade)
  - Busca Binária por nome (após ordenação)
  - Mostra tempo e comparações
  - Menu igual ao modelo do vídeo (com status e contagem)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_COMPONENTES 10
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

Componente mochila[MAX_COMPONENTES];
int qtdComponentes = 0;
bool estaOrdenadoPorNome = false;

/* ===================== FUNÇÕES AUXILIARES ===================== */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void mostrarCabecalho(void) {
    system("cls || clear");
    printf("====================================================\n");
    printf("PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("====================================================\n");
    printf("Itens na Mochila: %d/%d\n", qtdComponentes, MAX_COMPONENTES);
    printf("Status da Ordenacao por Nome: %s\n\n", estaOrdenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
}

/* ===================== OPERAÇÕES BÁSICAS ===================== */
void adicionarComponente(void) {
    if (qtdComponentes >= MAX_COMPONENTES) {
        printf("\n⚠️ Mochila cheia! Remova algo antes de adicionar.\n");
        pausar();
        return;
    }

    Componente c;
    printf("\nNome do componente: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Tipo do componente: ");
    fgets(c.tipo, sizeof(c.tipo), stdin);
    c.tipo[strcspn(c.tipo, "\n")] = '\0';

    printf("Prioridade (1-10): ");
    scanf("%d", &c.prioridade);
    limparBuffer();

    mochila[qtdComponentes++] = c;
    estaOrdenadoPorNome = false;
    printf("\n✅ Componente adicionado!\n");
    pausar();
}

void descartarComponente(void) {
    if (qtdComponentes == 0) {
        printf("\n⚠️ Mochila vazia!\n");
        pausar();
        return;
    }

    char nome[TAM_NOME];
    printf("\nDigite o nome do componente para descartar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < qtdComponentes; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int j = encontrado; j < qtdComponentes - 1; j++) {
            mochila[j] = mochila[j + 1];
        }
        qtdComponentes--;
        printf("\n🗑️ Componente removido com sucesso!\n");
    } else {
        printf("\n❌ Componente nao encontrado!\n");
    }
    estaOrdenadoPorNome = false;
    pausar();
}

void listarComponentes(void) {
    if (qtdComponentes == 0) {
        printf("\n⚠️ Nenhum componente cadastrado!\n");
        pausar();
        return;
    }

    printf("\n%-20s | %-15s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < qtdComponentes; i++) {
        printf("%-20s | %-15s | %2d\n", mochila[i].nome, mochila[i].tipo, mochila[i].prioridade);
    }
    printf("----------------------------------------------------\n");
    pausar();
}

/* ===================== ORDENAÇÕES ===================== */
void bubbleSortPorNome(void) {
    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < qtdComponentes - 1; i++) {
        for (int j = 0; j < qtdComponentes - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Componente tmp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = tmp;
            }
        }
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("\n✅ Mochila ordenada por NOME (Bubble Sort)");
    printf("\nComparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
    estaOrdenadoPorNome = true;
    pausar();
}

void insertionSortPorTipo(void) {
    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < qtdComponentes; i++) {
        Componente chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("\n✅ Mochila ordenada por TIPO (Insertion Sort)");
    printf("\nComparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
    estaOrdenadoPorNome = false;
    pausar();
}

void selectionSortPorPrioridade(void) {
    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < qtdComponentes - 1; i++) {
        int idxMaior = i;
        for (int j = i + 1; j < qtdComponentes; j++) {
            comparacoes++;
            if (mochila[j].prioridade > mochila[idxMaior].prioridade)
                idxMaior = j;
        }
        if (idxMaior != i) {
            Componente tmp = mochila[i];
            mochila[i] = mochila[idxMaior];
            mochila[idxMaior] = tmp;
        }
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("\n✅ Mochila ordenada por PRIORIDADE (Selection Sort)");
    printf("\nComparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
    estaOrdenadoPorNome = false;
    pausar();
}

/* ===================== BUSCA BINÁRIA ===================== */
void buscaBinariaPorNome(void) {
    if (!estaOrdenadoPorNome) {
        printf("\n⚠️ Para usar a busca binaria, ordene por nome primeiro!\n");
        pausar();
        return;
    }

    char chave[TAM_NOME];
    printf("\nDigite o nome do componente-chave: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int ini = 0, fim = qtdComponentes - 1, meio;
    long comparacoes = 0;
    clock_t inicio = clock();

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        comparacoes++;
        int cmp = strcmp(chave, mochila[meio].nome);
        if (cmp == 0) {
            double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
            printf("\n🔎 Componente encontrado!\n");
            printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].prioridade);
            printf("Comparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
            pausar();
            return;
        } else if (cmp < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("\n❌ Componente '%s' nao encontrado!\n", chave);
    printf("Comparacoes: %ld | Tempo: %.6f s\n", comparacoes, tempo);
    pausar();
}

/* ===================== MENU PRINCIPAL ===================== */
void menuPrincipal(void) {
    int opc;
    do {
        mostrarCabecalho();
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("----------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opc);
        limparBuffer();

        switch (opc) {
            case 1: adicionarComponente(); break;
            case 2: descartarComponente(); break;
            case 3: listarComponentes(); break;
            case 4:
                printf("\nEscolha o criterio de ordenacao:\n");
                printf("1 - Bubble Sort (Nome)\n");
                printf("2 - Insertion Sort (Tipo)\n");
                printf("3 - Selection Sort (Prioridade)\n");
                printf("Opcao: ");
                int metodo;
                scanf("%d", &metodo);
                limparBuffer();
                if (metodo == 1) bubbleSortPorNome();
                else if (metodo == 2) insertionSortPorTipo();
                else if (metodo == 3) selectionSortPorPrioridade();
                else printf("\nOpcao invalida!\n"), pausar();
                break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("\n🚀 Torre de fuga ativada! Fim da missao.\n"); break;
            default: printf("\nOpcao invalida!\n"), pausar();
        }
    } while (opc != 0);
}

/* ===================== MAIN ===================== */
int main(void) {
    menuPrincipal();
    return 0;
}

