#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    //Sobre leitura de arquivos

    FILE *arquivo;
    arquivo = fopen("dados.txt", "r");   //modo r para leitura

    fprintf(arquivo, "10 20 30");

    //tem que ficar atento para leituras de arquivos que não existem, pq ele não cria um arquivo, diferente do modo w.
    //por isso, tem q checar se o ponteiro é NULL
    if(arquivo == NULL){
        printf("Arquivo inexistente ou vazio\n");
        system("pause");
        return 0;
    }
    
    //int x, y, z;

    /* fscanf(arquivo, "%d %d %d", &x, &y, &z); //scanf para leitura em arquivos. tem que passar o ponteiro apontando para o arquivo desejado 
    //fscanf é meio ruim pq o arquivo tem q tar formatado perfeitamente para q a leitura de certo

    printf("%d %d %d\n", x, y, z); */

   /*  char palavra[1000];
    fscanf(arquivo, "%s", palavra);   //nesse formato, le uma string até que encontre um espaço
    printf("%s", palavra); */

   /*  char frase[1000];

    fgets(frase, 1000, arquivo);  //fgets pega uma string até encontrar uma quebra de linha, pega uma linha, da pra pegar td o arquivo usando um while
    printf("\n%s\n", frase); */

    char textocompleto[1000];
    char textocompleto2[1000];

    while(fgets(textocompleto, 1000, arquivo) != NULL){      //le cada frase, printa, e passa pra próxima
        printf("%s",textocompleto);
        strcat(textocompleto2, textocompleto);       //aqui eu to concatenando cada frase em uma string do texto completo
    }

    printf("\nAAAAAAAAA: %s", textocompleto2);

    


    fclose(arquivo);

    return 0;
}