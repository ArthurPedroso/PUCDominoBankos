#include "controller.h"
#include "model.h"
#include "view.h"
#include "common.h"

//Executado apenas uma vez no incio do jogo
void controllerInitialization()
{
    modelInitialization();
}

//----------Head Funcs----------//



void menuPlayerSelection(int _menuOp)
{
    switch(_menuOp)
    {
        case 1: //New Game
            displayPlayerSelection();
            //screenDisplay();
            //screenDisplayOptions();
            break;
        case 2: //Save Game
            menuInit(FALSE);
            break;
        case 3: //Load Game
            menuInit(FALSE);
            break;
        case 4: //Exit Game
            exitGameText(); 
            break; //Jogo não fecha (loop printDominoes());
        default:
            menuInit(TRUE);
            break;
    }
}

void playerNumberSelection(int _menuOP)
{
    if(_menuOP == 1)
    {
        //determinar q so tem 1 jogador
        //Chamar funcao q inicia jogo contra AI
    }
    else if (_menuOP == 2)
    {
        //determinar q tem 2 jogadores
        //Chamar funcao q inicia o jogo contra outro jogdor
    }
    else
    {
        exitGameText();
    }
}

void managePlayerChoice(int _playerIput)
{

    if (_playerIput == OPTION_ONE)
    {
        organizeDominoes();
    }
    else if (_playerIput == OPTION_TWO)
    {
        shuffleDominoesAndDisplay();
    }   
    else
    {
        exitGameText();
    }
    
}

int startGame()
{
    controllerInitialization();
    menuInit(FALSE);
    return 0;
}