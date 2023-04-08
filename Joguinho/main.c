#include <stdio.h>
#include <stdlib.h>
#include "personagem.h"


int main()
{
    // definindo personagens:
    struct Personagem personagem1 = {50, 3, 2};
    struct Personagem personagem2 = {30, 5, 2};

    // batalha entre eles:
    int flag = 1;
    while(flag == 1){
        if(personagem1.vida<=0 || personagem2.vida<=0){
            if(personagem1.vida<=0 && personagem2.vida<=0){
                printf("os dois morreram");
                flag = 2;
            }else if(personagem1.vida<=0){
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
            personagem1 = muda_vida(personagem1, personagem2.ataque*-1);
            personagem2 = muda_vida(personagem2, personagem1.ataque*-1);
        }
    }

    return 0;
}

