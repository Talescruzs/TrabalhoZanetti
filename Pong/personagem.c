#include "personagem.h"
#include "itens.h"
#include "frame.h"

//campo das funções:
struct Personagem cria_personagem(int vida, int pos_inicial_x, int pos_inicial_y, float ataque, float velocidade, struct Arma arma, struct Frame frame, struct Colision colision){
    struct Personagem personagem = {vida, pos_inicial_x, pos_inicial_y, ataque, velocidade, arma, frame, colision};

    return personagem;
}
struct Personagem muda_vida(struct Personagem personagem, int valor){
    personagem.vida += valor;
    if(personagem.vida < 0){
        personagem.vida = 0;
    }
    return personagem;
}

struct Personagem colision_parede(struct Personagem personagem, int tam_x, int tam_y){
    if(personagem.pos_x<=-30){
        personagem.colision.left = 1;
    }else{
        personagem.colision.left = 0;
    }
    if(personagem.pos_x>=tam_x-160){
        personagem.colision.right = 1;
    }else{
        personagem.colision.right = 0;
    }
    if(personagem.pos_y<=-25){
        personagem.colision.up = 1;
    }else{
        personagem.colision.up = 0;
    }
    if(personagem.pos_y>=tam_y-130){
        personagem.colision.down = 1;
    }else{
        personagem.colision.down = 0;
    }
    return personagem;
}

int dano_real(struct Personagem personagem){
    printf("%d", personagem.arma.dano);
    return (personagem.ataque+personagem.arma.dano);
}
int *pega_frame(struct Personagem personagem){
    int dados[] = {(personagem.frame.total_y/personagem.frame.n_linhas), (personagem.frame.total_x/personagem.frame.n_colunas)};
    return dados;
}

//preset:
struct Colision colision = {0, 0, 0, 0};

