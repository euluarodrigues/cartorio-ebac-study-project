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
    int opcao = 0;
    int laco = 1;

    // Define a linguagem do usuário
    setlocale(LC_ALL, "Portuguese");
    
    system("cls"); // Limpa a tela

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
    system("pause");
    
    // Sub-menu da tela registrar
    while (laco == 1) {
        system("cls");
        
        printf("Deseja fazer um novo registro?\n\n");
        printf("1- Fazer novo registro\n");
        printf("2- Voltar ao menu principal\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        
        getchar();  // Consome o caractere de nova linha que ficou no buffer

        switch (opcao) {
            case 1:
                registrar();
                break;
            case 2:
                return 0;
                break;
            default:
                printf("Esta opção não está disponível!\n\n");
                system("pause");
                break;
        }
    }
    
    return 0;
}

// Função chamada por outras funções do programa, para consultas no banco a partir de um CPF
int consultaBanco(const char *cpf) {
    char conteudo[200];
    int contador = 1;
    setlocale(LC_ALL, "Portuguese");
    
    // Retorna a lista com todos os registros
    if (cpf == 0) {
        for (contador = 1; contador < 100; contador++) {
            char nomeArquivo[20];
            sprintf(nomeArquivo, "%d", contador);
            
            FILE *file = fopen(nomeArquivo, "r");
            if (file == NULL) {
                continue;
            }
            if (fgets(conteudo, sizeof(conteudo), file) != NULL) {
                fclose(file);
                
                char *token = strtok(conteudo, ",");
                printf("CPF: %s\n", token);
                token = strtok(NULL, ",");
                printf("Nome: %s\n", token);
                token = strtok(NULL, ",");
                printf("Sobrenome: %s\n", token);
                token = strtok(NULL, ",");
                printf("Cargo: %s\n", token);
                printf("\n\n");
            } else {
                fclose(file);
            }
        }
    } else {
        // Busca o CPF nos arquivos e retorna o conteúdo tokenizado
        FILE *file = fopen(cpf, "r");
        if (file == NULL) {
            printf("\nUsuário não localizado. Confira se este CPF existe e tente novamente! \n\n");
            return 0; // Retorna 0 se o usuário não for encontrado
        } else {
            fgets(conteudo, sizeof(conteudo), file);
            fclose(file);
    
            char *token = strtok(conteudo, ",");
            printf("\nUsuário localizado:\n\n");
            printf("CPF: %s\n", token);
            token = strtok(NULL, ",");
            printf("Nome: %s\n", token);
            token = strtok(NULL, ",");
            printf("Sobrenome: %s\n", token);
            token = strtok(NULL, ",");
            printf("Cargo: %s\n", token);
            printf("\n\n");
            
            return 1; // Retorna 1 se o usuário for encontrado
        }
    }
    system("pause");
}

/*
 * Função para consulta de usuários
 * OBS: A função de consultar usa a função strtok para tokenizar os dados do arquivo.
 */
int consultar() {
    char cpf[40];
    int laco = 1;
    int opcao = 0;

    setlocale(LC_ALL, "Portuguese");
    
    system("cls"); // Limpa a tela

    // Solicita e lê o CPF
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);
    
    consultaBanco(cpf); // Chama a função consultaBanco com o CPF fornecido pelo usuário

    system("pause");
    
    // Sub-menu da tela Consultar
    while (laco == 1) {
        system("cls");
        
        printf("Deseja fazer uma nova consulta?\n\n");
        printf("1- Fazer nova consulta\n");
        printf("2- Voltar ao menu principal\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        
        getchar();  // Consome o caractere de nova linha que ficou no buffer

        switch (opcao) {
            case 1:
                consultar();
                break;
            case 2:
                return 0;
                break;
            default:
                printf("Esta opção não está disponível!\n\n");
                system("pause");
                break;
        }
    }
    
    return 0;
}

/*
 * Função para deletar usuários
 * OBS: A função deletar valida se o usuário existe antes de deletar o arquivo correspondente.
 */
int deletar() {
    char cpf[40];
    int laco = 1;
    int opcao = 0;

    setlocale(LC_ALL, "Portuguese");
    
    system("cls");
    
    // Solicita e lê o CPF
    printf("Digite o CPF do usuário a ser deletado: ");
    scanf("%s", cpf);
    
    // Chama a função consultaBanco com o CPF fornecido, para verificar se o usuário existe
    if (!consultaBanco(cpf)) {
        system("pause");
        deletar();
    } // Se o usuário não for encontrado, volta para o início da função deletar
    
    // Loop para confirmar a deleção
    while (laco == 1) {
        printf("Prosseguir com a deleção?\n");
        printf("1. Sim\n");
        printf("2. Não\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                remove(cpf);
                printf("\nUsuário deletado com sucesso!\n");
                laco++;
                break;
            case 2:
                printf("\nOperação cancelada!\n");
                laco++;
                break;
            default:
                printf("\nEsta opção não está disponível!\n\n");
                break;
        }
        
        system("pause");
        system("cls");
        consultaBanco(cpf);
    }
    
    // Sub-menu da tela Deletar
    while (laco) {
        system("cls");
        
        printf("Deseja fazer uma nova exclusão?\n\n");
        printf("1- Fazer nova exclusão\n");
        printf("2- Voltar ao menu principal\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        
        getchar();  // Consome o caractere de nova linha que ficou no buffer

        switch (opcao) {
            case 1:
                deletar();
                break;
            case 2:
                return 0;
                break;
            default:
                printf("Esta opção não está disponível!\n\n");
                system("pause");
                break;
        }
    }
    
    return 0;
}

/*
 * Função main
 * OBS: A função main contém o menu de acesso às opções do programa de Cartório da EBAC.
 */
int main() {
    int opcao = 0;
    int laco = 1;
    int cpf = 0;
    char senha[10] = "a";
    int comparacao;
		
	setlocale(LC_ALL, "Portuguese");
	
	// Área de login
	printf("### Cartório da EBAC ###\n\n");
	printf("Digite a sua senha para acessar o sistema: ");
	scanf("%s", senha);
	comparacao = strcmp(senha, "admin");
	
	if (comparacao == 0) {
		// Estrutura de repetição para o menu do programa
	    while (laco == 1) {
	        system("cls"); // Limpa a tela
	        
			printf("### Cartório da EBAC ###\n\n");
	        printf("Escolha a opção desejada do menu:\n\n");
	        printf("\t1 - Registrar usuário\n");
	        printf("\t2 - Consultar usuário por CPF\n");
	        printf("\t3 - Consultar lista de usuários\n");
	        printf("\t4 - Deletar usuário\n\n");
	        printf("\t5 - Sair do sistema\n\n");
	
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
			consultaBanco(cpf);
	                break;
	            case 4:
			deletar();
	                break;
	            case 5:
	            	system("cls");
	            	printf("Sistema encerrado. Até a próxima!");
			return 0;
	            	break;
	            default:
	                printf("Esta opção não está disponível!\n\n");
	                system("pause");
	                break;
	        }
	    }
	} else
		printf("\nSenha incorreta!\n\n");
		system ("pause");
		system ("cls");
		main();
}
