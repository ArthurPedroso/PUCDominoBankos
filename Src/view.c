#include "view.h"
#include "model.h"
#include "controller.h"
#include "OpenGLFiles/OGLManager.h"
#include <stdio.h>
#include <stdlib.h>


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
    textData = getTextData();

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
    menuInit(0);
}
//-----------Head Funcs-----------//
void menuInit(int _displayInvalidOption) //inica e printa menu
{
    //changeOGLText("Welcome! Let's play Domino!\nTo get started, select an option:\n1- New Game\n2- Save\n3- Load\n4- Exit\n");
    changeOGLText("Welcome! Let's play Domino!\nTo get started, select an option:\n1- Organize Dominoes\n2- Exit\n");

}

void screenDisplay() //mostra a tela de jogo (OpenGL)
{
    startRender(OGLManagerUpdateCB, OGLManagerFirstFrameCB);
}

void screenDisplayOptions() //mostra as opcoes do jogador
{
    changeOGLText("\n1- Show Organized Dominoes\n2- Shuffle Dominoes\n3- Go Back");
}

void printDominoes(Domino* _dominoArray, int _arraySize)
{
    DominoGObject* oglDominos = getDominoesGObjects();

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
        
        //oglDomino.left

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
    //screenDisplayOptions();
}

void exitGame()
{    
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("Thank you for playing!\n");
    printf("Game made by:\nArthur Naves Pedroso\nCaio Henrique Portella\nLuiz Eduardo Ramirez\nMauricio Macedo Villarnobo\n");
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    *shouldExitGame() = true;
}

void invalidOption()
{
    printf("Invalid selection!\n");
}