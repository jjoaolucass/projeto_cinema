#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0
#define MAX_FILMES 5


typedef struct filme{
    char nome[100];
    char genero[50];
    int ano;
} Filme;


typedef struct usuario {
    char nome[50];
    char senha[50];
} Usuario;


Filme filmes[MAX_FILMES];
int numFilmes = 0;


Usuario usuarioAtual;


void cadastrarUsuario(Usuario *usuario) {
    printf("Digite seu nome de usuario: ");
    scanf(" %s", usuario->nome);
    printf("Digite sua senha: ");
    scanf(" %s", usuario->senha);
    printf("Cadastro realizado com sucesso!\n");
}


bool login(Usuario *usuario) {
    char nome[50];
    char senha[50];
    
    while (true) {
        printf("Digite seu nome de usuario: ");
        scanf(" %s", nome);
        printf("Digite sua senha: ");
        scanf(" %s", senha);
        
        if (strcmp(nome, usuario->nome) == 0 && strcmp(senha, usuario->senha) == 0) {
            strcpy(usuarioAtual.nome, nome);
            strcpy(usuarioAtual.senha, senha);
            return true;
        } else {
            printf("Usuario ou senha incorretos. Tente novamente.\n");
        }
    }
}


void mensagemBoasVindas(const Usuario *usuario) {
    printf("Bem-vindo ao Cinema, %s! Aproveite os melhores filmes em nossa programacao.\n", usuario->nome);
}


void cadastrarFilme() {
    if (numFilmes >= MAX_FILMES) {
        printf("Limite de filmes atingido.\n");
        return;
    }
    
    Filme *filme = &filmes[numFilmes];
    printf("Digite o nome do filme: ");
    scanf(" %[^\n]", filme->nome); 
    printf("Digite o genero do filme: ");
    scanf(" %[^\n]", filme->genero);
    printf("Digite o ano de lancamento: ");
    scanf("%d", &filme->ano);
    
    numFilmes++;
    printf("Filme '%s' cadastrado com sucesso!\n", filme->nome);
}


void listarFilmes() {
    int i;  
    if (numFilmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }
    
    for (i = 0; i < numFilmes; i++) {
        printf("%d. Nome: %s, Genero: %s, Ano: %d\n", i + 1, filmes[i].nome, filmes[i].genero, filmes[i].ano);
    }
}


void editarFilme() {
    listarFilmes();
    int escolha;
    printf("Escolha o numero do filme para editar: ");
    scanf("%d", &escolha);
    escolha--;  
    
    if (escolha < 0 || escolha >= numFilmes) {
        printf("Filme não encontrado.\n");
        return;
    }
    
    Filme *filme = &filmes[escolha];
    printf("Digite o novo nome (atual: %s): ", filme->nome);
    scanf(" %[^\n]", filme->nome);
    printf("Digite o novo genero (atual: %s): ", filme->genero);
    scanf(" %[^\n]", filme->genero);
    printf("Digite o novo ano (atual: %d): ", filme->ano);
    scanf("%d", &filme->ano);
    printf("Filme atualizado com sucesso!\n");
}


void excluirFilme() {
    listarFilmes();
    int escolha;
    int i;  
    
    printf("Escolha o numero do filme para excluir: ");
    scanf(" %d", &escolha);
    escolha--;  
    
    if (escolha < 0 || escolha >= numFilmes) {
        printf("Filme nao encontrado.\n");
        return;
    }
    

    for (i = escolha; i < numFilmes - 1; i++) {
        filmes[i] = filmes[i + 1];
    }
    numFilmes--;
    printf("Filme excluido com sucesso!\n");
}


void buscarFilmesPorGenero() {
    char genero[50];
    int i; 
    
    printf("Digite o genero para busca: ");
    scanf(" %[^\n]", genero);
    
    bool encontrado = false;
    for (i = 0; i < numFilmes; i++) {
        if (strcmp(filmes[i].genero, genero) == 0) {
            printf("Nome: %s, Ano: %d\n", filmes[i].nome, filmes[i].ano);
            encontrado = true;
        }
    }
    if (!encontrado) {
        printf("Nenhum filme encontrado para o genero informado.\n");
    }
}


void exibirDetalhesFilme() {
    listarFilmes();
    int escolha;
    int i;  
    
    printf("Escolha o numero do filme para exibir detalhes: ");
    scanf(" %d", &escolha);
    escolha--;  
    
    if (escolha < 0 || escolha >= numFilmes) {
        printf("Filme não encontrado.\n");
        return;
    }
    
    Filme *filme = &filmes[escolha];
    printf("Detalhes do Filme:\nNome: %s\nGenero: %s\nAno: %d\n", filme->nome, filme->genero, filme->ano);
}


void mostrarEstatisticas() {
    printf("Quantidade de filmes cadastrados: %d\n", numFilmes);
}


void menu() {
    while (true) {
        printf("\nMenu:\n");
        printf("1. Cadastrar Filme\n");
        printf("2. Listar Filmes\n");
        printf("3. Editar Filme\n");
        printf("4. Excluir Filme\n");
        printf("5. Buscar Filmes por Genero\n");
        printf("6. Exibir Detalhes do Filme\n");
        printf("7. Mostrar Estatisticas dos Filmes\n");
        printf("0. Sair\n");
        
        int escolha;
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        
        switch (escolha) {
            case 1:
                cadastrarFilme();
                break;
            case 2:
                listarFilmes();
                break;
            case 3:
                editarFilme();
                break;
            case 4:
                excluirFilme();
                break;
            case 5:
                buscarFilmesPorGenero();
                break;
            case 6:
                exibirDetalhesFilme();
                break;
            case 7:
                mostrarEstatisticas();
                break;
            case 0:
                printf("Saindo...\n");
                return;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

int main() {
    Usuario novoUsuario;
    cadastrarUsuario(&novoUsuario);

    if (login(&novoUsuario)) {
        mensagemBoasVindas(&usuarioAtual);
        menu();
    }
    return 0;
}