#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

struct cadCliente {
   char codigo[9];
   char cpf[14];
   char nome[100];
   char telefone[20];
   char status;
   } Cliente;
   
struct cadFornecedor {
   int  codigo;
   char documento[20];
   char nome[100];
   char telefone[20];
   char status;
   } Fornecedor;   
   
struct cadProduto {
   int  codigo;
   char descricao[100];
   int  qtd;
   float precoCusto;
   float precoVenda;
   } Produto;   
   
FILE *fp;
/*Funções do Sistema*/
void incluir (void);
void consultar(void);
void excluir(void);
void alterar(void);
void abrir(void);
void listar(void);
void ajuda(void);

int main(void)
{
	setlocale(LC_ALL,"");
 char opcao[2], op;
 do{
    do{
       system("cls");
       printf("\n\n\n\n\n\n\n");
       printf("\t########################################################\n");
       printf("\t#        					       #\n");
       printf("\t#     Programa de Cadastro de Clientes e Produtos      #\n");
       printf("\t#                                                      #\n");
       printf("\t########################################################\n\n\n");
       printf("\n Digite uma das opções\n\n");
       printf("\n <I> - Incluir");
       printf("\n <A> - Alterar");
       printf("\n <E> - Excluir");
       printf("\n <C> - Consultar");
       printf("\n <L> - Listar");
       printf("\n <H> - Ajuda");
       printf("\n <S> - Sair");
       printf("\n\n\n Opção:");
       gets(opcao);
       op=tolower(*opcao);
    } while(!strchr("iaeclsh",op));
       switch(op){/*D*/
	  case 'i' : incluir(); break;
	  case 'a' : alterar(); break;
	  case 'e' : excluir(); break;
	  case 'c' : consultar(); break;
	  case 'l' : listar(); break;
	  case 's' : exit(0);
	  case 'h' : ajuda(); break;
       }
 }while(1);
}
		    
