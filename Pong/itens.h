#ifndef __ITENS_H_
#define __ITENS_H_
#include "frame.h"
//CLASSES
struct Arma{
    char nome[20];
    int alcance, dano;
    struct Frame frame;
};
struct Pocao{
    int vida;
};

//PRESETS:
struct Arma mao;
struct Arma adaga;
struct Arma espada;
struct Arma machado;
struct Arma pica;
#endif
