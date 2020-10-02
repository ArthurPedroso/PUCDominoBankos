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
#define UI_STATE_MAIN_GAME_PLAYER1_TURN 3
#define UI_STATE_MAIN_GAME_PLAYER2_TURN 4
#define UI_STATE_PLACE_DOMINO_PLAYER1_TURN 5
#define UI_STATE_PLACE_DOMINO_PLAYER2_TURN 6
#define UI_STATE_SHOW_INSTRUCTIONS 7
//-----UI_STATES-----// 

//-----StartDominosAssigmentMenuStates-----//
#define ASSIGMENT_MENU_INITIAL          0b0000000000000000
#define ASSIGMENT_MENU_PLAYER1_ASSIGNED 0b0000000000000010
#define ASSIGMENT_MENU_PLAYER2_ASSIGNED 0b0000000000000100
#define ASSIGMENT_MENU_PLAYER1_DISPLAY  0b0000000000001000
#define ASSIGMENT_MENU_PLAYER2_DISPLAY  0b0000000000010000
//-----StartDominosAssigmentMenuStates-----//

typedef int controllerState;

//Essa variável é responsável por divergir o fluxo de input para a funcao de controle específica para cada menu
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
//Gerencia o input do menu principal
void manageMainMenuInput(uiInput _menuInput)
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
        case 4: //Instructions
            displayInstructionsMenu();
            *s_getControllerState() = UI_STATE_SHOW_INSTRUCTIONS;
            break;
        case 5: //Exit Game
            exitGame(); 
            break; 
    }
}

void manageInstructionsExit(uiInput _playerInput)
{
    switch (_playerInput)
    {
    case 1:
        *s_getControllerState() = UI_STATE_MAIN_MENU;
        displayStartingMenu();
        break;
    }
}

//Gerencia o input do menu de selecao de jogadores
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
            displayStartDominosAssigmentMenu(FALSE);
            *s_getControllerState() = UI_STATE_ASSING_STARTING_DOMINOES;
            //determina q tem 2 jogadores
            //Chamar funcao q inicia o jogo contra outro jogdor
            break;
        case 3:
            *s_getControllerState() = UI_STATE_MAIN_MENU;
            displayStartingMenu(); //Go back
            break;
    }
}

//Gerencia o input do menu de atribuição de dominos
void manageStartDominosAssigmentMenuInput(uiInput _menuInput)
{
    static int assigmentMenuState = ASSIGMENT_MENU_INITIAL;
    switch (_menuInput)
    {
        case 1: //Iniciar jogo
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_ASSIGNED) != 0 && //Se os dominós já estiverem sido atribuidos para o jogador 1
               (int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_ASSIGNED) != 0) //E TAMBÉM Se os dominós já estiverem sido atribuidos para o jogador 2
            {
                //Avancar para o inicio do jogo
                displayMainGameUIPlayer1Turn();
                hideAllDominoes();
                *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER1_TURN;                
            }
            else //Se não, falta atribuir dominós para alguem
            {
                displayStartDominosAssigmentMenu(TRUE);                
            }
            
            break;
        case 2: //Atribuir dominós para o jogador 1
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_ASSIGNED) == 0) //Se o jogador 1 não tiver sido atribuido
            {
                assigmentMenuState += ASSIGMENT_MENU_PLAYER1_ASSIGNED; //Armazenar que o jogador 1 ja foi atribuido

                assignPlayerStartingHand(STATE_PLAYER_ONE);
            }
            break;
        case 3: //Atribuir dominós para o jogador 2
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_ASSIGNED) == 0) //Se o jogador 2 não tiver sido atribuido
            {
                assigmentMenuState += ASSIGMENT_MENU_PLAYER2_ASSIGNED; //Armazenar que o jogador 2 ja foi atribuido

                assignPlayerStartingHand(STATE_PLAYER_TWO);
            }
            break;
        case 4: //Show player 1 hand
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) == 0) //Se o jogador 1 estiver não estiver com a mão exposta
            {
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER2_DISPLAY; //Se o jogador 2 estiver com a mão exposta, armazenar que ele vai deixar de ter a mão exposta
                assigmentMenuState += ASSIGMENT_MENU_PLAYER1_DISPLAY; //Armazenar que o jogador 1 tem a mão exposta

                hideAllDominoes();
                displayPlayerHand(STATE_PLAYER_ONE);
            }
            break;
        case 5: //Show player 2 hand
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_DISPLAY) == 0) //Se o jogador 2 estiver não estiver com a mão exposta
            {
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER1_DISPLAY; //Se o jogador 1 estiver com a mão exposta, armazenar que ele vai deixar de ter a mão exposta
                assigmentMenuState += ASSIGMENT_MENU_PLAYER2_DISPLAY; //Armazenar que o jogador 2 tem a mão exposta

                hideAllDominoes();
                displayPlayerHand(STATE_PLAYER_TWO);                
            }
            break;
        case 6: //Hide all dominoes
            if((int)(assigmentMenuState & (ASSIGMENT_MENU_PLAYER2_DISPLAY + ASSIGMENT_MENU_PLAYER1_DISPLAY)) != 0) //Se algum dos jogadores estiver com a mão exposta
            {
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER2_DISPLAY; //se o jogador 2 estiver com a mão exposta
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER1_DISPLAY; //se o jogador 1 estiver com a mão exposta
                hideAllDominoes();
            }
            break;
        case 7: //Go back
            *s_getControllerState() = UI_STATE_SELECT_PLAYERS;
            assigmentMenuState = ASSIGMENT_MENU_INITIAL;
            resetDominoesState();
            hideAllDominoes();
            displayPlayerSelectionMenu();
            break;
    }
}

