#include "frame.h"
#include "itens.h"


//PRESETS:
struct Arma mao = {
    " ", 1,0,
    {
        "./imagens/bola.png",
        "./imagens/bola.png",
        "./imagens/bola.png",
        "./imagens/bola.png",
        77,77,1,1
    },
    {"", ""}
};
struct Arma adaga = {
    "adaga",
    1, 2,
    {
        "./imagens/adaga_chao.png",
        "./imagens/adaga_chao.png",
        "./imagens/adaga_chao.png",
        "./imagens/bola.png",
        15,30,1,1
    },
    {
        "./musicas/PegaArma/adaga.wav",
        "./musicas/Ataques/adaga.wav"
    }
};
struct Arma espada = {
    "espada",
    2, 5,
    {
        "./imagens/espada_chao.png",
        "./imagens/espada_chao.png",
        "./imagens/espada_chao.png",
        "./imagens/bola.png",
        46,46,1,1
    },
    {
        "./musicas/PegaArma/espada.wav",
        "./musicas/Ataques/espada.wav"
    }
};
struct Arma machado = {
    "machado",
    3, 15,
    {
        "./imagens/machado_chao.png",
        "./imagens/machado_chao.png",
        "./imagens/machado_chao.png",
        "./imagens/bola.png",
        50,67,1,1
    },
    {
        "./musicas/PegaArma/machado.wav",
        "./musicas/Ataques/machado.wav"
    }
};
struct Arma pica = {
    "pica",
    3, 1000,
    {
        "./imagens/bola.png",
        "./imagens/bola.png",
        "./imagens/bola.png",
        "./imagens/bola.png",
        77,77,1,1
    },
    {"", ""}
};
