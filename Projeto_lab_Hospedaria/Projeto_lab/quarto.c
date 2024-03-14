#include <stdio.h>
#include <stdlib.h>
#include "quarto.h"
#include "validarInput.h"

// Função para cadastrar quartos
int cadastrarQuartos() {
    FILE* arquivo;
    int identificacao, camasSolteiro, camasCasal;
    char tipoQuarto[20], status;
    double precoDiaria;

    arquivo = fopen("Quartos.csv", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Quartos.csv\n");
        return 0;
    }

    printf(" \n");
    printf("Identificacao do quarto (maior que 100): ");
    scanf("%d", &identificacao);

    // Validando identificação maior que 100
    if (identificacao <= 100) {
        printf("A identificacao do quarto deve ser maior que 100.\n");
        fclose(arquivo);
        return 0;
    }

    printf("Camas de solteiro (entre 1 e 3): ");
    scanf("%d", &camasSolteiro);

    // Validando camas de solteiro no intervalo especificado
    if (camasSolteiro < 1 || camasSolteiro > 3) {
        printf("O numero de camas de solteiro deve estar entre 1 e 3.\n");
        fclose(arquivo);
        return 0;
    }

    printf("Camas de casal (entre 1 e 3): ");
    scanf("%d", &camasCasal);

    // Validando camas de casal no intervalo especificado
    if (camasCasal < 1 || camasCasal > 3) {
        printf("O numero de camas de casal deve estar entre 1 e 3.\n");
        fclose(arquivo);
        return 0;
    }

    printf("Tipo de quarto (Single, Duplo, Triplo): ");
    scanf("%s", tipoQuarto);

    printf("Preco da diaria (com duas casas decimais): ");
    scanf("%lf", &precoDiaria);

    printf("Status do quarto (D para disponivel, I para indisponivel): ");
    scanf(" %c", &status);

    // Escreve os dados no arquivo separados por ";"
    fprintf(arquivo, "%d;%d;%d;%s;%.2lf;%c\n", identificacao, camasSolteiro, camasCasal, tipoQuarto, precoDiaria, status);

    // Fecha o arquivo
    fclose(arquivo);

    limparTela();
    imprimirTextoCercado("Cadastro do quarto concluido!", strlen("Cadastro do quarto concluido!"));

    return 1;
}

// Função para excluir quarto por identificação
int excluirQuarto(int identificacao) {
    FILE* arquivo;
    FILE* temp;
    char linha[256];

    arquivo = fopen("Quartos.csv", "r");
    temp = fopen("temp.csv", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo Quartos.csv ou temp.csv\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int id;
        sscanf(linha, "%d", &id);
        if (id != identificacao) {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("Quartos.csv");
    rename("temp.csv", "Quartos.csv");

    limparTela();
    imprimirTextoCercado("Quarto excluido com sucesso!", strlen("Quarto excluido com sucesso!"));

    return 1;
}

// Função para alterar tipo e quantidade de camas do quarto
int alterarQuarto(int identificacao) {
    FILE* arquivo;
    FILE* temp;
    char linha[256];
    int camasSolteiro, camasCasal;
    char tipoQuarto[20], status;
    double precoDiaria;

    arquivo = fopen("Quartos.csv", "r");
    temp = fopen("temp.csv", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo Quartos.csv ou temp.csv\n");
        return 0;
    }
    
    printf(" \n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int id;
        sscanf(linha, "%d", &id);
        if (id == identificacao) {
            printf("Camas de solteiro (entre 1 e 3): ");
            scanf("%d", &camasSolteiro);

            if (camasSolteiro < 1 || camasSolteiro > 3) {
                printf("O numero de camas de solteiro deve estar entre 1 e 3.\n");
                fclose(arquivo);
                fclose(temp);
                return 0;
            }

            printf("Camas de casal (entre 1 e 3): ");
            scanf("%d", &camasCasal);

            if (camasCasal < 1 || camasCasal > 3) {
                printf("O numero de camas de casal deve estar entre 1 e 3.\n");
                fclose(arquivo);
                fclose(temp);
                return 0;
            }

            printf("Tipo de quarto (Single, Duplo, Triplo): ");
            scanf("%s", tipoQuarto);

            printf("Preco da diaria (com duas casas decimais): ");
            scanf("%lf", &precoDiaria);

            printf("Status do quarto (D para disponivel, I para indisponivel): ");
            scanf(" %c", &status);

            fprintf(temp, "%d;%d;%d;%s;%.2lf;%c\n", identificacao, camasSolteiro, camasCasal, tipoQuarto, precoDiaria, status);
        }
        else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("Quartos.csv");
    rename("temp.csv", "Quartos.csv");

    limparTela();
    imprimirTextoCercado("Quarto alterado com sucesso!", strlen("Quarto alterado com sucesso!"));

    return 1;
}
