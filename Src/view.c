#include "view.h"
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
    printf("\n1- Place piece\n2- Buy piece\n3-Show screen\n4- Quit match");
}

char screenDisplayOptionsInput() //recebe input da opcao escolhida e o retona
{
    char playerInput;
    
    scanf("%c", &playerInput);
    return playerInput;
}