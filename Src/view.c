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

int menuInput() //recebe input do menu e returna
{
    int playerInput;

    scanf("%d", &playerInput);
    return playerInput;
}


void screenDisplayOptionsInput() //recebe input da opcao escolhida e o retona
{
    int playerInput = 0;

    scanf("%d", &playerInput);

    managePlayerChoice(playerInput);
}

void OGLManagerUpdateCB(float _deltaTime, int _input)
{
    if(_input != INPUT_NO_KEY_PRESSED) 
    {
        managePlayerChoice(_input);
    }
}
//-----------Head Funcs-----------//
void menuInit(int _displayInvalidOption) //inica e printa menu
{
    screenDisplay();
    return;
    clearTerminal();
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("\n");
    printf("Welcome! Let's play Domino!");
    printf("To get started, select an option:\n");
    printf("1- New Game\n2- Save\n3- Load\n4- Exit\n");
    printf("\n");
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("\n");
    if(_displayInvalidOption) invalidOption();
    printf("Chosen option: ");

    managePlayerChoice(menuInput());
}

void screenDisplay() //mostra a tela de jogo (OpenGL)
{
    startRender(OGLManagerUpdateCB);
}

void screenDisplayOptions() //mostra as opcoes do jogador
{
    //printf("\n1- Place piece\n2- Buy piece\n3-Show screen\n4- Quit match");
    printf("\n1- Show Organized Dominoes\n2- Shuffle Dominoes\n");
    screenDisplayOptionsInput();
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
        setGObjectPosition(&oglDomino.left, (columCount-0.25f) * 0.2f + (columCount * 0.05f - 0.8f),((-lineCount) * 0.2f) + 0.8f, 0.0f);
        setGObjectPosition(&oglDomino.right, (columCount+0.25f) * 0.2f + (columCount * 0.05f - 0.8f), ((-lineCount) * 0.2f) + 0.8f, 0.0f); 
        
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