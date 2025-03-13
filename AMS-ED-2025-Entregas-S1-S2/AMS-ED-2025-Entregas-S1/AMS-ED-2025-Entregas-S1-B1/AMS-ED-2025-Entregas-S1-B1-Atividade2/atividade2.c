/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2.                                */
/*             Objetivo: << Manipulação de array com ponteiro >>                    */
/*                                                                                  */
/*                                  Autor: Pedro Viterbo Zacchi.                    */
/*                                                                  Data:12/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50


struct Candidato {
    char nome[100];
    float PE[4], AC[5], PP[10], EB[3];
    float nota_final;
    struct Candidato *prox;  
};


void inserir_notas(float *notas, int tamanho, const char *descricao) {
    printf("\nDigite as %d notas para %s (valores entre 0.0 e 10.0):\n", tamanho, descricao);

    for (int i = 0; i < tamanho; i++) {
        do {
            printf("Nota %d: ", i + 1);
            scanf("%f", &notas[i]);

            if (notas[i] < 0.0 || notas[i] > 10.0) {
                printf("Erro: A nota deve estar entre 0.0 e 10.0. Tente novamente.\n");
            }

        } while (notas[i] < 0.0 || notas[i] > 10.0);
    }
}


float calcular_nota(float *notas, int tamanho) {
    float maior = notas[0], menor = notas[0], soma = 0.0;

    for (int i = 0; i < tamanho; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }

    return (soma - maior - menor) / (tamanho - 2);
}


void inserir_candidato(struct Candidato **inicio) {
    struct Candidato *novoCandidato = (struct Candidato*)malloc(sizeof(struct Candidato));
    if (novoCandidato == NULL) {
        printf("Erro ao alocar memória para o candidato!\n");
        return;
    }

    printf("\nNome do candidato: ");
    scanf(" %[^\n]", novoCandidato->nome);  

    inserir_notas(novoCandidato->PE, 4, "Prova Escrita (PE)");
    inserir_notas(novoCandidato->AC, 5, "Análise Curricular (AC)");
    inserir_notas(novoCandidato->PP, 10, "Prova Prática (PP)");
    inserir_notas(novoCandidato->EB, 3, "Entrevista em Banca Avaliadora (EB)");

    
    float nota_PE = calcular_nota(novoCandidato->PE, 4);
    float nota_AC = calcular_nota(novoCandidato->AC, 5);
    float nota_PP = calcular_nota(novoCandidato->PP, 10);
    float nota_EB = calcular_nota(novoCandidato->EB, 3);

    novoCandidato->nota_final = (nota_PE * 0.3) + (nota_AC * 0.1) + (nota_PP * 0.4) + (nota_EB * 0.2);

    
    novoCandidato->prox = *inicio;
    *inicio = novoCandidato;
}


void classificar_candidatos(struct Candidato *inicio) {
    struct Candidato *i, *j;
    float tempNF;
    char tempNome[100];

    for (i = inicio; i != NULL; i = i->prox) {
        for (j = i->prox; j != NULL; j = j->prox) {
            if (i->nota_final < j->nota_final) {
                tempNF = i->nota_final;
                i->nota_final = j->nota_final;
                j->nota_final = tempNF;

                strcpy(tempNome, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, tempNome);
            }
        }
    }
}


void exibir_classificacao(struct Candidato *inicio) {
    struct Candidato *ptr = inicio;
    printf("\n--- Classificação Final ---\n");
    int i = 0;

    while (ptr != NULL && i < 5) {
        printf("%dº - %s | Nota Final: %.2f\n", i + 1, ptr->nome, ptr->nota_final);
        ptr = ptr->prox;
        i++;
    }
}

int main() {
    struct Candidato *inicio = NULL;
    int num_candidatos = 0;
    char continuar;

  

    do {
        inserir_candidato(&inicio);
        num_candidatos++;

        if (num_candidatos >= MAX_CANDIDATOS) {
            printf("\nNúmero máximo de candidatos atingido!\n");
            break;
        }

        printf("\nDeseja inserir outro candidato? (digite 's' ou 'n'): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    if (num_candidatos > 0) {
        classificar_candidatos(inicio);
        exibir_classificacao(inicio);
    } else {
        printf("Nenhum candidato foi inserido.\n");
    }

    // Libera a memória alocada para os candidatos
    struct Candidato *temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }

    return 0;
}

