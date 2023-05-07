#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include "personagem.h"
#include "itens.h"
#include "frame.h"
#include <stdio.h>
#include <stdlib.h>

enum keys{UP, DOWN, LEFT, RIGHT};

int main (){
    int i, j = 0;
    int n_npc = 5, tam_disp_x = 1000, tam_disp_y = 500, velocidade = 5;
    bool keys [4] = {false, false, false, false};

    //CRIAÇÃO DE PERSONAGENS
    struct Personagem personagem1 = cria_personagem(50, 0, 0, 3, velocidade, machado, personagem_principal_f, colision);
    struct Personagem npc[n_npc];
    struct Personagem npc_temp[n_npc];
    for(i=0; i<n_npc; i++){
        npc[i] = cria_personagem(50, 100*i, 150, 3, 2, mao, personagem_teste_f, colision);
    }

    //INICIAÇÕES DAS BIBLIOTECAS
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    //DECLARAÇÕES DA JANELA
    ALLEGRO_DISPLAY * display = al_create_display(tam_disp_x,tam_disp_y);
    al_set_window_position(display, 10, 10);
    al_set_window_title(display, "Jooj");

    //TEXTOS DA TELA DO JOGO
    char *texto;
    char *menu_arma, *menu_vida;
    char *nome_arma, nome_vida[10];
    texto = "BATALHA ROLANDO (Z ATACA)";
    menu_arma = "ARMA: ";
    menu_vida = "VIDA: ";

    //CONFIG DOS SPRITES PARA DESENHAR
    ALLEGRO_BITMAP* spriteHeroi = al_load_bitmap(personagem1.frame.local_img);
    ALLEGRO_BITMAP* sprite_npc[n_npc];
    //POPULA SPRITES DOS NPCS
    int tam_y_f_t[n_npc], tam_x_f_t [n_npc];
    int current_frame_y_t[n_npc];
    for(i=0; i<n_npc; i++){
        sprite_npc[i] = al_load_bitmap(npc[i].frame.local_img);
        int *tams_f_t = pega_frame(npc[i]);
        tam_y_f_t[i] = tams_f_t[0];
        tam_x_f_t[i] = tams_f_t[1];
        current_frame_y_t[i] = tam_y_f_t[i];
    }
    //DEFINE SPRITE DO PERSONAGEM PRINCIPAL
    float frame = 0.f;
    int *tams_f = pega_frame(personagem1);
    int tam_y_f_pp = tams_f[0], tam_x_f_pp = tams_f[1];
    int current_frame_y_pp = tam_y_f_pp;

    //COISAS MEIO IRRELEVANTES DE MEXER
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    //FILA DE EVENTOS
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    //COMEÇA
    while(true){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        //VALORES DINAMICOS DO PERSONAGEM
        itoa(personagem1.vida, nome_vida, 10);
        nome_arma = personagem1.arma.nome;

        //FUNÇÕES DO JOGO
        if(personagem1.vida <= 0){
            texto = "VOCE PERDEU!!";
        }
        if(n_npc>0){
            for(i=0; i<n_npc; i++){
                npc[i] = colision_parede(npc[i], tam_disp_x, tam_disp_y);
                personagem1 = colision_final(personagem1, npc[i], tam_disp_x, tam_disp_y);
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
                        int flag[n_npc];
                        int c;
                        for(i=0;i<n_npc;i++){
                            npc[i] = ataque(personagem1, npc[i], current_frame_y_pp);
                            if(npc[i].vida<=0){
                                flag[j] = i;
                                j++;
                            }
                        }
                        for(i=0;i<j; i++){
                            for(c=flag[i]; c<n_npc-1;c++){
                                npc[c] = npc[c+1];
                            }
                            n_npc--;
                        }
                        j=0;
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
        if(personagem1.vida>0){
            al_draw_bitmap_region(spriteHeroi, tam_x_f_pp * (int)frame, current_frame_y_pp, tam_x_f_pp, tam_y_f_pp, personagem1.pos_x, personagem1.pos_y, 0);
        }
        //DESENHA NPCS
        for(i=0; i<n_npc; i++){
            al_draw_bitmap_region(sprite_npc[i], tam_x_f_t[i], current_frame_y_t[i], tam_x_f_t[i], tam_y_f_t[i], npc[i].pos_x, npc[i].pos_y, 0);
        }
        //MUCHO TEXTO
        al_draw_text(font, al_map_rgb(255,255,255), 230, 200, 0, texto);
        if(personagem1.vida>0){
            al_draw_text(font, al_map_rgb(255,255,255), 50, 50, 0, menu_arma);
            al_draw_text(font, al_map_rgb(255,255,255), 90, 50, 0, nome_arma);
            al_draw_text(font, al_map_rgb(255,255,255), 50, 70, 0, menu_vida);
            al_draw_text(font, al_map_rgb(255,255,255), 90, 70, 0, nome_vida);
        }

        al_flip_display();
    }
    exit_loop:; //PONTO DE FUGA

    //DESTROI TUDO
    al_destroy_bitmap(spriteHeroi);
    for(i=0; i<n_npc; i++){
        al_destroy_bitmap(sprite_npc[i]);
    }
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
