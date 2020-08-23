#include "controller.h"
#include "model.h"

//----------Head Funcs----------//

void controllerInitialization()
{
    modelInitialization();
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