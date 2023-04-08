#ifndef __PERSONAGEM_H_
#define __PERSONAGEM_H_

struct Personagem{
    int vida;
    float ataque, velocidade;
};

struct Personagem muda_vida(struct Personagem personagem, int valor_dano);



#endif // TESTE_H_INCLUDED
