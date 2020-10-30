#include "model.h"
#include "view.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

#ifdef OS_Windows
#include <winbase.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define _MAX_DIR FILENAME_MAX
#endif

#ifdef OS_Windows
#define SAVE_DIR "\\saves"
#define SAVE_FILE "\\save.bin"
#else
#define SAVE_DIR "/saves"
#define SAVE_FILE "/save.bin"
#endif

struct Vec2_TAG Vec2ZERO = {0.0f, 0.0f};

#ifdef OS_Windows
void createSaveDir(char* _path)
{
    CreateDirectory(_path, NULL); 
}
#else
void createSaveDir(char* _path)
{
    mkdir(_path, 0777);
}
#endif

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
//Armazena o offset de posicao de todos os dominos
Vec2* s_getTableDominoesOffsetPosition()
{
    static Vec2 tableDominoesSize;

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

void findLinkableDominoes(Domino** _outLeftLinkableDomino,  Domino** _outRightLinkableDomino)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* linkableDomino1 = NULL;
    Domino* linkableDomino2 = NULL;

    if(!checkIfThereIsDominosOnTable()) return;
    
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].linkableDominoState != UNLINKABLE_DOMINO)
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

    if(!linkableDomino2)
    {
        *_outLeftLinkableDomino = linkableDomino1;
        *_outRightLinkableDomino = linkableDomino1;
    }
    else
    {
        if(linkableDomino1->linkableDominoState == LINKABLE_DOMINO_RIGHT)
        {
            *_outLeftLinkableDomino = linkableDomino2;
            *_outRightLinkableDomino = linkableDomino1;
        }
        else
        {
            *_outLeftLinkableDomino = linkableDomino1;
            *_outRightLinkableDomino = linkableDomino2;
        }
    }
}

bool setAiDomino(Domino* _candidate, Domino* _tableDomino, int dominosLinkType)
{
    
}

bool tryToPlaceAiDomino()
{
    Domino* gameDominos = s_getGameDominoes();
    Domino* placementCandidate = NULL;
    Domino* linkableLeft = NULL;
    Domino* linkableRight = NULL;
    int linkableLeftType;
    int linkableRightType;

    findLinkableDominoes(&linkableLeft, &linkableRight);

    if(linkableLeft->rotation == DOMINO_ROTATION_180)
        linkableLeftType = linkableLeft->rightType;
    else
        linkableLeftType = linkableLeft->leftType;

    if(linkableRight->rotation == DOMINO_ROTATION_180)
        linkableRightType = linkableRight->leftType;
    else
        linkableRightType = linkableRight->rightType;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominos[i].state == STATE_PLAYER_TWO)
        {
            if(linkableLeftType == gameDominos[i].leftType || linkableLeftType == gameDominos[i].rightType)
            {
                placementCandidate = &gameDominos[i];
                placementCandidate->linkedDomino = linkableLeft;
                placementCandidate->position.posX = linkableLeft->position.posX - 2;
                placementCandidate->linkableDominoState = LINKABLE_DOMINO_LEFT;
                
                if(linkableLeft->linkableDominoState == LINKABLE_DOMINO_LEFT_RIGHT)
                    linkableLeft->linkableDominoState = LINKABLE_DOMINO_RIGHT;
                else
                    linkableLeft->linkableDominoState = UNLINKABLE_DOMINO;

                if(linkableLeftType == placementCandidate->leftType)
                    placementCandidate->rotation = DOMINO_ROTATION_180;
                break;
            }
            else if(linkableRightType == gameDominos[i].leftType || linkableRightType == gameDominos[i].rightType)
            {
                placementCandidate = &gameDominos[i];
                placementCandidate->linkedDomino = linkableRight;
                placementCandidate->position.posX = linkableRight->position.posX + 2;
                placementCandidate->linkableDominoState = LINKABLE_DOMINO_RIGHT;

                if(linkableRight->linkableDominoState == LINKABLE_DOMINO_LEFT_RIGHT)
                    linkableRight->linkableDominoState = LINKABLE_DOMINO_LEFT;
                else
                    linkableRight->linkableDominoState = UNLINKABLE_DOMINO;
                
                if(linkableRightType == placementCandidate->rightType)
                    placementCandidate->rotation = DOMINO_ROTATION_180;
                break;
            }
        }
    }
    if(placementCandidate)
    {
        placementCandidate->state = STATE_GAME_TABLE;
        placementCandidate->scale = *s_getTableDominoesSize();
        return TRUE;
    }
    return FALSE;
}
//---------Header Funcs----------//[
char* currentRunningDirName()
{
    static char buffer[FILENAME_MAX];
#ifdef OS_Windows
    GetCurrentDirectory( FILENAME_MAX,  buffer);
#else
    getcwd(buffer, FILENAME_MAX);
#endif
    return buffer;
}
char* checkSaveDirAndReturnPath(char* _runningDirPath)
{
    static char dirFullPath[_MAX_DIR];
    bool dirExist = false;
    
    strcpy(dirFullPath, _runningDirPath); //    A://PAsta1/Pasta3/BuildOutput + saves = A://PAsta1/Pasta3/BuildOutput/saves
    strcat(dirFullPath, SAVE_DIR);
    
    DIR* dir = opendir(dirFullPath);
    
    if (dir) 
    {
        /* Directory exists. */
        closedir(dir);
    } 
    else if (ENOENT == errno) 
    {
        createSaveDir(dirFullPath);
    }
    else 
    {
        printf("!ERRO!Pasta save nao abriu com sucesso");
    }

    return dirFullPath;
}

