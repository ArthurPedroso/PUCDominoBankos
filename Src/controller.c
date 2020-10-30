#include "controller.h"
#include "model.h"
#include "view.h"
#include "common.h"
#include <stdio.h>

//-----UI_STATES-----// 
#define UI_STATE_MAIN_MENU 0
#define UI_STATE_SELECT_PLAYERS 1
#define UI_STATE_ASSING_STARTING_DOMINOES 2
#define UI_STATE_MAIN_GAME_PLAYER1_TURN 3
#define UI_STATE_MAIN_GAME_PLAYER2_TURN 4
#define UI_STATE_PLACE_DOMINO_PLAYER1_TURN 5
#define UI_STATE_PLACE_DOMINO_PLAYER2_TURN 6
#define UI_STATE_SHOW_INSTRUCTIONS 7
#define UI_STATE_ASK_FOR_DRAW_PLAYER1 8
#define UI_STATE_ASK_FOR_DRAW_PLAYER2 9
#define UI_STATE_PLAYER_1_WIN 10
#define UI_STATE_PLAYER_2_WIN 11
#define UI_STATE_ASSING_STARTING_DOMINOES_1PLAYER 12
#define UI_STATE_AI_GAME_PLAYER1_TURN 13
#define UI_STATE_AI_PLACE_DOMINO_PLAYER1_TURN 14
#define UI_STATE_AI_PLAYER_DRAW 15
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
    int controllerLoadedState = 0;
    switch(_menuInput)
    {
        case 1: //New Game
            displayPlayerSelectionMenu();
            *s_getControllerState() = UI_STATE_SELECT_PLAYERS;
            break;
        case 2: //Load Game
            controllerLoadedState = readGameSave();

            if(controllerLoadedState != -1)
            {
                *s_getControllerState() = controllerLoadedState;
                
                if(*s_getControllerState() == UI_STATE_AI_GAME_PLAYER1_TURN || *s_getControllerState() == UI_STATE_MAIN_GAME_PLAYER1_TURN)
                    displayMainGameUIPlayer1Turn();
                else
                    displayMainGameUIPlayer2Turn();            
                hideAllDominoes();    
                printDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE, (Vec2){0.0f, 0.0f});
            }
            break;
        case 3: //Instructions
            displayInstructionsMenu();
            *s_getControllerState() = UI_STATE_SHOW_INSTRUCTIONS;
            break;
        case 4: //Exit Game
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
        resetOGLTextPosition();
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
            displayStartDominosAssigmentMenu1Player(FALSE);
            *s_getControllerState() = UI_STATE_ASSING_STARTING_DOMINOES_1PLAYER;
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
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) == 0) //Se o jogador 1 não estiver com a mão exposta
            {
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER2_DISPLAY; //Se o jogador 2 estiver com a mão exposta, armazenar que ele vai deixar de ter a mão exposta
                if ((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_ASSIGNED) != 0) assigmentMenuState += ASSIGMENT_MENU_PLAYER1_DISPLAY; //Armazenar que o jogador 1 tem a mão exposta

                hideAllDominoes();
                displayPlayerHand(STATE_PLAYER_ONE);
            }
            break;
        case 5: //Show player 2 hand
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_DISPLAY) == 0) //Se o jogador 2 não estiver com a mão exposta
            {
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER1_DISPLAY; //Se o jogador 1 estiver com a mão exposta, armazenar que ele vai deixar de ter a mão exposta
                if ((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER2_ASSIGNED) != 0) assigmentMenuState += ASSIGMENT_MENU_PLAYER2_DISPLAY; //Armazenar que o jogador 2 tem a mão exposta

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

//gerencia a escolha do menu de empate
void manageDrawChoice(uiInput _playerInput, int _UI_STATE_MAIN_GAME_PLAYER_TURN)
{
    switch (_playerInput)
    {
    case 1:
        *s_getControllerState() = UI_STATE_MAIN_MENU;
        resetDominoesState();
        hideAllDominoes();
        displayStartingMenu();
        break;
    case 2:
        *s_getControllerState() = _UI_STATE_MAIN_GAME_PLAYER_TURN;
        if(_UI_STATE_MAIN_GAME_PLAYER_TURN == 1)
        {
            hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_PLAYER_ONE);
            *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER2_TURN;
            displayMainGameUIPlayer2Turn();
            
        }
        else if(_UI_STATE_MAIN_GAME_PLAYER_TURN == 2)
        {
            hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_PLAYER_TWO);
            *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER1_TURN;
            displayMainGameUIPlayer1Turn();
        }
        else
        {
            *s_getControllerState() = UI_STATE_MAIN_MENU;
            resetDominoesState();
            hideAllDominoes();
            displayStartingMenu();
        }
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
        case 5:
            displayAskForDrawScreen();
            *s_getControllerState() = UI_STATE_ASK_FOR_DRAW_PLAYER1;
            break;
        case 6: //volta
            *s_getControllerState() = UI_STATE_MAIN_MENU;
            hideAllDominoes();
            resetDominoesState();
            displayStartingMenu();
            break;
        case 7:
            writeGameSave((*s_getControllerState()));
            break;
        case 12: //move todos os dominos para a esquerda
            moveAllDominoes(MOVE_DOMINOS_LEFT);
            break;            
        case 13: //move todos os dominos para a direita
            moveAllDominoes(MOVE_DOMINOS_RIGHT);
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
        case 5:
            displayAskForDrawScreen();
            *s_getControllerState() = UI_STATE_ASK_FOR_DRAW_PLAYER2;
            break;
        case 6: //volta
            *s_getControllerState() = UI_STATE_MAIN_MENU;
            hideAllDominoes();
            resetDominoesState();
            displayStartingMenu();
            break;        
        case 7:
            writeGameSave((*s_getControllerState()));
            break;
        case 12: //move todos os dominos para a esquerda
            moveAllDominoes(MOVE_DOMINOS_LEFT);
            break;            
        case 13: //move todos os dominos para a direita
            moveAllDominoes(MOVE_DOMINOS_RIGHT);
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
                if(checkIfPlayerWon(STATE_PLAYER_ONE))
                {
                    *s_getControllerState() = UI_STATE_PLAYER_1_WIN;
                    hideAllDominoes();
                    displayPlayer1Victory();
                }
                else
                {                
                    *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER2_TURN;
                    hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_PLAYER_ONE);
                    displayMainGameUIPlayer2Turn();
                }
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
                if(checkIfPlayerWon(STATE_PLAYER_TWO))
                {
                    *s_getControllerState() = UI_STATE_PLAYER_2_WIN;
                    hideAllDominoes();
                    displayPlayer2Victory();
                }
                else
                {                
                    *s_getControllerState() = UI_STATE_MAIN_GAME_PLAYER1_TURN;
                    hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_PLAYER_TWO);
                    displayMainGameUIPlayer2Turn();
                }
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

