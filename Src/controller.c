#include "controller.h"
#include "model.h"
#include "view.h"
#include "common.h"

#define STATE_MAIN_MENU 0
#define STATE_ORGANIZE_DOMINOES 1

typedef int controllerState;

controllerState* getControllerState()
{
    static controllerState s_controllerState = 1;

    return &s_controllerState;
}

//Executado apenas uma vez no incio do jogo
void controllerInitialization()
{
    modelInitialization();
}


void manageMenuInput(int _menuInput)
{
    switch(_menuInput)
    {
        case 1: //New Game
            //screenDisplay();
            //screenDisplayOptions(); 
            //managePlayerChoice(1);
            break;
        case 2: //Save Game
            menuInit(FALSE);
            break;
        case 3: //Load Game
            menuInit(FALSE);
            break;
        case 4: //Exit Game
            exitGame(); 
            break; 
        default:
            menuInit(TRUE);
            break;
    }
}


void manageOrganizeDominosInput(int _organizeDominosInput)
{
    switch (_organizeDominosInput)
    {
    case OPTION_ONE:
        organizeDominoes();
        break;
    case OPTION_TWO:
        shuffleDominoesAndDisplay();
        break;    
    default:
        exitGame();
        break;
    }
}
//----------Head Funcs----------//


/*
*/

void managePlayerChoice(int _playerIput)
{
    switch (*getControllerState())
    {
        case STATE_MAIN_MENU:
            manageMenuInput(_playerIput);
            break;
    
        case STATE_ORGANIZE_DOMINOES:
            manageOrganizeDominosInput(_playerIput);
            break;
    }    
}

int startGame()
{
    //Usado para passar erros de execução do programa
    int exitCode = 0;
    controllerInitialization();
    menuInit(FALSE); 
    return 0;
}