#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ---------------------------------------------------------------
// CÓDIGO DA ILHA – NÍVEL NOVATO
// Sistema de Inventário Inicial (Mochila de Loot)
// ---------------------------------------------------------------
// Este programa simula a coleta e o gerenciamento básico de recursos
// essenciais do jogador logo após pousar na ilha. O sistema utiliza
// estruturas de dados compostas (structs) e listas sequenciais para
// representar os itens armazenados na mochila.
// ---------------------------------------------------------------

// Definição da estrutura Item
// Armazena as informações essenciais de cada recurso coletado.
typedef struct {
    char nome[30];      // Nome do item (ex: pistola, kit médico)
    char tipo[20];      // Tipo do item (ex: arma, munição, cura)
    int quantidade;     // Quantidade disponível do item
} Item;

// Constante que define o limite máximo de itens na mochila
#define MAX_ITENS 10

// ---------------------------------------------------------------
// Protótipos das funções
// ---------------------------------------------------------------
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

// ---------------------------------------------------------------
// Função principal
// ---------------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS]; // Vetor de structs que representa a mochila
    int qtd = 0;             // Quantidade atual de itens cadastrados
    int opcao;               // Controle de menu

    printf("=============================================\n");
    printf("     CÓDIGO DA ILHA - NÍVEL NOVATO 🏝️\n");
    printf("     Sistema de Inventário Inicial\n");
    printf("=============================================\n");

    do {
        printf("\nMenu principal:\n");
        printf("1 - Adicionar item à mochila\n");
        printf("2 - Remover item da mochila\n");
        printf("3 - Listar todos os itens\n");
        printf("4 - Buscar item por nome\n");
        printf("0 - Sair do sistema\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nEncerrando o sistema... Boa sorte na ilha! 🌴\n");
                break;
            default:
                printf("\n⚠️ Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}

// ---------------------------------------------------------------
// Função: inserirItem()
// Adiciona um novo item à mochila, se houver espaço disponível.
// ---------------------------------------------------------------
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o '\n'

    printf("Digite o tipo do item (arma, munição, cura, etc): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\n✅ Item adicionado com sucesso!\n");
    listarItens(mochila, *qtd);
}

// ---------------------------------------------------------------
// Função: removerItem()
// Remove um item da mochila com base no nome informado.
// ---------------------------------------------------------------
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nA mochila está vazia! Nenhum item para remover.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int j = encontrado; j < *qtd - 1; j++) {
            mochila[j] = mochila[j + 1];
        }
        (*qtd)--;
        printf("\n🗑️ Item '%s' removido com sucesso!\n", nome);
    } else {
        printf("\n❌ Item não encontrado!\n");
    }

    listarItens(mochila, *qtd);
}

// ---------------------------------------------------------------
// Função: listarItens()
// Exibe todos os itens registrados na mochila.
// ---------------------------------------------------------------
void listarItens(Item mochila[], int qtd) {
    printf("\n========= ITENS NA MOCHILA =========\n");

    if (qtd == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// ---------------------------------------------------------------
// Função: buscarItem()
// Realiza uma busca sequencial pelo nome informado e exibe os dados.
// ---------------------------------------------------------------
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n🔎 Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item não encontrado!\n");
}
