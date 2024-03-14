#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Fun��o para validar a entrada de inteiros
int validarInputInteiro(char mensagem[]);

// Fun��o para verificar se um CPF existe em um arquivo
int cpfExiste(const char* cpf, FILE* arquivo);

void imprimirTextoCercado(char texto[], int tamanho);

//Fun��o para limpar o console
void limparTela();

#endif
