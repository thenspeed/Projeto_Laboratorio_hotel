#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

typedef struct {
    int identificacaoHospedagem;
    int identificacaoReserva;
    char cpfCliente[14];
    int checkInDia, checkInMes, checkInAno;
    int checkOutDia, checkOutMes, checkOutAno;
    double valorTotal;
    char status[20];
} Hospedagem;

// Função para iniciar hospedagem 
void iniciarHospedagem(int codigoReserva) {
    FILE* arquivoReservas;
    FILE* arquivoHospedagens;
    Reserva reserva;
    Hospedagem novaHospedagem;

    arquivoReservas = fopen("Reservas.txt", "r");
    arquivoHospedagens = fopen("Hospedagens.txt", "a");

    if (arquivoReservas == NULL || arquivoHospedagens == NULL) {
        printf("Erro ao abrir os arquivos Reservas.txt ou Hospedagens.txt\n");
        return;
    }

    int reservaEncontrada = 0;

    while (fscanf(arquivoReservas, "%d;%[^;];%d;%d;%d;%d;%d;%d;%[^;];%d\n",
        &reserva.identificacaoReserva, reserva.cpfCliente,
        &reserva.checkInDia, &reserva.checkInMes, &reserva.checkInAno,
        &reserva.checkOutDia, &reserva.checkOutMes, &reserva.checkOutAno,
        reserva.tipoQuarto, &reserva.identificacaoQuarto) == 10) {

        if (reserva.identificacaoReserva == codigoReserva) {
            reservaEncontrada = 1;

            // Preenche os dados da nova hospedagem
            novaHospedagem.identificacaoReserva = reserva.identificacaoReserva;
            strcpy(novaHospedagem.cpfCliente, reserva.cpfCliente);
            novaHospedagem.checkInDia = reserva.checkInDia;
            novaHospedagem.checkInMes = reserva.checkInMes;
            novaHospedagem.checkInAno = reserva.checkInAno;
            novaHospedagem.checkOutDia = 0; // A data de check-out é inicializada como zero
            novaHospedagem.checkOutMes = 0;
            novaHospedagem.checkOutAno = 0;
            strcpy(novaHospedagem.status, "Ativa"); // A hospedagem inicia como "Ativa"
            novaHospedagem.valorTotal = 0.0; // O valor total é inicializado como zero

            // Escreve os dados da nova hospedagem no arquivo
            fprintf(arquivoHospedagens, "%d;%s;%d;%d;%d;%d;%d;%d;%s;%.2lf\n",
                novaHospedagem.identificacaoReserva, novaHospedagem.cpfCliente,
                novaHospedagem.checkInDia, novaHospedagem.checkInMes, novaHospedagem.checkInAno,
                novaHospedagem.checkOutDia, novaHospedagem.checkOutMes, novaHospedagem.checkOutAno,
                novaHospedagem.status, novaHospedagem.valorTotal);

            // Atualiza o status da reserva para "Ativa"
      

            // Exibe mensagem de sucesso
            printf("Hospedagem iniciada com sucesso!\n");
        }
    }

    fclose(arquivoReservas);
    fclose(arquivoHospedagens);

    if (!reservaEncontrada) {
        printf("Reserva nao encontrada com o codigo %d.\n", codigoReserva);
    }
}


