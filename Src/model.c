#include "model.h"
#include "view.h"
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
    int columCount= 0;
    int lineCount = 0;

    for(int i = 0; i < GAME_DOMINOS_AMOUNT; i++)
    {
        _dominoArray[i].posX = 0;
        _dominoArray[i].posY = 0;
        _dominoArray[i].rotation = DOMINO_UP;
        _dominoArray[i].rightType = columCount + lineCount;
        _dominoArray[i].leftType = lineCount;
        
        if(columCount >= 6 - lineCount)
        {
            columCount = 0;
            lineCount++;
        }
        else
        {
            columCount++;
        }
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

    organizeDominoes();
    //shuffleDominos(gameDominos);
}

void organizeDominoes()
{
    initializeDominoArray(getGameDominos());
    printDominoes(getGameDominos(), GAME_DOMINOS_AMOUNT);
}