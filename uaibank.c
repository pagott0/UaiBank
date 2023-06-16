#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* SUMÁRIO GERAL: - Criar vetor dinâmico
            - ver como mexe com arquivo
            - ver maneira de buscar no array pelo id e pegar o nome da struct 
            - fazer os testes e adaptações para erros, por ex usar getchar ao inves de scanf e etc, tem q ver os slides do spatti
            - usar ponteiro, tem q ver onde, vai ser na base dos testes, acredito q tenha que usar pra passar para as funções conseguirem alterar struct/vetor */


//tem q ver se tem q adicionar return 0 nas funçoes

typedef struct {
    char nome[100];
    int idade, id;
    float saldo;
} usuarios;


//Inicializa um ponteiro do tipo struct usuarios apontando para nenhum lugar da memória (NULL), vai ser usado para o array.
usuarios *dadosUsuarios = NULL;


int contadorId = 0; //talvez tenha q passar ponteiro para as funções, n sei ainda, tem q testar









void imprimirOpcoes(){
    printf("\n0. Fechar\n");
    printf("1. Adicionar usuário\n");
    printf("2. Adicionar vários usuários\n");
    printf("3. Buscar usuário por ID\n");
    printf("4. Transferência entre usuários\n");
    printf("5. Remover usuário\n");

}

void addUsuario() {
    //Cria novo usuario do tipo de dado struct usuarios {idade, nome, saldo, id}
    usuarios novoUsuario;

    //Recebe os dados do novo usuario
    printf("\nEntre com nome, idade e saldo do novo usuário.\n");
    scanf("%s", novoUsuario.nome);
    scanf("%d", &novoUsuario.idade);
    scanf("%f", &novoUsuario.saldo);

    //Aumenta o contador
    contadorId++;

    //Define o ID do novo usuário para o contador atual.
    novoUsuario.id = contadorId;

    //Realoca memória para o tamanho do contador de IDS. Por exemplo; se tiverem 3 ids (0, 1, 2), quer dizer que precisamos de 3 espaços de memória, um vetor com indices [0, 1, 2]
    dadosUsuarios = (usuarios*)realloc(dadosUsuarios, contadorId * sizeof(usuarios));


    //Adiciona o novo usuario do tipo struct usuarios a posição (contadorId - 1) do array dinâmico.
    //O primeiro usuario está sendo armazenado na posição 0 do array, tendo ID 1 (talvez possamos mudar isso para ficar sempre igual, mas por enquanto fica assim)
    dadosUsuarios[contadorId - 1] = novoUsuario;

    
    // A FAZER: Atualizar o arquivo de texto

    printf("\nUsuário adicionado com sucesso.\n");
}



void addVariosUsuarios(){
    int qtdUsuarios;
    printf("\nEscreva a quantidade de usuários que deseja adicionar: ");
    scanf("%d", &qtdUsuarios);
    for(int i = 0; i < qtdUsuarios; i++){
        addUsuario();
    }

}

void buscarUsuarioPorId() {

    //Recebe um ID que o usuario deseja buscar e armazena numa variavel temporaria.
    int tempId;
    printf("\nDigite o ID do usuário a ser buscado: ");
    scanf("%d", &tempId);


    //Itera por todos os IDS, até o ID desejado. Checa se o ID de algum usuario no vetor é igual ao ID desejado.
    for(int i = 0; i <= tempId; i++){
        //Se algum ID for compativel, printa o nome, a idade e o saldo.
        if(dadosUsuarios[i].id == tempId){
            printf("NOME: %s\n", dadosUsuarios[i].nome);
            printf("IDADE: %d\n", dadosUsuarios[i].idade);
            printf("SALDO: %f\n", dadosUsuarios[i].saldo);
            return;
        }
    }

    //Se não existir nenhum ID compativel, printa "Usuario não encontrado"
    printf("\nUsuário não encontrado");
    return; //vai jogar o usuario para digitar denovo? ou volta pro switch?


    //A FAZER: tem que ver se é importante retornar a struct (igual o GPT fez), ou se só printar os dados tá bom

}


void transferenciaEntreUsuarios(){
    int id_origem, id_destino;
    bool idOrigemEncontrado = false, idDestinoEncontrado = false;
    float valorTransf;
    printf("\nEntre com o ID de origem: ");
    scanf("%d", &id_origem);
    printf("\nEntre com o ID de destino: ");
    scanf("%d", &id_destino);
    printf("\nEntre com o valor a ser transferido: ");
    scanf("%f", &valorTransf);
    //procura os usuarios no array pelos ids, nao da pra usar a funçao buscarUsuario pq ela printa tds as informacoes do user na tela e isso eh desnecessario
    //dnv precisa arranjar uma maneira de buscar pelo id e pegar o nome da struct do user
    if( idOrigemEncontrado && idDestinoEncontrado){
        printf("debug 2\n");
        /* if(usuarioOrigem.saldo - valorTransf >= 0){ //tem q mudar pelo nome da struct dos usuarios
            usuarioDeOrigem.saldo = usuarioDeOrigem.saldo - valorTransf; //tem q mudar pelo nome da struct dos usuarios
            usuarioDeDestino.saldo = usuarioDeDestino.saldo + valorTransf; //tem q mudar pelo nome da struct dos usuarios
            printf("\nTransferência realizada com sucesso.\n"); //talvez printar o nome dos usuarios?
        }
        else {
            printf("\nSaldo insuficiente\n");
        } */
    }
    else {
        printf("\nUsuário(s) não encontrado(s)\n");
    }

    //atualizar array de usuarios
    //atualizar arquivo

}

void removerUsuario(){
    int idRemovido;
    bool idExiste = false;
    printf("\nDigite o ID do usuário que você deseja remover: ");
    scanf("%d", &idRemovido);
    //procurar o usuario no array
    //remover usuario do array (como vou fazer isso? n sei)
    //atualiazr arquivo de texto
    if(idExiste){    //ver maneira de pegar struct do user pelo id
        printf("\nUsuário removido com sucesso.\n");
    }
    else {
        printf("\nUsuário não encontrado.\n");
    }
    


}

int main() {
    
    //Aloca a memoria inicial para o array dinâmico.
    //Por enquanto começa em 0, quando tiver arquivos vai ter q puxar o tamanho q ja tem no arquivo
    dadosUsuarios = (usuarios*)malloc(0*sizeof(usuarios));

    int opcaoSelecionada;
    //Carregar usuarios do arquivo

    printf("Bem-vindo ao UaiBank\n");

    do{
         

        
        imprimirOpcoes();
        scanf("%d", &opcaoSelecionada); //Mudar para a medida de segurança que o usuario só pode digitar 1 carac.
        switch (opcaoSelecionada) {
            case 0:
                break;
            case 1:
                addUsuario();

                //isso aqui era pra testar se estava realmente adicionando no array. pode apagar quando já tiver pronto.
                /* printf("Nome do ENZO: %s\n", dadosUsuarios[0].nome);
                printf("Idade do ENZO: %d\n", dadosUsuarios[0].idade);
                printf("Saldo do ENZO: %f\n", dadosUsuarios[0].saldo);
                printf("ID do ENZO: %d\n", dadosUsuarios[0].id); */


                break;
            case 2:
                addVariosUsuarios();
                break;
            case 3:
                buscarUsuarioPorId(dadosUsuarios);
                break;
            case 4:
                transferenciaEntreUsuarios();
                break;
            case 5:
                removerUsuario();
                break;
            default:
                printf("\nOpção inválida.\n");
                break;
        }
    } while(opcaoSelecionada != 0);

    free(dadosUsuarios);
    return 0;
}