#include "view.h"
#include "model.h"
#include "controller.h"
#include "common.h"
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
//-----------Head Funcs-----------//
void menuInit(int _displayInvalidOption) //inica e printa menu
{
    clearTerminal();
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("\n");
    printf("Welcome! Let's play Domino!\n");
    printf("To get started, select an option:\n");
    printf("\n");
    printf("1- New Game\n2- Save\n3- Load\n4- Exit\n");
    printf("\n");
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("\n");
    if(_displayInvalidOption) invalidOption();
    printf("Chosen option: ");

    menuPlayerSelection(menuInput());
}

void screenDisplay() //mostra a tela de jogo (OpenGL)
{
}

void screenDisplayOptions() //mostra as opcoes do jogador
{
    //printf("\n1- Place piece\n2- Buy piece\n3-Show screen\n4- Quit match");
    printf("\n1- Show Organized Dominoes\n2- Shuffle Dominoes\n");
    screenDisplayOptionsInput();
}

void printDominoes(Domino* _arrayDeDomino, int _arraySize)
{
    clearTerminal();

    int columCount = 0;
    int lineCount = 0;
    char leftChar = 0;
    char rightChar = 0;
    for(int i = 0; i < _arraySize; i++)
    {
        leftChar = _arrayDeDomino[i].leftType + 48;
        rightChar = _arrayDeDomino[i].rightType + 48;

        printf("%c%c ", leftChar, rightChar);

        if(columCount >= 6 - lineCount)
        {
            columCount = 0;
            lineCount++;
            printf("\n");
        }
        else
        {
            columCount++;
        }
    }

    screenDisplayOptions();
}

void exitGameText()
{
    clearTerminal();
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("Thank you for playing!\n");
    printf("\n");
    printf("Game made by:\n\nArthur Naves Pedroso\nCaio Henrique Portella\nLuiz Eduardo Ramirez\nMauricio Macedo Villarnobo\n\n");
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=\n");
}

void invalidOption()
{
    printf("Invalid selection!\n");
}