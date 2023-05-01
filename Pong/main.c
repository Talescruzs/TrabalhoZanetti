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

int main (){

    struct Personagem personagem1 = cria_personagem(50, 3, 1, mao, personagem_principal_f);

    //INICIAÇÕES DAS BIBLIOTECAS
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    //DECLARAÇÕES DA JANELA
    ALLEGRO_DISPLAY * display = al_create_display(640,480);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Jooj");

    //CONFIGURAÇÕES BASE QUE SERÃO UTILIZADAS
    ALLEGRO_BITMAP* spriteHeroi = al_load_bitmap(personagem1.frame.local_img);
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
    int pos_x = 0, pos_y = 0, tam_y_f = personagem1.frame.total_y/personagem1.frame.n_linhas, tam_x_f = personagem1.frame.total_x/personagem1.frame.n_colunas;
    int current_frame_y = tam_y_f;

    while(true){

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        //LISTA DE EVENTOS:
        if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){ //fecha
          break;
        }
        else if (event.keyboard.keycode != NULL){ //quaquer tecla
            if(
                event.keyboard.keycode==ALLEGRO_KEY_RIGHT ||
                event.keyboard.keycode==ALLEGRO_KEY_LEFT ||
                event.keyboard.keycode==ALLEGRO_KEY_UP ||
                event.keyboard.keycode==ALLEGRO_KEY_DOWN
            ){
                frame += 0.3f;
                if( frame > personagem1.frame.n_colunas){ //movimento do personagem
                    frame -= personagem1.frame.n_colunas;
                }
            }

            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_RIGHT:
                    pos_x += 5;
                    current_frame_y = tam_y_f;
                    break;
                case ALLEGRO_KEY_LEFT:
                    pos_x -= 5;
                    current_frame_y = tam_y_f*3;
                    break;
                case ALLEGRO_KEY_UP:
                    pos_y -= 5;
                    current_frame_y = 0;
                    break;
                case ALLEGRO_KEY_DOWN:
                    pos_y += 5;
                    current_frame_y = tam_y_f*2;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    goto exit_loop;
                default:
                    break;
            }
        }
        //DESENHO DA TELA (LEMBRA QUE O DE BAIXO SOBRESCREVE O DE CIMA)
        al_clear_to_color(al_map_rgb(0,0,0));

        al_draw_bitmap_region(spriteHeroi, tam_x_f * (int)frame, current_frame_y, tam_x_f, tam_y_f, pos_x, pos_y, 0);
        al_draw_text(font, al_map_rgb(255,255,255), 230, 200, 0, "Allegro is working!");

        al_flip_display();
    }
    exit_loop:;

    //DESTROI TUDO
    al_destroy_bitmap(spriteHeroi);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
