#ifndef __PERSONAGEM_H_
#define __PERSONAGEM_H_
#include "frame.h"
#include "itens.h"
//CLASSES
struct Colision{
    int up, down, left, right;
};
struct Personagem{
    int vida, pos_x, pos_y, linha;
    float coluna, ataque, velocidade;
    struct Arma arma;
    struct Frame frame;
    struct Colision colision;
};
//FUNÇÕES:
    //ALTERA PERSONAGEM
struct Personagem cria_personagem(int vida, int pos_inicial_x, int pos_inicial_y, int linha, float coluna, float ataque, float velocidade, struct Arma arma, struct Frame frame, struct Colision colision, int level, int i);
struct Personagem muda_vida(struct Personagem personagem, int valor);
struct Personagem colision_parede(struct Personagem personagem, int tam_x, int tam_y);
struct Personagem colision_personagem(struct Personagem personagem, struct Personagem npc);
struct Personagem colision_final(struct Personagem personagem, struct Personagem npc, int tam_x, int tam_y);
void pegou_item(struct Personagem *personagem, struct Arma arma, int pos_x, int pos_y);
void ataque(struct Personagem personagem, struct Personagem *npcP);
void movimento_npc(struct Personagem personagem, struct Personagem *npcP, int tam_f);
    //CONFERE PERSONAGEM
int dano_real(struct Personagem personagem);
int *pega_frame(struct Personagem personagem);
//PRESET:
struct Colision colision;
#endif