//-----IA-----//
void manageStartDominosAssigment1Player(uiInput _menuInput)
{    
    static int assigmentMenuState = ASSIGMENT_MENU_INITIAL;
    switch (_menuInput)
    {
        case 1: //Iniciar jogo
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_ASSIGNED) != 0) //Se os dominós já estiverem sido atribuidos para o jogador 1
            {
                assignPlayerStartingHand(STATE_PLAYER_TWO);
                //Avancar para o inicio do jogo
                displayMainGameUIPlayer1Turn();
                hideAllDominoes();
                *s_getControllerState() = UI_STATE_AI_GAME_PLAYER1_TURN;                
            }
            else //Se não, falta atribuir dominós para alguem
            {
                displayStartDominosAssigmentMenu1Player(TRUE);                
            }
            break;
        case 2: //Atribuir dominós para o jogador 1
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_ASSIGNED) == 0) //Se o jogador 1 não tiver sido atribuido
            {
                assigmentMenuState += ASSIGMENT_MENU_PLAYER1_ASSIGNED; //Armazenar que o jogador 1 ja foi atribuido

                assignPlayerStartingHand(STATE_PLAYER_ONE);
            }
            break;
        case 3: //Show player 1 hand
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) == 0) //Se o jogador 1 não estiver com a mão exposta
            {
                assigmentMenuState += ASSIGMENT_MENU_PLAYER1_DISPLAY; //Armazenar que o jogador 1 tem a mão exposta

                hideAllDominoes();
                displayPlayerHand(STATE_PLAYER_ONE);
            }
            break;
        case 4: //Hide all dominoes
            if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) != 0) //Se algum dos jogadores estiver com a mão exposta
            {
                if((int)(assigmentMenuState & ASSIGMENT_MENU_PLAYER1_DISPLAY) != 0) assigmentMenuState -= ASSIGMENT_MENU_PLAYER1_DISPLAY; //se o jogador 1 estiver com a mão exposta
                hideAllDominoes();
            }
            break;
        case 5: //Go back
            *s_getControllerState() = UI_STATE_SELECT_PLAYERS;
            assigmentMenuState = ASSIGMENT_MENU_INITIAL;
            resetDominoesState();
            hideAllDominoes();
            displayPlayerSelectionMenu();
            break;
    }
}

