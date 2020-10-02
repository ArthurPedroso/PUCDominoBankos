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

//Armazena o tamanho que dominós da mesa tem que adotar
float* s_getTableDominoesSize()
{
    static float tableDominoesSize = 0.4f;

    return &tableDominoesSize;
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
        _dominoArray[i].position.posX = 0;
        _dominoArray[i].position.posY = 0;
        _dominoArray[i].rotation = DOMINO_ROTATION_0;
        _dominoArray[i].rightType = columCount + lineCount;
        _dominoArray[i].leftType = lineCount;
        _dominoArray[i].scale = 1.0f;
        _dominoArray[i].linkableDominoState = UNLINKABLE_DOMINO;
        _dominoArray[i].linkedDomino = NULL;
        _dominoArray[i].playerColorID = 0;
        
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

//verifica se existem dominos na mesa
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
//retorna a quantidade de dominos posicionados na mesa de jogo
int getTableDominoesAmount()
{
    Domino* dominoes = s_getGameDominoes();
    int tableDominoesAmount = 0;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(dominoes[i].state == STATE_GAME_TABLE)
        {
            tableDominoesAmount++;
        }
    }

    return tableDominoesAmount;
}

void moveSelectedDominoToLinkedSpace(Domino* _selectedDomino)
{
    Domino* linkedDomino = _selectedDomino->linkedDomino;

    _selectedDomino->position.posY = 0;
    switch (linkedDomino->linkableDominoState)
    {
        case LINKABLE_DOMINO_LEFT:
            _selectedDomino->position.posX = linkedDomino->position.posX - 2;
            break;    
        case LINKABLE_DOMINO_RIGHT:
            _selectedDomino->position.posX = linkedDomino->position.posX + 2;
            break;
        case LINKABLE_DOMINO_LEFT_RIGHT:
            if(_selectedDomino->position.posX == linkedDomino->position.posX + 2)
                    _selectedDomino->position.posX = linkedDomino->position.posX - 2;
            else 
                    _selectedDomino->position.posX = linkedDomino->position.posX + 2;            
            break;
    }
}

void findSurroundingDominoes(Domino* _selectedDomino, Domino** _outDominoRight, Domino** _outDominoDown, Domino** _outDominoLeft, Domino** _outDominoUp)
{
    Domino* gameDominoes = s_getGameDominoes();

    

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state != STATE_GAME_TABLE) continue;

        if(_selectedDomino->position.posX - 2 == gameDominoes[i].position.posX)
            *_outDominoLeft = &gameDominoes[i];
        else if(_selectedDomino->position.posX + 2 == gameDominoes[i].position.posX)
            *_outDominoRight = &gameDominoes[i];
        else if(_selectedDomino->position.posY - 2 == gameDominoes[i].position.posY)
            *_outDominoDown = &gameDominoes[i];
        else if(_selectedDomino->position.posY + 2 == gameDominoes[i].position.posY)
            *_outDominoUp = &gameDominoes[i];
    }
}

//Verifica se o domino pode ser posicionado (em rpodução)
bool checkDominoPlacement(Domino** _outConnectingDomino)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* leftDomino = NULL;
    Domino* rightDomino = NULL;
    Domino* upDomino = NULL;
    Domino* downDomino = NULL;
    Domino* selectedDomino = NULL;
    *_outConnectingDomino = NULL;

    int selectedDominoLeftType = 0;
    int selectedDominoRightType = 0;

    bool placementIsValid = FALSE;

    if(!checkIfThereIsDominosOnTable()) return TRUE;

    for(int j = 0; j < GAME_DOMINOES_AMOUNT; j++)
    {
        if(gameDominoes[j].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[j];
            break;
        }
    }

    findSurroundingDominoes(selectedDomino, &rightDomino, &downDomino, &leftDomino, &upDomino);


    /* Rotation
    if(selectedDomino->rotation == DOMINO_ROTATION_0 || selectedDomino->rotation == DOMINO_ROTATION_180)
    {
        if(leftDomino || rightDomino)
    }
    */

    if(selectedDomino->rotation == DOMINO_ROTATION_180)
    {
        selectedDominoLeftType = selectedDomino->rightType;
        selectedDominoRightType = selectedDomino->leftType;
    }
    else if(selectedDomino->rotation == DOMINO_ROTATION_0)
    {
        selectedDominoLeftType = selectedDomino->leftType;
        selectedDominoRightType = selectedDomino->rightType;
    }
    else
    {
        return FALSE;
    }
    
    
    

    if(leftDomino)
    {
        if(leftDomino->rotation == DOMINO_ROTATION_180)
        {
            if(leftDomino->leftType == selectedDominoLeftType)
            {
                *_outConnectingDomino = leftDomino;
                placementIsValid = TRUE;
            }
        }
        else
        {   
            if(leftDomino->rightType == selectedDominoLeftType)
            {
                *_outConnectingDomino = leftDomino;
                placementIsValid = TRUE;
            }
        }
    }
    else if(rightDomino)
    {
        if(rightDomino->rotation == DOMINO_ROTATION_180)
        {
            if(rightDomino->rightType == selectedDominoRightType) 
            {
                *_outConnectingDomino = rightDomino;
                placementIsValid = TRUE;
            }
        }
        else
        {
            if(rightDomino->leftType == selectedDominoRightType) 
            {
                *_outConnectingDomino = rightDomino;
                placementIsValid = TRUE;
            }
        }
    }
    

    return placementIsValid;
}

