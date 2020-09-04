#include "controller.h"
#include "model.h"
#include "view.h"
#include "common.h"

#define STATE_MAIN_MENU 0
#define STATE_ORGANIZE_DOMINOES 1

typedef int controllerState;

controllerState* getControllerState()
{
    static controllerState s_controllerState = 0;

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
            screenDisplayOptions();
            *getControllerState() = STATE_ORGANIZE_DOMINOES;
            //old: displayPlayerSelection();
            break;
        case 2: //Save Game
            exitGame(); 
            break;
        case 3: //Load Game
            break;
        case 4: //Exit Game
            //exitGame(); 
            break; 
    }
}

//-----INCOMING-----//
void playerNumberSelection(int _menuOP)
{
    if(_menuOP == 1)
    {
        getPlayersHands(getGameDominoes());

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
//-----INCOMING-----//

void manageOrganizeDominosInput(int _organizeDominosInput)
{
    switch (_organizeDominosInput)
    {
    case 1:
        organizeDominoes();
        break;
    case 2:
        shuffleDominoesAndDisplay();
        break;    
    case 3:
        menuInit(0);
        *getControllerState() = STATE_MAIN_MENU;
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
    controllerInitialization();
    screenDisplay(); //old MENUINIT
    return 0;
}