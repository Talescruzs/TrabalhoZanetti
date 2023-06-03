#ifndef __FRAME_H_
#define __FRAME_H_
//CLASSES
struct Frame{
    char * local_img;
    int total_x, total_y, n_linhas, n_colunas;
};
// PRESETS PERSONAGEM:
struct Frame personagem_principal_f;
struct Frame personagem_principal_dano;
struct Frame personagem_teste_f;
// PRESETS ITEM:
struct Frame teste_bola;

#endif
