#include "controller.h"
#include "model.h"
#include "view.h"
#include "common.h"

//-----UI_STATES-----// 
#define UI_STATE_MAIN_MENU 0
#define UI_STATE_ORGANIZE_DOMINOES 1
//-----UI_STATES-----// 

typedef int controllerState;

controllerState* s_getControllerState()
{
    static controllerState s_controllerState = 0;

    return &s_controllerState;
}

//Executado apenas uma vez no incio do jogo
void controllerInitialization()
{
    modelInitialization();
}


//UI controllers
void manageMenuInput(uiInput _menuInput)
{
    switch(_menuInput)
    {
        case 1: //New Game
            screenDisplayOptions();
            *s_getControllerState() = UI_STATE_ORGANIZE_DOMINOES;
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
void playerNumberSelection(uiInput _menuOP)
{
    switch (_menuOP)
    {
        case 1:
            //getPlayersHands(getGameDominoes());

            //determinar q so tem 1 jogador
            //Chamar funcao q inicia jogo contra AI
            break;
        case 2: //Save Game
            //determinar q tem 2 jogadores
            //Chamar funcao q inicia o jogo contra outro jogdor
            break;
        case 3:
            exitGame();
            break;
    }
}
//-----INCOMING-----//

void manageOrganizeDominosInput(uiInput _organizeDominosInput)
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
        *s_getControllerState() = UI_STATE_MAIN_MENU;
        break;
    }
}
//UI controllers

//----------Head Funcs----------//
void managePlayerChoice(uiInput _playerIput)
{
    switch (*s_getControllerState())
    {
        case UI_STATE_MAIN_MENU:
            manageMenuInput(_playerIput);
            break;
    
        case UI_STATE_ORGANIZE_DOMINOES:
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