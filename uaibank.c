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

int contadorId = 0; //talvez tenha q passar ponteiro para as funções, n sei ainda, tem q testar


typedef struct {
    char nome[100];
    int idade, id;
    float saldo;
} usuarios;





void imprimirOpcoes(){
    printf("\n0. Fechar\n");
    printf("1. Adicionar usuário\n");
    printf("2. Adicionar vários usuários\n");
    printf("3. Buscar usuário por ID\n");
    printf("4. Transferência entre usuários\n");
    printf("5. Remover usuário\n");

}

void addUsuario () {
    usuarios novoUsuario;
    printf("\nEntre com nome, idade e saldo do novo usuário.\n");
    scanf("%s", novoUsuario.nome);
    scanf("%d", novoUsuario.idade);
    scanf("%f", novoUsuario.saldo);
    contadorId++;
    novoUsuario.id = contadorId;
    //Adicionar a struct ao array
    //Atualizar o arquivo de texto
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
    int tempId;
    bool userFound = false;
    boolean
    printf("\nDigite o ID do usuário a ser buscado: ");
    scanf("%d", &tempId);
    //procurar usuario no array pelo id;
    if(userFound == true){
        //print informaçoes do usuario, tem q fazer uma maneira de ao encontrar o user por id, pegar o nome da struct dele
        //printf("%d", struct.nome);
        //printf("%d", struct.idade);
        //printf("%d", struct.saldo);
    }
    else {
        printf("\nUsuário não encontrado"); //vai jogar o usuario para digitar denovo? ou volta pro switch?
    }
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
        if(usuarioOrigem.saldo - valorTransf >= 0){ //tem q mudar pelo nome da struct dos usuarios
            usuarioDeOrigem.saldo = usuarioDeOrigem.saldo - valorTransf; //tem q mudar pelo nome da struct dos usuarios
            usuarioDeDestino.saldo = usuarioDeDestino.saldo + valorTransf; //tem q mudar pelo nome da struct dos usuarios
            printf("\nTransferência realizada com sucesso.\n"); //talvez printar o nome dos usuarios?
        }
        else {
            printf("\nSaldo insuficiente\n");
        }
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
    scanf("%d", idRemovido);
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
    int opcaoSelecionada;
    usuarios dadosUsuarios[10000]; //tem q deixar dinâmico
    //Carregar usuarios do arquivo

    printf("Bem-vindo ao UaiBank\n");

    do{
        imprimirOpcoes();
        scanf("%d", opcao); //Mudar para a medida de segurança que o usuario só pode digitar 1 carac.
        Switch (opcao) {
            case 0:
                break;
            case 1:
                addUsuario();
                break;
            case 2:
                addVariosUsuarios();
                break;
            case 3:
                buscarUsuarioPorId();
                break;
            case 4:
                transferenciaEntreUsuarios();
                break;
            case 5:
                removerUsuario();
                break;
            default:
                printf("\nOpção inválida.\n");
        }
    } while(opcao != 0);

    return 0;
}