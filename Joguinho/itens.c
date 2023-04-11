#include "itens.h"

struct Arma cria_arma(char n[20], int a, int d){
    struct Arma arma = {.nome = n, .alcance = a, .dano = d};
    return arma;
};
