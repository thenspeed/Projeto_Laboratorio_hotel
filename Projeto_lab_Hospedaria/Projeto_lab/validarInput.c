#include <stdlib.h>
#include <string.h>
#include "validarInput.h"

// Função para validar a entrada de um número inteiro
int validarInputInteiro(char mensagem[]) {
    int valor;

    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            break;
        }
        else {
            printf("Entrada inválida. Por favor, digite um valor válido.\n");
            while (getchar() != '\n');  // Limpar o buffer de entrada
        }
    }

    return valor;
}

// Função para verificar se um CPF existe em um arquivo
int cpfExiste(const char* cpf, FILE* arquivo) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        char cpfArquivo[14];
        sscanf(buffer, "%13[^;]", cpfArquivo);
        if (strcmp(cpf, cpfArquivo) == 0) {
            return 1; // CPF encontrado
        }
    }
    return 0; // CPF não encontrado
}

// Função para imprimir um texto cercado por caracteres '+'
void imprimirTextoCercado(char texto[], int tamanho) {
   
    printf(" \n");
    for (int i = 0; i < tamanho + 4; i++) {
        printf("+");
    }
    printf("\n");

    // Imprime o texto cercado por caracteres '+'
    printf("+ ");
    printf("%s", texto);
    printf(" +\n");


    // Imprime linha inferior de caracteres '+'
    for (int i = 0; i < tamanho + 4; i++) {
        printf("+");
    }
    printf("\n");
    printf(" \n");
}

// Função para limpar a tela do console
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}