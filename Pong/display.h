#ifndef __DISPLAY_H_
#define __DISPLAY_H_
#include "personagem.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
//CLASSES
struct Display{
    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE * fila;
    ALLEGRO_FONT* fonte;
    ALLEGRO_TIMER* timer;
};
//FUNÇÕES
struct Display inicia_display(int tam_disp_x, int tam_disp_y, int disp_pos_x, int disp_pos_y, char *nome);
int pass_level(struct Personagem personagem, int n_npc);
#endif
