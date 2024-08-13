#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0
#define MAX_FILMES 5
#define MAX_USUARIOS 10

typedef struct filme {
    char nome[100];
    char genero[50];
    int ano;
    int faixaEtaria; 
} Filme;

typedef struct usuario {
    char nome[50];
    char senha[50]; 
    char email[80];
    int idade; 
} Usuario;

Filme filmes[MAX_FILMES];
int numFilmes = 0;

Usuario usuarios[MAX_USUARIOS];
int numUsuarios = 0;

Usuario usuarioAtual;

bool verificarEmail(const char *email) {
    if (strchr(email, '@') == NULL || strlen(email) >= 80) {
        return false;
    }
    int i;
    for (i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            return false;
        }
    }
    return true;
}

void cadastrarUsuario(Usuario *usuario) {
    char email[80];
    printf("Digite seu nome de usuario: ");
    scanf(" %[^\n]", usuario->nome);
    printf("Digite sua senha: ");
    scanf(" %s", usuario->senha);
    
    while (true) {
        printf("Digite seu e-mail: ");
        scanf(" %79[^\n]", email);
        
        if (verificarEmail(email)) {
            strcpy(usuario->email, email);
            break;
        } else {
            printf("E-mail inválido ou ja cadastrado. Tente novamente.\n");
        }
    }

    printf("Digite sua idade: ");
    scanf("%d", &usuario->idade);

    usuarios[numUsuarios++] = *usuario;
    printf("Cadastro realizado com sucesso!\n");
}

bool login() {
    char nome[50];
    char senha[50];

    while (true) {
        printf("Digite seu nome de usuario: ");
        scanf(" %[^\n]", nome);
        printf("Digite sua senha: ");
        scanf(" %s", senha);

        int i;
        for (i = 0; i < numUsuarios; i++) {
            if (strcmp(nome, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
                strcpy(usuarioAtual.nome, nome);
                strcpy(usuarioAtual.senha, senha);
                strcpy(usuarioAtual.email, usuarios[i].email);
                usuarioAtual.idade = usuarios[i].idade;
                return true;
            }
        }

        printf("Usuario ou senha incorretos. Tente novamente.\n");
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
    printf("Digite a faixa etaria do filme: ");
    scanf("%d", &filme->faixaEtaria);

    numFilmes++;
    printf("Filme '%s' cadastrado com sucesso!\n", filme->nome);
}

void listarFilmes() {
    if (numFilmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    int i;
    for (i = 0; i < numFilmes; i++) {
        printf("%d. Nome: %s, Genero: %s, Ano: %d, Faixa etaria: %d\n",
               i + 1, filmes[i].nome, filmes[i].genero, filmes[i].ano, filmes[i].faixaEtaria);
    }
}

void editarFilme() {
    listarFilmes();
    int escolha;
    printf("Escolha o numero do filme para editar: ");
    scanf("%d", &escolha);
    escolha--;

    if (escolha < 0 || escolha >= numFilmes) {
        printf("Filme nao encontrado.\n");
        return;
    }

    Filme *filme = &filmes[escolha];
    printf("Digite o novo nome (atual: %s): ", filme->nome);
    scanf(" %[^\n]", filme->nome);
    printf("Digite o novo genero (atual: %s): ", filme->genero);
    scanf(" %[^\n]", filme->genero);
    printf("Digite o novo ano (atual: %d): ", filme->ano);
    scanf("%d", &filme->ano);
    printf("Digite a nova faixa etaria (atual: %d): ", filme->faixaEtaria);
    scanf("%d", &filme->faixaEtaria);
    printf("Filme atualizado com sucesso!\n");
}

void excluirFilme() {
    listarFilmes();
    int escolha;
    printf("Escolha o numero do filme para excluir: ");
    scanf("%d", &escolha);
    escolha--;

    if (escolha < 0 || escolha >= numFilmes) {
        printf("Filme nao encontrado.\n");
        return;
    }

    int i;
    for (i = escolha; i < numFilmes - 1; i++) {
        filmes[i] = filmes[i + 1];
    }
    numFilmes--;
    printf("Filme excluido com sucesso!\n");
}

void buscarFilmesPorGenero() {
    char genero[50];
    printf("Digite o genero para busca: ");
    scanf(" %[^\n]", genero);

    bool encontrado = false;
    int i;
    for (i = 0; i < numFilmes; i++) {
        if (strcmp(filmes[i].genero, genero) == 0) {
            printf("Nome: %s, Ano: %d, Faixa etaria: %d\n",
                   filmes[i].nome, filmes[i].ano, filmes[i].faixaEtaria);
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
    printf("Escolha o numero do filme para exibir detalhes: ");
    scanf("%d", &escolha);
    escolha--;

    if (escolha < 0 || escolha >= numFilmes) {
        printf("Filme nao encontrado.\n");
        return;
    }

    Filme *filme = &filmes[escolha];
    printf("Detalhes do Filme:\nNome: %s\nGenero: %s\nAno: %d\nFaixa etaria: %d\n",
           filme->nome, filme->genero, filme->ano, filme->faixaEtaria);
}

void mostrarEstatisticas() {
    printf("Quantidade de filmes cadastrados: %d\n", numFilmes);
}

void menu() {
    while (true) {
        printf("\nMenu:\n");
        printf("1. Cadastrar filme\n");
        printf("2. Listar filmes\n");
        printf("3. Editar filme\n");
        printf("4. Excluir filme\n");
        printf("5. Buscar filmes por genero\n");
        printf("6. Exibir detalhes do filme\n");
        printf("7. Mostrar estatisticas dos filmes\n");
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
                printf("opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

int main() {
    Usuario novoUsuario;
    cadastrarUsuario(&novoUsuario);

    if (login()) {
        mensagemBoasVindas(&usuarioAtual);
        menu();
    }
    return 0;
}
