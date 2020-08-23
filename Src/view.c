#include "view.h"
#include "model.h"
#include "controller.h"
#include <stdio.h>


//-----------Head Funcs-----------//
void menuInit() //inica e printa menu
{
    //printf("\n1- Play\n\n2- Quit");
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
    printf("\n1- Show Organized Dominoes\n2- Shuffle Dominoes");
    screenDisplayOptionsInput();
}

void screenDisplayOptionsInput() //recebe input da opcao escolhida e o retona
{
    char playerInput = 0;

    scanf("%c", &playerInput);
    printf("\n %c ABACATAO", playerInput);
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