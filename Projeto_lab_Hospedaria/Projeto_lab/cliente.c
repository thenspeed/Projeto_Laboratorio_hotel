#include <stdio.h>
#include <string.h>
#include "cliente.h"

#include "validarInput.h"

int cadastrarClientes() {

    FILE* arquivo;
    int idade;
    char str_cpf[14], str_nome[51], str_endereco[101], str_cidade[101], str_estado[3];

    DataNascimento data_nascimento; // Variável corrigida para armazenar a data de nascimento
    arquivo = fopen("pessoas.txt", "a");

    // Verifica se o arquivo não pôde ser aberto
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo pessoas.txt\n");
        return 0;
    }

    printf("Digite o CPF que será cadastrado: ");
    scanf("%13s", str_cpf);
    getchar(); // Consumir o caractere de nova linha deixado no buffer

    printf("Digite o nome que será cadastrado: ");
    fgets(str_nome, sizeof(str_nome), stdin);
    str_nome[strcspn(str_nome, "\n")] = '\0';

    printf("Digite a data de nascimento (dia mes ano): ");
    data_nascimento.dia = validarInputInteiro("Dia: ");
    data_nascimento.mes = validarInputInteiro("Mês: ");
    data_nascimento.ano = validarInputInteiro("Ano: ");

    idade = validarInputInteiro("Digite a idade: ");

    getchar();
    printf("Digite o endereço a ser cadastrado: ");
    fgets(str_endereco, sizeof(str_endereco), stdin);
    str_endereco[strcspn(str_endereco, "\n")] = '\0';

    printf("Digite a cidade: ");
    fgets(str_cidade, sizeof(str_cidade), stdin);
    str_cidade[strcspn(str_cidade, "\n")] = '\0';

    printf("Digite a sigla do Estado (MT): ");
    scanf("%2s", str_estado);

    fprintf(arquivo, "%s;%s;%d;%d;%d;%i;%s;%s;%s;\n", str_cpf, str_nome, data_nascimento.dia, data_nascimento.mes, data_nascimento.ano, idade, str_endereco, str_cidade, str_estado);

    fclose(arquivo);

    limparTela();
    printf("Cadastro de pessoa concluído!!\n");

    return 1;
}



int removerCliente(const char* cpf) {
    FILE* arquivo, * temp;
    char linha[256];

    arquivo = fopen("pessoas.txt", "r");
    temp = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo pessoas.txt ou temp.txt\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, cpf) == NULL) {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("pessoas.txt");
    rename("temp.txt", "pessoas.txt");

    limparTela();
    printf("Remoção do cadastro concluido!!\n");

    return 1;
}




int alterarCliente(const char* cpf) {
    FILE* arquivo, * temp;
    char linha[256];
    char novo_nome[51], novo_endereco[101], nova_cidade[101], novo_estado[3];
    int novo_dia, novo_mes, novo_ano, nova_idade;

    arquivo = fopen("pessoas.txt", "r");
    temp = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo pessoas.txt ou temp.txt\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, cpf) != NULL) {
            printf("Digite o novo nome: ");
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = '\0';

            printf("Digite a nova data de nascimento (dia mes ano): ");
            novo_dia = validarInputInteiro("Dia: ");
            novo_mes = validarInputInteiro("Mês: ");
            novo_ano = validarInputInteiro("Ano: ");

            nova_idade = validarInputInteiro("Digite a nova idade: ");

            printf("Digite o novo endereço: ");
            fgets(novo_endereco, sizeof(novo_endereco), stdin);
            novo_endereco[strcspn(novo_endereco, "\n")] = '\0';

            printf("Digite a nova cidade: ");
            fgets(nova_cidade, sizeof(nova_cidade), stdin);
            nova_cidade[strcspn(nova_cidade, "\n")] = '\0';

            printf("Digite a nova sigla do Estado (MT): ");
            scanf("%2s", novo_estado);

            fprintf(temp, "%s;%s;%d;%d;%d;%i;%s;%s;%s;\n", cpf, novo_nome, novo_dia, novo_mes, novo_ano, nova_idade, novo_endereco, nova_cidade, novo_estado);
        }
        else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("pessoas.txt");
    rename("temp.txt", "pessoas.txt");

    limparTela();
    printf("Alteração do cadastro concluido!!\n");

    return 1;
}