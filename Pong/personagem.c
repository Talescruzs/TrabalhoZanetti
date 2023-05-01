#include "personagem.h"
#include "itens.h"
#include "frame.h"

//campo das fun��es:
struct Personagem cria_personagem(int vida, float ataque, float velocidade, struct Arma arma, struct Frame frame){
    struct Personagem personagem = {vida, ataque, velocidade, arma, frame};

    return personagem;
}

struct Personagem muda_vida(struct Personagem personagem, int valor){
    personagem.vida += valor;
    if(personagem.vida < 0){
        personagem.vida = 0;
    }
    return personagem;
}

int dano_real(struct Personagem personagem){
    printf("%d", personagem.arma.dano);
    return (personagem.ataque+personagem.arma.dano);
}

