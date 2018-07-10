#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>

//time_t converte time para string
typedef struct relatorio {
  char dia;
  char mes;
  char codigo;
  float valorCust;
  float valorLucr;
  struct Relatorio *prox;

}Relatorio;

struct cadProduto {
    char codigo[9];
    char descricao[100];
    int qtd, qtdVenda;
    float precoCusto;
    float precoVenda;
} Produto;

struct cadCliente {
    char codigo[9];
    char cpf[14];
    char nome[100];
    char telefone[20];
    char status;
} Cliente;

struct cadFornecedor {
    char codigo[9];
    char documento[20];
    char nome[100];
    char telefone[20];
    char status;
} Fornecedor;



FILE *fp;
/*Funções do Sistema*/
void incluir(void);
void consultar(void);
void excluir(void);
void alterar(void);
void abrir(char[3]);
void listar(void);
void ajuda(void);
int financeiro(void);
void subMenu(void);
void subMenuCadastros(void);
void buscarRelatorio(int, int, int);
void relat(void);

int iTag = 0;

Relatorio *novo;
Relatorio *inicio = NULL;
Relatorio *fim = NULL;
Relatorio *aux = NULL;
Relatorio *ponteiroAux = NULL;
Relatorio *inicioFila = NULL;
float totalVenda, valorVenda, valorLucro= 0, tLucroProd;

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    char opcao[2], op;
    do {
        do {
            system("cls");
            printf("\n\n");
            printf("\t########################################################\n");
            printf("\t#                                                      #\n");
            printf("\t#            Sistema de Gerenciamento de Caixa         #\n");
            printf("\t#                                                      #\n");
            printf("\t########################################################\n\n\n");
            printf("\n Digite uma das opções\n\n");
            printf("\n <C> - Cadastros");
            printf("\n <F> - Financeiro");
            printf("\n <R> - Relatórios");
            printf("\n <H> - Ajuda");
            printf("\n <S> - Sair");
            printf("\n\n\n Digite a Sua Opção:");
            gets(opcao);
            setbuf(stdin, NULL);
            op = tolower(*opcao);
        } while (!strchr("cfrhs", op));

        switch (op) {/*D*/
            case 'c': subMenu();
                break;
            case 'f': financeiro();
                break;
            case 'r': relat();
                break;
            case 'h': ajuda();
                break;
            case 's': exit(0);
        }
    } while (1);
}

void subMenu(void) {
    char opcao[2], op;
    do {
        do {
            system("cls");
            printf("\n\n");
            printf("\t########################################################\n");
            printf("\t#        					                             #\n");
            printf("\t#     Programa de Cadastro de Clientes e Produtos      #\n");
            printf("\t#                                                      #\n");
            printf("\t########################################################\n\n\n");
            printf("\n Digite uma das opções\n\n");
            printf("\n <C> - Clientes");
            printf("\n <F> - Fornecedores");
            printf("\n <P> - Produtos");
            printf("\n <V> - Voltar");
            printf("\n\n\n Digite a Sua Opção:");
            gets(opcao);
            setbuf(stdin, NULL);
            op = tolower(*opcao);
        } while (!strchr("cfpv", op));

        switch (op) {/*D*/
            case 'c':
                iTag = 1;
                subMenuCadastros();
                break;
            case 'f':
                iTag = 2;
                subMenuCadastros();
                break;
            case 'p':
                iTag = 3;
                subMenuCadastros();
                break;
            case 'v':
                main();
                break;
        }
    } while (1);
}

