#include "model.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

Domino* shuffleDominos(Domino* _arrayDeDomino)
{
    //pega caixa e guarda fora do array
    Domino temp;
    //seleciona lugar aleatório e troca de lugar
    for(int i = 0; i < sizeof(_arrayDeDomino)/sizeof(Domino); i++)
    {
        int random = rand();

        temp = _arrayDeDomino[i];
        _arrayDeDomino[i] = _arrayDeDomino[random];
        _arrayDeDomino[random] = temp;
    }

    printf("\n");

    for (int i = 0; i < sizeof(_arrayDeDomino)/sizeof(Domino); i++)
    {
        printf("%d, ", _arrayDeDomino[i].type);
    }

    printf("\n");
    printf("%d", sizeof(_arrayDeDomino)/sizeof(Domino));
        
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
    srand(time(NULL));

    Domino* player1Dominos = getPlayer1DominoArray();
    Domino* player2Dominos = getPlayer2DominoArray();

    initializeDominoArray(player1Dominos);
    initializeDominoArray(player2Dominos);
    shuffleDominos(player1Dominos);
}