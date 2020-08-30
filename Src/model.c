#include "model.h"
#include "view.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

Domino* getGameDominoes()
{
    static Domino array[GAME_DOMINOES_AMOUNT];

    return array;

    //Domino* array = malloc(GAME_DOMINOES_AMOUNT * sizeof(Domino));

    //return array;
}

void getPlayersHands(Domino* _dominoesPile) //Recebe a pilha inicial de dominos e atribui 7 para cada jogador
{
    int random = 0;

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;

        while(_dominoesPile[random].state != STATE_DOMINOES_PILE)
        {
            random = rand() % 28;
        }

        _dominoesPile[random].state = STATE_PLAYER_ONE;
    } 

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;
        
        while(_dominoesPile[random].state != STATE_DOMINOES_PILE)
        {
            random = rand() % 28;
        }

        _dominoesPile[random].state = STATE_PLAYER_TWO;
    }
} 

void pickDominoeFromPile(Domino* _dominoesPile, int player) //pega uma peca da pilha e atribui a um jogador especifico
{
    int random = 0;

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;
        
        while(_dominoesPile[random].state != STATE_DOMINOES_PILE)
        {
            random = rand() % 28;
        }

        _dominoesPile[random].state = player;
    }
}

void shuffleDominoes(Domino* _outArrayDeDomino) //embaralha a pilha de dominos
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

void initializeDominoArray(Domino* _dominoArray) //inicializa a pilha de dominos
{
    int columCount= 0;
    int lineCount = 0;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        _dominoArray[i].state = STATE_DOMINOES_PILE;
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