#include "model.h"
#include <stdlib.h>

Domino* shuffleDominos(Domino* _arrayDeDomino)
{
    return _arrayDeDomino;
}

void initializeDominoArray(Domino* _dominoArray)
{
    for(int i = 0; i < sizeof(_dominoArray) / sizeof(Domino); i++)
    {
        _dominoArray[i].posX = 0;
        _dominoArray[i].posY = 0;
        _dominoArray[i].rotation = DOMINO_UP;
        _dominoArray[i].type = i;
    }    
}

//---------Header Funcs----------//

Domino* getPlayer1DominoArray()
{
    static Domino array[GAME_DOMINOS_AMOUNT];

    return array;
}
Domino* getPlayer2DominoArray()
{
    static Domino array[GAME_DOMINOS_AMOUNT];

    return array;
}

void modelInitialization()
{
    Domino* player1Dominos = getPlayer1DominoArray();
    Domino* player2Dominos = getPlayer2DominoArray();

    initializeDominoArray(player1Dominos);
    initializeDominoArray(player2Dominos);
}