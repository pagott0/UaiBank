#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

//LEMBRETE: UM BANCO DE DADOS TXT CHAMADO: bancodados.txt  DEVE SER CRIADO NA PASTA JUNTO DO CÓDIGO PARA EVITAR PROBLEMAS. OBRIGADO.



typedef struct
{
    char nome[100];
    int idade, id;
    double saldo;  //Note que aqui usei double, pois ao usar float estava tendo erro de precisão em números muito grandes.
} usuarios;

// Inicializa um ponteiro do tipo struct usuarios apontando para nenhum lugar da memória (NULL), vai ser usado para o array.
usuarios *dadosUsuarios = NULL;

/* basicamente o maiorId é usado para ter controle de sempre criar usuarios com ids maiores que os ultimos criados, e o contadorId
usado para ter controle do número de usuarios no array e na alocação de memória */
int contadorId = 0; 
int maiorId = 0;

// Função para puxar os usuarios do arquivo para o array dinâmico
void carregarUsuariosArquivo()
{
    FILE *arquivo = fopen("bancodados.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }

    usuarios newUser;

    // O fscanf retorna a quantidade de atribuições bem sucedidas. Logo, se conseguir atribuir nome, idade, saldo e id, retornará 4, e assim, fará as atribuições e continuará o loop
    while (fscanf(arquivo, "%s %d %lf %d", newUser.nome, &newUser.idade, &newUser.saldo, &newUser.id) == 4)
    {
        contadorId++;
        if (contadorId > maiorId)
        {
            maiorId = contadorId;
        }
        dadosUsuarios = (usuarios *)realloc(dadosUsuarios, contadorId * sizeof(usuarios));
        dadosUsuarios[contadorId - 1] = newUser;
    }

    fclose(arquivo);
}

// Carrega os usuarios do array dinâmico pro banco de dados txt, roda no fim do código. Atualiza as adições, remoções e transferências.
void carregarUsuariosArray()
{
    FILE *arquivo = fopen("bancodados.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }

    for (int i = 0; i < contadorId; i++)
    {
        fprintf(arquivo, "%s %d %.2f %d\n", dadosUsuarios[i].nome, dadosUsuarios[i].idade, dadosUsuarios[i].saldo, dadosUsuarios[i].id);
    }

    fclose(arquivo);
}

// Checa se o ponteiro aponta para o nulo, ou seja, quando a memória é insuficiente. Passa o ponteiro do array como parâmetro.
void checkMemory(usuarios *usersStorage)
{
    if (usersStorage == NULL)
    {
        printf("Memória insuficiente\n");
        system("pause");
        exit(1);
    }
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

    // Lê o nome do novo usuário com tratamento de erro para alocação de memória
    printf("Nome: ");
    fflush(stdin); // Clear the input buffer
    if (fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin) == NULL) {
        printf("Erro ao ler o nome do usuário.\n");
        return;
    }

    //Checa se o usuário digitou mais de 100 carac., se sim, retorna.
    //Note que checa se é maior do que 98 caracteres, para assim se prevenir de erros, visto que o limite do novoUsuario.nome é 100.
    int temp = 0;
    temp = strlen(novoUsuario.nome);
    if(temp >= 98) { 
        printf("Você não pode cadastrar um usuário com nome com mais de 100 caractéres, tente novamente\n");
        return;
    }
    
    //limpa o buffer para evitar problemas no proximo input. 
    char *p;
            if(p=strchr(novoUsuario.nome, '\n')){
                *p = 0;
            } else {
                scanf("%*[^\n]");scanf("%*c");
            }
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = '\0'; 

    //Checagem para ver se o usuario não digitou números ou caracteres especiais no nome. 
    for(int i = 0; i < strlen(novoUsuario.nome); i++){
        int tempCheck;
        if(novoUsuario.nome[i] != ' ') {
            tempCheck = isalpha(novoUsuario.nome[i]);  //Função isalpha ve se o carac. está no alfabeto, retorna 0 se não estiver.
            if(tempCheck == 0){
                printf("Um ou mais caracteres digitados não podem ser utilizado no nome, tente novamente apenas com letras do alfabeto.\n");
                system("pause");
                return;
            }

        }
    }

    // Lê a idade do novo usuário com tratamento de erro
    printf("Idade: ");
    if (scanf("%d", &novoUsuario.idade) != 1)
    {
        printf("Erro ao ler a idade do usuário.\n");
        return;
    }
    if(novoUsuario.idade <= 0){
        printf("Idade inválida, entre com um número maior do que 0\n");
        return;
    }

    // Lê o saldo do novo usuário com tratamento de erro
    printf("Saldo: ");
    if (scanf("%lf", &novoUsuario.saldo) != 1)
    {
        printf("Erro ao ler o saldo do usuário.\n");
        return;
    }
    if(novoUsuario.saldo <= 0){
        printf("Saldo inválido, entre com um número maior do que 0\n");
        return;
    }

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
    checkMemory(dadosUsuarios);

    // Adiciona o novo usuario do tipo struct usuarios a posição (contadorId - 1) do array dinâmico.
    // O primeiro usuario está sendo armazenado na posição 0 do array, tendo ID 1 (talvez possamos mudar isso para ficar sempre igual, mas por enquanto fica assim)
    dadosUsuarios[contadorId - 1] = novoUsuario;



    printf("\nUsuário adicionado com sucesso.\n");
    printf("ID do novo usuário: %d\n", novoUsuario.id);

    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }     //Limpa o buffer (tira o enter e o \n)
}


