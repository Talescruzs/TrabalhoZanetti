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

enum keys{UP, DOWN, LEFT, RIGHT, Z};

int main (){
    int n_npc = 2, tam_disp_x = 800, tam_disp_y = 500;
    bool keys [5] = {false, false, false, false, false};
    bool Colision [4] = {false, false, false, false};

    struct Personagem npc[n_npc];

    struct Personagem personagem1 = cria_personagem(50, 0, 0, 3, 1, machado, personagem_principal_f);
    struct Personagem p_teste = cria_personagem(50, 500, 150, 3, 1, mao, personagem_teste_f);

    //INICIAÇÕES DAS BIBLIOTECAS
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    //DECLARAÇÕES DA JANELA
    ALLEGRO_DISPLAY * display = al_create_display(tam_disp_x,tam_disp_y);
    al_set_window_position(display, 100, 10);
    al_set_window_title(display, "Jooj");

    while(true){
        int i = 0;
        npc[i] = cria_personagem(50, 500, 150, 3, 1, mao, personagem_teste_f);
        i++;
        if(i>=1){
            break;
        }
    }

    //CONFIGURAÇÕES BASE QUE SERÃO UTILIZADAS
    ALLEGRO_BITMAP* spriteHeroi = al_load_bitmap(personagem1.frame.local_img);
    ALLEGRO_BITMAP* spriteTeste = al_load_bitmap(npc[0].frame.local_img);

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    //FILA DE EVENTOS
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    //VARIAVEIS BASE
    float frame = 0.f;
    int *tams_f = pega_frame(personagem1);
    int tam_y_f_pp = tams_f[0], tam_x_f_pp = tams_f[1];
    int current_frame_y_pp = tam_y_f_pp;

    int *tams_f_t = pega_frame(npc[0]);
    int tam_y_f_t = tams_f_t[0], tam_x_f_t = tams_f_t[1];
    int current_frame_y_t = tam_y_f_t;

    char *texto;
    char *menu_arma, *menu_vida;
    char *nome_arma, nome_vida[10];


    texto = "BATALHA ROLANDO (Z ATACA)";
    menu_arma = "ARMA: ";
    menu_vida = "VIDA: ";


    while(true){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        itoa(personagem1.vida, nome_vida, 10);
        nome_arma = personagem1.arma.nome;

        //LISTA DE EVENTOS:
        if(personagem1.vida == 0 || npc[0].vida == 0){
            texto = "ACABOU A BATALHA";
        }
        if(personagem1.pos_x<=-30){
            Colision[LEFT_C] = true;
        }else{
            Colision[LEFT_C] = false;
        }
        if(personagem1.pos_x>=tam_disp_x-160){
            Colision[RIGHT_C] = true;
        }else{
            Colision[RIGHT_C] = false;
        }
        if(personagem1.pos_y<=-25){
            Colision[UP_C] = true;
        }else{
            Colision[UP_C] = false;
        }
        if(personagem1.pos_y>=tam_disp_y-130){
            Colision[DOWN_C] = true;
        }else{
            Colision[DOWN_C] = false;
        }

        if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){ //fecha
          break;
        }
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
                        npc[0] = muda_vida(npc[0], dano_real(personagem1)*-1);
                        printf("\n%d\n", npc[0].vida);
                    }
            }


        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP){
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
        if(keys[UP] || keys[DOWN] || keys[RIGHT] || keys[LEFT]){
            frame += 0.1f;
            if( frame > personagem1.frame.n_colunas){ //movimento do personagem
                frame -= personagem1.frame.n_colunas;
            }
        }
        if(keys[UP] && Colision[UP_C]==false){
            personagem1.pos_y -= 2;
            current_frame_y_pp = 0;
        }
        if(keys[DOWN] && Colision[DOWN_C]==false){
            personagem1.pos_y += 2;
            current_frame_y_pp = tam_y_f_pp*2;
        }
        if(keys[RIGHT] && Colision[RIGHT_C]==false){
            personagem1.pos_x += 2;
            current_frame_y_pp = tam_y_f_pp;
        }
        if(keys[LEFT] && Colision[LEFT_C]==false){
            personagem1.pos_x -= 2;
            current_frame_y_pp = tam_y_f_pp*3;
        }

        //DESENHO DA TELA (LEMBRA QUE O DE BAIXO SOBRESCREVE O DE CIMA)
        al_clear_to_color(al_map_rgb(0,0,0));

        al_draw_bitmap_region(spriteHeroi, tam_x_f_pp * (int)frame, current_frame_y_pp, tam_x_f_pp, tam_y_f_pp, personagem1.pos_x, personagem1.pos_y, 0);
        if(npc[0].vida>0){
            al_draw_bitmap_region(spriteTeste, tam_x_f_t, current_frame_y_t, tam_x_f_t, tam_y_f_t, npc[0].pos_x, npc[0].pos_y, 0);
        }
        al_draw_text(font, al_map_rgb(255,255,255), 230, 200, 0, texto);
        al_draw_text(font, al_map_rgb(255,255,255), 50, 50, 0, menu_arma);
        al_draw_text(font, al_map_rgb(255,255,255), 90, 50, 0, nome_arma);
        al_draw_text(font, al_map_rgb(255,255,255), 50, 70, 0, menu_vida);
        al_draw_text(font, al_map_rgb(255,255,255), 90, 70, 0, nome_vida);

        al_flip_display();
    }
    exit_loop:;

    //DESTROI TUDO
    al_destroy_bitmap(spriteHeroi);
    al_destroy_bitmap(spriteTeste);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
