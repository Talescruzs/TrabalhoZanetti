#ifndef __ITENS_H_
#define __ITENS_H_

struct Arma{
    char nome[20];
    int alcance;
    float dano;
};

struct Pocao{
    int vida;
};

// fun��es:
struct Arma cria_arma(char nome[20], int alcance, float dano);

#endif
