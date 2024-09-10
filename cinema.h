#ifndef CINEMA_H
#define CINEMA_H

#include <stdbool.h>

#define MAX_FILMES 5
#define MAX_USUARIOS 10

typedef struct filme Filme;

typedef struct usuario Usuario;

extern Filme filmes[MAX_FILMES];
extern int numFilmes;

extern Usuario usuarios[MAX_USUARIOS];
extern int numUsuarios;

extern Usuario usuarioAtual;

int buscaBinaria(Filme filmes[], int inicio, int fim, const char *nome);
void merge(Filme filmes[], int l, int m, int r);
void mergeSort(Filme filmes[], int l, int r);
bool verificarEmail(const char *email);             
void cadastrarUsuario(Usuario *usuario);           
void salvarUsuarioEmArquivo(Usuario *usuario);       
void carregarUsuariosDeArquivo();                   
bool login();                                 
void mensagemBoasVindas(const Usuario *usuario);    
void cadastrarFilme();                           
void listarFilmes();                              
void editarFilme();                                
void excluirFilme();                              
void buscarFilmesPorGenero();                     
void exibirDetalhesFilme();                      
void menu();                                     
void salvarUsuarios();                               
void carregarUsuarios();                           
void salvarFilmes();                              
void carregarFilmes();                               

#endif