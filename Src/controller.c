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
            screenDisplay();
            screenDisplayOptions();
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