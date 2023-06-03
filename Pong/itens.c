#include "itens.h"
//CLASSES
struct Arma cria_arma(char n[20], int a, int d){
    struct Arma arma = {.nome = n, .alcance = a, .dano = d};
    return arma;
};
//PRESETS:
struct Arma mao = {" ",1,0};
struct Arma adaga = {"adaga", 1, 2};
struct Arma espada = {"espada", 2, 5};
struct Arma machado = {"machado", 3, 15};
struct Arma pica = {"pica", 3, 1000};