//Gerencia o input do menu de gameplay do jogador 1
void manageMainGameUIPlayer1Turn(uiInput _menuInput)
{
    switch (_menuInput)
    {
        case 1: //Mostra mão do jogador 1
            displayPlayerHand(STATE_PLAYER_ONE);
            break;
        case 2: //Esconde mão do jogador 1
            hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_PLAYER_ONE);
            break;
        case 3: //Pega 1 dominó da pilha de dominós
            pickDominoeFromPile(STATE_PLAYER_ONE);
            displayPlayerHand(STATE_PLAYER_ONE);
            break;
        case 4: 
            *s_getControllerState() = UI_STATE_PLACE_DOMINO_PLAYER1_TURN;
            displayPlaceDominoUIPlayer1Turn();
            changePlayerSelectedDomino(STATE_PLAYER_ONE);
            break;
        case 5: //volta
            *s_getControllerState() = UI_STATE_MAIN_MENU;
            hideAllDominoes();
            resetDominoesState();
            displayStartingMenu();
            break;
    }
}

//Gerencia o input do menu de gameplay do jogador 2
void manageMainGameUIPlayer2Turn(uiInput _menuInput)
{
    switch (_menuInput)
    {
        case 1: //Mostra mão do jogador 2
            displayPlayerHand(STATE_PLAYER_TWO);
            break;
        case 2: //Esconde mão do jogador 2
            hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_PLAYER_TWO);
            break;
        case 3: //Pega 2 dominó da pilha de dominós
            pickDominoeFromPile(STATE_PLAYER_TWO);
            displayPlayerHand(STATE_PLAYER_TWO);
            break;
        case 4: //entra na ui de posicionamento de dominos
            *s_getControllerState() = UI_STATE_PLACE_DOMINO_PLAYER2_TURN;
            displayPlaceDominoUIPlayer2Turn();
            changePlayerSelectedDomino(STATE_PLAYER_TWO);
            break;
        case 5: //Volta ao menu principal
            *s_getControllerState() = UI_STATE_MAIN_MENU;
            hideAllDominoes();
            resetDominoesState();
            displayStartingMenu();
            break;
    }
}

//Gerencia o input do menu de posicionamento de dominos do jogador 1
void managePlaceDominoUIPlayer1Turn(uiInput _menuInput)
{
    switch (_menuInput)
    {
        case 1: //Confirma a posicao do domino e passa o turno para o jogador 2
            if(tryToSetSelectedDominoToTable())
            {
                *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER2_TURN;
                hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_PLAYER_ONE);
                displayMainGameUIPlayer2Turn();
            }
            printf("end if\n");
            break;
        case 2: //Seleciona outro domino
            changePlayerSelectedDomino(STATE_PLAYER_ONE);
            break;
        case 3: //Move o domino selecionado para cima
            movePlayerDomino();
            break;
        case 4: //Rotaciona domino
            rotatePlayerDomino();
            break;
        case 5: //Volta para o menu anterior
            *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER1_TURN;
            hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING);
            displayMainGameUIPlayer1Turn();
            unselectPlayerDomino(STATE_PLAYER_ONE);
            break;
    }

}

//Gerencia o input do menu de posicionamento de dominos do jogador 2
void managePlaceDominoUIPlayer2Turn(uiInput _menuInput)
{
    switch (_menuInput)
    {
        case 1: //Confirma a posicao do domino
            if(tryToSetSelectedDominoToTable())
            {
                *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER1_TURN;
                hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_PLAYER_TWO);
                displayMainGameUIPlayer1Turn();
            }
            break;
        case 2: //Seleciona outro domino
            changePlayerSelectedDomino(STATE_PLAYER_TWO);
            break;
        case 3: //Move o domino selecionado para cima
            movePlayerDomino();
            break;
        case 4: //Rotaciona domino
            rotatePlayerDomino();
            break;
        case 5: //Volta para o menu anterior
            *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER2_TURN;
            hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING);
            displayMainGameUIPlayer2Turn();
            unselectPlayerDomino(STATE_PLAYER_TWO);
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

//Direciona o input do jogador para a funcao de gerenciamento de input adequada
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
        case UI_STATE_MAIN_GAME_PLAYER1_TURN:
            manageMainGameUIPlayer1Turn(_playerInput);
            break;
        case UI_STATE_MAIN_GAME_PLAYER2_TURN:
            manageMainGameUIPlayer2Turn(_playerInput);
            break;
        case UI_STATE_PLACE_DOMINO_PLAYER1_TURN:
            managePlaceDominoUIPlayer1Turn(_playerInput);
            break;
        case UI_STATE_PLACE_DOMINO_PLAYER2_TURN:
            managePlaceDominoUIPlayer2Turn(_playerInput);
            break;
        case UI_STATE_SHOW_INSTRUCTIONS:
            manageInstructionsExit(_playerInput);
            break;
    }    
}
//inicializa o controller
//Inicializa o OpenGL
int startGame()
{
    controllerInitialization();
    return screenDisplay();
}