void subMenuCadastros(void) {
    char opcao[2], op;
    do {
        do {
            system("cls");
            printf("\n\n");
            printf("\t########################################################\n");
            printf("\t#                                                      #\n");
            printf("\t#          Sistema de Gerenciamento de Caixa           #\n");
            printf("\t#                                                      #\n");
            printf("\t########################################################\n\n\n");
            printf("\n Digite uma das opções\n\n");
            printf("\n <I> - Incluir");
            printf("\n <A> - Alterar");
            printf("\n <E> - Excluir");
            printf("\n <C> - Consultar");
            printf("\n <L> - Listar");
            printf("\n <V> - Voltar");
            printf("\n\n\n Opção:");
            gets(opcao);
            setbuf(stdin, NULL);
            op = tolower(*opcao);
        } while (!strchr("iaeclv", op));
        switch (op) {
            case 'i': incluir();
                break;
            case 'a': alterar();
                break;
            case 'e': excluir();
                break;
            case 'c': consultar();
                break;
            case 'l': listar();
                break;
            case 'v': iTag = 0;
                subMenu();
                break;
        }
    } while (1);
}

void ajuda(void) {
    system("cls");
    printf("\a\n\n");
    printf("\t############################################################\n");
    printf("\t#   Trabalho de Final de Semestre - Estrutura de Dados 1   #\n");
    printf("\t#                                                          #\n");
    printf("\t# Engenharia da Computação - Universidade Federal de Goiás #\n");
    printf("\t#                                                          #\n");
    printf("\t#            Jonismar Morais // Mariana Casseta            #\n");
    printf("\t#            Pedro Lopes // Cristiano Gonçalves            #\n");
    printf("\t############################################################\n\n\n");
    printf("\n\n\nLUCRO\n\tO lucro é considerado todo o rendimento positivo obtido através de uma negociação econômica ou de qualquer outro gênero. Na economia, o lucro é tudo o que foi ganhado ou recebido a partir de um ato de comercialização financeira..\n");
    printf("\n\nCAIXA DE CUSTO\n\tO preço de custo é aquele cobrado sobre os produtos ou serviços e equivale apenas ao custo necessário para a matéria prima e mão de obra. Ou seja, nele não é acrescentado o lucro por parte de quem venderá o produto, nem valores referentes à estocagem, custos básicos..\n");
    printf("\n\nMELHOR FORMA DE INVESTIR\n\tÉ fundamental para a empresa manter certa reserva de seu lucro para eventuais necessidades ou imprevistos. Desta forma, em períodos de baixa ou mesmo falta de caixa, a empresa poderá passar pelas ""turbulências"" de forma muito mais tranquila e sem precisar recorrer a bancos ou outras intituições funanceiras, consequentemente sem precisar pagar juros a terceiros...\n\n\n");
    printf("\t\t\tTecle <ENTER> para voltar");
    getch();
}

void abrir(char tipo[3]) {
    if (iTag == 1) {
        if ((fp = fopen("clientes.txt", tipo)) == NULL) {
            printf("\n O arquivo nao pode ser aberto!!\n");
            getch();
            exit(1);
        }
    } else if (iTag == 2) {
        if ((fp = fopen("fornecedores.txt", tipo)) == NULL) {
            printf("\n O arquivo nao pode ser aberto!!\n");
            getch();
            exit(1);
        }
    } else if (iTag == 3) {
        if ((fp = fopen("produtos.txt", tipo)) == NULL) {
            printf("\n O arquivo nao pode ser aberto!!\n");
            getch();
            exit(1);
        }
    }
}

