#include "personagem.h"
#include "itens.h"

//campo das funções:
struct Personagem muda_vida(struct Personagem personagem, int valor){
    personagem.vida += valor;

    return personagem;
}

float dano_real(struct Personagem personagem){
    return personagem.ataque+personagem.arma.dano;
}

