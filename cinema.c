#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cinema.h"

#define MAX_FILMES 100
#define MAX_USUARIOS 100

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
    fgets(usuario->nome, sizeof(usuario->nome), stdin);
    strtok(usuario->nome, "\n");  // Remove newline
    
    printf("Digite sua senha: ");
    fgets(usuario->senha, sizeof(usuario->senha), stdin);
    strtok(usuario->senha, "\n");

    while (true) {
        printf("Digite seu e-mail: ");
        fgets(email, sizeof(email), stdin);
        strtok(email, "\n");
        
        if (verificarEmail(email)) {
            strcpy(usuario->email, email);
            break;
        } else {
            printf("E-mail inválido ou já cadastrado. Tente novamente.\n");
        }
    }

    printf("Digite sua idade: ");
    scanf("%d", &usuario->idade);
    getchar();  // Consome o newline após o scanf

    usuarios[numUsuarios++] = *usuario;
    printf("Cadastro realizado com sucesso!\n");
}

void salvarUsuarioEmArquivo(Usuario *usuario) {
    FILE *arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fwrite(usuario, sizeof(Usuario), 1, arquivo);
    fclose(arquivo);
}

void carregarUsuariosDeArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "r");
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
        fgets(nome, sizeof(nome), stdin);
        strtok(nome, "\n");
        printf("Digite sua senha: ");
        fgets(senha, sizeof(senha), stdin);
        strtok(senha, "\n");

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
    fgets(filme->nome, sizeof(filme->nome), stdin);
    strtok(filme->nome, "\n");

    printf("Digite o genero do filme: ");
    fgets(filme->genero, sizeof(filme->genero), stdin);
    strtok(filme->genero, "\n");

    printf("Digite o ano de lancamento: ");
    scanf("%d", &filme->ano);
    getchar();

    printf("Digite a faixa etaria do filme: ");
    scanf("%d", &filme->faixaEtaria);
    getchar();

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
    getchar();  // Consome newline

    if (escolha < 0 || escolha >= numFilmes) {
        printf("Filme nao encontrado.\n");
        return;
    }

    Filme *filme = &filmes[escolha];

    printf("Digite o novo nome do filme (ou pressione Enter para manter '%s'): ", filme->nome);
    char novoNome[100];
    fgets(novoNome, sizeof(novoNome), stdin);
    strtok(novoNome, "\n");
    if (strlen(novoNome) > 0) {
        strcpy(filme->nome, novoNome);
    }

    printf("Digite o novo genero do filme (ou pressione Enter para manter '%s'): ", filme->genero);
    char novoGenero[50];
    fgets(novoGenero, sizeof(novoGenero), stdin);
    strtok(novoGenero, "\n");
    if (strlen(novoGenero) > 0) {
        strcpy(filme->genero, novoGenero);
    }

    printf("Digite o novo ano de lancamento (ou pressione Enter para manter %d): ", filme->ano);
    char novoAnoStr[10];
    fgets(novoAnoStr, sizeof(novoAnoStr), stdin);
    if (strlen(novoAnoStr) > 1) {
        int novoAno = atoi(novoAnoStr);
        filme->ano = novoAno;
    }

    printf("Digite a nova faixa etaria (ou pressione Enter para manter %d): ", filme->faixaEtaria);
    char novaFaixaEtariaStr[10];
    fgets(novaFaixaEtariaStr, sizeof(novaFaixaEtariaStr), stdin);
    if (strlen(novaFaixaEtariaStr) > 1) {
        int novaFaixaEtaria = atoi(novaFaixaEtariaStr);
        filme->faixaEtaria = novaFaixaEtaria;
    }

    printf("Filme atualizado com sucesso!\n");
}

void excluirFilme() {
    listarFilmes();
    int escolha;
    printf("Escolha o numero do filme para excluir: ");
    scanf("%d", &escolha);
    escolha--;
    getchar();  // Consome newline

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

void exibirDetalhesFilme() {
    char nome[100];
    printf("Digite o nome do filme: ");
    fgets(nome, sizeof(nome), stdin);
    strtok(nome, "\n");

    mergeSort(filmes, 0, numFilmes - 1);  // Garantindo que a lista esteja ordenada

    int indice = buscaBinaria(filmes, 0, numFilmes - 1, nome);
    if (indice == -1) {
        printf("Filme nao encontrado.\n");
    } else {
        Filme *filme = &filmes[indice];
        printf("Nome: %s, Genero: %s, Ano: %d, Faixa etaria: %d\n", filme->nome, filme->genero, filme->ano, filme->faixaEtaria);
    }
}

int main() {
    carregarUsuariosDeArquivo();

    if (login()) {
        mensagemBoasVindas(&usuarioAtual);

        while (true) {
            int opcao;
            printf("\nMenu:\n1. Cadastrar Filme\n2. Listar Filmes\n3. Editar Filme\n4. Excluir Filme\n5. Exibir Detalhes de um Filme\n6. Sair\nEscolha uma opcao: ");
            scanf("%d", &opcao);
            getchar();  // Consome newline

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
                    exibirDetalhesFilme();
                    break;
                case 6:
                    printf("Saindo...\n");
                    return 0;
                default:
                    printf("Opcao invalida.\n");
            }
        }
    }

    return 0;
}