void incluir(void) { //char *um="0";
    if (iTag == 1) {
        system("cls");
        abrir("ab+");
        fseek(fp, 0L, SEEK_END);
        do {
            printf("\n Digite o nome ou <FIM> para sair:\n\n");
            printf(" ");
            gets(Cliente.nome);
            setbuf(stdin, NULL);
            if ((strcmp(Cliente.nome, "fim") != 0)&&(strcmp(Cliente.nome, "FIM") != 0)) {
                printf("\n Código:");
                gets(Cliente.codigo);
                setbuf(stdin, NULL);
                printf("\n CPF:");
                gets(Cliente.cpf);
                setbuf(stdin, NULL);
                printf("\n Telefone:");
                gets(Cliente.telefone);
                setbuf(stdin, NULL);
                Cliente.status = '1';
                if (fwrite(&Cliente, sizeof (struct cadCliente), 1, fp) != 1) {
                    printf("\n Erro de gravação!!");
                    getch();
                } else {
                    printf("\n Dados gravados com sucesso\n\n");
                }
            }
        } while ((strcmp(Cliente.nome, "fim") != 0)&&(strcmp(Cliente.nome, "FIM") != 0));
        fclose(fp);
    } else if (iTag == 2) {
        system("cls");
        abrir("ab+");
        fseek(fp, 0L, SEEK_END);
        do {
            printf("\n Digite o nome ou <FIM> para sair:\n\n");
            printf(" ");
            gets(Fornecedor.nome);
            setbuf(stdin, NULL);
            if ((strcmp(Fornecedor.nome, "fim") != 0)&&(strcmp(Fornecedor.nome, "FIM") != 0)) {
                printf("\n Código:");
                gets(Fornecedor.codigo);
                setbuf(stdin, NULL);
                printf("\n CPF:");
                gets(Fornecedor.documento);
                setbuf(stdin, NULL);
                printf("\n Telefone:");
                gets(Fornecedor.telefone);
                setbuf(stdin, NULL);
                Fornecedor.status = '1';
                if (fwrite(&Fornecedor, sizeof (struct cadFornecedor), 1, fp) != 1) {
                    printf("\n Erro de gravação!!");
                    getch();
                } else {
                    printf("\n Dados gravados com sucesso\n\n");
                }
            }
        } while ((strcmp(Fornecedor.nome, "fim") != 0)&&(strcmp(Fornecedor.nome, "FIM") != 0));
        fclose(fp);
    } else if (iTag == 3) {
        system("cls");
        abrir("ab+");
        fseek(fp, 0L, SEEK_END);
        do {
            printf("\n Digite A Descrição do Produto ou <FIM> para sair:\n\n");
            printf(" ");
            gets(Produto.descricao);
            setbuf(stdin, NULL);
            if ((strcmp(Produto.descricao, "fim") != 0)&&(strcmp(Produto.descricao, "FIM") != 0)) {
                printf("\n Código: ");
                gets(Produto.codigo);
                setbuf(stdin, NULL);
                printf("\n Preço de Custo: ");
                scanf("%f", &Produto.precoCusto);
                setbuf(stdin, NULL);
                printf("\n Preço de Venda: ");
                scanf("%f", &Produto.precoVenda);
                setbuf(stdin, NULL);
                printf("\n Quantidade Em Estoque: ");
                scanf("%d", &Produto.qtd);
                setbuf(stdin, NULL);
                if (fwrite(&Produto, sizeof (struct cadProduto), 1, fp) != 1) {
                    printf("\n Erro de gravação!!");
                    getch();
                } else {
                    printf("\n Dados gravados com sucesso\n\n");
                }
            }
        } while ((strcmp(Produto.descricao, "fim") != 0)&&(strcmp(Produto.descricao, "FIM") != 0));
        fclose(fp);
    }
}

int busca(void) {
    system("cls");
    int achou = -1, posicao = 0;
    char nomep[40];
    abrir("rb");
    printf("\nDigite o nome a ser procurado:");
    gets(nomep);
    setbuf(stdin, NULL);
    rewind(fp);
    while ((!feof(fp))&&(achou == -1)) {
        if (iTag == 1) {
            fread(&Cliente, sizeof (struct cadCliente), 1, fp);
            if (!feof(fp)) {
                if (strcmp(nomep, Cliente.nome) == 0) {
                    if (Cliente.status == '0') {
                        posicao = -2;
                    }
                    achou = 1;
                } else {
                    posicao++;
                }
            } else {
                posicao = -1;
            }
        } else if (iTag == 2) {
            fread(&Fornecedor, sizeof (struct cadFornecedor), 1, fp);
            if (!feof(fp)) {
                if (strcmp(nomep, Fornecedor.nome) == 0) {
                    if (Fornecedor.status == '0') {
                        posicao = -2;
                    }
                    achou = 1;
                } else {
                    posicao++;
                }
            } else {
                posicao = -1;
            }
        } else if (iTag == 3) {
            fread(&Produto, sizeof (struct cadProduto), 1, fp);
            if (!feof(fp)) {
                if (strcmp(nomep, Produto.descricao) == 0) {
                    achou = 1;
                } else {
                    posicao++;
                }
            } else {
                posicao = -1;
            }
        }
    }

    if (achou == -1) {
        posicao = -1;
    }
    fclose(fp);
    return (posicao);
}

