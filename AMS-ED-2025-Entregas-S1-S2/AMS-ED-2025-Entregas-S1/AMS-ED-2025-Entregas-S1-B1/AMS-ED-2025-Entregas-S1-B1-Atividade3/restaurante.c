/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-3.                                */
/*             Objetivo: << Manipulação de Lista Ligada >>                          */
/*                                                                                  */
/*                                  Autor: Pedro Viterbo Zacchi.                    */
/*                                                                  Data:24/03/2025 */
/*----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    int numero;
    char cliente[50];
    char descricao[100];
    int quantidade;
    char status[20];
    struct Pedido *prox;
} Pedido;

Pedido* criarPedido(int numero, char cliente[], char descricao[], int quantidade, char status[]) {
    Pedido *novo = (Pedido*) malloc(sizeof(Pedido));
    if(novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    novo->numero = numero;
    strcpy(novo->cliente, cliente);
    strcpy(novo->descricao, descricao);
    novo->quantidade = quantidade;
    strcpy(novo->status, status);
    novo->prox = NULL;
    return novo;
}

void inserirPedido(Pedido **lista, int numero, char cliente[], char descricao[], int quantidade, char status[]) {
    Pedido *novo = criarPedido(numero, cliente, descricao, quantidade, status);
    if(*lista == NULL) {
        *lista = novo;
    } else {
        Pedido *aux = *lista;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    printf("Pedido inserido com sucesso!\n");
}

Pedido* obterPedido(Pedido *lista, int numero) {
    Pedido *aux = lista;
    while(aux != NULL) {
        if(aux->numero == numero) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void atualizarStatus(Pedido *lista, int numero, char novoStatus[]) {
    Pedido *pedido = obterPedido(lista, numero);
    if(pedido != NULL) {
        strcpy(pedido->status, novoStatus);
        printf("Status do pedido %d atualizado para %s.\n", numero, novoStatus);
    } else {
        printf("Pedido %d nao encontrado.\n", numero);
    }
}

void deletarPedido(Pedido **lista, int numero) {
    Pedido *aux = *lista, *anterior = NULL;
    while(aux != NULL) {
        if(aux->numero == numero) {
            if(anterior == NULL) {
                *lista = aux->prox;
            } else {
                anterior->prox = aux->prox;
            }
            free(aux);
            printf("Pedido %d deletado com sucesso.\n", numero);
            return;
        }
        anterior = aux;
        aux = aux->prox;
    }
    printf("Pedido %d nao encontrado.\n", numero);
}

void listarPedidos(Pedido *lista) {
    if(lista == NULL) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    Pedido *aux = lista;
    while(aux != NULL) {
        printf("Numero: %d\n", aux->numero);
        printf("Cliente: %s\n", aux->cliente);
        printf("Descricao: %s\n", aux->descricao);
        printf("Quantidade: %d\n", aux->quantidade);
        printf("Status: %s\n", aux->status);
        printf("--------------------------\n");
        aux = aux->prox;
    }
}

void liberarLista(Pedido **lista) {
    Pedido *aux = *lista;
    while(aux != NULL) {
        Pedido *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    *lista = NULL;
    printf("Memoria liberada com sucesso!\n");
}

int main() {
    Pedido *listaPedidos = NULL;
    int opcao, numero, quantidade;
    char cliente[50], descricao[100], status[20], novoStatus[20];

    do {
        printf("\nSistema de Gerenciamento de Pedidos\n");
        printf("1. Inserir Pedido\n");
        printf("2. Obter Pedido\n");
        printf("3. Atualizar Status do Pedido\n");
        printf("4. Deletar Pedido\n");
        printf("5. Listar Pedidos\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                printf("Digite o numero do pedido: ");
                scanf("%d", &numero);
                getchar();
                printf("Digite o nome do cliente: ");
                fgets(cliente, sizeof(cliente), stdin);
                cliente[strcspn(cliente, "\n")] = '\0';
                printf("Digite a descricao do prato: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0';
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                getchar();
                printf("Digite o status do pedido (pendente, em preparo, pronto, entregue): ");
                fgets(status, sizeof(status), stdin);
                status[strcspn(status, "\n")] = '\0';
                inserirPedido(&listaPedidos, numero, cliente, descricao, quantidade, status);
                break;
            case 2: {
                printf("Digite o numero do pedido para obter: ");
                scanf("%d", &numero);
                getchar();
                Pedido *pedido = obterPedido(listaPedidos, numero);
                if(pedido != NULL) {
                    printf("Pedido encontrado:\n");
                    printf("Numero: %d\n", pedido->numero);
                    printf("Cliente: %s\n", pedido->cliente);
                    printf("Descricao: %s\n", pedido->descricao);
                    printf("Quantidade: %d\n", pedido->quantidade);
                    printf("Status: %s\n", pedido->status);
                } else {
                    printf("Pedido %d nao encontrado.\n", numero);
                }
                break;
            }
            case 3:
                printf("Digite o numero do pedido para atualizar o status: ");
                scanf("%d", &numero);
                getchar();
                printf("Digite o novo status: ");
                fgets(novoStatus, sizeof(novoStatus), stdin);
                novoStatus[strcspn(novoStatus, "\n")] = '\0';
                atualizarStatus(listaPedidos, numero, novoStatus);
                break;
            case 4:
                printf("Digite o numero do pedido para deletar: ");
                scanf("%d", &numero);
                getchar();
                deletarPedido(&listaPedidos, numero);
                break;
            case 5:
                listarPedidos(listaPedidos);
                break;
            case 6:
                liberarLista(&listaPedidos);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while(opcao != 6);

    return 0;
}
