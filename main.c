#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

// Defini��o de uma senha para o administrador acessar o sistema
#define SENHA_ADM 123
#define MAX_NOME 80 // Defini��o do tamanho m�ximo de caracteres para os nomes
#define MAX_CPF 20

typedef struct {
    int id;
    char cpf[MAX_CPF];
    char nome[MAX_NOME];
    float saldo;
}Cliente;

Cliente *clientes = NULL; // Cria��o de um ponteiro "clientes" do tipo Cliente que servir� como array para armazenar os clientes
int countClientes = 0;

void TelaInicial();
void CadastrarCliente();
void ConsultarCliente();
void ListarClientes();
void ExcluirCliente();
void AutenticarCliente();
void OperacoesBancarias();
void Saque();
void Deposito();
void ConsultarCliente();

void TelaInicial() {
    int opcaoSelecionada;
    float iniciarOperacoes = 0;
    bool opcaoSair = false;
    printf("\n\n\t\t\t\t     $$ ## $$\n\n\t\t $$ ## $$\t\t\t\t$$ ## $$\n\t\t\t\t Sistema Banc�rio\n\n\t\t\t$$ ## $$ ## $$ ## $$ ## $$ ## $$\n\n");
    printf("O que deseja fazer?\n\n\t1- Cadastrar novo cliente. \n\t2- Consultar cliente. \n\t3- Listar todos os clientes. \n\t");
    printf("4- Editar cliente. \n\t5- Excluir cliente. \n\t6- Realizar opera��o banc�ria. \n\t7- Sair.\n");
    printf("\n\nDigite o n�mero correspondente a a��o que deseja realizar: ");
    setbuf(stdin, NULL); //"Blindagem" do `scanf()` com `setbuf()` em cima e em baixo
    scanf("%d", &opcaoSelecionada);
    setbuf(stdin, NULL);

    switch(opcaoSelecionada) {
        case 1:
            system("cls");
            CadastrarCliente();
            break;
        case 2:
            system("cls");
            ConsultarCliente();
            break;
        case 3:
            system("cls");
            ListarClientes();
            break;
        case 4:
            system("cls");
            EditarCliente();
            break;
        case 5:
            system("cls");
            ExcluirCliente();
            break;
        case 6:
            system("cls");
            AutenticarCliente();
            break;
        default:
            printf("\nA��o inv�lida!\n\n");
            opcaoSair = true;
            system("pause");
            system("cls");

            if(opcaoSair)
                TelaInicial();
    }

}

void GerarArquivoCliente(Cliente cliente) {
    char filename[100];
    snprintf(filename, sizeof(filename), "cliente_%d.txt", cliente.id);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo do cliente ID %d\n", cliente.id);
        return;
    }
    fprintf(file, "ID: %d\n", cliente.id);
    fprintf(file, "Nome: %s", cliente.nome);
    fprintf(file, "CPF: %s", cliente.cpf);
    fprintf(file, "Saldo: R$ %.2f\n", cliente.saldo);
    fclose(file);
    printf("Arquivo do cliente %s gerado com sucesso.\n", cliente.nome);
}

void GerarRelatorioGeral() {
    FILE *file = fopen("relatorio_geral.txt", "w");
    if (file == NULL) {
        printf("Erro ao criar o relat�rio geral.\n");
        return;
    }
    fprintf(file, "Relat�rio Geral de Clientes\n");
    fprintf(file, "===========================\n");
    for (int i = 0; i < countClientes; i++) {
        fprintf(file, "ID: %d\n", clientes[i].id);
        fprintf(file, "Nome: %s", clientes[i].nome);
        fprintf(file, "CPF: %s", clientes[i].cpf);
        fprintf(file, "Saldo: R$ %.2f\n", clientes[i].saldo);
        fprintf(file, "---------------------------\n");
    }
    fclose(file);
    printf("Relat�rio geral gerado com sucesso.\n");
}