void consultar(void) {
    int pos;
    pos = busca();
    if (pos == -1) {
        printf("\nDados não encontrados no arquivo!");
        getch();
    } else if (pos == -2) {
        printf("\nDados não encontrados no arquivo!");
        getch();
    } else {
        abrir("rb+");
        if (iTag == 1) {
            fseek(fp, pos * sizeof (struct cadCliente), SEEK_SET);
            fread(&Cliente, sizeof (struct cadCliente), 1, fp);
            printf("\nNome: %s", Cliente.nome);
            printf("\nCódigo: %s", Cliente.codigo);
            printf("\nCPF: %s", Cliente.cpf);
            printf("\nTelefone: %s", Cliente.telefone);
            getch();
        } else if (iTag == 2) {
            fseek(fp, pos * sizeof (struct cadFornecedor), SEEK_SET);
            fread(&Fornecedor, sizeof (struct cadFornecedor), 1, fp);
            printf("\nNome: %s", Fornecedor.nome);
            printf("\nCódigo: %s", Fornecedor.codigo);
            printf("\nCPF/CNPJ: %s", Fornecedor.documento);
            printf("\nTelefone: %s", Fornecedor.telefone);
            getch();
        } else if (iTag == 3) {
            fseek(fp, pos * sizeof (struct cadProduto), SEEK_SET);
            fread(&Produto, sizeof (struct cadProduto), 1, fp);
            printf("\nCódigo: %s", Produto.codigo);
            printf("\nDescrição: %s", Produto.descricao);
            printf("\nPreço de Custo: %.2f", Produto.precoCusto);
            printf("\nPreço de Venda: %.2f", Produto.precoVenda);
            printf("\nEstoque Atual: %d", Produto.qtd);
            getch();
        }
    }
    fclose(fp);
}

