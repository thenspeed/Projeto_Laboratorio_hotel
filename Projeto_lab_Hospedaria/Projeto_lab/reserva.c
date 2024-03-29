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



// Fun��o para cancelar reserva por c�digo
void cancelarReservaPorCodigo(int codigoReserva) {
    FILE* arquivoReservas;
    FILE* temp;
    Reserva reserva;

    arquivoReservas = fopen("Reservas.csv", "r");
    temp = fopen("temp.csv", "w");

    if (arquivoReservas == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos Reservas.csv ou temp.csv\n");
        return;
    }

    int reservaEncontrada = 0;

    // Percorre as reservas e copia para o arquivo tempor�rio, excluindo a desejada
    while (fscanf(arquivoReservas, "%d;%[^;];%d;%d;%d;%d;%d;%d;%[^;];%d\n",
        &reserva.identificacaoReserva, reserva.cpfCliente,
        &reserva.checkInDia, &reserva.checkInMes, &reserva.checkInAno,
        &reserva.checkOutDia, &reserva.checkOutMes, &reserva.checkOutAno,
        reserva.tipoQuarto, &reserva.identificacaoQuarto) == 10) {

        if (reserva.identificacaoReserva == codigoReserva) {
            reservaEncontrada = 1;

            limparTela();
            imprimirTextoCercado("Reserva encontrada e cancelada com sucesso.", strlen("Reserva encontrada e cancelada com sucesso."));

        }
        else {
            fprintf(temp, "%d;%s;%d;%d;%d;%d;%d;%d;%s;%d\n",
                reserva.identificacaoReserva, reserva.cpfCliente,
                reserva.checkInDia, reserva.checkInMes, reserva.checkInAno,
                reserva.checkOutDia, reserva.checkOutMes, reserva.checkOutAno,
                reserva.tipoQuarto, reserva.identificacaoQuarto);
        }
    }

    // Substitui o arquivo original pelo tempor�rio
    fclose(arquivoReservas);
    fclose(temp);
    remove("Reservas.csv");
    rename("temp.csv", "Reservas.csv");

    if (!reservaEncontrada) {
        printf("Reserva nao encontrada com o codigo %d.\n", codigoReserva);
    }
}

// Fun��o para cancelar reserva por CPF e data de check-in
void cancelarReservaPorCPF(char cpfCliente[14], int checkInDia, int checkInMes, int checkInAno) {
    FILE* arquivoReservas;
    FILE* temp;
    Reserva reserva;

    arquivoReservas = fopen("Reservas.csv", "r");
    temp = fopen("temp.csv", "w");

    if (arquivoReservas == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos Reservas.csv ou temp.csv\n");
        return;
    }

    int reservaEncontrada = 0;

    // Percorre as reservas e copia para o arquivo tempor�rio, excluindo a desejada
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
            printf("\n");

            limparTela();
            imprimirTextoCercado("Reserva encontrada e cancelada com sucesso.!!", strlen("Reserva encontrada e cancelada com sucesso.!!"));

        }
        else {
            fprintf(temp, "%d;%s;%d;%d;%d;%d;%d;%d;%s;%d\n",
                reserva.identificacaoReserva, reserva.cpfCliente,
                reserva.checkInDia, reserva.checkInMes, reserva.checkInAno,
                reserva.checkOutDia, reserva.checkOutMes, reserva.checkOutAno,
                reserva.tipoQuarto, reserva.identificacaoQuarto);
        }
    }

    // Substitui o arquivo original pelo tempor�rio
    fclose(arquivoReservas);
    fclose(temp);
    remove("Reservas.csv");
    rename("temp.csv", "Reservas.csv");

    if (!reservaEncontrada) {
        printf("Reserva nao encontrada para o CPF %s e data de check-in %d/%d/%d.\n", cpfCliente, checkInDia, checkInMes, checkInAno);
    }
}


