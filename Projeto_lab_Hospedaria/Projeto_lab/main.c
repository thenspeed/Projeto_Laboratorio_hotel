

/*
typedef struct {
    int dia;
    int mes;
    int ano;
} DataCheckin;

typedef struct {
    int dia;
    int mes;
    int ano;
} DataCheckout;

typedef struct {
    char cpf[13];
    char nome[50];
    int dia;
    int mes;
    int ano;
    int idade;
    char endereco[100];
    char cidade[100];
    char estado[2];
} Pessoa;
*/



#include <stdio.h>

#include "menu.h"

int main() {
    int opcao;

    do {
        opcao = exibirMenu();
        executarOpcao(opcao);

    } while (opcao != 5);  // Continue até que a opção escolhida seja "Sair"

    return 0;
}





