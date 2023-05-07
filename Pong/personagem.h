#ifndef __PERSONAGEM_H_
#define __PERSONAGEM_H_
#include "itens.h"
#include "frame.h"

//enum Colision{UP_C, DOWN_C, LEFT_C, RIGHT_C};

struct Colision{
    int up, down, left, right;
};

struct Personagem{
    int vida, pos_x, pos_y;
    float ataque, velocidade;
    struct Arma arma;
    struct Frame frame;
    struct Colision colision;
};

//funcoes:
//ALTERA PERSONAGEM
struct Personagem cria_personagem(int vida, int pos_inicial_x, int pos_inicial_y, float ataque, float velocidade, struct Arma arma, struct Frame frame, struct Colision colision);
struct Personagem muda_vida(struct Personagem personagem, int valor);
struct Personagem colision_parede(struct Personagem personagem, int tam_x, int tam_y);
struct Personagem colision_personagem(struct Personagem personagem, struct Personagem npc);
struct Personagem colision_final(struct Personagem personagem, struct Personagem npc, int tam_x, int tam_y);
struct Personagem ataque(struct Personagem personagem, struct Personagem npc, int current_frame);

//CONFERE PERSONAGEM
int dano_real(struct Personagem personagem);
int *pega_frame(struct Personagem personagem);

//preset:
struct Colision colision;

#endif
