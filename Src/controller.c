#include "controller.h"
#include "model.h"

//----------Head Funcs----------//

void controllerInitialization()
{
    modelInitialization();
}

void managePlayerChoice(char _playerIput)
{

    if (_playerIput == OPTION_ONE)
    {
        organizeDominoes();
    }
    else if (_playerIput == OPTION_TWO)
    {

    }
}

void startGame()
{
    int exitCode = 1;

    controllerInitialization();
}