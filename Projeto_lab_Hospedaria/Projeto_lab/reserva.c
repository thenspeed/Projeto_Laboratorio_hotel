#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validarInput.h"

typedef struct {
    int identificacaoReserva;
    char cpfCliente[14];
    int checkInDia, checkInMes, checkInAno;
    int checkOutDia, checkOutMes, checkOutAno;
    char tipoQuarto[20];
    int identificacaoQuarto;
} Reserva;

typedef struct {
    int identificacao;
    int camasSolteiro;
    int camasCasal;
    char tipo[20];
    double precoDiaria;
    char status;
} Quarto;

typedef struct {
    int identificacaoReserva;
    char cpfCliente[14];
    int checkInDia, checkInMes, checkInAno;
    int checkOutDia, checkOutMes, checkOutAno;
    char tipoQuarto[20];
    int identificacaoQuarto;
} Reserva;




// Função para cadastrar reservas
int cadastrarReserva() {
    FILE* arquivo;
    Reserva reserva;

    arquivo = fopen("Reservas.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Reservas.txt\n");
        return 0;
    }

    printf("Identificacao da reserva (maior que 0): ");
    scanf("%d", &reserva.identificacaoReserva);

    // Validando identificacao da reserva maior que 0
    if (reserva.identificacaoReserva <= 0) {
        printf("A identificacao da reserva deve ser maior que 0.\n");
        fclose(arquivo);
        return 0;
    }

    printf("CPF do cliente (13 caracteres): ");
    scanf("%13s", reserva.cpfCliente);

    // Validando CPF
    // Implemente a validação do CPF conforme necessário

    printf("Data de Check-in (dia mes ano): ");
    scanf("%d %d %d", &reserva.checkInDia, &reserva.checkInMes, &reserva.checkInAno);

    printf("Data de Check-out (dia mes ano): ");
    scanf("%d %d %d", &reserva.checkOutDia, &reserva.checkOutMes, &reserva.checkOutAno);

    printf("Tipo de quarto (Single, Duplo, Triplo): ");
    scanf("%s", reserva.tipoQuarto);

    printf("Identificacao do quarto reservado: ");
    scanf("%d", &reserva.identificacaoQuarto);

    // Escreve os dados no arquivo separados por ";"
    fprintf(arquivo, "%d;%s;%d;%d;%d;%d;%d;%d;%s;%d\n",
        reserva.identificacaoReserva, reserva.cpfCliente,
        reserva.checkInDia, reserva.checkInMes, reserva.checkInAno,
        reserva.checkOutDia, reserva.checkOutMes, reserva.checkOutAno,
        reserva.tipoQuarto, reserva.identificacaoQuarto);

    // Fecha o arquivo
    fclose(arquivo);

    limparTela();
    printf("Cadastro da reserva concluido!\n");

    return 1;
}

// Função para consultar reservas por CPF do cliente
void consultarReservasPorCPF() {
    FILE* arquivo;
    char cpfConsulta[14];
    Reserva reserva;

    arquivo = fopen("Reservas.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Reservas.txt\n");
        return;
    }

    printf("Digite o CPF do cliente para consultar as reservas: ");
    scanf("%13s", cpfConsulta);

    printf("\nReservas associadas ao CPF %s:\n", cpfConsulta);

    while (fscanf(arquivo, "%d;%[^;];%d;%d;%d;%d;%d;%d;%[^;];%d\n",
        &reserva.identificacaoReserva, reserva.cpfCliente,
        &reserva.checkInDia, &reserva.checkInMes, &reserva.checkInAno,
        &reserva.checkOutDia, &reserva.checkOutMes, &reserva.checkOutAno,
        reserva.tipoQuarto, &reserva.identificacaoQuarto) == 10) {
        if (strcmp(reserva.cpfCliente, cpfConsulta) == 0) {
            printf("Identificacao da reserva: %d\n", reserva.identificacaoReserva);
            printf("Data de Check-in: %d/%d/%d\n", reserva.checkInDia, reserva.checkInMes, reserva.checkInAno);
            printf("Data de Check-out: %d/%d/%d\n", reserva.checkOutDia, reserva.checkOutMes, reserva.checkOutAno);
            printf("Tipo de quarto: %s\n", reserva.tipoQuarto);
            printf("Identificacao do quarto reservado: %d\n", reserva.identificacaoQuarto);
            printf("\n");
        }
    }

    fclose(arquivo);
}

