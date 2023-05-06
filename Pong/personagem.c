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

struct Personagem colision_personagem(struct Personagem personagem, struct Personagem npc){
    int var_bambiarra_y = 90, var_bambiarra_x = 70;
    if(
       personagem.pos_y<npc.pos_y+(npc.frame.total_y/npc.frame.n_linhas)-var_bambiarra_y &&
       personagem.pos_y+(personagem.frame.total_y/personagem.frame.n_linhas)-var_bambiarra_y>npc.pos_y
       ){
        if(personagem.pos_x<npc.pos_x+(npc.frame.total_x/npc.frame.n_colunas)-var_bambiarra_x &&
           personagem.pos_x>npc.pos_x

           ){
            personagem.colision.left = 1;
            personagem.pos_x+=50;
            personagem.vida -=dano_real(npc);
        }else{
            personagem.colision.left = 0;
        }
        if(npc.pos_x<personagem.pos_x+(personagem.frame.total_x/personagem.frame.n_colunas)-var_bambiarra_x &&
           personagem.pos_x<npc.pos_x
           ){
            personagem.colision.right = 1;
            personagem.pos_x-=50;
            personagem.vida -=dano_real(npc);
        }else{
            personagem.colision.right = 0;
        }
    }else{
        personagem.colision.left = 0;
        personagem.colision.right = 0;
    }
    if(
        personagem.pos_x<npc.pos_x+(npc.frame.total_x/npc.frame.n_colunas)-var_bambiarra_x &&
        npc.pos_x<personagem.pos_x+(personagem.frame.total_x/personagem.frame.n_colunas)-var_bambiarra_x
        ){
        if(
           personagem.pos_y<npc.pos_y+(npc.frame.total_y/npc.frame.n_linhas)-var_bambiarra_y &&
           personagem.pos_y>npc.pos_y
           ){
            personagem.colision.up = 1;
            personagem.pos_y+=30;
            personagem.vida -=dano_real(npc);
        }else{
            personagem.colision.up = 0;
        }
        if(
           personagem.pos_y+(personagem.frame.total_y/personagem.frame.n_linhas)-var_bambiarra_y>npc.pos_y &&
           personagem.pos_y<npc.pos_y
           ){
            personagem.colision.down = 1;
            personagem.pos_y-=30;
            personagem.vida -=dano_real(npc);
        }else{
            personagem.colision.down = 0;
        }
    }else{
        personagem.colision.down = 0;
        personagem.colision.up = 0;
    }

    return personagem;
}

struct Personagem colision_final(struct Personagem personagem, struct Personagem npc, int tam_x, int tam_y){
    struct Personagem a = colision_parede(personagem, tam_x, tam_y);
    struct Personagem b = colision_personagem(personagem, npc);

    if(a.colision.down == 0 && b.colision.down == 0){
        personagem.colision.down = 0;
    }else{
        personagem.colision.down = 1;
        if(b.colision.down == 1){
            personagem.vida = b.vida;
            personagem.pos_y = b.pos_y;
        }
    }
    if(a.colision.left == 0 && b.colision.left == 0){
        personagem.colision.left = 0;
    }else{
        personagem.colision.left = 1;
        if(b.colision.left == 1){
            personagem.vida = b.vida;
            personagem.pos_x = b.pos_x;
        }
    }
    if(a.colision.right == 0 && b.colision.right == 0){
        personagem.colision.right = 0;
    }else{
        personagem.colision.right = 1;
        if(b.colision.right == 1){
            personagem.vida = b.vida;
            personagem.pos_x = b.pos_x;
        }
    }
    if(a.colision.up == 0 && b.colision.up == 0){
        personagem.colision.up = 0;
    }else{
        personagem.colision.up = 1;
        if(b.colision.up == 1){
            personagem.vida = b.vida;
            personagem.pos_y = b.pos_y;
        }
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

