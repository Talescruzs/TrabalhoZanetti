#ifndef __ITENS_H_
#define __ITENS_H_

struct Arma{
    char nome[20];
    int alcance, dano;
};

struct Pocao{
    int vida;
};

// funções:
struct Arma cria_arma(char nome[20], int alcance, int dano);

//presets:
struct Arma mao;
struct Arma adaga;
struct Arma espada;
struct Arma machado;
#endif
