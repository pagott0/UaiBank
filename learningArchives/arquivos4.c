#include <stdio.h>
#include <stdlib.h>

void copiarConteudoArquivo(FILE *arquivoOrigem, FILE *arquivoDestino){
    char leitor[1000];
    
    while(fgets(leitor, 1000, arquivoOrigem) != NULL){
        fputs(leitor, arquivoDestino);
    }

}

int main (){

    FILE *firstFile = fopen("banco1.txt", "r");
    if(firstFile == NULL){
        printf("Arquivo Inexistente");
        system("pause");
        return 0;
    }
    FILE *secondFile = fopen("banco2.txt", "w");
    if(secondFile == NULL){
        printf("Arquivo Inexistente");
        system("pause");
        return 0;
    }

    copiarConteudoArquivo(firstFile, secondFile);

    fclose(firstFile);
    fclose(secondFile);
    
    return 0;

}