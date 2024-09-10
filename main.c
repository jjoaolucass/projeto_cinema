#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cinema.h"


int main() {
    Usuario novoUsuario;

    carregarUsuarios();
    carregarFilmes();

    cadastrarUsuario(&novoUsuario);

    if (login()) {
        mensagemBoasVindas(&usuarioAtual);
        menu();
    } else {
        printf("Falha no login.\n");
    }

    salvarUsuarios();
    salvarFilmes();

    return 0;
}