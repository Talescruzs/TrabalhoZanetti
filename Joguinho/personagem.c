#include "personagem.h"
#include "itens.h"

//campo das funções:
struct Personagem Cria_personagem(int vida, float ataque, float velocidade, struct Arma arma){
    struct Personagem personagem = { vida, ataque, velocidade, arma};

    return personagem;
};

struct Personagem muda_vida(struct Personagem personagem, int valor){
    personagem.vida += valor;
    if(personagem.vida < 0){
        personagem.vida = 0;
    }
    return personagem;
}

float dano_real(struct Personagem personagem){
    return personagem.ataque+personagem.arma.dano;
}