void addVariosUsuarios()
{

    int qtdUsuarios;
    printf("\nEscreva a quantidade de usuários que deseja adicionar: ");
    if (scanf("%d", &qtdUsuarios) != 1)     //Isso serve para ver se a leitura do scanf foi feita corretamente, se foi, retorna 1 e segue normalmente.
    {
        printf("Erro ao ler a quantidade, tente novamente apenas com números\n");
        return;
    }

    fflush(stdin);
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }     //Limpa o buffer (tira o enter e o \n)

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
    if (scanf("%d", &tempId) != 1)
    {
        printf("Erro ao ler o ID, tente novamente apenas com números\n");
        return;
    }

    // Se o id for maior que o maiorId já cadastrado, ou menor que 0, retorna, pois os IDS começam em 1, e nunca vai ter um ID maior do que o maior já cadastrado.
    if (tempId > maiorId || tempId <= 0)
    {
        printf("O ID não existe");
        fflush(stdin);
        int c;
        while ( (c = getchar()) != '\n' && c != EOF ) { }
        return;
    }

    // Itera por todos os IDS, até o ID desejado. Checa se o ID de algum usuario no vetor é igual ao ID desejado.
    for (int i = 0; i <= tempId; i++)
    {
        // Se algum ID for compativel, printa o nome, a idade e o saldo.
        if (dadosUsuarios[i].id == tempId)
        {
            printf("NOME: %s\n", dadosUsuarios[i].nome);
            printf("IDADE: %d\n", dadosUsuarios[i].idade);
            printf("SALDO: %f\n", dadosUsuarios[i].saldo);

            fflush(stdin); //Limpar buffer. Sim, eu sei que deveria ter criado uma função com essas 3 linhas já que usei muito elas (e provavelmente deveria ter usado mais)
            int c;
            while ( (c = getchar()) != '\n' && c != EOF ) { }

            return;
        }
    }

    // Se não existir nenhum ID compativel, printa "Usuario não encontrado"
    printf("\nUsuário não encontrado");
    return; 


    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }     //Limpa o buffer (tira o enter e o \n)
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
    if(valorTransf <= 0 ){
        printf("Saldo inválido, entre com um número maior que 0\n");
        return;
    }

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
    if (scanf("%d", &idRemovido) != 1)
    {
        printf("Erro ao ler o saldo do usuário.\n");
        return;
    }

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

        if(contadorId == 0){
            dadosUsuarios = (usuarios *)realloc(dadosUsuarios, 0);
        }
        else {
            dadosUsuarios = (usuarios *)realloc(dadosUsuarios, contadorId * sizeof(usuarios));
            checkMemory(dadosUsuarios);
        }
        // realoca memória com um usuário a menos.


        printf("Usuário removido com sucesso\n");
    }
    // se não achou o index com id igual ao id desejado, o booleano idExiste se mantém em falso, e printa usuário não encontrado.
    else
    {
        printf("Usuário não encontrado\n");
    }

}

int main()
{
    setlocale(LC_ALL, "Portuguese");


    // Aloca a memoria inicial para o array dinâmico.
    dadosUsuarios = (usuarios *)malloc(0 * sizeof(usuarios));
    checkMemory(dadosUsuarios);

    carregarUsuariosArquivo(); // Carrega os usuários do banco de dados para o array dinâmico.

    int opcaoSelecionada;


    printf("Bem-vindo ao UaiBank\n");

    do
    {

        imprimirOpcoes();
        opcaoSelecionada = getchar();

        int c;
        while ( (c = getchar()) != '\n' && c != EOF ) { }     //Limpa o buffer (tira o enter e o \n)

        opcaoSelecionada = opcaoSelecionada -'0';  //Converte de char pra int
        switch (opcaoSelecionada)
        {
        case 0:
            break;
        case 1:
            addUsuario();
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
        fflush(stdin); //Limpar buffer pro getchar
    } while (opcaoSelecionada != 0);

    carregarUsuariosArray();

    free(dadosUsuarios);
    return 0;
}