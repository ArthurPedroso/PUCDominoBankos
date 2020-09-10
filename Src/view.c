#include "view.h"
#include "model.h"
#include "controller.h"
#include "OpenGLFiles/OGLManager.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void clearTerminal()
{
#ifdef OS_Windows
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}
void changeOGLText(char* _newText)
{
    OGLTextData* textData;
    textData = s_getTextData();

    textData->textToDraw = _newText;
}
void OGLManagerUpdateCB(float _deltaTime, int _input)
{
    if(_input != INPUT_NO_KEY_PRESSED) 
    {
        managePlayerChoice(_input);
    }
}
void OGLManagerFirstFrameCB()
{
    menuInit();
}
//-----------Head Funcs-----------//

//-----UI_TEXT-----//
void menuInit() //inica e printa menu
{
    //O 104 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[104]; 

    strcpy(strBuffer, "Welcome! Let's play Domino!\n");
    strcat(strBuffer, "To get started, select an option:\n");
    strcat(strBuffer, "1- New Game\n");
    strcat(strBuffer, "2- Save\n");
    strcat(strBuffer, "3- Load\n");
    strcat(strBuffer, "4- Exit\n");

    changeOGLText(strBuffer);
}
/*
Old, only to organize dominoes
void screenDisplayOptions() //mostra as opcoes do jogador
{
    changeOGLText("\n1- Show Organized Dominoes\n2- Shuffle Dominoes\n3- Go Back");
}
*/
void displayPlayerSelectionMenu() //mostra a tela de seleção de jogadores
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[87]; 

    strcpy(strBuffer, "Quantos jogadores irão jogar?\n");
    strcat(strBuffer, "1- Jogar contra o AI\n");
    strcat(strBuffer, "2- Jogar com um amigo\n");
    strcat(strBuffer, "3- Voltar\n");

    changeOGLText(strBuffer);
}

void displayStartDominosAssigmentMenu()
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[270]; 

    strcpy(strBuffer, "Distribuir dominós iniciais entre os jogadores:\n");
    strcat(strBuffer, "1- Iniciar jogo\n");
    strcat(strBuffer, "2- Distribuir para jogador 1\n");
    strcat(strBuffer, "3- Distribuir para jogador 2\n");
    strcat(strBuffer, "4- Visualizar dominós atribuidos para jogador 1\n");
    strcat(strBuffer, "5- Visualizar dominós atribuidos para jogador 2\n");
    strcat(strBuffer, "6- Ocultar dominós\n");
    strcat(strBuffer, "7- Voltar\n");

    changeOGLText(strBuffer);
}
//-----UI_TEXT-----//

int screenDisplay() //Ativa o OpenGL e retorna qualquer codigo de erro
{
    return startRender(OGLManagerUpdateCB, OGLManagerFirstFrameCB);
}

void printDominoes(Domino* _dominoArray, int _arraySize)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();

    for(int i = 0; i < _arraySize; i++)
    {
        Domino currentDomino = _dominoArray[i];
        DominoGObject oglDomino;
        int dominoGObjectIndex = getDominoindexByType(currentDomino.leftType, currentDomino.rightType);

        oglDomino = oglDominos[dominoGObjectIndex]; //seleciona um dominó do opengl análogo ao domino do jogo

        oglDomino.visible = TRUE;
        setGObjectPosition(&oglDomino.left, (currentDomino.posX -0.25f) * 0.2f,(currentDomino.posY * 0.2f), -1.0f);
        setGObjectPosition(&oglDomino.right, (currentDomino.posX +0.25f) * 0.2f, (currentDomino.posY  * 0.2f), -1.0f); 

        oglDominos[dominoGObjectIndex] = oglDomino;
    }  
}

void printDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();

    for(int i = 0; i < _arraySize; i++)
    {
        if(_dominoArray[i].state != _stateFilter) continue;

        Domino currentDomino = _dominoArray[i];
        DominoGObject oglDomino;
        int dominoGObjectIndex = getDominoindexByType(currentDomino.leftType, currentDomino.rightType);

        oglDomino = oglDominos[dominoGObjectIndex]; //seleciona um dominó do opengl análogo ao domino do jogo

        oglDomino.visible = TRUE;        
        setDominoGOScale(&oglDomino, 0.4f, 0.4f, 0.4f);
        setDominoGOLocalPosition(&oglDomino, currentDomino.posX, currentDomino.posY, -1.0f);
        //setDominoGOPosition(&oglDomino, currentDomino.posX, currentDomino.posY, -1.0f);

        oglDominos[dominoGObjectIndex] = oglDomino;
    }  

}

void hideAllDominoes()
{
    DominoGObject* oglDominos = s_getDominoesGObjects();
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        oglDominos[i].visible = false;
    }
}

void exitGame()
{    
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("Thank you for playing!\n");
    printf("\n");
    printf("Game made by:\n\nArthur Naves Pedroso\nCaio Henrique Portella\nLuiz Eduardo Ramirez\nMauricio Macedo Villarnobo\n\n");
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    *s_shouldExitGame() = true;
}

void invalidOption()
{
    printf("Invalid selection!\n");
}

/*
Printa os dominos em uma piramide

void printDominoes(Domino* _dominoArray, int _arraySize)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();

    int columCount= 0;
    int lineCount = 0;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        Domino currentDomino = _dominoArray[i];
        DominoGObject oglDomino;
        int dominoGObjectIndex = getDominoindexByType(currentDomino.leftType, currentDomino.rightType);

        oglDomino = oglDominos[dominoGObjectIndex];

        oglDomino.visible = TRUE;
        setGObjectPosition(&oglDomino.left, (columCount-0.25f) * 0.2f + (columCount * 0.05f - 0.8f),((-lineCount) * 0.2f) + 0.8f, -1.0f);
        setGObjectPosition(&oglDomino.right, (columCount+0.25f) * 0.2f + (columCount * 0.05f - 0.8f), ((-lineCount) * 0.2f) + 0.8f, -1.0f); 

        oglDominos[dominoGObjectIndex] = oglDomino;

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
*/