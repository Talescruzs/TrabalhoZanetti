#include "personagem.h"
#include "itens.h"

//campo das funções:
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

