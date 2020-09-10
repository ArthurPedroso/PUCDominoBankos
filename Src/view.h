#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "common.h"

//-----UI_TEXT-----//
void displayStartingMenu();
void displayPlayerSelectionMenu();
void displayStartDominosAssigmentMenu(int _cantStartGameWarning);
void displayMainGameUIPlayer1Turn();
void displayMainGameUIPlayer2Turn();
//-----UI_TEXT-----//

int screenDisplay();
void hideAllDominoes();
void hideDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter);
void printDominoes(Domino* _dominoArray, int _arraySize);
void printDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter);
void exitGame();
//Adicionar playerSelection
void invalidOption();
#endif