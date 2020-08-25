#include "view.h"
#include "model.h"
#include "controller.h"
#include <stdio.h>


//-----------Head Funcs-----------//
void menuInit() //inica e printa menu
{
    int option;

    printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("\n");
    printf("Welcome! Let's play Domino!");
    printf("To get started, select an option:\n");
    printf("1- New Game\n2- Save\n3- Load\n4- Exit");
    printf("\n");
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("\n");
    printf("Chosen option: ");

    scanf("%d", option);
    menuPlayerSelection(option);
}

char menuInput() //recebe input do menu e returna
{
    char playerInput;

    scanf("%c", &playerInput);
    return playerInput;
}

void screenDisplay() //mostra a tela de jogo
{
}

void screenDisplayOptions() //mostra as opcoes do jogador
{
    //printf("\n1- Place piece\n2- Buy piece\n3-Show screen\n4- Quit match");
    printf("\n1- Show Organized Dominoes\n2- Shuffle Dominoes\n");
    screenDisplayOptionsInput();
}

void screenDisplayOptionsInput() //recebe input da opcao escolhida e o retona
{
    int playerInput = 0;

    scanf("%d", &playerInput);

    managePlayerChoice(playerInput);
}

void printDominoes(Domino* _arrayDeDomino, int _arraySize)
{
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
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=");
    printf("Thank you for playing!");
    printf("Game made by: Arthur Naves Pedroso\nCaio Henrique Portella\nLuiz Eduardo Ramirez\nMauricio Macedo Villarnobo");
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=");
}

void invalidOption()
{
    printf("Invalid selection\n");
}