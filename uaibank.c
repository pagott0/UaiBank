#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* SUMÁRIO GERAL: - Criar vetor dinâmico
            - ver como mexe com arquivo
            - ver maneira de buscar no array pelo id e pegar o nome da struct
            - fazer os testes e adaptações para erros, por ex usar getchar ao inves de scanf e etc, tem q ver os slides do spatti
            - usar ponteiro, tem q ver onde, vai ser na base dos testes, acredito q tenha que usar pra passar para as funções conseguirem alterar struct/vetor */

// tem q ver se tem q adicionar return 0 nas funçoes

typedef struct
{
    char nome[100];
    int idade, id;
    float saldo;
} usuarios;

// Inicializa um ponteiro do tipo struct usuarios apontando para nenhum lugar da memória (NULL), vai ser usado para o array.
usuarios *dadosUsuarios = NULL;

/* basicamente o maiorId é usado para ter controle de sempre criar usuarios com ids maiores que os ultimos criados, e o contadorId
usado para ter controle do número de usuarios no array e na alocação de memória */
int contadorId = 0; // talvez tenha q passar ponteiro para as funções, n sei ainda, tem q testar
int maiorId = 0;

// FUNCOES CRUD PARA ARQUIVO
// Função para adicionar um novo usuário ao arquivo de log
void logCreateUser(usuarios user)
{
    FILE *file = fopen("log.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        return;
    }

    fprintf(file, "%s;%d;%d;%.2f\n", user.nome, user.idade, user.id, user.saldo);
    fclose(file);
}

// Função para exibir todos os usuários do arquivo de log
void logReadUsers()
{
    FILE *file = fopen("log.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        return;
    }

    usuarios user;
    while (fscanf(file, "%[^;];%d;%d;%f\n", user.nome, &user.idade, &user.id, &user.saldo) == 4)
    {
        printf("Nome: %s, Idade: %d, ID: %d, Saldo: %.2f\n", user.nome, user.idade, user.id, user.saldo);
    }

    fclose(file);
}

// Função para excluir um usuário do arquivo de log
void logDeleteUser(int id)
{
    FILE *file = fopen("log.txt", "r+");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        return;
    }

    usuarios user;
    long fileOffset;
    int found = 0;
    while (fscanf(file, "%[^;];%d;%d;%f\n", user.nome, &user.idade, &user.id, &user.saldo) == 4)
    {
        if (user.id == id)
        {
            found = 1;
            fileOffset = ftell(file) - sizeof(user);
            break;
        }
    }

    if (found)
    {
        fseek(file, fileOffset, SEEK_SET);
        fprintf(file, "DELETED;");
        printf("Usuário excluído com sucesso.\n");
    }
    else
    {
        printf("ID do usuário não encontrado.\n");
    }

    fclose(file);
}

void imprimirOpcoes()
{
    printf("\n0. Fechar\n");
    printf("1. Adicionar usuário\n");
    printf("2. Adicionar vários usuários\n");
    printf("3. Buscar usuário por ID\n");
    printf("4. Transferência entre usuários\n");
    printf("5. Remover usuário\n");
}

void addUsuario()
{
    // Cria novo usuario do tipo de dado struct usuarios {idade, nome, saldo, id}
    usuarios novoUsuario;

    // Recebe os dados do novo usuario
    printf("\nEntre com nome, idade e saldo do novo usuário.\n");
    scanf("%s", novoUsuario.nome);
    scanf("%d", &novoUsuario.idade);
    scanf("%f", &novoUsuario.saldo);

    // Aumenta o contador
    contadorId++;
    if (contadorId > maiorId)
    { // se o contador for maior que o maiorId já criado, o maiorId passa a ser o contador atual.
        maiorId = contadorId;
    }
    else
    {
        maiorId++; // se não for maior, soma um no maiorId, para definir o próximo id apartir dele.
    }

    // Define o ID do novo usuário para o contador atual.
    // Usa o maiorId para evitar que Ids sejam repetidos ao remover usuarios e decrementar o contador.
    novoUsuario.id = maiorId;

    // Realoca memória para o tamanho do contador de IDS. Por exemplo; se tiverem 3 ids (0, 1, 2), quer dizer que precisamos de 3 espaços de memória, um vetor com indices [0, 1, 2]
    dadosUsuarios = (usuarios *)realloc(dadosUsuarios, contadorId * sizeof(usuarios));

    // Adiciona o novo usuario do tipo struct usuarios a posição (contadorId - 1) do array dinâmico.
    // O primeiro usuario está sendo armazenado na posição 0 do array, tendo ID 1 (talvez possamos mudar isso para ficar sempre igual, mas por enquanto fica assim)
    dadosUsuarios[contadorId - 1] = novoUsuario;

    // simulação para ver se tava adicionando e removendo corretamente. APAGAR DEPOIS.
    // index //0 1 2 3
    // id //1 4 5 6
    // memoria 4 espaços
    // contador 4, maior 6

    // A FAZER: Atualizar o arquivo de texto

    printf("\nUsuário adicionado com sucesso.\n");
}

void addVariosUsuarios()
{
    int qtdUsuarios;
    printf("\nEscreva a quantidade de usuários que deseja adicionar: ");
    scanf("%d", &qtdUsuarios);
    for (int i = 0; i < qtdUsuarios; i++)
    {
        addUsuario();
    }
}

