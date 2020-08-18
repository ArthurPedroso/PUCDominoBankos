#include "model.h"
#include <stdlib.h>
#include <time.h>

Domino* shuffleDominos(Domino* _arrayDeDomino)
{
    //pega caixa e guarda fora do array
    Domino temp;
    //seleciona lugar aleatório e troca de lugar
    for(int i = 0; i < sizeof(_arrayDeDomino)/sizeof(Domino); i++)
    {
        temp = _arrayDeDomino[i];
        _arrayDeDomino 
    }
    //por exemplo 1 no lugar no 5 e 5 no lugar do 1
    //de maneira aleatória e sem repetir
    
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