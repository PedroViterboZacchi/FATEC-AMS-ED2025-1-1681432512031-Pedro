/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-4.                                */
/*             Objetivo: << Manipulação de Pilha - Implementado HP12c >>            */
/*                                                                                  */
/*                                  Autor: Pedro Viterbo Zacchi.                    */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100      
#define MAX_STR 100  

typedef struct {
    double items[MAX];
    int topo;
} Pilha;

Pilha *criar_pilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

int vazia(Pilha *p) {
    return (p->topo == -1);
}

int cheia(Pilha *p) {
    return (p->topo == MAX - 1);
}

void push(Pilha *p, double valor) {
    if(cheia(p)) {
        printf("Erro: pilha cheia!\n");
        exit(1);
    }
    p->items[++(p->topo)] = valor;
}

double pop(Pilha *p) {
    if(vazia(p)) {
        printf("Erro: pilha vazia!\n");
        exit(1);
    }
    return p->items[(p->topo)--];
}

double top(Pilha *p) {
    if(vazia(p)) {
        printf("Erro: pilha vazia!\n");
        exit(1);
    }
    return p->items[p->topo];
}

typedef struct {
    char items[MAX][MAX_STR];
    int topo;
} PilhaStr;

PilhaStr *criar_pilha_str() {
    PilhaStr *p = (PilhaStr*) malloc(sizeof(PilhaStr));
    p->topo = -1;
    return p;
}

int vaziaStr(PilhaStr *p) {
    return (p->topo == -1);
}

int cheiaStr(PilhaStr *p) {
    return (p->topo == MAX - 1);
}

void pushStr(PilhaStr *p, char *str) {
    if(cheiaStr(p)) {
        printf("Erro: pilha de strings cheia!\n");
        exit(1);
    }
    p->topo++;
    strcpy(p->items[p->topo], str);
}

char* popStr(PilhaStr *p) {
    if(vaziaStr(p)) {
        printf("Erro: pilha de strings vazia!\n");
        exit(1);
    }
    return p->items[(p->topo)--];
}

int main() {
    char input[500];
    printf("Entre com a expressao em RPN (operandos e operadores separados por espaco):\n");
    fgets(input, sizeof(input), stdin);
    
    Pilha *numPilha = criar_pilha();
    PilhaStr *strPilha = criar_pilha_str();
    
    char *token = strtok(input, " \n");
    while(token != NULL) {
        if(strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
           strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            double op2 = pop(numPilha);
            double op1 = pop(numPilha);
            double result;
            if(strcmp(token, "+") == 0)
                result = op1 + op2;
            else if(strcmp(token, "-") == 0)
                result = op1 - op2;
            else if(strcmp(token, "*") == 0)
                result = op1 * op2;
            else if(strcmp(token, "/") == 0) {
                if(op2 == 0) {
                    printf("Erro: Divisao por zero!\n");
                    exit(1);
                }
                result = op1 / op2;
            }
            push(numPilha, result);
            
            char expr2[MAX_STR], expr1[MAX_STR];
            char newExpr[4 * MAX_STR];
            strcpy(expr2, popStr(strPilha));
            strcpy(expr1, popStr(strPilha));
            snprintf(newExpr, sizeof(newExpr), "(%s %s %s)", expr1, token, expr2);
            pushStr(strPilha, newExpr);
        } else {
            double valor = atof(token);
            push(numPilha, valor);
            pushStr(strPilha, token);
        }
        token = strtok(NULL, " \n");
    }
    
    if(numPilha->topo != 0) {
        printf("Erro: Expressao invalida!\n");
        exit(1);
    }
    
    double resultado = pop(numPilha);
    char *formula = popStr(strPilha);
    
    printf("Resultado: %g\n", resultado);
    printf("Expressao: %s\n", formula);
    
    free(numPilha);
    free(strPilha);
    
    return 0;
}
