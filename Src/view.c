#include "view.h"
#include <stdio.h>

void menuInit() //inica menu
{
    printf("\n1- Play\n\n2- Quit");
}

char menuInput() //recebe input do menu e returna
{
    char playerInput;

    scanf("%c", &playerInput);
    return playerInput;
}

void screenDisplay() //mostra a tela durante o jogo
{
    for(int linIndx = 0; linIndx < 10; linIndx++)
    {
        for(int colIndx = 0; colIndx < 10; colIndx++)
        {
        }        
        printf("\n");
    }
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
*/