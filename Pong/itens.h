#ifndef __ITENS_H_
#define __ITENS_H_
//CLASSES
struct Arma{
    char nome[20];
    int alcance, dano;
};
struct Pocao{
    int vida;
};
//FUNÇÕES:
struct Arma cria_arma(char nome[20], int alcance, int dano);
//PRESETS:
struct Arma mao;
struct Arma adaga;
struct Arma espada;
struct Arma machado;
struct Arma pica;
#endif
