#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "common.h"

//-----UI_TEXT-----//
void menuInit();
void displayPlayerSelectionMenu();
void displayStartDominosAssigmentMenu();
//-----UI_TEXT-----//

int screenDisplay();
void hideAllDominoes();
void printDominoes(Domino* _dominoArray, int _arraySize);
void printDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter);
void exitGame();
//Adicionar playerSelection
void invalidOption();
#endif