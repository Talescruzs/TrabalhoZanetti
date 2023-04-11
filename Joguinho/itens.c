#include "itens.h"

struct Arma cria_arma(char nome[20], int alcance, float dano){
    struct Arma arma = {nome, alcance, dano};
};
