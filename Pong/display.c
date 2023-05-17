#include "display.h"
#include "personagem.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

struct Display inicia_display(int tam_disp_x, int tam_disp_y, int disp_pos_x, int disp_pos_y, char *nome){
    ALLEGRO_DISPLAY * display = al_create_display(tam_disp_x,tam_disp_y);
    al_set_window_position(display, disp_pos_x, disp_pos_y);
    al_set_window_title(display, nome);
    //COISAS MEIO IRRELEVANTES DE MEXER
    ALLEGRO_FONT* font = al_load_font("C:/Windows/Fonts/arial.ttf", 15, 0);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    //FILA DE EVENTOS
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    struct Display dado;
    dado.display = display;
    dado.fila = event_queue;
    dado.fonte = font;

    return dado;
}

int pass_level(struct Personagem personagem, int n_npc){
    if(n_npc==0 && (personagem.pos_y>=200 && personagem.pos_y<=250) && personagem.pos_x>=760){
        return 1;
    }else{
        return 0;
    }
}










