#include "personagem.h"
#include "itens.h"
#include "frame.h"
//CAMPO DAS FUNÇÕES:
struct Personagem cria_personagem(int vida, int pos_inicial_x, int pos_inicial_y, int linha, float coluna, float ataque, float velocidade, struct Arma arma, struct Frame frame, struct Colision colision, int level, int i){
    struct Personagem personagem = {vida+(level*50), pos_inicial_x+(50*i), pos_inicial_y, linha, coluna, ataque, velocidade, arma, frame, colision};
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
    if(personagem.pos_y<=50){
        personagem.colision.up = 1;
        personagem.pos_y=50;
    }else{
        personagem.colision.up = 0;
    }
    if(personagem.pos_y>=tam_y-80){
        personagem.colision.down = 1;
        personagem.pos_y=tam_y-80;
    }else{
        personagem.colision.down = 0;
    }
    return personagem;
}
struct Personagem colision_personagem(struct Personagem personagem, struct Personagem npc){
    int pFimx = personagem.pos_x+(personagem.frame.total_x/personagem.frame.n_colunas);
    int pFimy = personagem.pos_y+(personagem.frame.total_y/personagem.frame.n_linhas);
    int nFimx = npc.pos_x+(npc.frame.total_x/npc.frame.n_colunas);
    int nFimy = npc.pos_y+(npc.frame.total_y/npc.frame.n_linhas);

    if(pFimy>npc.pos_y && personagem.pos_y<nFimy){
        if(nFimx>=personagem.pos_x && npc.pos_x<=personagem.pos_x){
            personagem.colision.left = 1;
            personagem.pos_x+=50;
            personagem.vida -=dano_real(npc);
        }else{
            personagem.colision.left = 0;
        }
        if(pFimx>=npc.pos_x && npc.pos_x>=personagem.pos_x){
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
    if(pFimx>npc.pos_x && personagem.pos_x<nFimx){
        if(nFimy>=personagem.pos_y && npc.pos_y<=personagem.pos_y){
            personagem.colision.up = 1;
            personagem.pos_y+=30;
            personagem.vida -=dano_real(npc);
        }else{
            personagem.colision.up = 0;
        }
        if(pFimy>=npc.pos_y && npc.pos_y>=personagem.pos_y){
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
void pegou_item(struct Personagem *p, struct Arma arma, int pos_x, int pos_y){
    struct Personagem personagem = *p;
    int pFimx = personagem.pos_x+(personagem.frame.total_x/personagem.frame.n_colunas);
    int pFimy = personagem.pos_y+(personagem.frame.total_y/personagem.frame.n_linhas);
    if(
        (pFimx>pos_x && personagem.pos_x<pos_x+arma.frame.total_x)
        &&
        (pFimy>pos_y && personagem.pos_y<pos_y+arma.frame.total_y)
       )
    {
        personagem.arma = arma;
    }
    switch(personagem.arma.dano){
    case 0:
        personagem.frame = personagem_principal_f;
        break;
    case 2:
        personagem.frame = personagem_adaga_f;
        break;
    case 5:
        personagem.frame = personagem_espada_f;
        break;
    case 15:
        personagem.frame = personagem_machado_f;
        break;
    default:
        break;
    }
    *p = personagem;
    void free(void *p);
}
void ataque(struct Personagem personagem, struct Personagem *npcP){
    struct Personagem npc = *npcP;
    int pFimx = personagem.pos_x+(personagem.frame.total_x/personagem.frame.n_colunas);
    int pFimy = personagem.pos_y+(personagem.frame.total_y/personagem.frame.n_linhas);
    int nFimx = npc.pos_x+(npc.frame.total_x/npc.frame.n_colunas);
    int nFimy = npc.pos_y+(npc.frame.total_y/npc.frame.n_linhas);
    int knockback = 60;

    int alcance = personagem.arma.alcance*40;
    int frame = personagem.linha/(personagem.frame.total_y/personagem.frame.n_linhas);

    switch (frame){
        case 0: //cima
            if(pFimx>npc.pos_x && personagem.pos_x<nFimx){
                if(personagem.pos_y-alcance<=nFimy && personagem.pos_y>npc.pos_y){
                    npc.vida-=dano_real(personagem);
                    npc.pos_y-=knockback;
                }
            }
            break;
        case 1: //direita
            if(pFimy>npc.pos_y && personagem.pos_y<nFimy){
                if(pFimx+alcance>=npc.pos_x && personagem.pos_x<npc.pos_x){
                    npc.vida-=dano_real(personagem);
                    npc.pos_x+=knockback;
                }
            }
            break;
        case 2: //baixo
            if(pFimx>npc.pos_x && personagem.pos_x<nFimx){
                if(pFimy+alcance>=npc.pos_y && personagem.pos_y<npc.pos_y){
                    npc.vida-=dano_real(personagem);
                    npc.pos_y+=knockback;
                }
            }
            break;
        case 3: //esquerda
            if(pFimy>npc.pos_y && personagem.pos_y<nFimy){
                if(personagem.pos_x-alcance<=nFimx && personagem.pos_x>npc.pos_x){
                    npc.vida-=dano_real(personagem);
                    npc.pos_x-=knockback;
                }
            }
            break;
        default:
            break;
    }
    *npcP = npc;
    void free(void *npcP);
};
void movimento_npc(struct Personagem personagem, struct Personagem *npcP, int tam_f){
    struct Personagem npc = *npcP;
    npc.coluna +=0.1f;
    if( npc.coluna > npc.frame.n_colunas){
        npc.coluna -= npc.frame.n_colunas;
    }
    if(personagem.pos_y+30>npc.pos_y){
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
    *npcP = npc;
    void free(void *npcP);
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
