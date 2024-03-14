
// Neste projeto, desenvolvemos um sistema de gerenciamento para um pequeno hotel, com o objetivo de melhor atender seus clientes, 
// agilizar o acesso à disponibilidade de quartos e controlar as datas de entrada e saída dos hóspedes.O sistema permite o gerenciamento de hospedagens, reservas,
// quartos e dados dos clientes.Utilizamos arquivos de formato texto(csv) e arquivos binários para armazenar os dados.
// A organização do projeto foi realizada por meio de diversas funções implementadas em arquivos - fonte separados, garantindo uma estrutura clara e modular.Adicionalmente, 
// inserimos comentários nos arquivos - fonte para facilitar a compreensão do código.Este projeto foi desenvolvido por :
//
// * Bernardo Vieira Barros
// * Daniel Vieira Soares
// * Marcella Silva dos Santos Guimarães
// * Maria Gabriely Rodrigues Rissão


#include <stdio.h>
#include "menu.h"
#include "validarInput.h"

int main() {
    int opcao;
    limparTela();
    
    do {
        opcao = exibirMenu();
        executarOpcao(opcao);

    } while (opcao != 5);  // Continue até que a opção escolhida seja "Sair"

    return 0;
}





