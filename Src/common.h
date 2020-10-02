#ifndef COMMON_HEADER
#define COMMON_HEADER

#include <stdbool.h>

#define TRUE 1
#define FALSE 0

//-----CHECK OS-----//
#ifdef __unix__ 

#elif defined(_WIN32) || defined(WIN32) 

#define OS_Windows

#endif
//-----CHECK OS-----//

#define GAME_DOMINOES_AMOUNT 28
#define HAND_DOMINOES_STARTING_AMOUNT 7

typedef struct DominoStructTAG
{
    //Estado de jogo do domino
    int state;
    //Posicao em x do domino
    float posX;
    //Posicao em x do domino
    float posY;
    //Rotacao do dominoP
    int rotation;
    //Tipo do quadrado da direira do domino
    int rightType;
    //Tipo do quadrado da esquerda do domino
    int leftType;
    //estado de conexão do domino
    int linkableDominoState;
    //Tamanho do domino
    float scale;
    //Domino linkado com esse domino
    struct DominoStructTAG* linkedDomino;
    //flag usada para determinar se o dominó foi pego pelo player 1->1 ou 2->2 ou nenhum 0
    int playerColorID;
}Domino;

typedef struct
{
    Domino* domino;
    int linkDirection;
} LinkableDomino;

#endif