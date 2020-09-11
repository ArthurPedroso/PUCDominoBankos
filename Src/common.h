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

typedef struct 
{
    int state;
    int posX;
    int posY;
    int rotation;
    int rightType;
    int leftType;
    float scale;
}Domino;

#endif