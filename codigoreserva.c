#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char nome[100];
    int idade, id;
    float saldo;
} Usuario;

void imprimirOpcoes() {
    printf("\n0. Fechar\n");
    printf("1. Adicionar usuário\n");
    printf("2. Adicionar vários usuários\n");
    printf("3. Buscar usuário por ID\n");
    printf("4. Transferência entre usuários\n");
    printf("5. Remover usuário\n");
}

Usuario* criarUsuario() {
    Usuario* novoUsuario = (Usuario*)malloc(sizeof(Usuario));
    if (novoUsuario == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    printf("\nEntre com nome, idade e saldo do novo usuário.\n");
    scanf("%s", novoUsuario->nome);
    scanf("%d", &novoUsuario->idade);
    scanf("%f", &novoUsuario->saldo);

    return novoUsuario;
}

void adicionarUsuario(Usuario** usuarios, int* contadorId) {
    Usuario* novoUsuario = criarUsuario();
    (*contadorId)++;
    novoUsuario->id = *contadorId;

    *usuarios = (Usuario*)realloc(*usuarios, (*contadorId) * sizeof(Usuario));
    if (*usuarios == NULL) {
        printf("Erro ao realocar memória.\n");
        exit(1);
    }

    (*usuarios)[(*contadorId) - 1] = *novoUsuario;

    printf("\nUsuário adicionado com sucesso.\n");
}

void adicionarVariosUsuarios(Usuario** usuarios, int* contadorId) {
    int qtdUsuarios;
    printf("\nEscreva a quantidade de usuários que deseja adicionar: ");
    scanf("%d", &qtdUsuarios);

    for (int i = 0; i < qtdUsuarios; i++) {
        adicionarUsuario(usuarios, contadorId);
    }
}

Usuario* buscarUsuarioPorId(Usuario* usuarios, int contadorId, int id) {
    for (int i = 0; i < contadorId; i++) {
        if (usuarios[i].id == id) {
            return &usuarios[i];
        }
    }

    return NULL;
}

void transferenciaEntreUsuarios(Usuario* usuarios, int contadorId) {
    int idOrigem, idDestino;
    float valorTransf;
    printf("\nEntre com o ID de origem: ");
    scanf("%d", &idOrigem);
    printf("\nEntre com o ID de destino: ");
    scanf("%d", &idDestino);
    printf("\nEntre com o valor a ser transferido: ");
    scanf("%f", &valorTransf);

    Usuario* usuarioOrigem = buscarUsuarioPorId(usuarios, contadorId, idOrigem);
    Usuario* usuarioDestino = buscarUsuarioPorId(usuarios, contadorId, idDestino);

    if (usuarioOrigem != NULL && usuarioDestino != NULL) {
        if (usuarioOrigem->saldo - valorTransf >= 0) {
            usuarioOrigem->saldo -= valorTransf;
            usuarioDestino->saldo += valorTransf;
            printf("\nTransferência realizada com sucesso.\n");
        } else {
            printf("\nSaldo insuficiente.\n");
        }
    } else {
        printf("\nUsuário(s) não encontrado(s).\n");
    }
}

void removerUsuario(Usuario** usuarios, int* contadorId, int id) {
    bool idExiste = false;

    for (int i = 0; i < *contadorId; i++) {
        if ((*usuarios)[i].id == id) {
            idExiste = true;
            for (int j = i; j < *contadorId - 1; j++) {
                (*usuarios)[j] = (*usuarios)[j + 1];
            }
            break;
        }
    }

    if (idExiste) {
        (*contadorId)--;
        *usuarios = (Usuario*)realloc(*usuarios, (*contadorId) * sizeof(Usuario));
        if (*usuarios == NULL && *contadorId > 0) {
            printf("Erro ao realocar memória.\n");
            exit(1);
        }
        printf("\nUsuário removido com sucesso.\n");
    } else {
        printf("\nUsuário não encontrado.\n");
    }
}

void liberarVetorUsuarios(Usuario* usuarios, int contadorId) {
    free(usuarios);
}

int main() {
    int opcaoSelecionada;
    int contadorId = 0;
    Usuario* usuarios = NULL;

    printf("Bem-vindo ao UaiBank\n");

    do {
        imprimirOpcoes();
        scanf("%d", &opcaoSelecionada);

        switch (opcaoSelecionada) {
            case 0:
                break;
            case 1:
                adicionarUsuario(&usuarios, &contadorId);
                break;
            case 2:
                adicionarVariosUsuarios(&usuarios, &contadorId);
                break;
            case 3: {
                int id;
                printf("\nDigite o ID do usuário a ser buscado: ");
                scanf("%d", &id);
                Usuario* usuario = buscarUsuarioPorId(usuarios, contadorId, id);
                if (usuario != NULL) {
                    printf("\nNome: %s\n", usuario->nome);
                    printf("Idade: %d\n", usuario->idade);
                    printf("Saldo: %.2f\n", usuario->saldo);
                } else {
                    printf("\nUsuário não encontrado.\n");
                }
                break;
            }
            case 4:
                transferenciaEntreUsuarios(usuarios, contadorId);
                break;
            case 5: {
                int id;
                printf("\nDigite o ID do usuário que você deseja remover: ");
                scanf("%d", &id);
                removerUsuario(&usuarios, &contadorId, id);
                break;
            }
            default:
                printf("\nOpção inválida.\n");
        }
    } while (opcaoSelecionada != 0);

    liberarVetorUsuarios(usuarios, contadorId);

    return 0;
}