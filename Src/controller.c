#include "controller.h"
#include "model.h"
#include "view.h"
#include "common.h"
#include <stdio.h>

//-----UI_STATES-----// 
#define UI_STATE_MAIN_MENU 0
//#define UI_STATE_ORGANIZE_DOMINOES 1 //old name
#define UI_STATE_SELECT_PLAYERS 1
#define UI_STATE_ASSING_STARTING_DOMINOES 2
//-----UI_STATES-----// 

//-----StartDominosAssigmentMenuStates-----//
#define ASSIGMENT_MENU_INITIAL          0b0000000000000000
#define ASSIGMENT_MENU_PLAYER1_ASSIGNED 0b0000000000000010
#define ASSIGMENT_MENU_PLAYER2_ASSIGNED 0b0000000000000100
#define ASSIGMENT_MENU_PLAYER1_DISPLAY  0b0000000000001000
#define ASSIGMENT_MENU_PLAYER2_DISPLAY  0b0000000000010000

//-----StartDominosAssigmentMenuStates-----//

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
    static int assigmentMenuState = ASSIGMENT_MENU_INITIAL;
    switch (_menuInput)
    {
        case 1:
            break;
        case 2:
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_ASSIGNED) == 0)
            {
                assigmentMenuState += ASSIGMENT_MENU_PLAYER1_ASSIGNED;

                assignPlayer1StartingHand();
            }
            break;
        case 3:
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_ASSIGNED) == 0)
            {
                assigmentMenuState += ASSIGMENT_MENU_PLAYER2_ASSIGNED;

                assignPlayer2StartingHand();
            }
            break;
        case 4:
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) == 0)
            {
                printf("dentro do case 4");
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER2_DISPLAY;
                assigmentMenuState += ASSIGMENT_MENU_PLAYER1_DISPLAY;

                hideAllDominoes();
                displayPlayer1Hand();
            }
            break;
        case 5:
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_DISPLAY) == 0)
            {
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER1_DISPLAY;
                assigmentMenuState += ASSIGMENT_MENU_PLAYER2_DISPLAY;

                hideAllDominoes();
                displayPlayer2Hand();                
            }
            break;
        case 6:
            if((int)(assigmentMenuState & (ASSIGMENT_MENU_PLAYER2_DISPLAY + ASSIGMENT_MENU_PLAYER1_DISPLAY)) != 0)
            {
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER2_DISPLAY;
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER1_DISPLAY;
                hideAllDominoes();
            }
            break;
        case 7:
            *s_getControllerState() = UI_STATE_SELECT_PLAYERS;
            assigmentMenuState = ASSIGMENT_MENU_INITIAL;
            resetDominoesState();
            hideAllDominoes();
            displayPlayerSelectionMenu(); //Go back
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