void alterar(void) {
    system("cls");
    int pos;
    char opcao[2], op;
    pos = busca();
    if (pos == -1) {
        printf("\nDados não encontrados no arquivo");
        getch();
    } else if (pos == -2) {
        printf("\nDados não encontrados no arquivo!");
        getch();
    } else if (iTag == 1) {
        abrir("rb+");
        fseek(fp, pos * sizeof (struct cadCliente), SEEK_CUR);
        fread(&Cliente, sizeof (struct cadCliente), 1, fp);
        printf("\nDeseja alterar o seguinte o registro a seguir?");
        printf("\nNome: %s", Cliente.nome);
        printf("\nCódigo: %s", Cliente.codigo);
        printf("\nCPF: %s", Cliente.cpf);
        printf("\nTelefone: %s", Cliente.telefone);

        printf("\n\n\n S p/ sim ou N p/ não: ");
        gets(opcao);
        op = tolower(*opcao);
        switch (op) {
            case 's':
                printf("\nDigite os dados corretos:");
                printf("\nNome: ");
                gets(Cliente.nome);
                printf("\nCódigo: ");
                gets(Cliente.codigo);
                printf("\nCPF: ");
                gets(Cliente.cpf);
                printf("\nTelefone: ");
                gets(Cliente.telefone);
                Cliente.status = '1';
                fseek(fp, pos * sizeof (struct cadCliente), SEEK_SET);
                if (fwrite(&Cliente, sizeof (struct cadCliente), 1, fp) != 1) {
                    printf("\nErro na gravação...");
                } else {
                    printf("\nDados alterados com sucesso...");
                    getch();
                }
                break;
            case 'n':
                subMenuCadastros();
                break;
            default:
                printf("\nOpção Inválida\n");
                getch();

        }
    } else if (iTag == 2) {
        abrir("rb+");
        fseek(fp, pos * sizeof (struct cadFornecedor), SEEK_CUR);
        fread(&Fornecedor, sizeof (struct cadFornecedor), 1, fp);
        printf("\nDeseja alterar o registro a seguir?");
        printf("\nNome: %s", Fornecedor.nome);
        printf("\nCódigo: %s", Fornecedor.codigo);
        printf("\nCPF/CNPJ: %s", Fornecedor.documento);
        printf("\nTelefone: %s", Fornecedor.telefone);

        printf("\n\n\n S p/ sim ou N p/ não: ");
        gets(opcao);
        op = tolower(*opcao);
        switch (op) {
            case 's':
                printf("\nDigite os dados corretos:");
                printf("\nNome: ");
                gets(Fornecedor.nome);
                printf("\nCódigo: ");
                gets(Fornecedor.codigo);
                printf("\nCPF: ");
                gets(Fornecedor.documento);
                printf("\nTelefone: ");
                gets(Fornecedor.telefone);
                Fornecedor.status = '1';
                fseek(fp, pos * sizeof (struct cadFornecedor), SEEK_SET);
                if (fwrite(&Fornecedor, sizeof (struct cadFornecedor), 1, fp) != 1) {
                    printf("\nErro na gravação...");
                } else {
                    printf("\nDados alterados com sucesso...");
                    getch();
                }
                break;
            case 'n':
                subMenuCadastros();
                break;
            default:
                printf("\nOpção Inválida\n");
                getch();
        }
    } else if (iTag == 3) {
        abrir("rb+");
        fseek(fp, pos * sizeof (struct cadProduto), SEEK_CUR);
        fread(&Produto, sizeof (struct cadProduto), 1, fp);
        printf("\nDeseja alterar o seguinte o registro a seguir?");
        printf("\nCódigo: %s", Produto.codigo);
        printf("\nDescrição: %s", Produto.descricao);
        printf("\nPreço de Custo: %f", Produto.precoCusto);
        printf("\nPreço de Venda: %f", Produto.precoVenda);
        printf("\nEstoque Atual: %d", Produto.qtd);
        printf("\n\n\n S p/ sim ou N p/ não: ");
        gets(opcao);
        op = tolower(*opcao);
        switch (op) {
            case 's':
                printf("\nDigite os dados corretos:");
                printf("\nCódigo: ");
                gets(Produto.codigo);
                printf("\nDescrição: ");
                gets(Produto.descricao);
                printf("\nPreço de Custo: ");
                scanf("%f", &Produto.precoCusto);
                printf("\nPreço de Venda: ");
                scanf("%f", &Produto.precoVenda);
                printf("\nNovo Estoque: ");
                scanf("&d", &Produto.qtd);
                Cliente.status = '1';
                fseek(fp, pos * sizeof (struct cadProduto), SEEK_SET);
                if (fwrite(&Produto, sizeof (struct cadProduto), 1, fp) != 1) {
                    printf("\nErro na gravação...");
                } else {
                    printf("\nDados alterados com sucesso...");
                    getch();
                }
                break;
            case 'n':
                subMenuCadastros();
                break;
            default:
                printf("\nOpção Inválida\n");
                getch();
        }
    }
    fclose(fp);
}