void CadastrarCliente() {
    int i, opcaoSair;
    char cpfDigitado[MAX_CPF];
    bool cpfExistente = false;
    Cliente *temp = realloc(clientes, (countClientes + 1) * sizeof(Cliente));// Aloca dinamicamente espa�o para o cliente que ser� cadastrado.
    // A fun��o realloc recebe dois par�metros: o vetor que ele precisa copiar os dados e o tamanho de mem�ria que ele precisa alocar.
    // O realloc funciona alocando um novo espa�o de mem�ria, copiando os dados de outro local, o que da a sensa��o de poder crescer
    // indeterminadamente.
    if(temp == NULL) {
        printf("\nErro de aloca��o de mem�ria");
        exit(1);
    } // Tratamento de erro, acontece que a fun��o realloc pode falhar na tentativa de alocar mem�ria, caso falhe o programa termina a execu��o.
    clientes = temp;

    getchar();
    printf("\nDigite o CPF do cliente que deseja cadastrar: ");
    fgets(cpfDigitado, MAX_CPF, stdin);
    for(i=0; i<countClientes; i++) {
        if (strcmp(cpfDigitado, clientes[i].cpf) == 0) {
            cpfExistente = true;
        }
    }

    if(cpfExistente) {
        printf("\nCliente j� cadastrado!\n");
        printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
        scanf("%d", &opcaoSair);
        if(opcaoSair == 1){
            system("cls");
            CadastrarCliente();
        }else {
            printf("\nSaindo...\n");
            system("pause");
            system("cls");
            TelaInicial(); // Chama a tela inicial do sistema
        }
    } else {
        clientes[countClientes].id = countClientes + 1;
        strcpy(clientes[countClientes].cpf, cpfDigitado);
        clientes[countClientes].saldo = 0.0;
        getchar();
        printf("\nDigite o nome do cliente: ");
        fgets(clientes[countClientes].nome, MAX_NOME, stdin);
        printf("O cliente de CPF: %s, foi cadastrado com sucesso!", clientes[countClientes].cpf);

        countClientes++;
        GerarArquivoCliente(clientes[countClientes - 1]);
        GerarRelatorioGeral();
    }
    printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
    scanf("%d", &opcaoSair);
    setbuf(stdin,NULL);
    if(opcaoSair == 1){
        system("cls");
        CadastrarCliente();
    }else{
        printf("\nSaindo...\n");
        system("pause");
        system("cls");
        TelaInicial();
    }
}

