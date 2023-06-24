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
    struct Personagem personagem1 = cria_personagem(50, pos_x_inicial, pos_y_inicial, lin, col, 3, velocidade, mao, personagem_principal_f, colision, 0, 0);
    struct Personagem npc[n_npc];

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

    al_reserve_samples(3);
    //MUSICA DE FUNDO:
    ALLEGRO_SAMPLE *musica = al_load_sample("./musicas/fundo1.wav");
    ALLEGRO_SAMPLE_INSTANCE *instMusica = al_create_sample_instance(musica);
    al_attach_sample_instance_to_mixer(instMusica, al_get_default_mixer());
    //SONS DOS ATAQUES:
    ALLEGRO_SAMPLE *som_ataque_1 = al_load_sample("./musicas/dano.wav");
    ALLEGRO_SAMPLE *som_ataque_2 = al_load_sample(adaga.sons.ataca);
    ALLEGRO_SAMPLE *som_ataque_3 = al_load_sample(espada.sons.ataca);
    ALLEGRO_SAMPLE *som_ataque_4 = al_load_sample(machado.sons.ataca);
    ALLEGRO_SAMPLE_INSTANCE *instance_som_ataque_1 = al_create_sample_instance(som_ataque_1);
    ALLEGRO_SAMPLE_INSTANCE *instance_som_ataque_2 = al_create_sample_instance(som_ataque_2);
    ALLEGRO_SAMPLE_INSTANCE *instance_som_ataque_3 = al_create_sample_instance(som_ataque_3);
    ALLEGRO_SAMPLE_INSTANCE *instance_som_ataque_4 = al_create_sample_instance(som_ataque_4);
    al_attach_sample_instance_to_mixer(instance_som_ataque_1, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(instance_som_ataque_2, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(instance_som_ataque_3, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(instance_som_ataque_4, al_get_default_mixer());
    //SONS DE PEGAR ITEM:
    ALLEGRO_SAMPLE *som_pega_2 = al_load_sample(adaga.sons.pega);
    ALLEGRO_SAMPLE *som_pega_3 = al_load_sample(espada.sons.pega);
    ALLEGRO_SAMPLE *som_pega_4 = al_load_sample(machado.sons.pega);
    ALLEGRO_SAMPLE_INSTANCE *instance_som_pega_2 = al_create_sample_instance(som_pega_2);
    ALLEGRO_SAMPLE_INSTANCE *instance_som_pega_3 = al_create_sample_instance(som_pega_3);
    ALLEGRO_SAMPLE_INSTANCE *instance_som_pega_4 = al_create_sample_instance(som_pega_4);
    al_attach_sample_instance_to_mixer(instance_som_pega_2, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(instance_som_pega_3, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(instance_som_pega_4, al_get_default_mixer());


    //CONFIG DOS SPRITES PARA DESENHAR
    ALLEGRO_BITMAP* spriteHeroiNormal = al_load_bitmap(personagem1.frame.local_img);
    ALLEGRO_BITMAP* spriteHeroiDano = al_load_bitmap(personagem1.frame.local_img_dano);
    ALLEGRO_BITMAP* spriteHeroiAtaque = al_load_bitmap(personagem1.frame.local_img_ataque);
    ALLEGRO_BITMAP* spriteHeroiAtaqueDano = al_load_bitmap(personagem1.frame.local_img_ataque_dano);
    ALLEGRO_BITMAP* spriteHeroi;

    ALLEGRO_BITMAP* sprite_npc[n_npc];
    ALLEGRO_BITMAP* sprite_fundo = al_load_bitmap("./imagens/Inkedmapa.png");

    ALLEGRO_BITMAP* sprite_arma_1 = al_load_bitmap(adaga.frame.local_img);
    ALLEGRO_BITMAP* sprite_arma_2 = al_load_bitmap(espada.frame.local_img);
    ALLEGRO_BITMAP* sprite_arma_3 = al_load_bitmap(machado.frame.local_img);
    ALLEGRO_BITMAP* sprite_arma_4 = al_load_bitmap(pica.frame.local_img);


    int tam_y_f_t[n_npc], tam_x_f_t[n_npc];
    int *tams_f_t;

    //DEFINE SPRITE DO PERSONAGEM PRINCIPAL
    int *tams_f = pega_frame(personagem1);
    int tam_y_f_pp = tams_f[0], tam_x_f_pp = tams_f[1];
    personagem1.linha = tam_y_f_pp;
    //TEXTOS DA TELA DO JOGO
    int text_l_1 = 6;
    char *texto[text_l_1], *texto_final, *texto_perdeu;
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
    char menu_arma[] = "Arma: ";
    char menu_vida[] = "Vida: ";
    //COMEÇA
    n_npc = 0;
    int flag_frame1 = 0;
    int flag_frame2 = 0;
    int flag_sprite = 0;
    int flag_item = 0;
    struct Arma arma_temp;
    struct Frame frame_temp;
    al_play_sample(musica, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
    while(true){
        ALLEGRO_EVENT event;
        al_wait_for_event(dados.fila, &event);
        //VALORES DINAMICOS DO PERSONAGEM
        itoa(personagem1.vida, &nome_vida, 10);
        nome_arma = personagem1.arma.nome;

        if(personagem1.vida<=0){
            goto exit_loop;
        }
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
                for(i=0; i<n_npc; i++){
                    npc[i] = cria_personagem(10, 500, 250, lin, col, 3, 2, mao, personagem_inimigo_f, colision, level, i);
                    sprite_npc[i] = al_load_bitmap(npc[i].frame.local_img);
                    tams_f_t = pega_frame(npc[i]);
                    tam_y_f_t[i] = tams_f_t[0];
                    tam_x_f_t[i] = tams_f_t[1];
                    npc[i].linha = tam_y_f_t[i];
                }
            }
        }
        //COLISAO
        if(n_npc>0 && level>0 && level<=n_levels && personagem1.vida>0){
            for(i=0; i<n_npc; i++){
                npc[i] = colision_parede(npc[i], tam_disp_x, tam_disp_y);
                npc[i] = movimento_npc(personagem1, npc[i], tam_y_f_t[i]);
                int vida_temp = personagem1.vida;
                personagem1 = colision_final(personagem1, npc[i], tam_disp_x, tam_disp_y);
                if(vida_temp>personagem1.vida){
                    flag_frame1++;
                }
                if(flag_frame1>0 && flag_frame1<50){
                    flag_frame1++;
                }else{
                    flag_frame1 = 0;
                }
            }
        }else{
            personagem1 = colision_parede(personagem1, tam_disp_x, tam_disp_y);
        }
        frame_temp = personagem1.frame;
        if(n_npc==0){
            flag_frame1 = 0;
            personagem1.frame = frame_temp;
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
                        flag_frame2 ++;
                        switch(personagem1.arma.dano){
                            case 0:
                                al_play_sample_instance(instance_som_ataque_1);
                                break;
                            case 2:
                                al_play_sample_instance(instance_som_ataque_2);
                                break;
                            case 5:
                                al_play_sample_instance(instance_som_ataque_3);
                                break;
                            case 15:
                                al_play_sample_instance(instance_som_ataque_4);
                                break;
                            default:
                                break;
                        }
                        if(level>0 && level<=n_levels){
                            int flag[n_npc];
                            int c;
                            for(i=0;i<n_npc;i++){
                                npc[i] = ataque(personagem1, npc[i], personagem1.linha);
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
        if(flag_frame2>0 && flag_frame2<40){
            personagem1.coluna += 0.1f;
            if( personagem1.coluna > personagem1.frame.n_colunas){
                personagem1.coluna -= personagem1.frame.n_colunas;
            }
            flag_frame2 ++;
        }else{
            flag_frame2 = 0;
        }
        //FAZ O MOVIMENTO DA IMAGEM
        if((keys[UP] || keys[DOWN] || keys[RIGHT] || keys[LEFT])&&flag_frame2==0){
            personagem1.coluna += 0.1f;
            if( personagem1.coluna > personagem1.frame.n_colunas){
                personagem1.coluna -= personagem1.frame.n_colunas;
            }
        }
        //FAZ O MOVIMENTO DO PERSONAGEM
        if(keys[UP] && personagem1.colision.up==0 && flag_frame2==0){
            personagem1.pos_y -= personagem1.velocidade;
            personagem1.linha = 0;
        }
        if(keys[DOWN] && personagem1.colision.down==0 && flag_frame2==0){
            personagem1.pos_y += personagem1.velocidade;
            personagem1.linha = tam_y_f_pp*2;
        }
        if(keys[RIGHT] && personagem1.colision.right==0 && flag_frame2==0){
            personagem1.pos_x += personagem1.velocidade;
            personagem1.linha = tam_y_f_pp;
        }
        if(keys[LEFT] && personagem1.colision.left==0 && flag_frame2==0){
            personagem1.pos_x -= personagem1.velocidade;
            personagem1.linha = tam_y_f_pp*3;
        }

        //DESENHO DA TELA (LEMBRA QUE O DE BAIXO SOBRESCREVE O DE CIMA)
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(sprite_fundo, 0, 0, 0);
        //DESENHA NPCS
        if(level>0 && level<=n_levels && personagem1.vida>0){
            for(i=0; i<n_npc; i++){
                al_draw_bitmap_region(sprite_npc[i], tam_x_f_t[i] * (int)npc[i].coluna, npc[i].linha, tam_x_f_t[i], tam_y_f_t[i], npc[i].pos_x, npc[i].pos_y, 0);
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
                tams_f = pega_frame(personagem1);
                al_play_sample_instance(instance_som_pega_2);
                tam_y_f_pp = tams_f[0], tam_x_f_pp = tams_f[1];
                al_destroy_bitmap(sprite_arma_1);
                al_destroy_sample_instance(instance_som_ataque_1);
                al_destroy_sample(som_ataque_1);
            }
            if(flag_item == 0){
                al_draw_bitmap(sprite_arma_1, pos_item_x, pos_item_y, 0);
            }
        }else if(level == 2){
            struct Arma arma_temp = personagem1.arma;
            personagem1 = pegou_item(personagem1, espada, pos_item_x, pos_item_y);
            if(arma_temp.dano!=personagem1.arma.dano){
                flag_item = 1;
                tams_f = pega_frame(personagem1);
                al_play_sample_instance(instance_som_pega_3);
                tam_y_f_pp = tams_f[0], tam_x_f_pp = tams_f[1];
                    al_destroy_bitmap(sprite_arma_2);
                    al_destroy_sample_instance(instance_som_ataque_2);
                    al_destroy_sample(som_ataque_2);
                    al_destroy_sample_instance(instance_som_pega_2);
                    al_destroy_sample(som_pega_2);
            }
            if(flag_item == 0){
                al_draw_bitmap(sprite_arma_2, pos_item_x, pos_item_y, 0);
            }
        }else if(level == 4){
            struct Arma arma_temp = personagem1.arma;
            personagem1 = pegou_item(personagem1, machado, pos_item_x, pos_item_y);
            if(arma_temp.dano!=personagem1.arma.dano){
                flag_item = 1;
                tams_f = pega_frame(personagem1);
                al_play_sample_instance(instance_som_pega_4);
                tam_y_f_pp = tams_f[0], tam_x_f_pp = tams_f[1];
                    al_destroy_bitmap(sprite_arma_3);
                    al_destroy_sample_instance(instance_som_ataque_3);
                    al_destroy_sample(som_ataque_3);
                    al_destroy_sample_instance(instance_som_pega_3);
                    al_destroy_sample(som_pega_3);
            }
            if(flag_item == 0){
                al_draw_bitmap(sprite_arma_3, pos_item_x, pos_item_y, 0);
            }
        }
        if(flag_item==1){
            spriteHeroiNormal = al_load_bitmap(personagem1.frame.local_img);
            spriteHeroiDano = al_load_bitmap(personagem1.frame.local_img_dano);
            spriteHeroiAtaque = al_load_bitmap(personagem1.frame.local_img_ataque);
            spriteHeroiAtaqueDano = al_load_bitmap(personagem1.frame.local_img_ataque_dano);
            flag_item ++;
            flag_sprite = 0;
        }
        if(flag_frame1 == 0 && flag_frame2 == 0 && flag_sprite!=1){
            spriteHeroi = spriteHeroiNormal;
            flag_sprite=1;
        }else if(flag_frame1!=0&&flag_frame2==0 && flag_sprite!=2){
            spriteHeroi = spriteHeroiDano;
            flag_sprite=2;
        }else if(flag_frame1==0&&flag_frame2!=0 && flag_sprite!=3){
            spriteHeroi = spriteHeroiAtaque;
            flag_sprite = 3;
        }else if(flag_frame1!=0&&flag_frame2!=0 && flag_sprite!=4){
            spriteHeroi = spriteHeroiAtaqueDano;
            flag_sprite = 4;
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

        if(personagem1.vida>0){
            al_draw_bitmap_region(spriteHeroi, tam_x_f_pp * (int)personagem1.coluna, personagem1.linha, tam_x_f_pp, tam_y_f_pp, personagem1.pos_x, personagem1.pos_y, 0);
        }
        al_flip_display();
    }
    exit_loop:; //PONTO DE FUGA
    //DESTROI TUDO
    al_destroy_bitmap(sprite_fundo);
    al_destroy_bitmap(spriteHeroi);
    al_destroy_bitmap(spriteHeroiNormal);
    al_destroy_bitmap(spriteHeroiDano);
    al_destroy_bitmap(spriteHeroiAtaque);
    al_destroy_bitmap(spriteHeroiAtaqueDano);
    al_destroy_bitmap(sprite_arma_4);
    for(i=0; i<n_npc; i++){
        al_destroy_bitmap(sprite_npc[i]);
    }
    al_destroy_sample_instance(instMusica);
    al_destroy_sample(musica);
    al_destroy_sample_instance(instance_som_ataque_4);
    al_destroy_sample(som_ataque_4);
    al_destroy_sample_instance(instance_som_pega_4);
    al_destroy_sample(som_pega_4);
    al_destroy_font(dados.fonte);
    al_destroy_display(dados.display);
    al_destroy_event_queue(dados.fila);
    al_destroy_timer(dados.timer);
    return 0;
}