void listar(void) {
    if (iTag == 1) {
        int cont = 0;
        abrir("rb");
        fseek(fp, 0L, SEEK_SET);
        fread(&Cliente, sizeof (struct cadCliente), 1, fp);
        do {
            if (Cliente.status != '0') {
                printf("\nNome: %s", Cliente.nome);
                printf("\nCódigo: %s", Cliente.codigo);
                printf("\nCPF: %s", Cliente.cpf);
                printf("\nTelefone: %s", Cliente.telefone);
                cont++;
            }
            fread(&Cliente, sizeof (struct cadCliente), 1, fp);
        } while (!feof(fp));
        printf("\n#Quantidade de Registros: %d", cont);
        getch();
    } else if (iTag == 2) {
        int cont = 0;
        abrir("rb");
        fseek(fp, 0L, SEEK_SET);
        fread(&Fornecedor, sizeof (struct cadFornecedor), 1, fp);
        do {
            if (Fornecedor.status != '0') {
                printf("\nNome: %s", Fornecedor.nome);
                printf("\nCódigo: %s", Fornecedor.codigo);
                printf("\nCPF/CNPJ: %s", Fornecedor.documento);
                printf("\nTelefone: %s", Fornecedor.telefone);
                cont++;
            }
            fread(&Fornecedor, sizeof (struct cadFornecedor), 1, fp);
        } while (!feof(fp));
        printf("\n#Quantidade de Registros: %d", cont);
        getch();
    } else if (iTag == 3) {
        int cont = 0;
        abrir("rb");
        fseek(fp, 0L, SEEK_SET);
        fread(&Produto, sizeof (struct cadProduto), 1, fp);
        do {
            printf("\nCódigo: %s", Produto.codigo);
            printf("\nDescrição: %s", Produto.descricao);
            printf("\nPreço de Custo: %.2f", Produto.precoCusto);
            printf("\nTelefone: %.2f", Produto.precoVenda);
            printf("\nTelefone: %d", Produto.qtd);
            cont++;
            fread(&Produto, sizeof (struct cadProduto), 1, fp);
        } while (!feof(fp));
        printf("\n#Quantidade de Registros: %d", cont);
        getch();
    }
}

void excluir(void) {
    if (iTag == 1) {
        int pos;
        pos = busca();
        if (pos == -1) {
            printf("\nCliente inexistente no arquivo");
            getch();
        } else {
            if (pos == -2) {
                printf("\nCliente excluído do arquivo");
                getch();
            } else {
                abrir("rb+");
                fseek(fp, pos * sizeof (struct cadCliente), SEEK_SET);
                fread(&Cliente, sizeof (struct cadCliente), 1, fp);
                printf("\nNome: %s", Cliente.nome);
                printf("\nCódigo: %s", Cliente.codigo);
                printf("\nCPF: %s", Cliente.cpf);
                printf("\nTelefone: %s", Cliente.telefone);
                printf("\nEste Registro #%d sera excluido", (pos + 1));
                getch();
                //strcpy(reg.status,"0");
                Cliente.status = '0';
                fseek(fp, pos * sizeof (struct cadCliente), SEEK_SET);
                if (fwrite(&Cliente, sizeof (struct cadCliente), 1, fp) != 1) {
                    printf("\nErro na gravação...");
                    getch();
                } else {
                    printf("\nCliente excluído com sucesso!");
                    getch();
                }
            }
        }
        fclose(fp);
    } else if (iTag == 2) {
        int pos;
        pos = busca();
        if (pos == -1) {
            printf("\nFornecedor inexistente no arquivo");
            getch();
        } else {
            if (pos == -2) {
                printf("\nFornecedor excluído do arquivo");
                getch();
            } else {
                abrir("rb+");
                fseek(fp, pos * sizeof (struct cadFornecedor), SEEK_SET);
                fread(&Cliente, sizeof (struct cadFornecedor), 1, fp);
                printf("\nNome: %s", Fornecedor.nome);
                printf("\nCódigo: %s", Fornecedor.codigo);
                printf("\nCPF: %s", Fornecedor.documento);
                printf("\nTelefone: %s", Fornecedor.telefone);
                printf("\nEste Registro #%d sera excluido", (pos + 1));
                getch();
                //strcpy(reg.status,"0");
                Fornecedor.status = '0';
                fseek(fp, pos * sizeof (struct cadFornecedor), SEEK_SET);
                if (fwrite(&Fornecedor, sizeof (struct cadFornecedor), 1, fp) != 1) {
                    printf("\nErro na gravação...");
                    getch();
                } else {
                    printf("\nFornecedor excluído com sucesso!");
                    getch();
                }
            }
        }
        fclose(fp);
    } else if (iTag == 3) {
        int pos;
        pos = busca();
        if (pos == -1) {
            printf("\nProduto inexistente no arquivo");
            getch();
        } else {
            if (pos == -2) {
                printf("\nProduto excluído do arquivo");
                getch();
            } else {
                abrir("rb+");
                fseek(fp, pos * sizeof (struct cadProduto), SEEK_SET);
                fread(&Cliente, sizeof (struct cadProduto), 1, fp);
                printf("\nDescrição: %s", Produto.descricao);
                printf("\nCódigo: %s", Produto.codigo);
                printf("\nPreço de Custo: %.2f", Produto.precoCusto);
                printf("\nPreço de Venda: %.2fs", Produto.precoVenda);
                printf("\nQuantidade Em Estoque: %d", Produto.qtd);
                printf("\nEste Registro #%d sera excluido", (pos + 1));
                getch();
                //strcpy(reg.status,"0");
                fseek(fp, pos * sizeof (struct cadProduto), SEEK_SET);
                if (fwrite(&Produto, sizeof (struct cadProduto), 1, fp) != 1) {
                    printf("\nErro na gravação...");
                    getch();
                } else {
                    printf("\nProduto excluído com sucesso!");
                    getch();
                }
            }
        }
        fclose(fp);

    }
}

