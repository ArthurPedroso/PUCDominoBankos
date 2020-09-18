#include "model.h"
#include "view.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//Armazena os dados dos dominós do jogo 
Domino* s_getGameDominoes()
{
    static Domino array[GAME_DOMINOES_AMOUNT];

    return array;
}


//Embaralha o array de dominos do jogo
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

//Atribui valores iniciais para todos os elementos do array de dominós
void initializeDominoArray(Domino* _dominoArray) //inicializa a pilha de dominos
{
    int columCount= 0;
    int lineCount = 0;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        _dominoArray[i].state = STATE_DOMINOES_PILE;
        _dominoArray[i].posX = 0;
        _dominoArray[i].posY = 0;
        _dominoArray[i].rotation = DOMINO_ROTATION_0;
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

int checkDominoesPile(Domino* _dominoArray)
{
    int dominoesInPileNumber = 0;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(_dominoArray[i].state == STATE_DOMINOES_PILE)
        {
            dominoesInPileNumber++;
        }
    }

    return dominoesInPileNumber;
}
//---------Header Funcs----------//

//Inicia o sistema de numeros aleatorios e Aloca a memoria utilizada pelo array de dominos
void modelInitialization()
{
    srand(time(NULL));
    initializeDominoArray(s_getGameDominoes());
}
//Aplica o estado de "STATE_DOMINOES_PILE" a todos os dominos do jogo
void resetDominoesState()
{
    Domino* gameDominos = s_getGameDominoes();

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        gameDominos[i].state = STATE_DOMINOES_PILE;
    }
}

void shuffleIntArray(int* _arrayInt, int _arraySize)
{
    int temp = 0;
    int random = 0;

    for(int i = 0; i < _arraySize; i++)
    {
        random = rand() % _arraySize;
        temp = _arrayInt[i];
        _arrayInt[i] = _arrayInt[random];
        _arrayInt[random] = temp;
    }
}

//Atribui 7 dominos para o jogador especificado
void assignPlayerStartingHand(int _player) 
{
    Domino* gameDominos = s_getGameDominoes();
    int arrayInt[28];
    int nDominosAlocados = 0;

    if(checkDominoesPile(gameDominos) >= 7)
    {
        for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
        {
            arrayInt[i] = i;
        }
        shuffleIntArray(arrayInt, GAME_DOMINOES_AMOUNT);

        for (int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
        {
            if(nDominosAlocados == 7)
            {
                break;
            }
            else if(gameDominos[arrayInt[i]].state == STATE_DOMINOES_PILE)
            {
                gameDominos[arrayInt[i]].state = _player;
                nDominosAlocados++;
            }
        }

        printf("Atribuida mao do jogador");
    }
    else
    {
        printf("Nao ha dominos suficientes na pilha");
    }
}



//Pega aleatoriamento um domiono da pilha de dominos e atribui ele ao jogador indicado pela variavel "_playerState"
void pickDominoeFromPile(int _playerState)
{
    Domino* gameDominos = s_getGameDominoes();
    int arrayInt[28];

    if(checkDominoesPile(gameDominos) >= 1)
    {
        for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
        {
            arrayInt[i] = i;
        }
        shuffleIntArray(arrayInt, GAME_DOMINOES_AMOUNT);

        for (int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
        {
            if(gameDominos[arrayInt[i]].state == STATE_DOMINOES_PILE)
            {
                gameDominos[arrayInt[i]].state = _playerState;
                break;
            }
        }

        printf("Domino retirado da pilha");
    }
    else
    {
        printf("Nao ha dominos suficientes na pilha");
    }
}

//Posiciona os dominos na área de "mão do jogador" na tela do opengl e pede para ele renderizar esse dominos
void displayPlayerHand(int _player)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino domino;
    
    int lastDominoXPos = -8;
    int lastDominoYPos = -2;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        domino = gameDominoes[i];
        if(domino.state != _player) continue;

        domino.posX = lastDominoXPos;
        lastDominoXPos += 3;
        domino.posY = lastDominoYPos;
        gameDominoes[i] = domino;
    }

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, _player);
}

//Move o domino selecionado do jogador 1 casa para determinada direcao
void movePlayerDomino(int _moveDirection, int _player)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* selectedDomino;
    bool foundSelectedDomino = FALSE;
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
            foundSelectedDomino = TRUE;
        } 
    }
    if(!foundSelectedDomino) 
    {
        printf("!ERRO! - Nenhum domino no estado de movimento encontrado!");
        return;
    }

    switch (_moveDirection)
    {
        case MOVE_DOMINO_UP:
            selectedDomino->posY += 1;
            break;
        case MOVE_DOMINO_DOWN:
            selectedDomino->posY -= 1;
            break;
        case MOVE_DOMINO_LEFT:
            selectedDomino->posX -= 1;
            break;
        case MOVE_DOMINO_RIGHT:
            selectedDomino->posX += 1;
            break;
    }    
    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING);
}

//Troca a selecao de domino do jogador para o proximo domino da sua mão
void changePlayerSelectedDomino(int _player)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* selectedDomino;
    bool foundSelectedDomino = FALSE;
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
            selectedDomino->state = _player;
            selectedDomino->posX = 0;
            selectedDomino->posY = 0;
            foundSelectedDomino = TRUE;
        }
        else if(foundSelectedDomino)
        {
            if(gameDominoes[i].state == _player)
            {
                gameDominoes[i].state = STATE_GAME_MOVING;
                hideDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, _player); //esconde o domino deselecionado
                printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING); //exibe o novo domino selecionado
                return;
            }          
        }
        
    }
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == _player)
        {
            gameDominoes[i].state = STATE_GAME_MOVING;
            hideDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, _player); //esconde o domino deselecionado
            printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING); //exibe o novo domino selecionado
            return;
        }          
    }
}

//Deseleciona o domino que o jogador estava movendo
void unselectPlayerDomino(int _player)
{
    Domino* gameDominoes = s_getGameDominoes();
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) gameDominoes[i].state = STATE_PLAYER_ONE;
    }
}

//Verifica se o domino pode ser posicionado (em rpodução)
//bool checkIfDominoCanBePlaced()
//{
//    Domino* gameDominoes = s_getGameDominoes();
//    Domino* leftDomino = NULL;
//    Domino* rightDomino = NULL;
//    Domino* upDomino = NULL;
//    Domino* downDomino = NULL;
//    Domino* selectedDomino = NULL;
//
//    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
//    {
//        if(gameDominoes[i].state == STATE_GAME_MOVING) 
//        {
//            selectedDomino = &gameDominoes[i];
//            break;
//        }
//    }
//
//    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
//    {
//        if(selectedDomino->posX - 1 == gameDominoes[i].posX)
//            leftDomino = &gameDominoes[i];
//        else if(selectedDomino->posX + 1 == gameDominoes[i].posX)
//            rightDomino = &gameDominoes[i];
//        else if(selectedDomino->posY - 1 == gameDominoes[i].posY)
//            downDomino = &gameDominoes[i];
//        else if(selectedDomino->posY + 1 == gameDominoes[i].posY)
//            upDomino = &gameDominoes[i];
//    }
//
//
//
//    if(selectedDomino->rotation == DOMINO_ROTATION_0 || selectedDomino->rotation == DOMINO_ROTATION_180)
//    {
//        if(leftDomino || rightDomino)
//    }
//
//    return FALSE;
//}


//-----ORGANIZE/SHUFFLE DOMINOS-----//

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
//-----ORGANIZE/SHUFFLE DOMINOS-----//