#include <stdio.h>

int main () {
    FILE *arquivo; //cria 1 ponteiro do tipo arquivo
    
    //modo w (writing) é para escrever no arquivo, se ele não existir, ele cria. ele sobreescreve o que tá escrito, não adiciona, cuidado.
    arquivo = fopen("dados.txt", "w"); //define para onde esse ponteiro do tipo FILE aponta, vai ser para um txt aberto/criado com o fopen. Recebe 2 parametros: nome do arquivo, w/r/a
    fprintf(arquivo, "pao de queijo mineiro"); //escreve no arquivo, tem q passar 2 parametros: ponteiro pro arquivo, texto a ser escrito.
    fclose(arquivo); //confirma o fechamento e o salvamento do arquivo, bom sempre usar pra evitar erros.

    return 0;
}