void buscarUsuarioPorId()
{

    // Recebe um ID que o usuario deseja buscar e armazena numa variavel temporaria.
    int tempId;
    printf("\nDigite o ID do usuário a ser buscado: ");
    scanf("%d", &tempId);

    // Itera por todos os IDS, até o ID desejado. Checa se o ID de algum usuario no vetor é igual ao ID desejado.
    for (int i = 0; i <= tempId; i++)
    {
        // Se algum ID for compativel, printa o nome, a idade e o saldo.
        if (dadosUsuarios[i].id == tempId)
        {
            printf("NOME: %s\n", dadosUsuarios[i].nome);
            printf("IDADE: %d\n", dadosUsuarios[i].idade);
            printf("SALDO: %f\n", dadosUsuarios[i].saldo);
            return;
        }
    }

    // Se não existir nenhum ID compativel, printa "Usuario não encontrado"
    printf("\nUsuário não encontrado");
    return; // vai jogar o usuario para digitar denovo? ou volta pro switch?

    // A FAZER: tem que ver se é importante retornar a struct (igual o GPT fez), ou se só printar os dados tá bom
}

void transferenciaEntreUsuarios()
{
    int id_origem, id_destino, indexOrigem, indexDestino;
    bool idOrigemEncontrado = false, idDestinoEncontrado = false;
    float valorTransf;

    printf("\nEntre com o ID de origem: ");
    scanf("%d", &id_origem);
    printf("\nEntre com o ID de destino: ");
    scanf("%d", &id_destino);
    printf("\nEntre com o valor a ser transferido: ");
    scanf("%f", &valorTransf);

    // Como os ids começam em 1, caso o id de origem ou de destino desejados sejam igual ou menor que 0, não precisa buscar, pois não vai existir.
    if (id_origem > 0 && id_destino > 0)
    {
        // se os id existem, busca qual index do array contém eles.
        for (int i = 0; i < contadorId; i++)
        {
            if (dadosUsuarios[i].id == id_origem)
            {
                indexOrigem = i;
                idOrigemEncontrado = true;
            }
            if (dadosUsuarios[i].id == id_destino)
            {
                indexDestino = i;
                idDestinoEncontrado = true;
            }
        }
    }

    // Caso tenha encontrado os IDS, os booleanos de controle vão estar true.
    if (idOrigemEncontrado && idDestinoEncontrado)
    {
        // checa se o saldo de origem é suficiente.
        if (dadosUsuarios[indexOrigem].saldo - valorTransf >= 0)
        {
            dadosUsuarios[indexOrigem].saldo = dadosUsuarios[indexOrigem].saldo - valorTransf;
            dadosUsuarios[indexDestino].saldo = dadosUsuarios[indexDestino].saldo + valorTransf;
            printf("\nTransferência realizada com sucesso.\n"); // talvez printar o nome dos usuarios?
        }
        else
        {
            printf("\nSaldo insuficiente\n");
        }
    }
    else
    {
        printf("\nUsuário(s) não encontrado(s)\n");
    }

    // atualizar arquivo
}

void removerUsuario()
{
    // id a ser removido
    int idRemovido;

    // booleano para controlar se o id foi encontrado.
    bool idExiste = false;

    // variavel para armazenar o index do usuario que deseja remover no array
    int indexToRemove;

    // recebe o id a ser removido
    printf("\nDigite o ID do usuário que você deseja remover: ");
    scanf("%d", &idRemovido);

    // Se o id buscado for menor ou igual a 0, não tem porque buscar no array, visto que os ids começam em 1
    if (idRemovido > 0)
    {
        // se o id existe, busca qual index do array contém ele.
        for (int i = 0; i < contadorId; i++)
        {
            if (dadosUsuarios[i].id == idRemovido)
            {
                indexToRemove = i;
                idExiste = true;
            }
        }
    }

    if (idExiste == true)
    {
        // uma vez que achou o index, itera apartir desse index até o contadorId, movendo cada dado uma casa a esquerda no array.
        for (int i = indexToRemove; i < contadorId; i++)
        {
            dadosUsuarios[i] = dadosUsuarios[i + 1];
        }

        // decrementa o contadorId para ter controle do número de usuarios
        contadorId--;

        // realoca memória com um usuário a menos.
        dadosUsuarios = (usuarios *)realloc(dadosUsuarios, contadorId * sizeof(usuarios));

        printf("Usuário removido com sucesso\n");
    }
    // se não achou o index com id igual ao id desejado, o booleano idExiste se mantém em falso, e printa usuário não encontrado.
    else
    {
        printf("Usuário não encontrado\n");
    }

    // TODO: atualizar arquivo de texto.

    // 1, 2, 3   ultimo id: 3 maiorId: 3, contadorId: 3
    // removo o 2:   1, 3,   contador q tava em 3, foi decrementado para 2, maiorId se mantem em 3;
    // quando eu for adicionar,   1, 4, 3,     adiciona na posição 2
}

int main()
{

    // Aloca a memoria inicial para o array dinâmico.
    // Por enquanto começa em 0, quando tiver arquivos vai ter q puxar o tamanho q ja tem no arquivo
    dadosUsuarios = (usuarios *)malloc(0 * sizeof(usuarios));

    int opcaoSelecionada;
    // Carregar usuarios do arquivo

    printf("Bem-vindo ao UaiBank\n");

    do
    {

        imprimirOpcoes();
        scanf("%d", &opcaoSelecionada); // Mudar para a medida de segurança que o usuario só pode digitar 1 carac.
        switch (opcaoSelecionada)
        {
        case 0:
            break;
        case 1:
            addUsuario();

            // isso aqui era pra testar se estava realmente adicionando no array. pode apagar quando já tiver pronto.
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
    } while (opcaoSelecionada != 0);

    free(dadosUsuarios);
    return 0;
}