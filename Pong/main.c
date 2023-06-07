#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/keyboard.h>
#include "frame.h"
#include "itens.h"
#include "personagem.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
enum keys{UP, DOWN, LEFT, RIGHT};
int main (){
    int i, a, j = 0;
    int finely = 0, lin = 0;
    int n_levels = 5, level = 0;
    int pos_x_inicial = 50, pos_y_inicial = 250;
    int n_npc = 4, n_npc_base = n_npc, tam_disp_x = 958, tam_disp_y = 600, velocidade = 5;
    float col = 0.f;
    bool keys [4] = {false, false, false, false};
    int pos_item_x = 200, pos_item_y = 200;

    //CRIAÇÃO DE PERSONAGENS
    struct Personagem personagem1 = cria_personagem(50, pos_x_inicial, pos_y_inicial, lin, col, 3, velocidade, mao, personagem_principal_f, colision);
    struct Personagem npc[n_levels][n_npc];
    struct Personagem npc_temp[n_levels][n_npc];
    for(a=0; a<n_levels; a++){
        for(i=0; i<n_npc; i++){
            npc[a][i] = cria_personagem(50+(50*a), 700-(50*i), 200, lin, col, 3, 1, mao, personagem_inimigo_f, colision);
        }
    }
    //INICIAÇÕES DAS BIBLIOTECAS
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_install_keyboard();
    //DECLARAÇÕES DA JANELA
    struct Display dados = inicia_display(tam_disp_x, tam_disp_y, 10, 10, "jogo do balacobaco");
    ALLEGRO_SAMPLE *musica = al_load_sample("./musicas/fundo1.wav");
    al_reserve_samples(1);
    //CONFIG DOS SPRITES PARA DESENHAR
    ALLEGRO_BITMAP* spriteHeroi = al_load_bitmap(personagem1.frame.local_img);
    ALLEGRO_BITMAP* sprite_npc[n_levels][n_npc];
    ALLEGRO_BITMAP* sprite_fundo = al_load_bitmap("./imagens/Inkedmapa.png");
    ALLEGRO_BITMAP* sprite_teste = al_load_bitmap(adaga.frame.local_img);
    //POPULA SPRITES DOS NPCS
    int tam_y_f_t[n_levels][n_npc], tam_x_f_t[n_levels][n_npc];
    for(a=0; a<n_levels; a++){
        for(i=0; i<n_npc; i++){
            sprite_npc[a][i] = al_load_bitmap(npc[a][i].frame.local_img);
            int *tams_f_t = pega_frame(npc[a][i]);
            tam_y_f_t[a][i] = tams_f_t[0];
            tam_x_f_t[a][i] = tams_f_t[1];
            npc[a][i].linha = tam_y_f_t[a][i];
        }
    }
    //DEFINE SPRITE DO PERSONAGEM PRINCIPAL
    int *tams_f = pega_frame(personagem1);
    int tam_y_f_pp = tams_f[0], tam_x_f_pp = tams_f[1];
    personagem1.linha = tam_y_f_pp;
    //TEXTOS DA TELA DO JOGO
    int text_l_1 = 6;
    char *texto[text_l_1], *texto_final, *texto_perdeu;
    char *menu_arma, *menu_vida;
    char *nome_arma, nome_vida[10];
    texto[0] = "Nosso heroi esta aqui, seu nome e (nome)";
    texto[1] = "voce pode se locomover com as setas";
    texto[2] = "e atacar com a tecla Z";
    texto[3] = "lembre-se, CUIDADO COM OS INIMIGOS";
    texto[4] = "";
    texto[5] = "jogo feito por:";
    texto[6] = "Tales Cruz da Silva, Rian (SOBRENOME) E Marcus (SOBRENOME)";
    texto_final = "Voce ganhou, parabens, campeao ;)";
    texto_perdeu = "Voce perdeu, seu lixo :(";
    menu_arma = "Arma: ";
    menu_vida = "Vida: ";
    //COMEÇA
    n_npc = 0;
    int flag_frame = 0;
    int flag_item = 0;
    struct Arma arma_temp;
    while(true){
        ALLEGRO_EVENT event;
        al_wait_for_event(dados.fila, &event);
        al_play_sample(musica, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
        //VALORES DINAMICOS DO PERSONAGEM
        itoa(personagem1.vida, nome_vida, 10);
        nome_arma = personagem1.arma.nome;
        spriteHeroi = al_load_bitmap(personagem1.frame.local_img);
        //PASSAGEM DE LEVEL
        if(level<=n_levels && personagem1.vida>0){
            finely = pass_level(personagem1, n_npc);
            if(finely == 1){
                level++;
                n_npc = n_npc_base;
                flag_item = 0;
                personagem1.pos_x = pos_x_inicial;
                personagem1.pos_y = pos_y_inicial;
                finely = 0;
            }
        }
        //COLISAO
        if(n_npc>0 && level>0 && level<=n_levels && personagem1.vida>0){
            for(i=0; i<n_npc; i++){
                npc[level-1][i] = colision_parede(npc[level-1][i], tam_disp_x, tam_disp_y);
                npc[level-1][i] = movimento_npc(personagem1, npc[level-1][i], tam_y_f_t[level-1][i]);
                int vida_temp = personagem1.vida;
                personagem1 = colision_final(personagem1, npc[level-1][i], tam_disp_x, tam_disp_y);
                if(vida_temp>personagem1.vida){
                    flag_frame++;
                }
                if(flag_frame>0 && flag_frame<50){
                    spriteHeroi = al_load_bitmap(personagem1.frame.local_img_dano);
                    flag_frame++;
                }else{
                    flag_frame = 0;
                }
            }
        }else{
            personagem1 = colision_parede(personagem1, tam_disp_x, tam_disp_y);
        }
        if(n_npc==0){
            flag_frame = 0;
            personagem1.frame = personagem_principal_f;
        }
        //BOTÃO DE FECHAR JANELA
        if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){ //fecha
          break;
        }
        //FUNÇÕES DE TECLAS
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN){ //quaquer tecla
            if(
                event.keyboard.keycode==ALLEGRO_KEY_RIGHT ||
                event.keyboard.keycode==ALLEGRO_KEY_LEFT ||
                event.keyboard.keycode==ALLEGRO_KEY_UP ||
                event.keyboard.keycode==ALLEGRO_KEY_DOWN
            ){
            }
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    goto exit_loop;
                default:
                    break;
            }
            if(event.keyboard.keycode==ALLEGRO_KEY_Z){
                    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
                        if(level>0 && level<=n_levels){
                            int flag[n_npc];
                            int c;
                            for(i=0;i<n_npc;i++){
                                npc[level-1][i] = ataque(personagem1, npc[level-1][i], personagem1.linha);
                                if(npc[level-1][i].vida<=0){
                                    flag[j] = i;
                                    j++;
                                }
                            }
                            for(i=0;i<j; i++){
                                for(c=flag[i]; c<n_npc-1;c++){
                                    npc[level-1][c] = npc[level-1][c+1];
                                }
                                n_npc--;
                            }
                            j=0;
                        }
                    }
            }
        }else if(event.type == ALLEGRO_EVENT_KEY_UP){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = false;
                    break;
                default:
                    break;
            }
        }
        //FAZ O MOVIMENTO DA IMAGEM
        if(keys[UP] || keys[DOWN] || keys[RIGHT] || keys[LEFT]){
            personagem1.coluna += 0.1f;
            if( personagem1.coluna > personagem1.frame.n_colunas){
                personagem1.coluna -= personagem1.frame.n_colunas;
            }
        }
        //FAZ O MOVIMENTO DO PERSONAGEM
        if(keys[UP] && personagem1.colision.up==0){
            personagem1.pos_y -= personagem1.velocidade;
            personagem1.linha = 0;
        }
        if(keys[DOWN] && personagem1.colision.down==0){
            personagem1.pos_y += personagem1.velocidade;
            personagem1.linha = tam_y_f_pp*2;
        }
        if(keys[RIGHT] && personagem1.colision.right==0){
            personagem1.pos_x += personagem1.velocidade;
            personagem1.linha = tam_y_f_pp;
        }
        if(keys[LEFT] && personagem1.colision.left==0){
            personagem1.pos_x -= personagem1.velocidade;
            personagem1.linha = tam_y_f_pp*3;
        }
        //DESENHO DA TELA (LEMBRA QUE O DE BAIXO SOBRESCREVE O DE CIMA)
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(sprite_fundo, 0, 0, 0);

        if(personagem1.vida>0){
            al_draw_bitmap_region(spriteHeroi, tam_x_f_pp * (int)personagem1.coluna, personagem1.linha, tam_x_f_pp, tam_y_f_pp, personagem1.pos_x, personagem1.pos_y, 0);
        }
        //DESENHA NPCS
        if(level>0 && level<=n_levels && personagem1.vida>0){
            for(i=0; i<n_npc; i++){
                al_draw_bitmap_region(sprite_npc[level-1][i], tam_x_f_t[level-1][i] * (int)npc[level-1][i].coluna, npc[level-1][i].linha, tam_x_f_t[level-1][i], tam_y_f_t[level-1][i], npc[level-1][i].pos_x, npc[level-1][i].pos_y, 0);
            }
        }
        if(level == 0){
            for(i=0; i<=text_l_1; i++){
                al_draw_text(dados.fonte, al_map_rgb(255,255,255), 400, 100+(20*i), 0, texto[i]);
            }
            arma_temp = personagem1.arma;
            personagem1 = pegou_item(personagem1, adaga, pos_item_x, pos_item_y);
            if(arma_temp.dano!=personagem1.arma.dano){
                flag_item = 1;
            }
            if(flag_item == 0){
                al_draw_bitmap(sprite_teste, pos_item_x, pos_item_y, 0);
            }
        }else if(level == 2){
            struct Arma arma_temp = personagem1.arma;
            personagem1 = pegou_item(personagem1, espada, pos_item_x, pos_item_y);
            if(arma_temp.dano!=personagem1.arma.dano){
                flag_item = 1;
            }
            if(flag_item == 0){
                al_draw_bitmap(sprite_teste, pos_item_x, pos_item_y, 0);
            }
        }else if(level == 4){
            struct Arma arma_temp = personagem1.arma;
            personagem1 = pegou_item(personagem1, machado, pos_item_x, pos_item_y);
            if(arma_temp.dano!=personagem1.arma.dano){
                flag_item = 1;
            }
            if(flag_item == 0){
                al_draw_bitmap(sprite_teste, pos_item_x, pos_item_y, 0);
            }
        }
        if(level > n_levels){
            al_draw_text(dados.fonte, al_map_rgb(255,255,255), 230, 200, 0, texto_final);
        }
        if(personagem1.vida>0){
            al_draw_text(dados.fonte, al_map_rgb(255,255,255), 50, 50, 0, menu_arma);
            al_draw_text(dados.fonte, al_map_rgb(255,255,255), 100, 50, 0, nome_arma);
            al_draw_text(dados.fonte, al_map_rgb(255,255,255), 50, 70, 0, menu_vida);
            al_draw_text(dados.fonte, al_map_rgb(255,255,255), 100, 70, 0, nome_vida);
        }else{
            al_draw_text(dados.fonte, al_map_rgb(255,255,255), 300, 200, 0, texto_perdeu);
        }
        al_flip_display();
    }
    exit_loop:; //PONTO DE FUGA
    //DESTROI TUDO
    al_destroy_bitmap(sprite_fundo);
    al_destroy_bitmap(spriteHeroi);
    al_destroy_bitmap(sprite_teste);
    for(a=0; a<n_levels; a++){
        for(i=0; i<n_npc; i++){
            al_destroy_bitmap(sprite_npc[a][i]);
        }
    }
    al_destroy_sample(musica);
    al_destroy_font(dados.fonte);
    al_destroy_display(dados.display);
    al_destroy_event_queue(dados.fila);
    return 0;
}
