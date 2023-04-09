#ifndef __PERSONAGEM_H_
#define __PERSONAGEM_H_
#include "itens.h"

struct Personagem{
    int vida;
    float ataque, velocidade;
    struct Arma arma;
};

//funcoes:
struct Personagem muda_vida(struct Personagem personagem, int valor);

float dano_real(struct Personagem personagem);

#endif
