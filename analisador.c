#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct no {
    char algarismo;
    struct no* prox;
}No;

No* empilhar(No* pilha, char op) {
    No* novo = malloc(sizeof(No));
    novo->algarismo = op;
    novo->prox = pilha;
    return novo; 
}

char desempilhar(No** pilha) {
    char operador = (*pilha)->algarismo;
    No* tmp = *pilha;
    *pilha = (*pilha)->prox;
    free(tmp);
    return operador;
}

void getExpressao(char expressao[]) {
    printf("> ");
    scanf("%s", expressao);
}

int getOp(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int prioridade(char op) {
    if (op == '+' || op == '-') return 1; //menor prioridade
    if (op == '*' || op == '/') return 2; //maior prioridade
    return 0;
}

void checaExpressao(char expressao[]) {
    int qntdOperador = 0;
    int qntdAlgarismo = 0;

    for (int i = 0; expressao[i] != '\0'; i++) {
        char atual = expressao[i];
        if (isdigit(atual)) {
            qntdAlgarismo++;
        } else if (getOp(atual)) {
            qntdOperador++;
        }
    }
    
    if (qntdOperador >= qntdAlgarismo) printf("Erro > Excesso de operadores.\n");
    if (qntdAlgarismo > qntdOperador + 1) printf("Erro > Excesso de algoritmos.\n");

}

int main() {
    char expressao[50];
    getExpressao(expressao);

    checaExpressao(expressao);

    No* pilhaAlgarismos = NULL;

    for (int i = 0; expressao[i] != '\0'; i++) {
        char atual = expressao[i];

        if (isdigit(atual)) {
            printf("%c", atual);

        } else if (getOp(atual)) {
            while (pilhaAlgarismos != NULL && getOp(pilhaAlgarismos->algarismo) && prioridade(pilhaAlgarismos->algarismo) >= prioridade(atual)) {
                char operador = desempilhar(&pilhaAlgarismos);
                printf("%c", operador);
            }

            pilhaAlgarismos = empilhar(pilhaAlgarismos, atual);
        }
    
    }

    while(pilhaAlgarismos != NULL) {
        char operador = desempilhar(&pilhaAlgarismos);
        printf("%c", operador);
    }

    printf("\n");

    return 0;
} 