#include <stdio.h>
#include <stdio.h>
#include "personagem.h"


//campo das funções:
struct Personagem muda_vida(struct Personagem personagem, int valor_dano){
    personagem.vida += valor_dano;

    return personagem;
}

