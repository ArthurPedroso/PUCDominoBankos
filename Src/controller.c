#include "controller.h"
#include "model.h"
#include "view.h"
#include "common.h"

//-----UI_STATES-----// 
#define UI_STATE_MAIN_MENU 0
//#define UI_STATE_ORGANIZE_DOMINOES 1 //old name
#define UI_STATE_SELECT_PLAYERS 1
#define UI_STATE_ASSING_STARTING_DOMINOES 2
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
    *s_getControllerState() = UI_STATE_MAIN_MENU;
    modelInitialization();
}


//----------UI controllers----------//
void manageMainMenuInput(uiInput _menuInput) //Menu principal
{
    switch(_menuInput)
    {
        case 1: //New Game
            displayPlayerSelectionMenu();
            *s_getControllerState() = UI_STATE_SELECT_PLAYERS;
            break;
        case 2: //Save Game
            break;
        case 3: //Load Game
            break;
        case 4: //Exit Game
            exitGame(); 
            break; 
    }
}

void playerNumberSelection(uiInput _menuInput)
{
    switch (_menuInput)
    {
        case 1:
            // *old getPlayersHands(getGameDominoes());

            //determina q so tem 1 jogador
            //Chamar funcao q inicia jogo contra AI
            break;
        case 2:
            displayStartDominosAssigmentMenu();
            *s_getControllerState() = UI_STATE_ASSING_STARTING_DOMINOES;
            //determina q tem 2 jogadores
            //Chamar funcao q inicia o jogo contra outro jogdor
            break;
        case 3:
            *s_getControllerState() = UI_STATE_MAIN_MENU;
            menuInit(); //Go back
            break;
    }
}

void manageStartDominosAssigmentMenuInput(uiInput _menuInput)
{
    switch (_menuInput)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            hideAllDominoes();
            break;
        case 6:
            *s_getControllerState() = UI_STATE_SELECT_PLAYERS;
            resetDominoesState();
            menuInit(); //Go back
            break;
        case 7:
            break;
    }
}

/* essa função não será mais utilizada
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
*/
//-----------UI controllers----------//

//----------Head Funcs----------//
void managePlayerChoice(uiInput _playerInput)
{
    switch (*s_getControllerState())
    {
        case UI_STATE_MAIN_MENU:
            manageMainMenuInput(_playerInput);
            break;
    
        case UI_STATE_SELECT_PLAYERS:
            playerNumberSelection(_playerInput);
            break;
        case UI_STATE_ASSING_STARTING_DOMINOES:
            manageStartDominosAssigmentMenuInput(_playerInput);
            break;
    }    
}
int startGame()
{
    controllerInitialization();
    return screenDisplay();
}