void excluirReserva() {
    int opcaoCancelamento;
    limparTela();

    printf("Escolha a opcao de cancelamento:\n");
    printf("1: Pelo codigo da reserva\n");
    printf("2: Pelo CPF do cliente e data de check-in\n");
    printf("Escolha uma opcao (1-2): ");
    scanf("%d", &opcaoCancelamento);

    if (opcaoCancelamento == 1) {
        int codigoReserva;
        printf("Digite o codigo da reserva: ");
        scanf("%d", &codigoReserva);

        // Chama a função de cancelar reserva por código
        cancelarReservaPorCodigo(codigoReserva);
    }
    else if (opcaoCancelamento == 2) {
        char cpfCliente[14];
        int checkInDia, checkInMes, checkInAno;

        printf("Digite o CPF do cliente: ");
        scanf("%13s", cpfCliente);

        printf("Digite a data de check-in (dia mes ano): ");
        scanf("%d %d %d", &checkInDia, &checkInMes, &checkInAno);

        // Chama a função de cancelar reserva por CPF e data de check-in
        cancelarReservaPorCPF(cpfCliente, checkInDia, checkInMes, checkInAno);
    }
    else {
        printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
    }
}


// Função para verificar a disponibilidade de quartos
void verificarDisponibilidade() {
    FILE* arquivoQuartos;
    FILE* arquivoReservas;
    Quarto quarto;
    Reserva reserva;

    arquivoQuartos = fopen("Quartos.txt", "r");
    arquivoReservas = fopen("Reservas.txt", "r");

    if (arquivoQuartos == NULL || arquivoReservas == NULL) {
        printf("Erro ao abrir os arquivos Quartos.txt ou Reservas.txt\n");
        return;
    }

    // Coleta os dados para a verificação de disponibilidade
    char tipoQuarto[20];
    int checkInDia, checkInMes, checkInAno;
    int checkOutDia, checkOutMes, checkOutAno;

    printf("Digite o tipo de quarto desejado (Single, Duplo, Triplo): ");
    scanf("%s", tipoQuarto);

    printf("Digite a data de check-in (dia mes ano): ");
    scanf("%d %d %d", &checkInDia, &checkInMes, &checkInAno);

    printf("Digite a data de check-out (dia mes ano): ");
    scanf("%d %d %d", &checkOutDia, &checkOutMes, &checkOutAno);

    // Exibir cabeçalho da tabela
    printf("\nIdentificacao | Tipo | Preco Diaria | Status\n");
    printf("--------------------------------------------\n");

    while (fscanf(arquivoQuartos, "%d;%d;%d;%[^;];%lf;%c\n",
        &quarto.identificacao, &quarto.camasSolteiro, &quarto.camasCasal,
        quarto.tipo, &quarto.precoDiaria, &quarto.status) == 6) {

        int disponivel = 1;

        // Verificar se o quarto está reservado para as datas especificadas
        while (fscanf(arquivoReservas, "%d;%[^;];%d;%d;%d;%d;%d;%d;%[^;];%d\n",
            &reserva.identificacaoReserva, reserva.cpfCliente,
            &reserva.checkInDia, &reserva.checkInMes, &reserva.checkInAno,
            &reserva.checkOutDia, &reserva.checkOutMes, &reserva.checkOutAno,
            reserva.tipoQuarto, &reserva.identificacaoQuarto) == 10) {

            if (strcmp(reserva.tipoQuarto, tipoQuarto) == 0 &&
                ((checkInAno < reserva.checkOutAno) ||
                    (checkInAno == reserva.checkOutAno && checkInMes < reserva.checkOutMes) ||
                    (checkInAno == reserva.checkOutAno && checkInMes == reserva.checkOutMes && checkInDia < reserva.checkOutDia)) &&
                ((checkOutAno > reserva.checkInAno) ||
                    (checkOutAno == reserva.checkInAno && checkOutMes > reserva.checkInMes) ||
                    (checkOutAno == reserva.checkInAno && checkOutMes == reserva.checkInMes && checkOutDia > reserva.checkInDia))) {
                // Quarto está reservado para o período especificado
                disponivel = 0;
                break;
            }
        }

        // Voltar ao início do arquivo de reservas para a próxima iteração
        fseek(arquivoReservas, 0, SEEK_SET);

        // Exibir informações do quarto se estiver disponível
        if (disponivel) {
            printf("%13d | %s | %.2lf | %c\n", quarto.identificacao, quarto.tipo, quarto.precoDiaria, quarto.status);
        }
    }

    fclose(arquivoQuartos);
    fclose(arquivoReservas);
}




