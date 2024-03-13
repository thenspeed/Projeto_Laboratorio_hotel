#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int dia;
    int mes;
    int ano;
} DataNascimento;

//Fun��o para remover um cliente cadastrado
int removerCliente(const char* cpf);

//Fun��o para alterar o cadastro de um cliente
int alterarCliente(const char* cpf);

// Fun��o para cadastrar clientes
int cadastrarClientes();

#endif
