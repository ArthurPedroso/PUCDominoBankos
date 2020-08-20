#include "model.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void shuffleDominos(Domino* _outArrayDeDomino)
{
    //pega struct e guarda fora do array
    Domino temp;
    //seleciona lugar aleatório e troca de lugar
    for(int i = 0; i < GAME_DOMINOS_AMOUNT; i++)
    {
        int random = rand() % GAME_DOMINOS_AMOUNT;

        temp = _outArrayDeDomino[i];
        _outArrayDeDomino[i] = _outArrayDeDomino[random];
        _outArrayDeDomino[random] = temp;
    }

    //-----DEBUG-----//
    /*
    printf("\n");

    for (int j = 0; j < GAME_DOMINOS_AMOUNT; j++)
    {
        printf("%d, ", _outArrayDeDomino[j].type);
    }

    printf("\n");
    */
    //-----DEBUG-----//
}

void initializeDominoArray(Domino* _dominoArray)
{
    for(int i = 0; i < GAME_DOMINOS_AMOUNT; i++)
    {
        _dominoArray[i].posX = 0;
        _dominoArray[i].posY = 0;
        _dominoArray[i].rotation = DOMINO_UP;
        _dominoArray[i].type = i + 1;
    }    
}

//---------Header Funcs----------//

Domino* getGameDominos()
{
    static Domino array[GAME_DOMINOS_AMOUNT];

    return array;
}

void modelInitialization()
{
    srand(time(NULL));

    Domino* gameDominos = getGameDominos();

    initializeDominoArray(gameDominos);
    shuffleDominos(gameDominos);
}