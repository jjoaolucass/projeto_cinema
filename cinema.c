#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cinema.h"

Filme filmes[MAX_FILMES];
int numFilmes = 0;

Usuario usuarios[MAX_USUARIOS];
int numUsuarios = 0;

Usuario usuarioAtual;

bool verificarEmail(const char *email) {
    if (strchr(email, '@') == NULL || strlen(email) >= 80) {
        return false;
    }
    for (int i = 0; i < numUsuarios; i++) {
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
            printf("E-mail inválido ou já cadastrado. Tente novamente.\n");
        }
    }

    printf("Digite sua idade: ");
    scanf("%d", &usuario->idade);

    usuarios[numUsuarios++] = *usuario;
    printf("Cadastro realizado com sucesso!\n");
}

void salvarUsuarioEmArquivo(Usuario *usuario) {
    FILE *arquivo = fopen("usuarios.txt", "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fwrite(usuario, sizeof(Usuario), 1, arquivo);
    fclose(arquivo);
}

void carregarUsuariosDeArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivo)) {
        if (numUsuarios < MAX_USUARIOS) {
            usuarios[numUsuarios++] = usuario;
        }
    }

    fclose(arquivo);
}

int buscaBinaria(Filme filmes[], int inicio, int fim, const char *nome) {
    if (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        
        int cmp = strcmp(filmes[meio].nome, nome);
        if (cmp == 0)
            return meio;
        
        if (cmp > 0)
            return buscaBinaria(filmes, inicio, meio - 1, nome);
        
        return buscaBinaria(filmes, meio + 1, fim, nome);
    }
    return -1;
}

void merge(Filme filmes[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Filme *L = malloc(n1 * sizeof(Filme));
    Filme *R = malloc(n2 * sizeof(Filme));

    if (L == NULL || R == NULL) {
        perror("Erro de alocacao de memoria");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n1; i++)
        L[i] = filmes[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = filmes[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].nome, R[j].nome) <= 0) {
            filmes[k] = L[i];
            i++;
        } else {
            filmes[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        filmes[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        filmes[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Filme filmes[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(filmes, l, m);
        mergeSort(filmes, m + 1, r);
        merge(filmes, l, m, r);
    }
}

bool login() {
    char nome[50];
    char senha[50];

    while (true) {
        printf("Digite seu nome de usuario: ");
        scanf(" %[^\n]", nome);
        printf("Digite sua senha: ");
        scanf(" %s", senha);

        for (int i = 0; i < numUsuarios; i++) {
            if (strcmp(nome, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
                usuarioAtual = usuarios[i];
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

    for (int i = 0; i < numFilmes; i++) {
        printf("%d. Nome: %s, Genero: %s, Ano: %d, Faixa etaria: %d\n", i + 1, filmes[i].nome, filmes[i].genero, filmes[i].ano, filmes[i].faixaEtaria);
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
    printf("Digite o novo nome do filme (ou pressione Enter para manter '%s'): ", filme->nome);
    char novoNome[100];
    scanf(" %[^\n]", novoNome);
    if (strlen(novoNome) > 0) {
        strcpy(filme->nome, novoNome);
    }

    printf("Digite o novo genero do filme (ou pressione Enter para manter '%s'): ", filme->genero);
    char novoGenero[50];
    scanf(" %[^\n]", novoGenero);
    if (strlen(novoGenero) > 0) {
        strcpy(filme->genero, novoGenero);
    }

    printf("Digite o novo ano de lancamento (ou pressione Enter para manter %d): ", filme->ano);
    int novoAno;
    if (scanf("%d", &novoAno) == 1) {
        filme->ano = novoAno;
    }
    
    printf("Digite a nova faixa etaria (ou pressione Enter para manter %d): ", filme->faixaEtaria);
    int novaFaixaEtaria;
    if (scanf("%d", &novaFaixaEtaria) == 1) {
        filme->faixaEtaria = novaFaixaEtaria;
    }

    printf("Filme editado com sucesso!\n");
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

    for (int i = escolha; i < numFilmes - 1; i++) {
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
    for (int i = 0; i < numFilmes; i++) {
        if (strcmp(filmes[i].genero, genero) == 0) {
            printf("Nome: %s, Ano: %d, Faixa etaria: %d\n", filmes[i].nome, filmes[i].ano, filmes[i].faixaEtaria);
            encontrado = true;
        }
    }

    if (!encontrado) {
        printf("Nenhum filme encontrado para o genero '%s'.\n", genero);
    }
}

void exibirDetalhesFilme() {
    char nome[100];
    printf("Digite o nome do filme para exibir detalhes: ");
    scanf(" %[^\n]", nome);

    int index = buscaBinaria(filmes, 0, numFilmes - 1, nome);
    if (index != -1) {
        Filme *filme = &filmes[index];
        printf("Nome: %s\nGenero: %s\nAno: %d\nFaixa etaria: %d\n", filme->nome, filme->genero, filme->ano, filme->faixaEtaria);
    } else {
        printf("Filme nao encontrado.\n");
    }
}

void menu() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Filme\n");
        printf("2. Listar Filmes\n");
        printf("3. Editar Filme\n");
        printf("4. Excluir Filme\n");
        printf("5. Buscar Filmes por Gênero\n");
        printf("6. Exibir Detalhes de um Filme\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
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
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 7);
}

void salvarUsuarios() {
    FILE *arquivo = fopen("usuarios.txt", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    fwrite(usuarios, sizeof(Usuario), numUsuarios, arquivo);
    fclose(arquivo);
}

void carregarUsuarios() {
    FILE *arquivo = fopen("usuarios.txt", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    numUsuarios = fread(usuarios, sizeof(Usuario), MAX_USUARIOS, arquivo);
    fclose(arquivo);
}

void salvarFilmes() {
    FILE *arquivo = fopen("filmes.txt", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    fwrite(filmes, sizeof(Filme), numFilmes, arquivo);
    fclose(arquivo);
}

void carregarFilmes() {
    FILE *arquivo = fopen("filmes.txt", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    numFilmes = fread(filmes, sizeof(Filme), MAX_FILMES, arquivo);
    fclose(arquivo);
}