void setGameTableDominoesSize(float _newScale)
{
    Domino* gameDominoes = s_getGameDominoes();
    *s_getTableDominoesSize() = _newScale;
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state != STATE_GAME_MOVING && gameDominoes[i].state != STATE_GAME_TABLE) continue;
        gameDominoes[i].scale = _newScale;
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

        for (int j = 0; j < GAME_DOMINOES_AMOUNT; j++)
        {
            if(nDominosAlocados == 7)
            {
                break;
            }
            else if(gameDominos[arrayInt[j]].state == STATE_DOMINOES_PILE)
            {
                gameDominos[arrayInt[j]].state = _player;
                gameDominos[arrayInt[j]].playerColorID = _player;
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
        for(int j = 0; j < GAME_DOMINOES_AMOUNT; j++)
        {
            arrayInt[j] = j;
        }
        shuffleIntArray(arrayInt, GAME_DOMINOES_AMOUNT);

        for (int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
        {
            if(gameDominos[arrayInt[i]].state == STATE_DOMINOES_PILE)
            {
                gameDominos[arrayInt[i]].state = _playerState;
                gameDominos[arrayInt[i]].playerColorID = _playerState;
                gameDominos[arrayInt[i]].position.posX = 0;
                gameDominos[arrayInt[i]].position.posY = 0;
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
    
    float lastDominoXPos = -12.0f;
    float lastDominoYPos = -2.0f;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state != _player) continue;

        gameDominoes[i].position.posX = lastDominoXPos;
        lastDominoXPos += 2.0f;
        gameDominoes[i].position.posY = lastDominoYPos;
        if(lastDominoXPos >= 13.0f) 
        {
            lastDominoXPos = -12.0f;
            lastDominoYPos -= 2.5f;
        }
        gameDominoes[i].linkableDominoState = UNLINKABLE_DOMINO;
        gameDominoes[i].linkedDomino = NULL;
        gameDominoes[i].playerColorID = _player;
        gameDominoes[i].rotation = DOMINO_ROTATION_90;
        gameDominoes[i].scale = 0.4f;
    }

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, _player);
}

void rotatePlayerDomino()
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* selectedDomino = NULL;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
        } 
    }
    selectedDomino->rotation = (90 + selectedDomino->rotation) % 360;
    selectedDomino->scale = *s_getTableDominoesSize();
    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING);
}

//Move o domino selecionado do jogador 1 casa para determinada direcao
void movePlayerDomino()
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* selectedDomino = NULL;
    Domino* linkableDomino1 = NULL;
    Domino* linkableDomino2 = NULL;
    int linkableDominosIndex;

    if(!checkIfThereIsDominosOnTable()) return;
    
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
        } 
        else if(gameDominoes[i].linkableDominoState != UNLINKABLE_DOMINO)
        {
            if(!linkableDomino1) // linkableDomino1 == false -> linkableDomino1 não existe
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

    if(linkableDomino2)
    {    
        if(selectedDomino->linkedDomino == linkableDomino1)
            selectedDomino->linkedDomino = linkableDomino2;
        else
            selectedDomino->linkedDomino = linkableDomino1;        
    }
    else
        selectedDomino->linkedDomino = linkableDomino1;   
    

    printf("Pointerrr 1 anterior %p\n", (void*)linkableDomino1);
    printf("Pointerrr 2 anterior %p\n", (void*)linkableDomino2);
    moveSelectedDominoToLinkedSpace(selectedDomino);
    selectedDomino->scale = *s_getTableDominoesSize();

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING);
}