int financeiro(void) {

    char controle[3];
    int pos, contProd;

    time_t data;
    time(&data);
    struct tm *d = localtime(&data);

    tLucroProd=0;
    iTag=3;
    controle[3]='nao';
    totalVenda=0;


    do {
        pos=busca();

        if (pos == -1) {
            printf("\nDados não encontrados no arquivo!\n");
            system("pause");
        } else if (pos == -2) {
            printf("\nDados não encontrados no arquivo!\n");
            system("pause");
        } else {
            abrir("rb+");
            fseek(fp, pos * sizeof (struct cadProduto), SEEK_SET);
            fread(&Produto, sizeof (struct cadProduto), 1, fp);
            printf("\nCódigo: %s", Produto.codigo);
            printf("\nDescrição: %s", Produto.descricao);
            printf("\nPreço de Custo: %.2f", Produto.precoCusto);
            printf("\nEstoque Atual: %d", Produto.qtd);
            printf("\n\nEste é o produto que deseja? (sim/não): ");
            gets(controle);
            setbuf(stdin,NULL);
        }
    } while ((strcmp(controle, "sim") != 0)&&(strcmp(controle, "SIM") != 0));

    printf("\nPreço Unitário de Venda: ");
    scanf("%f", &Produto.precoVenda);
    printf("\nQuantidade de produtos vendidos: ");
    scanf("%d", &Produto.qtdVenda);
    valorVenda = Produto.precoVenda * Produto.qtdVenda;

    printf("\n\n");

    system("cls");
    printf("Código:%s\n", Produto.codigo);
    printf(" %s\n", Produto.descricao);
    printf("Quantidade: %.2d\n", Produto.qtdVenda);
    printf("Valor Unitário de venda: %.2f\n", Produto.precoVenda);
    printf("Valor Total da venda: %.2f\n\n", valorVenda);

    valorLucro = valorVenda - Produto.precoCusto * Produto.qtdVenda;


    fp = fopen("financeiro.txt", "r");


    if (fgets(Produto.codigo, 9, fp)!=NULL){
            fgets(Produto.descricao, 100, fp);
            fscanf(fp, "%d\n\n", &Produto.qtd);
            fscanf(fp, "%d\n\n", &Produto.qtdVenda);
            fscanf(fp, "%f\n", &Produto.precoCusto);
    }

        fclose(fp);
        totalVenda = totalVenda + valorVenda;

    fopen("financeiro.txt", "a");

        fprintf(fp, "%s\n", Produto.codigo);
        fprintf(fp, "%s\n", Produto.descricao);
        fprintf(fp, "%d\n", Produto.qtd);
        fprintf(fp, "%d\n", Produto.qtdVenda);
        fprintf(fp, "%.2f\n\n", Produto.precoCusto);


    fclose(fp);

    novo=(Relatorio*)malloc(sizeof(Relatorio));
    novo->dia = (d->tm_mday);
    novo->mes = (d ->tm_mon + 1);
    novo->valorCust = Produto.precoCusto;
    novo->valorLucr = valorLucro;


    fopen("relatorio.txt", "a");

        fprintf(fp, "%d\n", novo->dia);
        fprintf(fp, "%d\n", novo->mes);
        fprintf(fp, "%s\n", Produto.codigo);
        fprintf(fp, "%.2f\n", novo->valorCust);
        fprintf(fp, "%.2f\n\n", novo->valorLucr);

    fclose(fp);

    novo->prox = NULL;

    if(inicio == NULL){
        inicio = novo;
        inicioFila = inicio;
        fim = novo;
    }else{
        fim->prox = novo;
        fim=novo;
    }

    printf("\n\n\tGravado com suscesso!\n\n");
    system("pause");

    main();
}

