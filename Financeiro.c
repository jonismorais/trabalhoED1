#include<stdio.h>
#include<stdlib.h>

typedef struct cadProduto {
    int codigo;
    char descricao[100];
    int qtd;
    float precoCusto;
    float precoVenda;
} Produto;

FILE *file;

main(){
    
    file = fopen("produtos.txt", "r"); //Verificar nome do arquivo
    
    if (file==NULL){
        printf("Não existe um arquivo de cadastro, ir para a parte de cadastramento");
        exit(0);
    }
    
    Produto produto[10];
    int i;
   
    
    for (i=0; i<10; i++){
    
        fscanf(file, "%d\n", &produto[i].codigo);
        fgets(produto[i].descricao, 100, file);
        fscanf(file, "%d\n", &produto[i].qtd);
        fscanf(file, "%f\n", &produto[i].precoCusto);
        fscanf(file, "%f\n", &produto[i].precoVenda);
        
    }
    
    fclose(file);
    
    Produto produtoEncotrado;
    int controle=0;
    float totalCusto=0, totalVenda=0, totalLucro=0, valorVenda, valorLucro;
    
    
    do{
        printf("Informe o código do produto: ");
        scanf("%d", &produtoEncotrado.codigo);
        for (i=0; i<10; i++){
            if (produtoEncotrado.codigo == produto[i].codigo){
                produtoEncotrado.descricao = produto[i].descricao;
                produtoEncotrado.precoCusto = produto[i].precoCusto;
                produtoEncotrado.precoVenda = produto[i].precoVenda;
                printf ("Código: %d\n", produtoEncotrado.codigo);
                printf ("%s\n", produtoEncotrado.descricao);
                printf ("Preço de venda: %f\n", produtoEncotrado.precoVenda);
                printf ("Digite 1, se este é o produto que deseja, 0 caso não seja: ");
                scanf ("%i", &controle);
                
            }else{
                
                printf ("Código do Produto não encontrado \n");
                
            }
        }    
    }while(controle==1);
    
    printf ("Quantidade de produtos vendidos: ");
    scanf ("%d", &produtoEncotrado.qtd);
    
    valorVenda = produtoEncotrado.precoVenda*produtoEncotrado.qtd;
    valorLucro = valorVenda - produtoEncotrado.precoCusto*produtoEncotrado.qtd;
    
    totalLucro = totalLucro + valorLucro;
    
    printf("Total Custo %f, Total Venda %f, Total Lucro %f", totalCusto, totalVenda, totalLucro);
    
}
