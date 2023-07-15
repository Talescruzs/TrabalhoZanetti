#ifndef __FRAME_H_
#define __FRAME_H_
//CLASSES
struct Frame{
    char * local_img;
    char * local_img_dano;
    char * local_img_ataque;
    char * local_img_ataque_dano;
    int total_x, total_y, n_linhas, n_colunas;
};

struct Fundo{
    char * fechado;
    char * aberto;
};

// PRESETS PERSONAGEM:
struct Frame personagem_principal_f;
struct Frame personagem_adaga_f;
struct Frame personagem_espada_f;
struct Frame personagem_machado_f;
struct Frame personagem_inimigo_f;
struct Frame personagem_chefe_f;
// PRESETS ITEM:
struct Frame teste_bola;

#endif
