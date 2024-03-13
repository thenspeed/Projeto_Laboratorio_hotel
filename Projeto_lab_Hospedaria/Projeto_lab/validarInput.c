#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validarInput.h"

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

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
