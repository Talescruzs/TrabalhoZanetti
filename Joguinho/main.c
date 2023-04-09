#include <stdio.h>
#include <stdlib.h>
#include "personagem.h"
#include "itens.h"
//personagens:
#define HEROI(...) { .vida = 50, .ataque = 3, .velocidade = 2, .arma = {"nada", 1, 0}}
#define INIMIGO_BASICO(...) { .vida = 10, .ataque = 1, .velocidade = 5, .arma = {"nada", 1, 0}}
#define INIMIGO_MEDIO(...) { .vida = 30, .ataque = 3, .velocidade = 3, .arma = {"nada", 2, 0}}
#define INIMIGO_CHEFE(...) { .vida = 150, .ataque = 7, .velocidade = 2, .arma = {"nada", 3, 0}}
//armas:
#define ARMA_BASICA(...) { .nome = "adaga", .alcance = 1, .dano = 2}
#define ARMA_MEDIA(...) { .nome = "espada", .alcance = 2, .dano = 5}
#define ARMA_BOA(...) { .nome = "machado", .alcance = 3, .dano = 15}
//pocao:
#define POCAO(...) { .vida = 5}

int main()
{
    //itens:
    struct Arma arma = ARMA_BASICA();
    struct Pocao pocao = POCAO();

    // definindo personagens:
    struct Personagem personagem1 = HEROI();
    struct Personagem personagem2 = INIMIGO_CHEFE();

    //equipar:
    personagem1.arma = arma;

    // batalha entre eles:
    int flag = 1;
    while(flag == 1){
        if(personagem1.vida==0 || personagem2.vida==0){
            if(personagem1.vida==0 && personagem2.vida==0){
                printf("os dois morreram");
                flag = 2;
            }else if(personagem1.vida==0){
                printf("personagem 1 morreu");
                flag = 2;
            }else{
                printf("personagem 2 morreu");
                flag = 2;
            }
        }else{
            printf("---------------------------\nBatalha rolando: \n\n\nDados da batalha:\n\n");
            printf("Vida P1: %d \n", personagem1.vida);
            printf("Vida P2: %d \n\n\n", personagem2.vida);
            personagem1 = muda_vida(personagem1, pocao.vida);
            personagem1 = muda_vida(personagem1, dano_real(personagem2)*-1);
            personagem2 = muda_vida(personagem2, dano_real(personagem1)*-1);
        }
    }
    return 0;
}

