#include "personagem.h"
#include "itens.h"
#include "frame.h"

//campo das funções:
struct Personagem cria_personagem(int vida, int pos_inicial_x, int pos_inicial_y, float ataque, float velocidade, struct Arma arma, struct Frame frame){
    struct Personagem personagem = {vida, pos_inicial_x, pos_inicial_y, ataque, velocidade, arma, frame};

    return personagem;
}
struct Personagem muda_vida(struct Personagem personagem, int valor){
    personagem.vida += valor;
    if(personagem.vida < 0){
        personagem.vida = 0;
    }
    return personagem;
}

int dano_real(struct Personagem personagem){
    printf("%d", personagem.arma.dano);
    return (personagem.ataque+personagem.arma.dano);
}
int *pega_frame(struct Personagem personagem){
    int dados[] = {(personagem.frame.total_y/personagem.frame.n_linhas), (personagem.frame.total_x/personagem.frame.n_colunas)};
    return dados;
}











