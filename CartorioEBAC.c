#include <stdio.h>   // Lib de comunicação com user
#include <stdlib.h>  // Lib de alocação de espaço em memória
#include <locale.h>  // Lib de alocação de texto por região
#include <string.h>  // Lib responsável por cuidar das strings

// Função para remover o caractere de nova linha '\n' da string lida por fgets
void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/*
 * Função para registro de usuários
 * OBS: Usei fgets ao invés de scanf para salvar nomes com espaços. 
 * A função removerNovaLinha ajuda a remover o '\n' lido por fgets.
 */
int registrar() {
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    // Define a linguagem do usuário
    setlocale(LC_ALL, "Portuguese");

    // Solicita e lê o CPF
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

    // Solicita e lê o nome
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

    // Solicita e lê o sobrenome
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

    // Solicita e lê o cargo
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

    // Congela a tela para o usuário com as últimas modificações
    system("pause");
    return 0;
}

/*
 * Função para consulta de usuários
 * OBS: A função de consultar usa a função strtok para tokenizar os dados do arquivo.
 */
int consultar() {
    char cpf[40];
    char conteudo[200];

    setlocale(LC_ALL, "Portuguese");

	// Solicita e lê o CPF
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);
	
	// Busca o CPF nos arquivos e retorna o conteúdo tokenizado
    FILE *file = fopen(cpf, "r");
    if (file == NULL) {
        printf("\nRegistro não localizado. Confira se este CPF existe e tente novamente! \n\n");
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
 * Função para deletar usuários
 * OBS: A função deletar valida se o usuário existe antes de deletar o arquivo correspondente.
 */
int deletar() {
    char cpf[40];

    setlocale(LC_ALL, "Portuguese");
	
	// Solicita e lê o CPF
    printf("Digite o CPF do usuário a ser deletado: ");
    scanf("%s", cpf);
	
	// Busca o CPF solicitado e faz a remoção do arquivo correspondente
    FILE *file = fopen(cpf, "r");
    if (file != NULL) {
        fclose(file);
        remove(cpf);
        printf("Usuário deletado com sucesso!\n");
    } else {
        printf("Usuário não encontrado.\n");
    }

    system("pause");
    return 0;
}

/*
 * Função main
 * OBS: A função main contém o menu de acesso às opções do programa de Cartório da EBAC.
 */
int main() {
    int opcao = 0;
    int laco = 1;

	// Estrutura de repetição para o menu do programa
    while (laco == 1) {
        system("cls"); // Limpa a tela
        setlocale(LC_ALL, "Portuguese");

        printf("### Cartório da EBAC ###\n\n");
        printf("Escolha a opção desejada do menu:\n\n");
        printf("\t1 - Registrar usuário\n");
        printf("\t2 - Consultar usuário\n");
        printf("\t3 - Deletar usuário\n\n");

        printf("Opção: ");
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
                printf("Esta opção não está disponível!\n\n");
                system("pause");
                break;
        }
    }

    return 0;
}
