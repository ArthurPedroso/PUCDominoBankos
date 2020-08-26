#include "controller.h"
#include "model.h"
#include "view.h"

//----------Head Funcs----------//

void controllerInitialization()
{
    modelInitialization();
}

void menuPlayerSelection(int _menuOp)
{
    switch(_menuOp)
    {
        case 1: //New Game
            screenDisplay(); break;
            screenDisplayOptions(); break;
        case 2: //Save Game

        case 3: //Load Game

        case 4: //Exit Game
            exitGameText(); break;
        default:
            invalidOption(); break;
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
    
}

void startGame()
{
    int exitCode = 1;

    controllerInitialization();
}