//le os dados dos dominos e retorna o estado do controlador 
int readGameSave()
{
    Domino* gameDominoes = s_getGameDominoes();
    int controllerStateOut = -1;
    char filePath[_MAX_DIR];     
    
     
    strcpy(filePath, checkSaveDirAndReturnPath(currentRunningDirName())); //    A://PAsta1/Pasta3/BuildOutput/saves + save.bin = A://PAsta1/Pasta3/BuildOutput/saves/save.bin
    strcat(filePath, SAVE_FILE);

    FILE* readingFile;

    readingFile = fopen(filePath, "rb");

    if(readingFile)
    {

        for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
        {
            fread(&gameDominoes[i],sizeof(Domino),1,readingFile);
        }
        fread(&controllerStateOut,sizeof(controllerStateOut),1,readingFile);


        fclose(readingFile);
    }

    return controllerStateOut;
}
void writeGameSave(int _controllerStateIn)
{
    Domino* gameDominoes = s_getGameDominoes();
    char filePath[_MAX_DIR];     
    
     
    strcpy(filePath, checkSaveDirAndReturnPath(currentRunningDirName())); //    A://PAsta1/Pasta3/BuildOutput/saves + save.bin = A://PAsta1/Pasta3/BuildOutput/saves/save.bin
    strcat(filePath, SAVE_FILE);

    FILE* writingFile;

    writingFile = fopen(filePath, "wb");

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        fwrite(&gameDominoes[i],sizeof(Domino),1,writingFile);
    }
    fwrite(&_controllerStateIn,sizeof(_controllerStateIn),1,writingFile);

    fclose(writingFile);
}




//Inicia o sistema de numeros aleatorios e Aloca a memoria utilizada pelo array de dominos
void modelInitialization()
{
    srand(time(NULL));
    initializeDominoArray(s_getGameDominoes());
    s_getTableDominoesOffsetPosition()->posX = 0.0f;
    s_getTableDominoesOffsetPosition()->posY = 0.0f;
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

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, _player, Vec2ZERO);
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
    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING, *s_getTableDominoesOffsetPosition());
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

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING, *s_getTableDominoesOffsetPosition());
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
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING, *s_getTableDominoesOffsetPosition()); //exibe o novo domino selecionado
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
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE, *s_getTableDominoesOffsetPosition());
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
        
        //if(getTableDominoesAmount() > 7) setGameTableDominoesSize(0.3f);
        
        printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE, *s_getTableDominoesOffsetPosition());

        printf("if 3\n");
        return TRUE;
    }
    return FALSE;
}
bool checkIfPlayerWon(int _player)
{
    Domino* gameDominos = s_getGameDominoes();
    bool playerWon = TRUE;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominos[i].state == _player) playerWon = FALSE;
    }
    return playerWon;
}
void moveAllDominoes(int _direction)
{
    Domino* gameDominoes = s_getGameDominoes();

    s_getTableDominoesOffsetPosition()->posX += (getDeltaTime() * 6.0f) * _direction;
    s_getTableDominoesOffsetPosition()->posY = 0;
        
    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE, *s_getTableDominoesOffsetPosition());
    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING, *s_getTableDominoesOffsetPosition()); 

}
//Executa o turno da AI e retorna true se ela quiser empate
bool playAiTurn()
{
    int dominoesInDominoPile = checkDominoesPile(s_getGameDominoes());
    bool dominoPlaced = FALSE;
    
    dominoPlaced = tryToPlaceAiDomino();
    while (!dominoPlaced && dominoesInDominoPile)
    {
        printf("AI comprou domino!");
        pickDominoeFromPile(STATE_PLAYER_TWO);
        dominoesInDominoPile = checkDominoesPile(s_getGameDominoes());
        dominoPlaced = tryToPlaceAiDomino();
    }
    if(checkDominoesPile(s_getGameDominoes()) <= 0 && !dominoPlaced)
    {
        printf("Acabaram os dominos da pilha");
        return TRUE;
    }
    else
    {        
        hideAllDominoes();
        printDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE, *s_getTableDominoesOffsetPosition());
        return FALSE;
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