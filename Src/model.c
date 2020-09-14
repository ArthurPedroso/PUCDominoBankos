#include "model.h"
#include "view.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//Armazena os dados dos dominós do jogo 
Domino* s_getGameDominoes()
{
    static Domino array[GAME_DOMINOES_AMOUNT];

    return array;
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
        _dominoArray[i].posX = 0;
        _dominoArray[i].posY = 0;
        _dominoArray[i].rotation = DOMINO_UP;
        _dominoArray[i].rightType = columCount + lineCount;
        _dominoArray[i].leftType = lineCount;
        _dominoArray[i].scale = 1.0f;
        
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

//---------Header Funcs----------//

//Inicia o sistema de numeros aleatorios e Aloca a memoria utilizada pelo array de dominos
void modelInitialization()
{
    srand(time(NULL));
    initializeDominoArray(s_getGameDominoes());
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
//Atribui 7 dominos aleatorios para o jogador 1
void assignPlayer1StartingHand() 
{
    Domino* gameDominos = s_getGameDominoes();
    int random = 0;

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;

        while(gameDominos[random].state != STATE_DOMINOES_PILE) //Reescrever, pode travar o programa se o random não bater com um domino sem dono
        {
            random = rand() % 28;
        }

        gameDominos[random].state = STATE_PLAYER_ONE;
    } 

    printf("Atribuida mao do jogador 1");
}
//Atribui 7 dominos aleatorios para o jogador 2
void assignPlayer2StartingHand() //Atribui 7 dominos para o jogador 2
{
    Domino* gameDominos = s_getGameDominoes();
    int random = 0;
    

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;
        
        while(gameDominos[random].state != STATE_DOMINOES_PILE) //Reescrever, pode travar o programa se o random não bater com um domino sem dono
        {
            random = rand() % 28;
        }

        gameDominos[random].state = STATE_PLAYER_TWO;
    }
    
    printf("Atribuida mao do jogador 1");
} 



//Pega aleatoriamento um domiono da pilha de dominos e atribui ele ao jogador indicado pela variavel "_playerState"
void pickDominoeFromPile(int _playerState)
{
    int random = 0;

    Domino* gameDominoes = s_getGameDominoes();

    for(int i = 0; i < HAND_DOMINOES_STARTING_AMOUNT; i++)
    {
        random = rand() % 28;
        
        while(gameDominoes[random].state != STATE_DOMINOES_PILE)
        {
            random = rand() % 28;
        }

        gameDominoes[random].state = _playerState;
    }
}

void displayPlayer1Hand()
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino domino;
    
    int lastDominoXPos = -8;
    int lastDominoYPos = -2;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        domino = gameDominoes[i];
        if(domino.state != STATE_PLAYER_ONE) continue;

        domino.posX = lastDominoXPos;
        lastDominoXPos += 3;
        domino.posY = lastDominoYPos;
        gameDominoes[i] = domino;
    }

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_PLAYER_ONE);
}

//Posiciona os dominos na área de "mão do jogador" na tela do opengl e pede para ele renderizar esse dominos
void displayPlayer2Hand()
{    
    Domino* gameDominoes = s_getGameDominoes();
    Domino domino;
    
    int lastDominoXPos = -8;
    int lastDominoYPos = -2;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        domino = gameDominoes[i];
        if(domino.state != STATE_PLAYER_TWO) continue;

        domino.posX = lastDominoXPos;
        lastDominoXPos += 3;
        domino.posY = lastDominoYPos;
        gameDominoes[i] = domino;
    }

    printDominoesBasedOnState(gameDominoes, GAME_DOMINOES_AMOUNT, STATE_PLAYER_TWO);
}

//Move o domino selecionado do jogador 1, 1 casa para determinada direcao
void movePlayer1Domino(int _moveDirection)
{
    Domino* gameDominoes = s_getGameDominoes();
    Domino* selectedDomino;
    bool foundSelectedDomino = FALSE;
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        if(gameDominoes[i].state == STATE_GAME_MOVING) 
        {
            selectedDomino = &gameDominoes[i];
            foundSelectedDomino = TRUE;
        } 
    }
    if(!foundSelectedDomino) 
    {
        printf("!ERRO! - Nenhum domino no estado de movimento encontrado!");
        return;
    }

    switch (_moveDirection)
    {
        case DOMINO_UP:
            selectedDomino->posY += 1;
            break;
        case DOMINO_DOWN:
            selectedDomino->posY -= 1;
            break;
        case DOMINO_LEFT:
            selectedDomino->posX -= 1;
            break;
        case DOMINO_RIGHT:
            selectedDomino->posX += 1;
            break;
    }

    
}

//Troca a selecao de domino do jogador 1 para o proximo domino da sua mão
void changePlayer1SelectedDomino()
{

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