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
    float totalCusto=0, totalVenda=0, totalLucro;
    
    for (i=0; i<1; i++){
    
        fscanf(file, "%i\n", &produto[i].codigo);
        fgets(produto[i].descricao, 100, file);
        fscanf(file, "%i\n", &produto[i].qtd);
        fscanf(file, "%f\n", &produto[i].precoCusto);
        fscanf(file, "%f\n", &produto[i].precoVenda);
        
        totalCusto = totalCusto + produto[i].precoCusto;
        totalVenda = totalVenda + produto[i].precoCusto;
    }
    
    fclose(file);
    
    totalLucro = totalVenda-totalCusto;
    
    printf("Total Custo %f, Total Venda %f, Total Lucro %f", totalCusto, totalVenda, totalLucro);
    
}