// Função para cancelar reserva por código
void cancelarReservaPorCodigo(int codigoReserva) {
    FILE* arquivoReservas;
    FILE* temp;
    Reserva reserva;

    arquivoReservas = fopen("Reservas.txt", "r");
    temp = fopen("temp.txt", "w");

    if (arquivoReservas == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos Reservas.txt ou temp.txt\n");
        return;
    }

    int reservaEncontrada = 0;

    // Percorre as reservas e copia para o arquivo temporário, excluindo a desejada
    while (fscanf(arquivoReservas, "%d;%[^;];%d;%d;%d;%d;%d;%d;%[^;];%d\n",
        &reserva.identificacaoReserva, reserva.cpfCliente,
        &reserva.checkInDia, &reserva.checkInMes, &reserva.checkInAno,
        &reserva.checkOutDia, &reserva.checkOutMes, &reserva.checkOutAno,
        reserva.tipoQuarto, &reserva.identificacaoQuarto) == 10) {

        if (reserva.identificacaoReserva == codigoReserva) {
            reservaEncontrada = 1;
            printf("Reserva encontrada e cancelada com sucesso.\n");
        }
        else {
            fprintf(temp, "%d;%s;%d;%d;%d;%d;%d;%d;%s;%d\n",
                reserva.identificacaoReserva, reserva.cpfCliente,
                reserva.checkInDia, reserva.checkInMes, reserva.checkInAno,
                reserva.checkOutDia, reserva.checkOutMes, reserva.checkOutAno,
                reserva.tipoQuarto, reserva.identificacaoQuarto);
        }
    }

    // Substitui o arquivo original pelo temporário
    fclose(arquivoReservas);
    fclose(temp);
    remove("Reservas.txt");
    rename("temp.txt", "Reservas.txt");

    if (!reservaEncontrada) {
        printf("Reserva nao encontrada com o codigo %d.\n", codigoReserva);
    }
}

// Função para cancelar reserva por CPF e data de check-in
void cancelarReservaPorCPF(char cpfCliente[14], int checkInDia, int checkInMes, int checkInAno) {
    FILE* arquivoReservas;
    FILE* temp;
    Reserva reserva;

    arquivoReservas = fopen("Reservas.txt", "r");
    temp = fopen("temp.txt", "w");

    if (arquivoReservas == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos Reservas.txt ou temp.txt\n");
        return;
    }

    int reservaEncontrada = 0;

    // Percorre as reservas e copia para o arquivo temporário, excluindo a desejada
    while (fscanf(arquivoReservas, "%d;%[^;];%d;%d;%d;%d;%d;%d;%[^;];%d\n",
        &reserva.identificacaoReserva, reserva.cpfCliente,
        &reserva.checkInDia, &reserva.checkInMes, &reserva.checkInAno,
        &reserva.checkOutDia, &reserva.checkOutMes, &reserva.checkOutAno,
        reserva.tipoQuarto, &reserva.identificacaoQuarto) == 10) {

        if (strcmp(reserva.cpfCliente, cpfCliente) == 0 &&
            reserva.checkInDia == checkInDia &&
            reserva.checkInMes == checkInMes &&
            reserva.checkInAno == checkInAno) {
            reservaEncontrada = 1;
            printf("Reserva encontrada e cancelada com sucesso.\n");
        }
        else {
            fprintf(temp, "%d;%s;%d;%d;%d;%d;%d;%d;%s;%d\n",
                reserva.identificacaoReserva, reserva.cpfCliente,
                reserva.checkInDia, reserva.checkInMes, reserva.checkInAno,
                reserva.checkOutDia, reserva.checkOutMes, reserva.checkOutAno,
                reserva.tipoQuarto, reserva.identificacaoQuarto);
        }
    }

    // Substitui o arquivo original pelo temporário
    fclose(arquivoReservas);
    fclose(temp);
    remove("Reservas.txt");
    rename("temp.txt", "Reservas.txt");

    if (!reservaEncontrada) {
        printf("Reserva nao encontrada para o CPF %s e data de check-in %d/%d/%d.\n", cpfCliente, checkInDia, checkInMes, checkInAno);
    }
}