void ConsultarCliente() {
    bool encontrado = false;
    bool opcSair = false;
    int idDigitado;
    int opcaoPesquisa, i, opcaoSair, pos;
    char nomeDigitado[MAX_NOME], cpfDigitado[MAX_CPF]; // As vari�veis que terminam com "digitado" v�o receber os dados para serem pesquisados

    if(countClientes == 0)
        printf("\nAinda n�o h� clientes cadastrados em nosso banco.\n");

    printf("Como deseja buscar o cliente?\n\t1- ID\n\t2- CPF\n\t3- Nome\nDigite o nome correspondente ao tipo de pesquisa que deseja: ");
    setbuf(stdin,NULL);
    scanf("%d", &opcaoPesquisa);
    setbuf(stdin,NULL);

    switch(opcaoPesquisa) {
        case 1:
            printf("\nDigite o ID a ser buscado: ");
            scanf("%d", &idDigitado);
            setbuf(stdin,NULL);
            for(i=0; i<countClientes; i++) {
                if(idDigitado == clientes[i].id) {
                    encontrado = true;
                    pos = i;
                }
            }
            if(encontrado) {
                printf("\nCliente encontrado, dados:\n");
                printf("\tID: %d\n\tCPF: %s\n\tNome: %s\n", clientes[pos].id, clientes[pos].cpf, clientes[pos].nome);
            } else {
                printf("\nO id digitado n�o corresponde a nenhum registro no banco de dados!");
            }
            printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
            scanf("%d", &opcaoSair);
            setbuf(stdin,NULL);
                if(opcaoSair == 1){
                    system("cls");
                    ConsultarCliente();
                }else{
                    printf("\nSaindo...\n");
                    system("pause");
                    system("cls");
                    TelaInicial();
                }
            break;
        case 2:
            getchar();
            printf("Digite o CPF a ser buscado: ");
            fgets(cpfDigitado, MAX_CPF, stdin);
            //nomeDigitado[strcspn(nomeDigitado,"\n")] = '\0';
            for(i=0; i<countClientes; i++) {
                if (strcmp(cpfDigitado, clientes[i].cpf) == 0) {
                    encontrado = true;
                    pos = i;
                }
            }
            if(encontrado) {
                printf("Cliente encontrado, dados:\n");
                printf("\tID: %d\n\tCPF: %s\n\tNome: %s\n", clientes[pos].id, clientes[pos].cpf, clientes[pos].nome);
            } else {
                printf("O CPF digitado n�o corresponde a nenhum registro no banco de dados!");
            }
            printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
            scanf("%d", &opcaoSair);
            setbuf(stdin,NULL);
            if(opcaoSair == 1){
                system("cls");
                ConsultarCliente();
            }else{
                printf("Saindo...\n");
                system("pause");
                system("cls");
                TelaInicial();
            }
            break;
        case 3:
            getchar();
            printf("Digite o nome a ser buscado: ");
            fgets(nomeDigitado, MAX_NOME, stdin);
            //nomeDigitado[strcspn(nomeDigitado,"\n")] = '\0';
            for(i=0; i<countClientes; i++) {
                if (strcmp(nomeDigitado, clientes[i].nome) == 0) {
                    encontrado = true;
                    pos = i;
                }
            }
            if(encontrado) {
                printf("Cliente encontrado, dados:\n");
                printf("\tID: %d\n\tCPF: %s\n\tNome: %s\n", clientes[pos].id, clientes[pos].cpf, clientes[pos].nome);
            } else {
                printf("O nome digitado n�o corresponde a nenhum registro no banco de dados!");
            }
            printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
            scanf("%d", &opcaoSair);
            setbuf(stdin,NULL);
            if(opcaoSair == 1){
                system("cls");
                ConsultarCliente();
            }else{
                printf("Saindo...\n");
                system("pause");
                system("cls");
                TelaInicial();
            }
            break;
        default:
            printf("Op��o inv�lida!");
            opcSair = true;
    }
}

void ListarClientes() {
    int i, opcaoSair;
    if(countClientes == 0)
        printf("Ainda n�o h� clientes cadastrados em nosso banco.\n");
    for(i=0; i<countClientes; i++) {
        printf("Dados:\n\tID: %d\n\tCPF: %s\n\tNome: %s\n", clientes[i].id, clientes[i].cpf, clientes[i].nome);
    } // Esse for percorre os vetores com dados at� acabarem os dados, ou seja, at� chegar nas posi��es vazias que n�o s�o percorridas.
    printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
    scanf("%d", &opcaoSair);
    setbuf(stdin,NULL);
    if(opcaoSair == 1){
        system("cls");
        ListarClientes();
    }else{
        printf("Saindo...\n");
        system("pause");
        system("cls");
        TelaInicial();
    }
}

