#include<stdio.h>
#include<stdlib.h>

typedef struct cadProduto {
    int codigo;
    char descricao[100];
    int qtd;
    float precoCusto;
    float precoVenda;
} Produto;

main(){
    
    FILE *file, *file2;
        
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
    
    controle =0;
    
    printf ("Quantidade de produtos vendidos: ");
    scanf ("%d", &produtoEncotrado.qtd);
    printf ("\n\n");
    
    printf ("Código:         %d\n", produtoEncotrado.codigo);
    printf ("%s\n", produtoEncotrado.descricao);
    printf ("Quantidade:     %d", produtoEncotrado.qtd);
    printf ("Preço de venda: %f\n\n", produtoEncotrado.precoVenda);
    
    printf ("Digite 1, se deseja lançar venda, 0 caso não: ");
    scanf ("%d", &controle);
    
    if(controle!=1) exit(0);
    
    
    valorVenda = produtoEncotrado.precoVenda*produtoEncotrado.qtd;
    valorLucro = valorVenda - produtoEncotrado.precoCusto*produtoEncotrado.qtd;
    
    file2 = fopen ("financeiro.txt", "a");
    
    fscanf(file, "%f\n", &totalVenda);
    fscanf(file, "%f\n", &totalLucro);
    
    fprintf ("%f\n", codigo);
    fprintf ("%d\n", )
        
    fclose(file2);
}
