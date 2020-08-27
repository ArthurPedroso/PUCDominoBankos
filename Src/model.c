#include "model.h"
#include "view.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


Domino* getPlayerHand(Domino* _pilhaDominos)
{
    Player Player1;

    for(int i = 0; i < HAND_DOMINOES_AMOUNT; i++)
    {

        int random = rand() % GAME_DOMINOES_AMOUNT;

        Player1.handDominoes[i] = _pilhaDominos[random];
        _pilhaDominos[random].leftType = EMPTY;
        _pilhaDominos[random].rightType = EMPTY;
    }

    return Player1.handDominoes;
} 

Domino* getGameDominoes()
{
    static Domino array[GAME_DOMINOES_AMOUNT];

    return array;
}

void shuffleDominoes(Domino* _outArrayDeDomino)
{
    //pega struct e guarda fora do array
    Domino temp;
    //seleciona lugar aleatório e troca de lugar
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        int random = rand() % GAME_DOMINOES_AMOUNT;

        temp = _outArrayDeDomino[i];
        _outArrayDeDomino[i] = _outArrayDeDomino[random];
        _outArrayDeDomino[random] = temp;
    }
}

void initializeDominoArray(Domino* _dominoArray)
{
    int columCount= 0;
    int lineCount = 0;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
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

void modelInitialization()
{
    srand(time(NULL));
}

void organizeDominoes()
{
    initializeDominoArray(getGameDominoes());
    printDominoes(getGameDominoes(), GAME_DOMINOES_AMOUNT);
}

void shuffleDominoesAndDisplay()
{
    shuffleDominoes(getGameDominoes());
    printDominoes(getGameDominoes(), GAME_DOMINOES_AMOUNT);
}