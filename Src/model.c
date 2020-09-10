#include "model.h"
#include "view.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

Domino* s_getGameDominoes()
{
    static Domino array[GAME_DOMINOES_AMOUNT];

    return array;
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
        _dominoArray[i].scale = 1.0f;
        
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
    initializeDominoArray(s_getGameDominoes());
}
void resetDominoesState()
{
    Domino* gameDominos = s_getGameDominoes();

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        gameDominos[i].state = STATE_DOMINOES_PILE;
    }
}

void assignPlayer1StartingHand() //Atribui 7 dominos para o jogador 1
{
    Domino* gameDominos = s_getGameDominoes();
    int random = 0;

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;

        while(gameDominos[random].state != STATE_DOMINOES_PILE) //Reescrever, pode travar o programa se o random não bater com um domino sem dono
        {
            random = rand() % 28;
        }

        gameDominos[random].state = STATE_PLAYER_ONE;
    } 

    printf("Atribuida mao do jogador 1");
}
void assignPlayer2StartingHand() //Atribui 7 dominos para o jogador 2
{
    Domino* gameDominos = s_getGameDominoes();
    int random = 0;
    

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;
        
        while(gameDominos[random].state != STATE_DOMINOES_PILE) //Reescrever, pode travar o programa se o random não bater com um domino sem dono
        {
            random = rand() % 28;
        }

        gameDominos[random].state = STATE_PLAYER_TWO;
    }
    
    printf("Atribuida mao do jogador 1");
} 

//-----ORGANIZE/SHUFFLE DOMINOS-----//



void pickDominoeFromPile(int _playerState) //pega uma peca da pilha e atribui a um jogador especifico
{
    int random = 0;

    Domino* gameDominoes = s_getGameDominoes();

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;
        
        while(gameDominoes[random].state != STATE_DOMINOES_PILE)
        {
            random = rand() % 28;
        }

        gameDominoes[random].state = _playerState;
    }
}
void organizeDominoes()
{
    initializeDominoArray(s_getGameDominoes());
    printDominoes(s_getGameDominoes(), GAME_DOMINOES_AMOUNT);
}

void shuffleDominoesAndDisplay()
{
    shuffleDominoes(s_getGameDominoes());
    printDominoes(s_getGameDominoes(), GAME_DOMINOES_AMOUNT);
}

void displayPlayer1Hand()
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino domino;
    
    int lastDominoXPos = -8;
    int lastDominoYPos = -2;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        domino = gameDominoes[i];
        if(domino.state != STATE_PLAYER_ONE) continue;

        domino.posX = lastDominoXPos;
        lastDominoXPos += 3;
        domino.posY = lastDominoYPos;
        gameDominoes[i] = domino;
    }

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_PLAYER_ONE);
}

void displayPlayer2Hand()
{    
    Domino* gameDominoes = s_getGameDominoes();
    Domino domino;
    
    int lastDominoXPos = -8;
    int lastDominoYPos = -2;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        domino = gameDominoes[i];
        if(domino.state != STATE_PLAYER_TWO) continue;

        domino.posX = lastDominoXPos;
        lastDominoXPos += 3;
        domino.posY = lastDominoYPos;
        gameDominoes[i] = domino;
    }

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_PLAYER_TWO);
}
//-----ORGANIZE/SHUFFLE DOMINOS-----//