void ajuda(void) {
	system("cls");
	printf("\a\n\n\n\n\n\n\n");
	printf("\t############################################################\n");
	printf("\t#   Trabalho de Final de Semestre - Estrutura de Dados 1   #\n");
	printf("\t#							   #\n");
	printf("\t# Engenharia da Computação - Universidade Federal de Goiás #\n");
	printf("\t#   						   	   #\n");
	printf("\t#     Jonismar Morais // Mariana Casseta // Pedro Lopes    #\n");
	printf("\t############################################################\n\n\n");
	printf("\t\t\tTecle <ENTER> para voltar");
	getch();
}
void abrir(char tipo[3])
{
     if((fp=fopen("C:\\Users\\user\\Documents\\ed1\\clientes.txt", tipo))==NULL)
     {printf("\n O arquivo nao pode ser aberto!!\n");
      getch();
      exit(1);
     }
}
void incluir(void)
{    //char *um="0";
	system("cls");
     abrir("ab+");
     fseek(fp,0L, SEEK_END);

     do
     {
	printf("\n Digite o nome ou <FIM> para sair:\n\n");
	gets(Cliente.nome);

	if ((strcmp(Cliente.nome,"fim")!=0)&&(strcmp(Cliente.nome,"FIM")!=0)){
		printf("\n Código:"); gets(Cliente.codigo);
		printf("\n CPF:"); gets(Cliente.cpf);
		printf("\n Telefone:"); gets(Cliente.telefone);
		Cliente.status='1';
		if(fwrite(&Cliente, sizeof(struct cadCliente), 1, fp) != 1)
		{
		printf("\n Erro de gravação!!");
		getch();
		}
		else
		{   printf("\n Dados gravados com sucesso\n\n");}
		}
     }while((strcmp(Cliente.nome,"fim")!=0)&&(strcmp(Cliente.nome,"FIM")!=0));
     fclose(fp);
}
int busca (void){
	system("cls");
   	int achou=-1,posicao=0;
   	char nomep[40];
   	abrir("rb");
   	printf("\nDigite o nome a ser procurado:");
   	gets(nomep);
   	rewind(fp);
   	while((!feof(fp))&&(achou==-1)) {
		fread(&Cliente, sizeof(struct cadCliente), 1, fp);
      	if (!feof(fp)) {
			if (strcmp(nomep, Cliente.nome)==0) {
				if (Cliente.status=='0') {
					posicao=-2;
				}
	     	achou=1;
	    	}
	  		else{
			  	posicao++;
			}
		}
      	else {
		  	posicao=-1;
		}
   	}
   if (achou==-1)
      {posicao=-1;}
   fclose(fp);
   return(posicao);
}
void consultar(void){
   int pos;
   pos=busca();
   if(pos==-1)
      {
	 printf("\nCliente inexistente no arquivo!");
	 getch();
      }
      else if(pos==-2)
	      {
		 printf("\nCliente inexistente no arquivo!");
		 getch();
	      }
	      else
		 {
		    abrir("rb+");
		    fseek(fp,pos*sizeof(struct cadCliente),SEEK_SET);
		    fread(&Cliente, sizeof(struct cadCliente), 1, fp);
		    printf("\nNome:%s",Cliente.nome);
		    printf("\nCódigo:%s",Cliente.codigo);
		    printf("\nCPF:%s",Cliente.cpf);
		    printf("\nTelefone:%s",Cliente.telefone);
			getch();
		 }
   fclose(fp);
}
void alterar(void){
	system("cls");
   int pos;
   pos=busca();
   if (pos==-1)
      {
	 printf("\nCliente inexistente no arquivo");
	 getch();
      }
      else if(pos==-2)
	      {
		 printf("\nCliente inexistente no arquivo!");
		 getch();
	      }
	      else
		 {
		    abrir("rb+");
		    fseek(fp,pos*sizeof(struct cadCliente),SEEK_CUR);
		    fread(&Cliente, sizeof(struct cadCliente), 1, fp);
		    printf("\nDeseja alterar o seguinte o registro a seguir?");
		    printf("\nNome:%s",Cliente.nome);
		    printf("\nCódigo:%s",Cliente.codigo);
		    printf("\nCPF:%s",Cliente.cpf);
		    printf("\nTelefone:%s",Cliente.telefone);
		    getch();
		    printf("\nDigite os dados corretos:");
		    printf("\nNome:");
		    gets(Cliente.nome);
		    printf("\nCódigo:");
		    gets(Cliente.codigo);
		    printf("\nCPF:");
		    gets(Cliente.cpf);
		    printf("\nTelefone:");
		    gets(Cliente.telefone);
		    Cliente.status='1';
		    fseek(fp,pos*sizeof(struct cadCliente),SEEK_SET);
		    if(fwrite(&Cliente, sizeof(struct cadCliente),1, fp)!=1)
		       {
			  printf("\nErro na gravação...");
		       }
		       else
			  {
			     printf("\nDados alterados com sucesso...");
			     getch();
			  }
		 }
   fclose(fp);
}
void listar(void) {
   int cont=0;

   abrir("rb");
   fseek(fp, 0L, SEEK_SET);
   fread(&Cliente, sizeof(struct cadCliente),1, fp);
   do
   {
      if (Cliente.status!='0')
	 {
	    printf("\nNome: %s",Cliente.nome);
	    printf("\nCódigo: %s",Cliente.codigo);
	    printf("\nCPF: %s",Cliente.cpf);
	    printf("\nTelefone: %s",Cliente.telefone);
	    cont++;
	 }
      fread(&Cliente, sizeof(struct cadCliente),1, fp);
      }while(!feof(fp));
   printf("\n#Quantidade de Registros: %d",cont);
   getch();
}
void excluir(void){
   int pos;
   pos=busca();
   if(pos==-1)
      {
	 printf("\nCliente inexistente no arquivo");
	 getch();
      }
      else
	 {
	    if(pos==-2)
	       {
		  printf("\nCliente excluído do arquivo");
		  getch();
	       }
	       else
		  {
		     abrir("rb+");
		     fseek(fp, pos*sizeof(struct cadCliente), SEEK_SET);
		     fread(&Cliente, sizeof(struct cadCliente), 1, fp);
		     printf("\nNome: %s",Cliente.nome);
		     printf("\nCódigo: %s",Cliente.codigo);
		     printf("\nCPF: %s",Cliente.cpf);
		     printf("\nTelefone: %s",Cliente.telefone);
		     printf("\nEste Registro #%d sera excluido",(pos+1));
		     getch();
		     //strcpy(reg.status,"0");
		     Cliente.status='0';
		     fseek(fp, pos*sizeof(struct cadCliente), SEEK_SET);
		     if(fwrite(&Cliente, sizeof(struct cadCliente), 1, fp)!=1)
			{
			   printf("\nErro na gravação...");
			   getch();
			}
			else
			{
			   printf("\nCliente excluído com sucesso!");
			   getch();
			}
		  }
	 }
   fclose(fp);
}
