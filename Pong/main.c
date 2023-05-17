#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include "personagem.h"
#include "itens.h"
#include "frame.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>

enum keys{UP, DOWN, LEFT, RIGHT};

int main (){
    int i, a, j = 0;
    int finely = 0;
    int n_levels = 3, level = 0;
    int n_npc = 2, tam_disp_x = 958, tam_disp_y = 600, velocidade = 5;
    bool keys [4] = {false, false, false, false};
    int pos_x_inicial = 50, pos_y_inicial = 250;

    //CRIAÇÃO DE PERSONAGENS
    struct Personagem personagem1 = cria_personagem(50, pos_x_inicial, pos_y_inicial, 3, velocidade, machado, personagem_principal_f, colision);
    struct Personagem npc[n_levels-1][n_npc];
    struct Personagem npc_temp[n_levels-1][n_npc];
    for(a=0; a<n_levels-1; a++){
        for(i=0; i<n_npc; i++){
            npc[a][i] = cria_personagem(50*a, 700-(50*i), 200, 3, 2, mao, personagem_teste_f, colision);
        }
    }

    //INICIAÇÕES DAS BIBLIOTECAS
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    //DECLARAÇÕES DA JANELA
    struct Display dados = inicia_display(tam_disp_x, tam_disp_y, 10, 10, "jooj");

    //CONFIG DOS SPRITES PARA DESENHAR
    ALLEGRO_BITMAP* spriteHeroi = al_load_bitmap(personagem1.frame.local_img);
    ALLEGRO_BITMAP* sprite_npc[n_levels-1][n_npc];

    ALLEGRO_BITMAP* sprite_fundo = al_load_bitmap("./imagens/Inkedmapa.png");
    //POPULA SPRITES DOS NPCS
    int tam_y_f_t[n_levels-1][n_npc], tam_x_f_t[n_levels-1][n_npc];
    int current_frame_y_t[n_levels-1][n_npc];
    for(a=0; a<n_levels-1; a++){
        for(i=0; i<n_npc; i++){
            sprite_npc[a][i] = al_load_bitmap(npc[a][i].frame.local_img);
            int *tams_f_t = pega_frame(npc[a][i]);
            tam_y_f_t[a][i] = tams_f_t[0];
            tam_x_f_t[a][i] = tams_f_t[1];
            current_frame_y_t[a][i] = tam_y_f_t[a][i];
        }
    }

    //DEFINE SPRITE DO PERSONAGEM PRINCIPAL
    float frame = 0.f;
    int *tams_f = pega_frame(personagem1);
    int tam_y_f_pp = tams_f[0], tam_x_f_pp = tams_f[1];
    int current_frame_y_pp = tam_y_f_pp;

    //TEXTOS DA TELA DO JOGO
    int text_l_1 = 5;
    char *texto[text_l_1], *texto_final, *texto_perdeu;
    char *menu_arma, *menu_vida;
    char *nome_arma, nome_vida[10];
    texto[0] = "NOSSO HEROI ESTA AQUI, SEU NOME E (NOME)";
    texto[1] = "VOCE PODE SE LOCOMOVER COM AS SETAS";
    texto[2] = "E ATACAR COM A TECLA Z";
    texto[3] = "LEMBRE-SE CUIDADO COM OS INIMIGOS";
    texto[4] = "JOGO FEITO POR:";
    texto[5] = "TALES CRUZ DA SILVA, RIAN (SOBRENOME) E MARCUS (SOBRENOME)";
    texto_final = "VOCE GANHOU ;)";
    texto_perdeu = "VOCE PERDEU :(";
    menu_arma = "ARMA: ";
    menu_vida = "VIDA: ";

    n_npc = 0;
    //COMEÇA
    while(true){
        ALLEGRO_EVENT event;
        al_wait_for_event(dados.fila, &event);

        //VALORES DINAMICOS DO PERSONAGEM
        itoa(personagem1.vida, nome_vida, 10);
        nome_arma = personagem1.arma.nome;

        if(level<n_levels){
            finely = pass_level(personagem1, n_npc);

            if(finely == 1){
                level++;
                n_npc = 2;
                personagem1.pos_x = pos_x_inicial;
                personagem1.pos_y = pos_y_inicial;
                finely = 0;
            }
        }
        if(n_npc>0 && level>0 && level<n_levels){
            for(i=0; i<n_npc; i++){
                npc[level-1][i] = colision_parede(npc[level-1][i], tam_disp_x, tam_disp_y);
                personagem1 = colision_final(personagem1, npc[level-1][i], tam_disp_x, tam_disp_y);
            }
        }else{
            personagem1 = colision_parede(personagem1, tam_disp_x, tam_disp_y);
        }



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
                        if(level>0 && level<n_levels){
                            int flag[n_npc];
                            int c;
                            for(i=0;i<n_npc;i++){
                                npc[level-1][i] = ataque(personagem1, npc[level-1][i], current_frame_y_pp);
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
            frame += 0.1f;
            if( frame > personagem1.frame.n_colunas){
                frame -= personagem1.frame.n_colunas;
            }
        }
        //FAZ O MOVIMENTO DO PERSONAGEM
        if(keys[UP] && personagem1.colision.up==0){
            personagem1.pos_y -= personagem1.velocidade;
            current_frame_y_pp = 0;
        }
        if(keys[DOWN] && personagem1.colision.down==0){
            personagem1.pos_y += personagem1.velocidade;
            current_frame_y_pp = tam_y_f_pp*2;
        }
        if(keys[RIGHT] && personagem1.colision.right==0){
            personagem1.pos_x += personagem1.velocidade;
            current_frame_y_pp = tam_y_f_pp;
        }
        if(keys[LEFT] && personagem1.colision.left==0){
            personagem1.pos_x -= personagem1.velocidade;
            current_frame_y_pp = tam_y_f_pp*3;
        }

        //DESENHO DA TELA (LEMBRA QUE O DE BAIXO SOBRESCREVE O DE CIMA)
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(sprite_fundo, 0, 0, 0);
        if(personagem1.vida>0){
            al_draw_bitmap_region(spriteHeroi, tam_x_f_pp * (int)frame, current_frame_y_pp, tam_x_f_pp, tam_y_f_pp, personagem1.pos_x, personagem1.pos_y, 0);
        }
        //DESENHA NPCS
        if(level>0 && level<n_levels){
            for(i=0; i<n_npc; i++){
                al_draw_bitmap_region(sprite_npc[level-1][i], tam_x_f_t[level-1][i], current_frame_y_t[level-1][i], tam_x_f_t[level-1][i], tam_y_f_t[level-1][i], npc[level-1][i].pos_x, npc[level-1][i].pos_y, 0);
            }
        }
        //MUCHO TEXTO
        if(level == 0){
            for(i=0; i<=text_l_1; i++){
                al_draw_text(dados.fonte, al_map_rgb(255,255,255), 400, 100+(15*i), 0, texto[i]);
            }
        }
        if(level == n_levels){
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
    for(a=0; a<n_levels-1; a++){
        for(i=0; i<n_npc; i++){
            al_destroy_bitmap(sprite_npc[a][i]);
        }
    }
    al_destroy_font(dados.fonte);
    al_destroy_display(dados.display);
    al_destroy_event_queue(dados.fila);

    return 0;
}
