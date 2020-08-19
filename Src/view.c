#include "view.h"
#include <stdio.h>

void printBoard()
{
    printf("\n");

    char boardChars[84][280];

    for(int linIndx = 0; linIndx < 84; linIndx++)
    {
        for(int colIndx = 0; colIndx < 280; colIndx++)
        {
            if(linIndx % 4 == 0) 
                boardChars[linIndx][colIndx] = '+';
            else 
                boardChars[linIndx][colIndx] = ' ';
            printf("%c",boardChars[linIndx][colIndx]);
        }
        
        printf("\n");        
    }
}

//-----------Head Funcs-----------//
void menuInit() //inica menu
{
    //printf("\n1- Play\n\n2- Quit");
    printBoard();
}

char menuInput() //recebe input do menu e returna
{
    char playerInput;

    scanf("%c", &playerInput);
    return playerInput;
}

void screenDisplay() //mostra a tela durante o jogo
{
}

void screenDisplayOptions() //mostra as opcoes do jogador
{
    printf("\n1- Place piece\n2- Buy piece\n3-Show screen\n4- Quit match");
}

char screenDisplayOptionsInput() //recebe input da opcao escolhida e o retona
{
    char playerInput;
    
    scanf("%c", &playerInput);
    return playerInput;
}

/*
for(int linIndx = 0; linIndx < 10; linIndx++)
    {
        for(int colIndx = 0; colIndx < 10; colIndx++)
        {
        }        
        printf("\n");
    }



    printf("+―――+―――+\n");
    printf("|:: |:::|\n");
    printf("+―――+―――+\n");
*/