// Fun��o para cadastrar reservas
int cadastrarReserva() {
    FILE* arquivo;
    Reserva reserva;

    arquivo = fopen("Reservas.csv", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Reservas.csv\n");
        return 0;
    }
    printf(" \n");
   
    // Gerar identifica��o de reserva aleat�ria
    srand(time(NULL)); // Semente para a fun��o rand()
    reserva.identificacaoReserva = rand() % 1000000 + 1; // N�mero aleat�rio entre 1 e 999999

    printf("CPF do cliente (13 caracteres): ");
    scanf("%13s", reserva.cpfCliente);

    // Validando CPF
    // Implemente a valida��o do CPF conforme necess�rio

    printf("Data de Check-in:\n");
    printf("Dia: ");
    scanf("%d", &reserva.checkInDia);
    printf("Mes: ");
    scanf("%d", &reserva.checkInMes);
    printf("Ano: ");
    scanf("%d", &reserva.checkInAno);

    printf("\nData de Check-out:\n");
    printf("Dia: ");
    scanf("%d", &reserva.checkOutDia);
    printf("Mes: ");
    scanf("%d", &reserva.checkOutMes);
    printf("Ano: ");
    scanf("%d", &reserva.checkOutAno);

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
    imprimirTextoCercado("Cadastro da reserva concluido!", strlen("Cadastro da reserva concluido!"));
    printf("Identificacao da reserva: %d\n", reserva.identificacaoReserva);

    return 1;
}

// Fun��o para consultar reservas por CPF do cliente
void consultarReservasPorCPF() {
    FILE* arquivo;
    char cpfConsulta[14];
    Reserva reserva;

    arquivo = fopen("Reservas.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Reservas.csv\n");
        return;
    }
    printf(" \n");
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
    printf(" \n");
    if (opcaoCancelamento == 1) {
        int codigoReserva;
        printf("Digite o codigo da reserva: ");
        scanf("%d", &codigoReserva);

        // Chama a fun��o de cancelar reserva por c�digo
        cancelarReservaPorCodigo(codigoReserva);
    }
    else if (opcaoCancelamento == 2) {
        char cpfCliente[14];
        int checkInDia, checkInMes, checkInAno;

        printf("Digite o CPF do cliente: ");
        scanf("%13s", cpfCliente);

        printf("Digite a data de check-in (dia mes ano): ");
        scanf("%d %d %d", &checkInDia, &checkInMes, &checkInAno);

        // Chama a fun��o de cancelar reserva por CPF e data de check-in
        cancelarReservaPorCPF(cpfCliente, checkInDia, checkInMes, checkInAno);
    }
    else {
        printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
    }
}


// Fun��o para verificar a disponibilidade de quartos
void verificarDisponibilidade() {
    FILE* arquivoQuartos;
    FILE* arquivoReservas;
    Quarto quarto;
    Reserva reserva;

    arquivoQuartos = fopen("Quartos.csv", "r");
    arquivoReservas = fopen("Reservas.csv", "r");

    if (arquivoQuartos == NULL || arquivoReservas == NULL) {
        printf("Erro ao abrir os arquivos Quartos.csv ou Reservas.csv\n");
        return;
    }
    printf(" \n");
    // Coleta os dados para a verifica��o de disponibilidade
    char tipoQuarto[20];
    int checkInDia, checkInMes, checkInAno;
    int checkOutDia, checkOutMes, checkOutAno;

    printf("Digite o tipo de quarto desejado (Single, Duplo, Triplo): ");
    scanf("%s", tipoQuarto);

    printf("Data de Check-in:\n");
    printf("Dia: ");
    scanf("%d", &checkInDia);
    printf("Mes: ");
    scanf("%d", &checkInMes);
    printf("Ano: ");
    scanf("%d", &checkInAno);

    printf("\nData de Check-out:\n");
    printf("Dia: ");
    scanf("%d", &checkOutDia);
    printf("Mes: ");
    scanf("%d", &checkOutMes);
    printf("Ano: ");
    scanf("%d", &checkOutAno);



    // Exibir cabe�alho da tabela
    printf("\nIdentificacao | Tipo | Preco Diaria | Status\n");
    printf("--------------------------------------------\n");

    while (fscanf(arquivoQuartos, "%d;%d;%d;%[^;];%lf;%c\n",
        &quarto.identificacao, &quarto.camasSolteiro, &quarto.camasCasal,
        quarto.tipo, &quarto.precoDiaria, &quarto.status) == 6) {

        int disponivel = 1;

        // Verificar se o quarto est� reservado para as datas especificadas
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
                // Quarto est� reservado para o per�odo especificado
                disponivel = 0;
                break;
            }
        }

        // Voltar ao in�cio do arquivo de reservas para a pr�xima itera��o
        fseek(arquivoReservas, 0, SEEK_SET);

        // Exibir informa��es do quarto se estiver dispon�vel
        if (disponivel) {
            printf("%13d | %s | %.2lf | %c\n", quarto.identificacao, quarto.tipo, quarto.precoDiaria, quarto.status);
        }
    }

    fclose(arquivoQuartos);
    fclose(arquivoReservas);
}