void EditarCliente() {
    int escolhaEditar, i, opcaoSair, pos;
    char cpfTroca[MAX_CPF], novoCpf[MAX_CPF];
    bool encontrado = false;
    char nomeTroca[MAX_NOME], novoNome[MAX_NOME];
    printf("\nDigite 1 para editar o CPF ou 2 para editar o nome do cliente: ");
    setbuf(stdin,NULL);
    scanf("%d", &escolhaEditar);
    setbuf(stdin,NULL);

    switch(escolhaEditar) {
        case 1:
            getchar();
            printf("CPF que deseja alterar: ");
            fgets(cpfTroca, MAX_CPF, stdin);
            //cpfTroca[strcspn(cpfTroca,"\n")] = '\0';
            printf("Novo CPF: ");
            fgets(novoCpf, MAX_CPF, stdin);
            //novoCpf[strcspn(novoCpf,"\n")] = '\0';

            for(i=0; i<countClientes; i++) {
                if(strcmp(cpfTroca, clientes[i].cpf) == 0){
                    encontrado = true;
                    pos = i;
                    break;
                }
            }
            if(encontrado) {
                strcpy(clientes[pos].cpf, novoCpf);
                printf("CPF alterado com sucesso! o CPF do usu�rio agora � %s", clientes[pos].cpf);
                GerarArquivoCliente(clientes[pos]);
                GerarRelatorioGeral();
            }
            printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
            scanf("%d", &opcaoSair);
            setbuf(stdin,NULL);
            if(opcaoSair == 1){
                system("cls");
                EditarCliente();
            }else{
                printf("Saindo...\n");
                system("pause");
                system("cls");
                TelaInicial();
            }
            break;
        case 2:
            getchar();
            printf("Nome que deseja alterar: ");
            fgets(nomeTroca, MAX_NOME, stdin);
            //nomeTroca[strcspn(nomeTroca,"\n")] = '\0';
            printf("Novo nome: ");
            fgets(novoNome, MAX_NOME, stdin);
            //novoNome[strcspn(novoNome,"\n")] = '\0';

            for(i=0; i<countClientes; i++) {
                if(strcmp(nomeTroca, clientes[i].nome) == 0){
                    encontrado = true;
                    pos = i;
                    break;
                }
            }
            if(encontrado) {
                strcpy(clientes[pos].nome, novoNome);
                printf("Nome alterado com sucesso! o CPF do usu�rio agora � %s", clientes[pos].nome);
                GerarArquivoCliente(clientes[pos]);
                GerarRelatorioGeral();
            }
            printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
            scanf("%d", &opcaoSair);
            setbuf(stdin,NULL);
            if(opcaoSair == 1){
                system("cls");
                EditarCliente();
            }else{
                printf("Saindo...\n");
                system("pause");
                system("cls");
                TelaInicial();
            }
            break;
        default:
            printf("Op��o inv�lida!");
    }
}

void ExcluirCliente() {
    int idExcluir, i, pos = -1, opcaoSair;
    char oldFilename[100], newFilename[100];

    printf("Digite o ID do cliente que deseja excluir: ");
    scanf("%d", &idExcluir);

    // Encontrar a posi��o do cliente com o ID correspondente
    for (i=0; i<countClientes; i++) {
        if (clientes[i].id == idExcluir) {
            pos = i;
            break;
        }
    }

    // Se o cliente foi encontrado
    if (pos != -1) {
        // Gerar o nome do arquivo existente e o novo nome
        snprintf(oldFilename, sizeof(oldFilename), "cliente_%d.txt", clientes[pos].id);
        snprintf(newFilename, sizeof(newFilename), "clienteDesistente_%d.txt", clientes[pos].id);

        // Renomear o arquivo do cliente exclu�do
        if (rename(oldFilename, newFilename) == 0) {
            printf("Arquivo do cliente renomeado para: %s\n", newFilename);
        } else {
            printf("Erro ao renomear o arquivo do cliente ID %d.\n", clientes[pos].id);
        }

        printf("Excluindo o cliente: %sCPF: %s, ID: %d\n", clientes[pos].nome, clientes[pos].cpf, clientes[pos].id);

        // Mover todos os clientes ap�s o cliente exclu�do uma posi��o para tr�s
        for (i = pos; i < countClientes - 1; i++) {
            strcpy(clientes[i].nome, clientes[i + 1].nome);  // Copiar o nome do pr�ximo cliente
            strcpy(clientes[i].cpf, clientes[i + 1].cpf);
        }

        // Reduzir o contador de clientes
        countClientes--;

        printf("Cliente exclu�do com sucesso!\n");
        GerarRelatorioGeral();
    }
    else
        printf("Cliente com ID %d n�o encontrado.\n", idExcluir);
    printf("Digite 0 para sair ou 1 para tentar novamente: ");
    scanf("%d", &opcaoSair);
    if(opcaoSair == 1)
        ExcluirCliente();
    else {
        printf("Saindo...\n");
        TelaInicial();
    }
}

