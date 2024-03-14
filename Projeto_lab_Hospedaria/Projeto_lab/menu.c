#include <stdio.h>
#include "menu.h"
#include "validarInput.h"
#include "cliente.h"
#include "reserva.h"
#include "hospedagem.h"
#include "quarto.h"

// Função para exibir o menu principal e obter a opção escolhida pelo usuário
int exibirMenu() {
    int opcao;

    imprimirTextoCercado("Sistema de Gerenciamento Hoteleiro", strlen("Sistema de Gerenciamento Hoteleiro"));
    printf("1: Quartos\n");
    printf("2: Clientes\n");
    printf("3: Reservas\n");
    printf("4: Hospedagens\n");
    printf("5: Sair (fechar o programa)\n");
    printf("Escolha uma opcao (1-5): ");

    opcao = validarInputInteiro("");

    return opcao;
}

// Função para executar a opção escolhida pelo usuário
void executarOpcao(int opcao) {
    char cpf[14]; // Variável para armazenar o CPF do cliente
    limparTela();

    switch (opcao) {
    case 1:
        imprimirTextoCercado("Opcao 1 selecionada: Quartos", strlen("Opcao 1 selecionada: Quartos"));
        printf("1: Novo Quarto\n");
        printf("2: Excluir Quarto\n");
        printf("3: Alterar Quarto\n");
        printf("4: Sair (Voltar ao menu principal)\n");
        printf("Escolha uma opcao (1-4): ");
        opcao = validarInputInteiro("");
        switch (opcao) {
        case 1:
            cadastrarQuartos();
            break;
        case 2:
            printf("Digite a identificacao do quarto que deseja excluir: ");
            scanf("%d", &opcao);
            excluirQuarto(opcao);
            break;
        case 3:
            printf("Digite a identificacao do quarto que deseja alterar: ");
            scanf("%d", &opcao);
            alterarQuarto(opcao);
            break;
        case 4:
            break;
        default:
            printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
            break;
        }
        break;

    case 2:
        imprimirTextoCercado("Opcao 2 selecionada: Cadastro de clientes", strlen("Opcao 2 selecionada: Cadastro de clientes"));
        printf("1: Novo Cliente\n");
        printf("2: Alterar Cliente\n");
        printf("3: Remover Cliente\n");
        printf("4: Sair (Voltar ao menu principal)\n");
        printf("Escolha uma opcao (1-4): ");
        opcao = validarInputInteiro("");
        switch (opcao) {
        case 1:
            cadastrarClientes();
            break;
        case 2:
            printf("Digite o CPF do cliente que deseja alterar: ");
            scanf("%13s", cpf);
            alterarCliente(cpf);
            break;
        case 3:
            printf("Digite o CPF do cliente que deseja excluir: ");
            scanf("%13s", cpf);
            removerCliente(cpf);
            break;
        case 4:
            break;
        default:
            printf("Opcao invalida. Por favor, escolha uma opcao válida.\n");
            break;
        }
        break;

    case 3:
        imprimirTextoCercado("Opcao 3 selecionada: Reservas", strlen("Opcao 3 selecionada: Reservas"));
        printf("1: Reservar quarto\n");
        printf("2: Cancelar reserva\n");
        printf("3: Buscar Reserva\n");
        printf("4: Quartos disponiveis para reserva\n");
        printf("5: Sair (Voltar ao menu principal)\n");
        printf("Escolha uma opcao (1-4): ");
        opcao = validarInputInteiro("");
        switch (opcao) {
        case 1:
            cadastrarReserva();
            break;
        case 2:
            excluirReserva();
            break;
        case 3:
            consultarReservasPorCPF();
            break;
        case 4:
            verificarDisponibilidade();
            break;
        default:
            printf("Opcao invalida. Por favor, escolha uma opcao válida.\n");
            break;
        }
        break;

    case 4:
        imprimirTextoCercado("Opcao 4 selecionada: Hospedagens", strlen("Opcao 4 selecionada: Hospedagens"));
        printf("1: Check-in de cliente\n");
        printf("2: Check-out de cliente\n");
        printf("3: Buscar hospedagem do cliente\n");
        printf("4: Sair (Voltar ao menu principal)\n");
        printf("Escolha uma opcao (1-4): ");
        opcao = validarInputInteiro("");
        switch (opcao) {
        case 1:
            // Solicitar o código da reserva para iniciar a hospedagem
            printf("Digite o codigo da reserva para iniciar a hospedagem: ");
            int codigoReservaCheckIn;
            scanf("%d", &codigoReservaCheckIn);
            iniciarHospedagem(codigoReservaCheckIn);
            break;

        case 2:
            //// Solicitar o código da reserva para finalizar a hospedagem
            printf("Digite o codigo da reserva para finalizar a hospedagem: ");
            int codigoReservaCheckOut;
            scanf("%d", &codigoReservaCheckOut);
            finalizarHospedagem(codigoReservaCheckOut);
            break;

        case 3:
            // Solicitar o CPF do cliente para mostrar as hospedagens
            printf("Digite o CPF do cliente para mostrar as hospedagens: ");
            char cpfMostrarHospedagens[14];
            scanf("%13s", cpfMostrarHospedagens);
            mostrarHospedagensPorCliente(cpfMostrarHospedagens);
            break;
        case 4:
            break;
        default:
            printf("Opcao invalida. Por favor, escolha uma opcao válida.\n");
            break;
        }
        break;


    case 5:
        imprimirTextoCercado("Saindo do programa. Ate logo!", strlen("Saindo do programa. Ate logo!"));
        break;

    default:
        printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
        break;
    }
}
