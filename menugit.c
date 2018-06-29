#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

setlocale(LC_ALL, "Portuguese");ss

int main(){

  int menu, menu1, menu2, menu3;
  int m1, m2, m3;

  printf("\n\t\t\tBEM VINDO AO PROGRAMA ....\t\n\n\n\n");
  system("pause");
  printf("\n\t Iniciando...\n\n\n\n");
  system("pause");
  system("cls");
  printf("\tDigite onde deseja acessar...\n\n");
  printf("1 - Área de Cadastros\n");
  printf("2 - Financeiro\n");
  printf("3 - Relatórios\n");
  printf("4 - Sair");
  printf("\n\n\t\t:");
  scanf("%i", &menu);
  fflush(stdin);

  do{
    switch (menu) {
      case 1:
        do{
          //area de CADASTRO
          system("cls");
          printf("\n*****************************CADASTRO*****************************\n\n");
          printf("\tDigite onde deseja acessar...\n\n");
          printf("\n1 - Cadastrar cliente");
          printf("\n2 - Cadastrar produto");
          printf("\n3 - Cadastrar fornecedor");
          printf("\n4 - Sair");
          printf("\n\n\t\t:");
          scanf("%i", &menu1);
          //chamar função...
        }while(menu1!=4);
        break;
      case 2:
        do{
          system("cls");
          printf("\n*****************************FINANCEIRO*****************************\n\n");
          printf("\tDigite onde deseja acessar...\n\n");
          printf("\n1 - ");
          printf("\n2 - ");
          printf("\n3 - ");
          printf("\n4 - Sair");
          printf("\n\n\t\t:");
          scanf("%i", &menu2);
          //chamar função...
        }while(menu2!=4);
        break;
      case 3:
      do{
        system("cls");
        printf("\n*****************************RELATORIO*****************************\n\n");
        printf("\tDigite onde deseja acessar...\n\n");
        printf("\n1 - Relatório diário");
        printf("\n2 - Relatório");
        printf("\n3 - ");
        printf("\n4 - Sair");
        printf("\n\n\t\t:");
        scanf("%i", &menu3);
        //chamar função...
      }while(menu3!=4);
      break;
      case 4:
        return 0;
        break;
      default: printf("\nOpção INVALIDA, tente novamente....");
    }
  }while(menu!=4);



  return 0;
}