// Função para finalizar hospedagem 
void finalizarHospedagem(int codigoReserva) {
    FILE* arquivoHospedagens;
    Hospedagem hospedagem;

    arquivoHospedagens = fopen("Hospedagens.txt", "r+");

    if (arquivoHospedagens == NULL) {
        printf("Erro ao abrir o arquivo Hospedagens.txt\n");
        return;
    }

    int hospedagemEncontrada = 0;

    while (fscanf(arquivoHospedagens, "%d;%[^;];%d;%d;%d;%d;%d;%d;%[^;];%lf\n",
        &hospedagem.identificacaoReserva, hospedagem.cpfCliente,
        &hospedagem.checkInDia, &hospedagem.checkInMes, &hospedagem.checkInAno,
        &hospedagem.checkOutDia, &hospedagem.checkOutMes, &hospedagem.checkOutAno,
        hospedagem.status, &hospedagem.valorTotal) == 10) {

        if (hospedagem.identificacaoReserva == codigoReserva && strcmp(hospedagem.status, "Ativa") == 0) {
            hospedagemEncontrada = 1;

            // Atualiza a data de check-out
            printf("Digite a data de check-out (dia mes ano): ");
            scanf("%d %d %d", &hospedagem.checkOutDia, &hospedagem.checkOutMes, &hospedagem.checkOutAno);

            double valorQuarto = 100.0;
            hospedagem.valorTotal = valorQuarto;

            // Atualiza o status da hospedagem para "Finalizada"
            strcpy(hospedagem.status, "Finalizada");

            // Volta para a posição inicial no arquivo para realizar as atualizações
            fseek(arquivoHospedagens, -1 * sizeof(hospedagem), SEEK_CUR);

            // Escreve as atualizações no arquivo
            fprintf(arquivoHospedagens, "%d;%s;%d;%d;%d;%d;%d;%d;%s;%.2lf\n",
                hospedagem.identificacaoReserva, hospedagem.cpfCliente,
                hospedagem.checkInDia, hospedagem.checkInMes, hospedagem.checkInAno,
                hospedagem.checkOutDia, hospedagem.checkOutMes, hospedagem.checkOutAno,
                hospedagem.status, hospedagem.valorTotal);

            // Exibe mensagem de sucesso
            printf("Hospedagem finalizada com sucesso!\n");
        }
    }

    fclose(arquivoHospedagens);

    if (!hospedagemEncontrada) {
        printf("Hospedagem nao encontrada com o codigo %d ou ja finalizada.\n", codigoReserva);
    }
}


// Função para mostrar hospedagens por cliente 
void mostrarHospedagensPorCliente(char cpfCliente[14]) {
    FILE* arquivoHospedagens;
    Hospedagem hospedagem;

    arquivoHospedagens = fopen("Hospedagens.txt", "r");

    if (arquivoHospedagens == NULL) {
        printf("Erro ao abrir o arquivo Hospedagens.txt\n");
        return;
    }

    int hospedagemEncontrada = 0;

    while (fscanf(arquivoHospedagens, "%d;%[^;];%d;%d;%d;%d;%d;%d;%[^;];%lf\n",
        &hospedagem.identificacaoReserva, hospedagem.cpfCliente,
        &hospedagem.checkInDia, &hospedagem.checkInMes, &hospedagem.checkInAno,
        &hospedagem.checkOutDia, &hospedagem.checkOutMes, &hospedagem.checkOutAno,
        hospedagem.status, &hospedagem.valorTotal) == 10) {

        if (strcmp(hospedagem.cpfCliente, cpfCliente) == 0) {
            hospedagemEncontrada = 1;

            // Exibe os detalhes da hospedagem
            printf("Código da Reserva: %d\n", hospedagem.identificacaoReserva);
            printf("Data de Check-in: %d/%d/%d\n", hospedagem.checkInDia, hospedagem.checkInMes, hospedagem.checkInAno);

            if (strcmp(hospedagem.status, "Finalizada") == 0) {
                printf("Data de Check-out: %d/%d/%d\n", hospedagem.checkOutDia, hospedagem.checkOutMes, hospedagem.checkOutAno);
                printf("Valor Pago: R$ %.2lf\n", hospedagem.valorTotal);
            }
            else {
                printf("Status: Ativa\n");
            }

            printf("\n");
        }
    }

    fclose(arquivoHospedagens);

    if (!hospedagemEncontrada) {
        printf("Nenhuma hospedagem encontrada para o CPF %s.\n", cpfCliente);
    }
}