void relat(){
    time_t data;
    time(&data);
    struct tm *d = localtime(&data);

    int diaInicio, diaFim, mesInicio, mesFim;
    char menu[2], men;

    do{
        do{
            system("cls");
            printf("\n\n");
            printf("\t########################################################\n");
            printf("\t#                                                      #\n");
            printf("\t#         Programa de Relatórios Financeiros           #\n");
            printf("\t#                                                      #\n");
            printf("\t########################################################\n\n\n");
            printf("\n Digite uma das opções que deseja obter o relatório\n\n");
            printf("\n <P> - Relatório do dia");
            printf("\n <V> - Voltar");
            printf("\n\n\n Digite a Sua Opção:");
            fflush(stdin);
            setbuf(stdin, NULL);
            gets(menu);
            setbuf(stdin, NULL);
            men = tolower(*menu);
        }while(!strchr("cfpv", men));


    switch (men) {

        case 'p':
            system("cls");
            printf("\n\n\tRELATORIO DO DIA (%d / %d)\n\n", (d->tm_mday), (d ->tm_mon + 1));

            printf("\n\tLucro do Dia: %.2f", valorLucro);
            printf("\n\tValor Custo: %.2f\n\n", (valorVenda-valorLucro));

            printf("\n\n\nLUCRO\n\tO lucro é considerado todo o rendimento positivo obtido através de uma negociação econômica ou de qualquer outro gênero. Na economia, o lucro é tudo o que foi ganhado ou recebido a partir de um ato de comercialização financeira..\n");
            printf("\n\nCAIXA DE CUSTO\n\tO preço de custo é aquele cobrado sobre os produtos ou serviços e equivale apenas ao custo necessário para a matéria prima e mão de obra. Ou seja, nele não é acrescentado o lucro por parte de quem venderá o produto, nem valores referentes à estocagem, custos básicos..\n");
            printf("\n\nMELHOR FORMA DE INVESTIR\n\tÉ fundamental para a empresa manter certa reserva de seu lucro para eventuais necessidades ou imprevistos. Desta forma, em períodos de baixa ou mesmo falta de caixa, a empresa poderá passar pelas ""turbulências"" de forma muito mais tranquila e sem precisar recorrer a bancos ou outras intituições funanceiras, consequentemente sem precisar pagar juros a terceiros...\n\n\n");
            system("pause");
            break;

        case 'v':
            main();
            break;
        default: relat();
    }
  }while(1);
}
