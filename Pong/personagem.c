#include "personagem.h"
#include "itens.h"
#include "frame.h"
//CAMPO DAS FUNÇÕES:
struct Personagem cria_personagem(int vida, int pos_inicial_x, int pos_inicial_y, int linha, float coluna, float ataque, float velocidade, struct Arma arma, struct Frame frame, struct Colision colision){
    struct Personagem personagem = {vida, pos_inicial_x, pos_inicial_y, linha, coluna, ataque, velocidade, arma, frame, colision};
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
    if(personagem.pos_x<=25){
        personagem.colision.left = 1;
        personagem.pos_x=25;
    }else{
        personagem.colision.left = 0;
    }
    if(personagem.pos_x>=tam_x-50){
        personagem.colision.right = 1;
        personagem.pos_x=tam_x-50;
    }else{
        personagem.colision.right = 0;
    }
    if(personagem.pos_y<=30){
        personagem.colision.up = 1;
        personagem.pos_y=30;
    }else{
        personagem.colision.up = 0;
    }
    if(personagem.pos_y>=tam_y-60){
        personagem.colision.down = 1;
        personagem.pos_y=tam_y-60;
    }else{
        personagem.colision.down = 0;
    }
    return personagem;
}
struct Personagem colision_personagem(struct Personagem personagem, struct Personagem npc){
    int var_bambiarra_y = 30, var_bambiarra_x = 30;
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
struct Personagem ataque(struct Personagem personagem, struct Personagem npc, int current_frame){
    int var_bambiarra_y = 30, var_bambiarra_x = 30;
    int alcance = personagem.arma.alcance*40;
    int pf_p_x = personagem.pos_x+(personagem.frame.total_x/personagem.frame.n_colunas)-var_bambiarra_x;
    int pf_p_y = personagem.pos_y+(personagem.frame.total_y/personagem.frame.n_linhas)-var_bambiarra_y;
    int pf_npc_x = npc.pos_x+(npc.frame.total_x/npc.frame.n_colunas)-var_bambiarra_x;
    int pf_npc_y = npc.pos_y+(npc.frame.total_y/npc.frame.n_linhas)-var_bambiarra_y;
    int pi_p_x = personagem.pos_x, pi_p_y = personagem.pos_y;
    int pi_npc_x = npc.pos_x, pi_npc_y = npc.pos_y;
    int frame = current_frame/(personagem.frame.total_y/personagem.frame.n_linhas);
    switch (frame){
        case 0: //cima
            if(pi_p_x<=pf_npc_x && pi_p_x>=pi_npc_x && pi_npc_y<pi_p_y || (pf_p_x<=pf_npc_x && pf_p_x>=pi_npc_x && pi_npc_y<pi_p_y)){
                if(pi_p_y-alcance<=pf_npc_y){
                    npc.vida-=dano_real(personagem);
                    npc.pos_y-=30;
                }
            }
            return npc;
            break;
        case 1: //direita
            if(pi_p_y<=pf_npc_y && pi_p_y>=pi_npc_y && pi_npc_x>pi_p_x || (pf_p_y<=pf_npc_y && pf_p_y>=pi_npc_y && pi_npc_x>pi_p_x)){
                if(pf_p_x+alcance>=pi_npc_x){
                    npc.vida-=dano_real(personagem);
                    npc.pos_x+=30;
                }
            }
            return npc;
            break;
        case 2: //baixo
            if(pi_p_x<=pf_npc_x && pi_p_x>=pi_npc_x && pi_npc_y>pi_p_y || (pf_p_x<=pf_npc_x && pf_p_x>=pi_npc_x && pi_npc_y>pi_p_y)){
                if(pf_p_y+alcance>=pi_npc_y){
                    npc.vida-=dano_real(personagem);
                    npc.pos_y+=30;
                }
            }
            return npc;
            break;
        case 3: //esquerda
            if(pi_p_y<=pf_npc_y && pi_p_y>=pi_npc_y && pi_npc_x<pi_p_x || (pf_p_y<=pf_npc_y && pf_p_y>=pi_npc_y && pi_npc_x<pi_p_x)){
                if(pi_p_x-alcance<=pf_npc_x){
                    npc.vida-=dano_real(personagem);
                    npc.pos_x-=30;
                }
            }
            return npc;
            break;
        default:
            return npc;
            break;
    }
};
struct Personagem movimento_npc(struct Personagem personagem, struct Personagem npc, int tam_f){
    npc.coluna +=0.1f;
    if( npc.coluna > npc.frame.n_colunas){
        npc.coluna -= npc.frame.n_colunas;
    }
    if(personagem.pos_y-30>npc.pos_y){
        npc.pos_y += npc.velocidade;
        npc.linha = tam_f*2;
    }
    if(personagem.pos_y<npc.pos_y){
        npc.pos_y -= npc.velocidade;
        npc.linha = 0;
    }
    if(personagem.pos_x>npc.pos_x){
        npc.pos_x += npc.velocidade;
        npc.linha = tam_f;
    }
    if(personagem.pos_x<npc.pos_x){
        npc.pos_x -= npc.velocidade;
        npc.linha = tam_f*3;
    }
    return npc;
}
int dano_real(struct Personagem personagem){
    return (personagem.ataque+personagem.arma.dano);
}
int *pega_frame(struct Personagem personagem){
    int dados[] = {(personagem.frame.total_y/personagem.frame.n_linhas), (personagem.frame.total_x/personagem.frame.n_colunas)};
    return dados;
}
//PRESET:
struct Colision colision = {0, 0, 0, 0};
