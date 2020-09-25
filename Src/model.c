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
        _dominoArray[i].linkableDominoState = UNLINKABLE_DOMINO;
        _dominoArray[i].linkedDomino = NULL;
        _dominoArray[i].pickedByPlayer1 = 0;
        
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

bool checkIfThereIsDominosOnTable()
{
    Domino* dominoes = s_getGameDominoes();
    bool dominoOnTable = FALSE;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(dominoes[i].state == STATE_GAME_TABLE)
        {
            dominoOnTable = TRUE;
            break;
        }
    }

    return dominoOnTable;
}

void moveSelectedDominoToLinkedSpace(Domino* _selectedDomino)
{
    Domino* linkedDomino = _selectedDomino->linkedDomino;
    switch (linkedDomino->linkableDominoState)
    {
        case LINKABLE_DOMINO_LEFT:
            _selectedDomino->posX = linkedDomino->posX - 1;
            break;    
        case LINKABLE_DOMINO_RIGHT:
            _selectedDomino->posX = linkedDomino->posX + 1;
            break;
        case LINKABLE_DOMINO_LEFT_RIGHT:
            if(_selectedDomino->posX == linkedDomino->posX + 1)
                _selectedDomino->posX = linkedDomino->posX - 1;
            else 
                _selectedDomino->posX = linkedDomino->posX + 1;            
            break;
    }
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
                gameDominos[arrayInt[i]].pickedByPlayer1 = _player;
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
                gameDominos[arrayInt[i]].pickedByPlayer1 = _playerState;
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
void movePlayerDomino(int _player)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* selectedDomino;
    Domino* linkableDomino1 = NULL;
    Domino* linkableDomino2 = NULL;
    int linkableDominosIndex;
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
        } 
        else if(gameDominoes[i].linkableDominoState != UNLINKABLE_DOMINO)
        {
            if(!linkableDomino1)
            {
                linkableDomino1 = &gameDominoes[i];
            }
            else if(!linkableDomino2)
            {
                linkableDomino2 =  &gameDominoes[i];
            }
            else
            {
                printf("!ERRO! - Mais de um domino linkavel!!!");
                return;
            }          
        }
    }

    if(!selectedDomino) 
    {
        printf("!ERRO! - Nenhum domino no estado de movimento encontrado!");
        return;
    }

    if(selectedDomino->linkedDomino == linkableDomino1)
        selectedDomino->linkedDomino = linkableDomino2;
    else
        selectedDomino->linkedDomino = linkableDomino1;

    
    moveSelectedDominoToLinkedSpace(selectedDomino);

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING);
}

//Troca a selecao de domino do jogador para o proximo domino da sua mão
void changePlayerSelectedDomino(int _player)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* selectedDomino;
    bool foundSelectedDomino = FALSE;
    int playerSelectedDomino = -1;

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
            if(gameDominoes[i].state == _player) playerSelectedDomino = i;      
        }        
    }
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == _player) playerSelectedDomino = i;
    }
    if(playerSelectedDomino != -1)
    {
        gameDominoes[playerSelectedDomino].state = STATE_GAME_MOVING;
        if(!checkIfThereIsDominosOnTable()) 
        {
            gameDominoes[playerSelectedDomino].posX = 0;
            gameDominoes[playerSelectedDomino].posY = 0;
        }

        hideDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, _player); //esconde o domino deselecionado
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING); //exibe o novo domino selecionado
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
bool checkIfDominoCanBePlaced()
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* leftDomino = NULL;
    Domino* rightDomino = NULL;
    Domino* upDomino = NULL;
    Domino* downDomino = NULL;
    Domino* selectedDomino = NULL;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
            break;
        }
    }

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(selectedDomino->posX - 1 == gameDominoes[i].posX)
            leftDomino = &gameDominoes[i];
        else if(selectedDomino->posX + 1 == gameDominoes[i].posX)
            rightDomino = &gameDominoes[i];
        else if(selectedDomino->posY - 1 == gameDominoes[i].posY)
            downDomino = &gameDominoes[i];
        else if(selectedDomino->posY + 1 == gameDominoes[i].posY)
            upDomino = &gameDominoes[i];
    }


    /* Rotation
    if(selectedDomino->rotation == DOMINO_ROTATION_0 || selectedDomino->rotation == DOMINO_ROTATION_180)
    {
        if(leftDomino || rightDomino)
    }
    */

    if(leftDomino)
    {
        if(leftDomino->rightType == selectedDomino->leftType)
            return TRUE;
    }
    else if(rightDomino)
    {
        if(rightDomino->leftType == selectedDomino->rightType) 
            return TRUE;
    }
    

    return FALSE;
}

//Tenta posicionar o domino na mesa e mudar automaticamente a peça selecionada pelo jogador
bool tryToSetSelectedDominoToTable()
{   
    Domino* selectedDomino;
    Domino* gameDominoes = s_getGameDominoes();
    bool oneOrMoreDominosPlaced = FALSE;
    bool canPlaceDomino = FALSE;
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
            break;
        }
    }

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_TABLE) 
        {
            oneOrMoreDominosPlaced = TRUE;
            break;
        }
    }

    canPlaceDomino = checkIfDominoCanBePlaced();

    if(oneOrMoreDominosPlaced && !canPlaceDomino)
    {
        return FALSE;
    }
    else if(!oneOrMoreDominosPlaced)
    {
        selectedDomino->state = STATE_GAME_TABLE;
        selectedDomino->posX = 0;
        selectedDomino->posY = 0;
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE);
        return TRUE;
    }
    else
    {
        selectedDomino->state = STATE_GAME_TABLE;
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE);
        return TRUE;
    }
    return FALSE;
}

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