//Troca a selecao de domino do jogador para o proximo domino da sua mão
void changePlayerSelectedDomino(int _player)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* selectedDomino = NULL;
    bool foundSelectedDomino = FALSE;
    int playerSelectedDomino = -1;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT && playerSelectedDomino == -1; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
            selectedDomino->state = _player;
            foundSelectedDomino = TRUE;
        }
        else if(foundSelectedDomino)
        {
            if(gameDominoes[i].state == _player) 
                playerSelectedDomino = i;      
        }        
    }
    for(int j = 0; j < GAME_DOMINOES_AMOUNT && playerSelectedDomino == -1; j++)
    {
        if(gameDominoes[j].state == _player) playerSelectedDomino = j;
    }
    if(playerSelectedDomino != -1)
    {
        gameDominoes[playerSelectedDomino].state = STATE_GAME_MOVING;
        gameDominoes[playerSelectedDomino].rotation = DOMINO_ROTATION_0;
        gameDominoes[playerSelectedDomino].scale = *s_getTableDominoesSize();
        if(!checkIfThereIsDominosOnTable()) 
        {
            gameDominoes[playerSelectedDomino].position.posX = 0;
            gameDominoes[playerSelectedDomino].position.posY = 0;
        }
        else if(!foundSelectedDomino) //foundSelectedDomino == false
        {
            movePlayerDomino(_player);            
        }
        else
        {
            gameDominoes[playerSelectedDomino].position.posX = selectedDomino->position.posX;
            gameDominoes[playerSelectedDomino].position.posY = selectedDomino->position.posY;
            gameDominoes[playerSelectedDomino].rotation = selectedDomino->rotation;
        }
        hideDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, _player); //esconde o domino deselecionado
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING); //exibe o novo domino selecionado
    }
    else
    {
        printf("!ERRO! Nenhum domino encontrado na mão do jogador");
    }    
}

//Deseleciona o domino que o jogador estava movendo
void unselectPlayerDomino(int _player)
{
    Domino* gameDominoes = s_getGameDominoes();
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) gameDominoes[i].state = _player;
    }
}
//Tenta posicionar o domino na mesa e mudar automaticamente a peça selecionada pelo jogador
bool tryToSetSelectedDominoToTable()
{   
    Domino* selectedDomino = NULL;
    Domino* linkingDomino = NULL;
    Domino* leftDomino = NULL;
    Domino* rightDomino = NULL;
    Domino* upDomino = NULL;
    Domino* downDomino = NULL;
    Domino* gameDominoes = s_getGameDominoes();
    bool oneOrMoreDominosPlaced = checkIfThereIsDominosOnTable();
    bool canPlaceDomino = FALSE;
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
            break;
        }
    }

    canPlaceDomino = checkDominoPlacement(&linkingDomino);
    
    if(!selectedDomino)
    {
        printf("!ERRO!Nenhum domino selecionado!!!!\n");
        return false;
    }
    else if(oneOrMoreDominosPlaced && !canPlaceDomino)
    {
        printf("if 1\n");
        return FALSE;
    }
    else if(!oneOrMoreDominosPlaced)
    {
        selectedDomino->state = STATE_GAME_TABLE;
        selectedDomino->linkableDominoState = LINKABLE_DOMINO_LEFT_RIGHT;
        selectedDomino->position.posX = 0;
        selectedDomino->position.posY = 0;
        printf("if 2\n");

        selectedDomino->scale = *s_getTableDominoesSize();
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE);
        return TRUE;
    }
    else
    {
        findSurroundingDominoes(selectedDomino, &rightDomino, &downDomino, &leftDomino, &upDomino);
        selectedDomino->state = STATE_GAME_TABLE;
        selectedDomino->linkedDomino = linkingDomino;
        selectedDomino->scale = *s_getTableDominoesSize();
        if(linkingDomino->linkableDominoState == LINKABLE_DOMINO_LEFT_RIGHT)
        {            
            if(rightDomino)
                linkingDomino->linkableDominoState = LINKABLE_DOMINO_RIGHT;
            else if(leftDomino)
                linkingDomino->linkableDominoState = LINKABLE_DOMINO_LEFT;
        }
        else 
            linkingDomino->linkableDominoState = UNLINKABLE_DOMINO;
        
        if(rightDomino)
        {
            selectedDomino->linkableDominoState = LINKABLE_DOMINO_LEFT;
        }
        else if(leftDomino)
        {
            selectedDomino->linkableDominoState = LINKABLE_DOMINO_RIGHT;            
        }
        
        if(getTableDominoesAmount() > 7) setGameTableDominoesSize(0.3f);
        
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE);

        printf("if 3\n");
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