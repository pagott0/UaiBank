#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *arquivo; //cria 1 ponteiro do tipo arquivo
    
   //modo de abertura "a" (append) serve para adicionar dados no arquivo, não sobreescreve oq tava adicionado, ele adiciona 
    arquivo = fopen("dados.txt", "a"); //define para onde esse ponteiro do tipo FILE aponta, vai ser para um txt aberto/criado com o fopen. Recebe 2 parametros: nome do arquivo, w/r/a
    
    //posso usar o fprintf padrão
    char firstText[100] = "\nquem sabe sabe";
    fprintf(arquivo, "%s", firstText);

    //posso usar o fputs (exclusivo para strings)

    char secondText[100] = "\nadam sandler > leo dicaprio";
    fputs(secondText, arquivo);

    //e posso usar o fputc (exclusivo para chars)

    char thirdText = '7';
    fputc(thirdText, arquivo);




    fclose(arquivo); //confirma o fechamento e o salvamento do arquivo, bom sempre usar pra evitar erros.

    return 0;
}