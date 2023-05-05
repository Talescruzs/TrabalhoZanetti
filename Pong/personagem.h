#ifndef __PERSONAGEM_H_
#define __PERSONAGEM_H_
#include "itens.h"
#include "frame.h"

struct Personagem{
    int vida, pos_x, pos_y;
    float ataque, velocidade;
    struct Arma arma;
    struct Frame frame;
};

//funcoes:
struct Personagem cria_personagem(int vida, int pos_inicial_x, int pos_inicial_y, float ataque, float velocidade, struct Arma arma, struct Frame frame);

struct Personagem muda_vida(struct Personagem personagem, int valor);

int dano_real(struct Personagem personagem);

int *pega_frame(struct Personagem personagem);

#endif
