#include <stdio.h>
#include <stdlib.h>

//campo dos structs:
struct Personagem{
    int vida;
    float ataque, velocidade;

}padrao = {50, 3.5, 2};
typedef struct Personagem Personagem_a;

//campo das funções:
struct Personagem muda_vida(struct Personagem personagem, int valor_dano){
    personagem.vida += valor_dano;

    return personagem;
}

int main()
{
    // definindo personagens:
    Personagem_a personagem1 = padrao;
    Personagem_a personagem2 = {30, 5, 2};

    // batalha entre eles:
    int flag = 1;
    while(flag == 1){
        switch(personagem1.vida<=0 && personagem2.vida<=0){
            case 1:
                printf("os dois morreram");
                flag = 2;
                break;
            default:
                if(personagem1.vida<=0){
                    printf("personagem 1 morreu");
                    flag = 2;
                    break;
                }
                if(personagem2.vida<=0){
                    printf("personagem 2 morreu");
                    flag = 2;
                    break;
                }
                printf("---------------------------\nBatalha rolando: \n\n\nDados da batalha:\n\n");
                printf("Vida P1: %d \n", personagem1.vida);
                printf("Vida P2: %d \n\n\n", personagem2.vida);
                personagem1 = muda_vida(personagem1, personagem2.ataque*-1);
                personagem2 = muda_vida(personagem2, personagem1.ataque*-1);

        }
    }

    return 0;
}