void AutenticarCliente() {
    int i, opcaoSair, pos;
    char cpfDigitado[MAX_CPF];
    bool cpfIgual = false;
    getchar();
    printf("Digite o CPF do cliente: ");
    fgets(cpfDigitado, MAX_CPF, stdin);

    for (i=0; i<countClientes; i++) {
        if(strcmp(cpfDigitado, clientes[i].cpf) == 0) {
            cpfIgual = true;
            pos = i;
        }
    }
    if (cpfIgual) {
        printf("\n\t\t\t    Seja bem vindo %s", clientes[pos].nome);
        OperacoesBancarias();
    }
    else
        printf("Desculpe, o cliente de CPF:\n\t%s \nn�o foi encontrado no registro de usu�rios do nosso banco.", cpfDigitado);
    printf("\nDigite 0 para sair ou 1 para tentar novamente: ");
    scanf("%d", &opcaoSair);
    if(opcaoSair == 1)
        AutenticarCliente();
    else {
        printf("Saindo...\n");
        TelaInicial();
    }
}

void OperacoesBancarias() {
    int opcaoSelecionada;

    printf("\n\n\t\t\t\t      $$ ## $$\n\n\t\t $$ ## $$\t\t\t\t$$ ## $$\n\t\t\t\t Opera��es banc�rias\n\n\t\t\t$$ ## $$ ## $$ ## $$ ## $$ ## $$\n\n");
    printf("O que deseja fazer?\n\n\t1- Saque. \n\t2- Dep�sito. \n\t3- Consultar saldo. \n\t4- Sair. \n");
    printf("Digite o n�mero correspondente a a��o que deseja realizar: ");
    scanf("%d", &opcaoSelecionada);

    switch(opcaoSelecionada) {
        case 1:
            Saque();
            break;
        case 2:
            Deposito();
            break;
        case 3:
            ConsultarSaldo();
            break;
        case 4:
            printf("Saindo...");
            TelaInicial();
            break;
        default:
            printf("Op��o inv�lida!");
    }
}

void Saque() {
    int i, opcaoSair, pos;
    char cpfDigitado[MAX_CPF];
    bool encontrado = false;
    float valorSaque = 0;

    getchar();
    printf("Digite o CPF: ");
    fgets(cpfDigitado, MAX_CPF, stdin);
    //setbuf(stdin,NULL);
    for(i=0; i<countClientes; i++) {
        if(strcmp(cpfDigitado, clientes[i].cpf) == 0) {
            encontrado = true;
            pos = i;
        }
    }
    if(encontrado) {
        printf("Digite quanto deseja sacar: ");
        scanf("%f", &valorSaque);

        if (valorSaque > clientes[pos].saldo) {
            printf("Saldo insuficiente!");
            OperacoesBancarias();
        }
        else {
            clientes[pos].saldo = clientes[pos].saldo - valorSaque;
            printf("Saque realizado com sucesso!\nSeu saldo agora � de R$ %.2f", clientes[pos].saldo);
            GerarArquivoCliente(clientes[pos]);
            GerarRelatorioGeral();

            printf("\nDigite 0 se deseja sair ou 1 se deseja realizar um novo saque: ");
            scanf("%d", &opcaoSair);

            if (opcaoSair == 1)
                Saque();
            else {
                printf("Saindo...");
                OperacoesBancarias();
            }
        }
    } else {
        printf("O CPF digitado n�o corresponde a nenhum registro no banco de dados!");
    }
    printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
    scanf("%d", &opcaoSair);
    setbuf(stdin,NULL);
    if (opcaoSair == 1)
        Saque();
    else {
        printf("Saindo...");
        OperacoesBancarias();
    }
}