void manageAIGameUIPlayer1Turn(uiInput _menuInput)
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
            *s_getControllerState() = UI_STATE_AI_PLACE_DOMINO_PLAYER1_TURN;
            displayPlaceDominoUIPlayer1Turn();
            changePlayerSelectedDomino(STATE_PLAYER_ONE);
            break;            
        case 5:
            displaySinglePlayerDrawScreen();
            hideAllDominoes();
            *s_getControllerState() = UI_STATE_AI_PLAYER_DRAW;
            break;
        case 6: //volta
            *s_getControllerState() = UI_STATE_MAIN_MENU;
            hideAllDominoes();
            resetDominoesState();
            displayStartingMenu();
            break;
        case 7:
            writeGameSave((*s_getControllerState()));
            break;
        case 12: //move todos os dominos para a esquerda
            moveAllDominoes(MOVE_DOMINOS_LEFT);
            break;            
        case 13: //move todos os dominos para a direita
            moveAllDominoes(MOVE_DOMINOS_RIGHT);
            break;
    }
}
void manageSinglePlayerDrawUI(uiInput _menuInput)
{
    switch (_menuInput)
    {
        case 1: //Mostra mão do jogador 1
            exitGame();
            break;
        case 2: //Esconde mão do jogador 1
            displayMainGameUIPlayer1Turn();
            hideAllDominoes();
            printDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_GAME_TABLE, (Vec2){0.0f, 0.0f});
            *s_getControllerState() = UI_STATE_AI_GAME_PLAYER1_TURN;  
            break;
    }
}
//Gerencia o input do menu de posicionamento de dominos do jogador 1
void managePlaceDominoUIAIPlayer1Turn(uiInput _menuInput)
{
    switch (_menuInput)
    {
        case 1: //Confirma a posicao do domino e faz a jogada do jogador 2
            if(tryToSetSelectedDominoToTable())
            {
                if(checkIfPlayerWon(STATE_PLAYER_ONE))
                {
                    *s_getControllerState() = UI_STATE_PLAYER_1_WIN;
                    hideAllDominoes();
                    displayPlayer1Victory();
                }
                else
                {                
                    if(playAiTurn())
                    {
                        *s_getControllerState() = UI_STATE_PLAYER_1_WIN; //esse controlador consegue controlar esse estado
                        hideAllDominoes();
                        displayAIDraw();
                    }
                    else if(checkIfPlayerWon(STATE_PLAYER_TWO))
                    {
                        *s_getControllerState() = UI_STATE_PLAYER_2_WIN;
                        hideAllDominoes();
                        displayPlayer2Victory();
                    }
                    else
                    {
                        displayMainGameUIPlayer1Turn();
                        *s_getControllerState() = UI_STATE_AI_GAME_PLAYER1_TURN;    
                    }
                }
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
            *s_getControllerState() = UI_STATE_AI_GAME_PLAYER1_TURN;
            hideDominoesBasedOnState(s_getGameDominoes(), GAME_DOMINOES_AMOUNT, STATE_GAME_MOVING);
            displayMainGameUIPlayer1Turn();
            unselectPlayerDomino(STATE_PLAYER_ONE);
            break;
    }
}
//-----IA-----//

//Gerencia Vitoria jogador 1
void managePlayer1VicoryUI(uiInput _menuInput)
{
    if(_menuInput == 1)
    {
        exitGame();
    }
}

//Gerencia Vitoria jogador 2
void managePlayer2VicoryUI(uiInput _menuInput)
{
    if(_menuInput == 1)
    {
        exitGame();
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
        case UI_STATE_ASK_FOR_DRAW_PLAYER1:
            manageDrawChoice(_playerInput, 1);
            break;
        case UI_STATE_ASK_FOR_DRAW_PLAYER2:
            manageDrawChoice(_playerInput, 2);
            break;
        case UI_STATE_PLAYER_1_WIN:
            managePlayer1VicoryUI(_playerInput);
            break;
        case UI_STATE_PLAYER_2_WIN:
            managePlayer2VicoryUI(_playerInput);
            break;
        //-----AI-----//
        case UI_STATE_ASSING_STARTING_DOMINOES_1PLAYER:
            manageStartDominosAssigment1Player(_playerInput);
            break;
        case UI_STATE_AI_GAME_PLAYER1_TURN:
            manageAIGameUIPlayer1Turn(_playerInput);
            break;
        case UI_STATE_AI_PLAYER_DRAW:
            manageSinglePlayerDrawUI(_playerInput);
            break;
        case UI_STATE_AI_PLACE_DOMINO_PLAYER1_TURN:
            managePlaceDominoUIAIPlayer1Turn(_playerInput);
            break;
        //-----AI-----//
    }    
}
//inicializa o controller
//Inicializa o OpenGL
int startGame()
{
    controllerInitialization();
    return screenDisplay();
}