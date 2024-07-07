#include <stdio.h>   // Lib de comunica��o com user
#include <stdlib.h>  // Lib de aloca��o de espa�o em mem�ria
#include <locale.h>  // Lib de aloca��o de texto por regi�o
#include <string.h>  // Lib respons�vel por cuidar das strings

// Fun��o para remover o caractere de nova linha '\n' da string lida por fgets
void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/*
 * Fun��o para registro de usu�rios
 * OBS: Usei fgets ao inv�s de scanf para salvar nomes com espa�os. 
 * A fun��o removerNovaLinha ajuda a remover o '\n' lido por fgets.
 */
int registrar() {
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    // Define a linguagem do usu�rio
    setlocale(LC_ALL, "Portuguese");

    // Solicita e l� o CPF
    printf("Digite o CPF a ser cadastrado: ");
    fgets(cpf, sizeof(cpf), stdin);
    removerNovaLinha(cpf);
    strcpy(arquivo, cpf);

    // Cria o arquivo para armazenar os dados
    FILE *file = fopen(arquivo, "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo");
        return 1;
    }

    // Salva o CPF no arquivo
    fprintf(file, "%s,", cpf);
    fclose(file);
    printf("\nCPF cadastrado com sucesso! \n\n");

    // Solicita e l� o nome
    printf("Digite o nome a ser cadastrado: ");
    fgets(nome, sizeof(nome), stdin);
    removerNovaLinha(nome);
    file = fopen(arquivo, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fprintf(file, "%s,", nome);
    fclose(file);
    printf("\nNome cadastrado com sucesso! \n\n");

    // Solicita e l� o sobrenome
    printf("Digite o sobrenome a ser cadastrado: ");
    fgets(sobrenome, sizeof(sobrenome), stdin);
    removerNovaLinha(sobrenome);
    file = fopen(arquivo, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fprintf(file, "%s,", sobrenome);
    fclose(file);
    printf("\nSobrenome cadastrado com sucesso! \n\n");

    // Solicita e l� o cargo
    printf("Digite o cargo a ser cadastrado: ");
    fgets(cargo, sizeof(cargo), stdin);
    removerNovaLinha(cargo);
    file = fopen(arquivo, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fprintf(file, "%s", cargo);
    fclose(file);
    printf("\nCargo cadastrado com sucesso! \n\n");

    // Congela a tela para o usu�rio com as �ltimas modifica��es
    system("pause");
    return 0;
}

/*
 * Fun��o para consulta de usu�rios
 * OBS: A fun��o de consultar usa a fun��o strtok para tokenizar os dados do arquivo.
 */
int consultar() {
    char cpf[40];
    char conteudo[200];

    setlocale(LC_ALL, "Portuguese");

	// Solicita e l� o CPF
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);
	
	// Busca o CPF nos arquivos e retorna o conte�do tokenizado
    FILE *file = fopen(cpf, "r");
    if (file == NULL) {
        printf("\nRegistro n�o localizado. Confira se este CPF existe e tente novamente! \n\n");
    } else {
        fgets(conteudo, sizeof(conteudo), file);
        fclose(file);

        char *token = strtok(conteudo, ",");
        printf("\nResultado da busca:\n\n");
        printf("CPF: %s\n", token);
        token = strtok(NULL, ",");
        printf("Nome: %s\n", token);
        token = strtok(NULL, ",");
        printf("Sobrenome: %s\n", token);
        token = strtok(NULL, ",");
        printf("Cargo: %s\n", token);
        printf("\n\n");
    }

    system("pause");
    return 0;
}

/*
 * Fun��o para deletar usu�rios
 * OBS: A fun��o deletar valida se o usu�rio existe antes de deletar o arquivo correspondente.
 */
int deletar() {
    char cpf[40];

    setlocale(LC_ALL, "Portuguese");
	
	// Solicita e l� o CPF
    printf("Digite o CPF do usu�rio a ser deletado: ");
    scanf("%s", cpf);
	
	// Busca o CPF solicitado e faz a remo��o do arquivo correspondente
    FILE *file = fopen(cpf, "r");
    if (file != NULL) {
        fclose(file);
        remove(cpf);
        printf("Usu�rio deletado com sucesso!\n");
    } else {
        printf("Usu�rio n�o encontrado.\n");
    }

    system("pause");
    return 0;
}

/*
 * Fun��o main
 * OBS: A fun��o main cont�m o menu de acesso �s op��es do programa de Cart�rio da EBAC.
 */
int main() {
    int opcao = 0;
    int laco = 1;

	// Estrutura de repeti��o para o menu do programa
    while (laco == 1) {
        system("cls"); // Limpa a tela
        setlocale(LC_ALL, "Portuguese");

        printf("### Cart�rio da EBAC ###\n\n");
        printf("Escolha a op��o desejada do menu:\n\n");
        printf("\t1 - Registrar usu�rio\n");
        printf("\t2 - Consultar usu�rio\n");
        printf("\t3 - Deletar usu�rio\n\n");

        printf("Op��o: ");
        scanf("%d", &opcao);
        getchar();  // Consome o caractere de nova linha que ficou no buffer

        system("cls");

        switch (opcao) {
            case 1:
                registrar();
                break;
            case 2:
                consultar();
                break;
            case 3:
                deletar();
                break;
            default:
                printf("Esta op��o n�o est� dispon�vel!\n\n");
                system("pause");
                break;
        }
    }

    return 0;
}
