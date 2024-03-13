#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int dia;
    int mes;
    int ano;
} DataNascimento;

//Função para remover um cliente cadastrado
int removerCliente(const char* cpf);

//Função para alterar o cadastro de um cliente
int alterarCliente(const char* cpf);

// Função para cadastrar clientes
int cadastrarClientes();

#endif
