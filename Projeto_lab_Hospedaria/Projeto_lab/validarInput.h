#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Função para validar a entrada de inteiros
int validarInputInteiro(char mensagem[]);

// Função para verificar se um CPF existe em um arquivo
int cpfExiste(const char* cpf, FILE* arquivo);

void imprimirTextoCercado(char texto[], int tamanho);

//Função para limpar o console
void limparTela();

#endif
