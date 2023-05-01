#ifndef __PERSONAGEM_H_
#define __PERSONAGEM_H_
#include "itens.h"
#include "frame.h"

struct Personagem{
    int vida;
    float ataque, velocidade;
    struct Arma arma;
    struct Frame frame;
};

//funcoes:
struct Personagem cria_personagem(int vida, float ataque, float velocidade, struct Arma arma, struct Frame frame);

struct Personagem muda_vida(struct Personagem personagem, int valor);

int dano_real(struct Personagem personagem);

#endif
