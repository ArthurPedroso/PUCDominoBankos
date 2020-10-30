#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "common.h"

//-----UI_TEXT-----//
void displayStartingMenu();
void displayPlayerSelectionMenu();
void displayInstructionsMenu();
void displayStartDominosAssigmentMenu(int _cantStartGameWarning);
void displayStartDominosAssigmentMenu1Player(int _cantStartGameWarning);
void displayMainGameUIPlayer1Turn();
void displayMainGameUIPlayer2Turn();
void displayPlaceDominoUIPlayer1Turn();
void displayPlaceDominoUIPlayer2Turn();
void displayAskForDrawScreen();
void displaySinglePlayerDrawScreen();
void displayPlayer1Victory();
void displayPlayer2Victory();
void displayAIDraw();
//-----UI_TEXT-----//
void resetOGLTextPosition();
int screenDisplay();
void hideAllDominoes();
void hideDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter);
void printDominoes(Domino* _dominoArray, int _arraySize);
void printDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter, Vec2 _offset);
void exitGame();
float getDeltaTime();
//Adicionar playerSelection
void invalidOption();
#endif