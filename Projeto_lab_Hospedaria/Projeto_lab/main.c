
// Neste projeto, desenvolvemos um sistema de gerenciamento para um pequeno hotel, com o objetivo de melhor atender seus clientes, 
// agilizar o acesso � disponibilidade de quartos e controlar as datas de entrada e sa�da dos h�spedes.O sistema permite o gerenciamento de hospedagens, reservas,
// quartos e dados dos clientes.Utilizamos arquivos de formato texto(csv) e arquivos bin�rios para armazenar os dados.
// A organiza��o do projeto foi realizada por meio de diversas fun��es implementadas em arquivos - fonte separados, garantindo uma estrutura clara e modular.Adicionalmente, 
// inserimos coment�rios nos arquivos - fonte para facilitar a compreens�o do c�digo.Este projeto foi desenvolvido por :
//
// * Bernardo Vieira Barros
// * Daniel Vieira Soares
// * Marcella Silva dos Santos Guimar�es
// * Maria Gabriely Rodrigues Riss�o


#include <stdio.h>
#include "menu.h"
#include "validarInput.h"

int main() {
    int opcao;
    limparTela();
    
    do {
        opcao = exibirMenu();
        executarOpcao(opcao);

    } while (opcao != 5);  // Continue at� que a op��o escolhida seja "Sair"

    return 0;
}