void Deposito() {
    int i, opcaoSair, pos;
    char cpfDigitado[MAX_CPF];
    bool encontrado = false;
    float valorDeposito = 0;

    getchar();
    printf("Digite o CPF: ");
    fgets(cpfDigitado, MAX_CPF, stdin);
    //setbuf(stdin,NULL);
    for(i=0; i<countClientes; i++) {
        if(strcmp(cpfDigitado, clientes[i].cpf) == 0) {
            encontrado = true;
            pos = i;
        }
    }
    if(encontrado) {
        printf("Digite quanto deseja depositar: ");
        scanf("%f", &valorDeposito);

        clientes[pos].saldo = clientes[pos].saldo + valorDeposito;
        printf("Dep�sito realizado com sucesso!\nSeu saldo agora � de R$ %.2f", clientes[pos].saldo);
        GerarArquivoCliente(clientes[pos]);
        GerarRelatorioGeral();

        printf("\nDigite 0 se deseja sair ou 1 se deseja realizar um novo dep�sito: ");
        scanf("%d", &opcaoSair);

        if (opcaoSair == 1)
            Deposito();
        else {
            printf("Saindo...");
            OperacoesBancarias();
        }
    } else {
        printf("O CPF digitado n�o corresponde a nenhum registro no banco de dados!");
    }
    printf("\nDigite 1 para tentar novamente ou qualquer outro d�gito para sair: ");
    scanf("%d", &opcaoSair);
    setbuf(stdin,NULL);
    if (opcaoSair == 1)
        Deposito();
    else {
        printf("Saindo...");
        OperacoesBancarias();
    }
}

void ConsultarSaldo() {
    int i, opcaoSair, pos;
    char cpfDigitado[MAX_CPF];
    bool encontrado = false;

    getchar();
    printf("Digite o CPF: ");
    fgets(cpfDigitado, MAX_CPF, stdin);
    //setbuf(stdin,NULL);
    for(i=0; i<countClientes; i++) {
        if(strcmp(cpfDigitado, clientes[i].cpf) == 0) {
            encontrado = true;
            pos = i;
        }
    }
    if(encontrado) {
        printf("Seu saldo � de R$ %.2f", clientes[pos].saldo);
        printf("\nDigite 0 se deseja sair ou 1 se deseja tentar novamente: ");
        scanf("%d", &opcaoSair);

        if (opcaoSair == 1)
            ConsultarSaldo();
        else {
            printf("Saindo...");
            OperacoesBancarias();
        }
    } else {
        printf("O CPF digitado n�o corresponde a nenhum registro no banco de dados!");
    }
    printf("\nDigite 0 se deseja sair ou 1 se deseja tentar novamente: ");
    scanf("%d", &opcaoSair);

    if (opcaoSair == 1)
        ConsultarSaldo();
    else {
        printf("Saindo...");
        OperacoesBancarias();
    }
}

int main()
{
    int senhaDigitada;
    setlocale(LC_ALL, "");

    // Para acessar o sistema deve digitar a senha corretamente
    printf("Digite a senha para acessar o sistema: ");
    setbuf(stdin,NULL);
    scanf("%d", &senhaDigitada);
    setbuf(stdin,NULL);

    // Verifica��o se a senha fornecida corresponde com a senha de acesso ao sistema
    if(senhaDigitada != SENHA_ADM) {
        do {
            printf("Senha incorreta, digite a senha novamente: ");
            scanf("%d", &senhaDigitada);
            setbuf(stdin,NULL);
        } while(senhaDigitada != SENHA_ADM);
    }
    system("cls");

    TelaInicial();

    return 0;
}
